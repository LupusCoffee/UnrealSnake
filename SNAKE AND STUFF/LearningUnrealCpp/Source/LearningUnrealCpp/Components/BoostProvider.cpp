// Fill out your copyright notice in the Description page of Project Settings.


#include "BoostProvider.h"

#include "BoostReciever.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"


// Sets default values for this component's properties
UBoostProvider::UBoostProvider()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBoostProvider::BeginPlay()
{
	Super::BeginPlay();

	//ugh
	UActorComponent* BoxActorComponent = GetOwner()->GetComponentByClass(UBoxComponent::StaticClass());
	if (BoxActorComponent)
	{
		UBoxComponent* BoxComponent = Cast<UBoxComponent>(BoxActorComponent);
		if (BoxComponent)
		{
			BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &UBoostProvider::OnBeginOverlap);
			return;
		}
	}
	UActorComponent* SphereActorComponent = GetOwner()->GetComponentByClass(USphereComponent::StaticClass());
	if (SphereActorComponent)
	{
		USphereComponent* SphereComponent = Cast<USphereComponent>(BoxActorComponent);
		if (SphereComponent)
		{
			SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &UBoostProvider::OnBeginOverlap);
			return;
		}
	}
	UActorComponent* CapsuleActorComponent = GetOwner()->GetComponentByClass(UCapsuleComponent::StaticClass());
	if (CapsuleActorComponent)
	{
		UCapsuleComponent* CapsuleComponent = Cast<UCapsuleComponent>(BoxActorComponent);
		if (CapsuleComponent) CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &UBoostProvider::OnBeginOverlap);
	}
}

void UBoostProvider::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UActorComponent* ComponentActor = OtherActor->GetComponentByClass(UBoostReciever::StaticClass());
	if (ComponentActor)
	{
		UBoostReciever* BoostReciever = Cast<UBoostReciever>(ComponentActor);
		if (BoostReciever) BoostReciever->Boost(BoostForce);
	}
}

