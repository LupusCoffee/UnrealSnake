// Fill out your copyright notice in the Description page of Project Settings.


#include "BoostReciever.h"


// Sets default values for this component's properties
UBoostReciever::UBoostReciever(): StaticMesh(nullptr), MoveDirection(FVector(0,0,0)),
								  ThisFrameOwnerPosition(FVector(0,0,0)), LastFrameOwnerPosition(FVector(0,0,0))
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UBoostReciever::BeginPlay()
{
	Super::BeginPlay();

	UActorComponent* ActorComponent = GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass());
	if (ActorComponent) StaticMesh = Cast<UStaticMeshComponent>(ActorComponent);
}

void UBoostReciever::TickComponent(float DeltaTime, enum ELevelTick TickType,
                                   FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!StaticMesh) return;
	
	//is this dumb to do, since we already have calculated this on the tail
	//component that a snake has? hmmmmm. maybe we should check if the owner
	//has an available move direction calculated already?
	//OR maybe we use an interface? idk. this works lol
	
	//Calculate Direction
	ThisFrameOwnerPosition = GetOwner()->GetActorLocation();
	MoveDirection = FVector
	(
		ThisFrameOwnerPosition.X-LastFrameOwnerPosition.X,
		ThisFrameOwnerPosition.Y-LastFrameOwnerPosition.Y,
		ThisFrameOwnerPosition.Z-LastFrameOwnerPosition.Z
	);
	MoveDirection = MoveDirection.GetSafeNormal();
	LastFrameOwnerPosition = GetOwner()->GetActorLocation();
}

void UBoostReciever::Boost(float Force) const
{
	if (StaticMesh) StaticMesh->AddImpulse(MoveDirection * Force);
}

