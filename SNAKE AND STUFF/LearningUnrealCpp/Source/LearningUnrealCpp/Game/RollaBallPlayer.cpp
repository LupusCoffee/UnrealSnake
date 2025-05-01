// Fill out your copyright notice in the Description page of Project Settings.

#include "RollaBallPlayer.h"
#include "Input/BaseMovementDataConfig.h"
#include "PlayerStateBase.h"
#include "BattleMode/BattleGameState.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/PointLightComponent.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "HighScoreMode/HighScorePlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "LearningUnrealCpp/Components/PlayerTailComponent.h"

// Sets default values
ARollaBallPlayer::ARollaBallPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Create Components
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	CameraScene = CreateDefaultSubobject<USceneComponent>("CameraScene");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm2 = CreateDefaultSubobject<USpringArmComponent>("SpringArm2");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	VisualScene = CreateDefaultSubobject<USceneComponent>("VisualScene");
	Light = CreateDefaultSubobject<UPointLightComponent>("Light!");
	//TailComponent = CreateDefaultSubobject<UPlayerTailComponent>(TEXT("TailComponent")); //WTFFFFFFFFFFFFFFFFFFFFFFFF
	UActorComponent* Bruh = GetComponentByClass(UPlayerTailComponent::StaticClass());
	if (Bruh) TailComponent = Cast<UPlayerTailComponent>(Bruh);
	
	//Set hierarchy
	RootComponent = Mesh;
	CameraScene->SetupAttachment(RootComponent);
	SpringArm->SetupAttachment(CameraScene);
	SpringArm2->SetupAttachment(SpringArm);
	Camera->SetupAttachment(SpringArm2);
	VisualScene->SetupAttachment(RootComponent);
	Light->SetupAttachment(VisualScene);
	
	//Set physics to true as a default (since it's in the constructor)
	Mesh->SetSimulatePhysics(true);
	
	//Bindings
	//Dynamic Delegate Binding between mesh's "OnComponentHit" function and RollaBallPlayer's "OnHit" function
	Mesh->OnComponentHit.AddDynamic(this, &ARollaBallPlayer::OnHit);
}

// Called when the game starts or when spawned
void ARollaBallPlayer::BeginPlay()
{
	Super::BeginPlay();

	//Delay getting player state a bit
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ARollaBallPlayer::DelayGettingPlayerState, 1.0, false);	
	
	//so we work with smaller values when setting move and jump force
	MoveForce *= Mesh->GetMass();
	JumpForce *= Mesh->GetMass();
	GravityForce *= Mesh->GetMass();

	//Set random name lol - i'd like to do this through the game mode and game state to prevent duplicates, but got no time
	SetName(PossiblePlayerNames[rand() % PossiblePlayerNames.Num()]);
	//TODO: ACTUALLY. I'd like to skip names all together and just set the color randomly. Again through game mode tho to prevent duplicate colors.

	//Broadcast Player Spawn
	AGameStateBase* GameState = UGameplayStatics::GetGameState(GetWorld());
	if (GameState)
	{
		AHighScoreGameState* HighScoreGameState = Cast<AHighScoreGameState>(GameState);
		if (HighScoreGameState) HighScoreGameState->OnPlayerSpawn.Broadcast(this);

		ABattleGameState* BattleGameState = Cast<ABattleGameState>(GameState);
		if (BattleGameState) BattleGameState->OnPlayerSpawn.Broadcast(this);
	}
}

void ARollaBallPlayer::DelayGettingPlayerState()
{
	//Timer
	if (--RepeatingCallsRemaining <= 0) GetWorldTimerManager().ClearTimer(MemberTimerHandle);
	//stuff we wanna do after timer
	SnakePlayerState = GetPlayerState<APlayerStateBase>();
}

void ARollaBallPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Gravity Push Down
	const FVector Direction = FVector(0,0,-1.0f);
	Mesh->AddForce(Direction * GravityForce);
}

inline void ARollaBallPlayer::RotateCamera(const FInputActionValue& Value)
{
	FVector2D CameraInput = Value.Get<FVector2D>();

	//rotate both spring arms, since the second spring arm doesn't inherit the rotation of their parents
	SpringArm->AddLocalRotation(FRotator(0, CameraInput.X*CameraForce, 0));
	SpringArm2->AddLocalRotation(FRotator(0, CameraInput.X*CameraForce,0)); //camera is its child
}

void ARollaBallPlayer::MoveRight(const FInputActionValue& Value)
{
	float HorizontalInput = Value.Get<float>();

	//the direction we wanna go > right or left of the camera, based on the horizontal input
	const FVector Direction = Camera->GetRightVector() * HorizontalInput; //note: uses camera as mesh is rolling

	//movement force in the correct direction
	const FVector HorizontalForce = Direction * MoveForce;

	//move the MESH in the horizontal direction with a certain force
	Mesh->AddForce(HorizontalForce);
}

void ARollaBallPlayer::MoveForward(const FInputActionValue& Value)
{
	float VerticalInput = Value.Get<float>();

	//the direction we wanna go > forward or back of the camera, based on the vertical input
	const FVector Direction = FVector(Camera->GetForwardVector().X, Camera->GetForwardVector().Y, 0) * VerticalInput; //note: uses camera as mesh is rolling

	//movement force in the correct direction
	const FVector VerticalForce = Direction * MoveForce;

	//move the MESH in the vertical direction with a certain force
	Mesh->AddForce(VerticalForce);

	//TODO: cap velocity at a "MaximumVelocity" + combine MoveForward and MoveRight
	/*if (Mesh->GetComponentVelocity().Size() >= MaximumVelocity)
		Mesh->SetAllPhysicsLinearVelocity(MoveDirection * MaximumVelocity);*/

}

void ARollaBallPlayer::Jump()
{
	if (JumpCount >= MaxJumpCount) return;

	Mesh->AddImpulse(FVector(0, 0, JumpForce));
	//dash jump
	
	JumpCount++;
}


//this function is bound to the mesh's "OnComponentHit" function.
//In other words, this gets called when that function is called and some info is passed through
void ARollaBallPlayer::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	FVector NormalImpulse, const FHitResult& Hit)
{
	//The further below us the hit, the closer to 1 the HitDirection.
	//The further above us the hit, the closer to -1 the HitDirection.
	const float HitDirection = Hit.Normal.Z;
	if (HitDirection > 0) JumpCount = 0;
}

FString ARollaBallPlayer::GetName()
{
	if (PlayerName == "") return FString("None"); 
	return PlayerName;
}

void ARollaBallPlayer::SetName(FString Name)
{
	PlayerName = Name;
}

//Interfaces
UTail_Component* ARollaBallPlayer::GetTailComponent_Implementation()
{
	return TailComponent;
}

void ARollaBallPlayer::Kill_Implementation()
{
	//tell player state that i'm dead
	if (SnakePlayerState) SnakePlayerState->SetDeathStatus(true);
}
