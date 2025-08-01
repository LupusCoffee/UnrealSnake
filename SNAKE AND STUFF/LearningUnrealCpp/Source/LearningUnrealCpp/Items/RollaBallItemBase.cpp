// Fill out your copyright notice in the Description page of Project Settings.


#include "RollaBallItemBase.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LearningUnrealCpp/Game/RollaBallPlayer.h"
#include "LearningUnrealCpp/Game/BattleMode/BattleGameState.h"
#include "LearningUnrealCpp/Game/HighScoreMode/HighScoreGameState.h"
#include "LearningUnrealCpp/Interfaces/TailInterface.h"

// Sets default values
ARollaBallItemBase::ARollaBallItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	//Create Components
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Pole1 = CreateDefaultSubobject<UStaticMeshComponent>("Pole1");
	Pole2 = CreateDefaultSubobject<UStaticMeshComponent>("Pole2");
	Trigger = CreateDefaultSubobject<UBoxComponent>("Trigger");
	TriggerMesh = CreateDefaultSubobject<UStaticMeshComponent>("TriggerMesh");

	//Set attatchments
	RootComponent = SceneRoot;
	Pole1->SetupAttachment(SceneRoot);
	Pole2->SetupAttachment(SceneRoot);
	Trigger->SetupAttachment(SceneRoot);
	TriggerMesh->SetupAttachment(Trigger);

	//Bindings
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ARollaBallItemBase::OnBoxBeginOverlap);
}

// Called when the game starts or when spawned
void ARollaBallItemBase::BeginPlay()
{
	Super::BeginPlay();

	//set state, delayed
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ARollaBallItemBase::SetGameState, 1.0, false);	
}

void ARollaBallItemBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (CurrentCooldown > 0) CurrentCooldown -= DeltaSeconds;
}

void ARollaBallItemBase::SetGameState()
{
	//Timer
	if (--RepeatingCallsRemaining <= 0) GetWorldTimerManager().ClearTimer(MemberTimerHandle);

	//stuff we wanna do after timer
	if (AGameStateBase* GameStateBase = UGameplayStatics::GetGameState(GetWorld()))
	{
		HighScoreGameState = Cast<AHighScoreGameState>(GameStateBase);
		if (HighScoreGameState) HighScoreGameState->OnGateCreated.Broadcast(this);

		BattleGameState = Cast<ABattleGameState>(GameStateBase);
		if (BattleGameState) BattleGameState->OnGateCreated.Broadcast(this);
	}
}


void ARollaBallItemBase::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (CurrentCooldown > 0) return;
	
	UActorComponent* ComponentActor = OtherActor->GetComponentByClass(UTail_Component::StaticClass());
	if (ComponentActor)
	{
		UTail_Component* TailComponent = Cast<UTail_Component>(ComponentActor);
		if (TailComponent)
		{
			TailComponent->AddTail();
			CurrentCooldown = Cooldown;
			OnTailOverlap();
		}
	}
}

float ARollaBallItemBase::GetCurrentCooldown()
{
	return CurrentCooldown;
}

