// Fill out your copyright notice in the Description page of Project Settings.

#include "RollaBallPlayer.h"

#include <string>

#include "BaseMovementDataConfig.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"

// Sets default values
ARollaBallPlayer::ARollaBallPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//TO-DO: remove them? or perhaps unreal has a garbage collector for it?
	//Create Components
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	//Set the Root Component to be our Mesh
	RootComponent = Mesh;
	//Attach the spring arm to the mesh. SpringArm will now follow the mesh transform (rotation and location).
	SpringArm->SetupAttachment(Mesh);
	//Attach the camera to the spring arm. Camera will now follow the spring arm transform (rotation and location).
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ARollaBallPlayer::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ARollaBallPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PlayerController = Cast<APlayerController>(GetController()); //get player controller + set

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	//BindAction(const UInputAction* Action, ETriggerEvent TriggerEvent, UObject* Object, FName FunctionName)
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	Input->BindAction(InputActions->MoveRight, ETriggerEvent::Started, this, "MoveRight");
	Input->BindAction(InputActions->MoveForward, ETriggerEvent::Started, this, "MoveForward");
	Input->BindAction(InputActions->Jump, ETriggerEvent::Started, this, "Jump");
}

void ARollaBallPlayer::MoveRight(float Value)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("RIGHT"));
}

void ARollaBallPlayer::MoveForward(float Value)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("FORWARD"));
}

void ARollaBallPlayer::Jump()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("JUMP"));
}
