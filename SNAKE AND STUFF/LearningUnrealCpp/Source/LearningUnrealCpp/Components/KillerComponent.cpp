// Fill out your copyright notice in the Description page of Project Settings.


#include "KillerComponent.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "LearningUnrealCpp/Interfaces/KillableInterface.h"
#include "LearningUnrealCpp/Items/RollaBallItemBase.h"

// Sets default values for this component's properties
UKillerComponent::UKillerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	BoxTrigger = CreateDefaultSubobject<UBoxComponent>("BoxTrigger");
	CapsuleTrigger = CreateDefaultSubobject<UCapsuleComponent>("CapsuleTrigger");
}

void UKillerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (BoxTrigger) BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &UKillerComponent::OnTriggerBeginOverlap);
	if (CapsuleTrigger) CapsuleTrigger->OnComponentBeginOverlap.AddDynamic(this, &UKillerComponent::OnTriggerBeginOverlap);
}

// Called every frame
void UKillerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (BoxTrigger)
	{
		BoxTrigger->SetWorldLocation(GetOwner()->GetActorLocation());
		BoxTrigger->SetWorldRotation(GetOwner()->GetActorRotation());
	}
	if (CapsuleTrigger)
	{
		CapsuleTrigger->SetWorldLocation(GetOwner()->GetActorLocation());
		CapsuleTrigger->SetWorldRotation(GetOwner()->GetActorRotation());
	}
}


void UKillerComponent::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UKillableInterface>())
		IKillableInterface::Execute_Kill(OtherActor);
}

