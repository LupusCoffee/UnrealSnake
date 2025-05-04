// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTailObj.h"
#include "Components/PointLightComponent.h"

// Sets default values
ABaseTailObj::ABaseTailObj()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TailMesh"));
	
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ABaseTailObj::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseTailObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetOwner())
	{
		this->Destroy();
		return;
	}
	ThisFramePosition = GetOwner()->GetActorLocation();
	Direction = FVector
	(
		ThisFramePosition.X-LastFramePosition.X,
		ThisFramePosition.Y-LastFramePosition.Y,
		ThisFramePosition.Z-LastFramePosition.Z
	);
	Direction = Direction.GetSafeNormal();
	LastFramePosition = GetOwner()->GetActorLocation();
}

FVector ABaseTailObj::GetDirection()
{
	return Direction;
}

