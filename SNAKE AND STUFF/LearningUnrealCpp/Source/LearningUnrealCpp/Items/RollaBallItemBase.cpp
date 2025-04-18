// Fill out your copyright notice in the Description page of Project Settings.


#include "RollaBallItemBase.h"

#include "Components/BoxComponent.h"
#include "LearningUnrealCpp/Game/RollaBallPlayer.h"
#include "LearningUnrealCpp/Interfaces/TailInterface.h"

// Sets default values
ARollaBallItemBase::ARollaBallItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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
	
}

//what do i do about this???
void ARollaBallItemBase::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//is there a way to just cast to the component itself?
	//Cause like, making the whole tail interface just for this is really annoying

	if (OtherActor->Implements<UTailInterface>())
	{
		ITailInterface::Execute_GetTailComponent(OtherActor)->AddTail();
	}
}

