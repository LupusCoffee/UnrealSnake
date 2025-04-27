// Fill out your copyright notice in the Description page of Project Settings.


#include "Tail_Component.h"
#include "BaseTailObj.h"

// Sets default values for this component's properties
UTail_Component::UTail_Component(): ThisFrameOwnerPosition(FVector::ZeroVector), LastFrameOwnerPosition(FVector::ZeroVector)
{
	PrimaryComponentTick.bCanEverTick = true;
	TailSpawnLocation = CreateDefaultSubobject<USceneComponent>("TailSpawnLocation");
}

// Called when the game starts
void UTail_Component::BeginPlay()
{
	Super::BeginPlay();
	
	for (int i = 0; i < InitialLength; ++i) AddTail();
}


// Called every frame
void UTail_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//calculate owner direction
	ThisFrameOwnerPosition = GetOwner()->GetActorLocation();
	OwnerDirection = FVector
	(
		ThisFrameOwnerPosition.X-LastFrameOwnerPosition.X,
		ThisFrameOwnerPosition.Y-LastFrameOwnerPosition.Y,
		ThisFrameOwnerPosition.Z-LastFrameOwnerPosition.Z
	);
	OwnerDirection = OwnerDirection.GetSafeNormal();
	LastFrameOwnerPosition = GetOwner()->GetActorLocation();
	
	//move tail
	//first tail object
	if (TailObjects.Num() > 0)
	{
		//TODO: properly understand what VInterpTo actually does
		TailObjects[0]->SetActorLocation(FMath::VInterpTo(
			TailObjects[0]->GetActorLocation(),
			ThisFrameOwnerPosition - OwnerDirection*HeadObjectPadding,
			DeltaTime, TailSpeed));
	}
	//other tail objects
	for (int i = 1; i < TailObjects.Num(); i++)
	{
		TailObjects[i]->SetActorLocation(FMath::VInterpTo(
			TailObjects[i]->GetActorLocation(),
			TailObjects[i-1]->GetActorLocation() - TailObjects[i-1]->GetDirection()*TailObjectPadding,
			DeltaTime, TailSpeed));
	}

	//Move tail spawn point
	TailSpawnLocation->SetWorldLocation(FVector(GetOwner()->GetActorLocation().X, GetOwner()->GetActorLocation().Y, SpawnHeightAbovePlayer));
}

int UTail_Component::GetTailLength()
{
	return CurrentLength;
}

int UTail_Component::GetTailIncrement()
{
	return TailIncrement;
}

void UTail_Component::AddTail()
{
	if (!TailActorToSpawn)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
			"TailActorToSpawn is null. You probably didn't add an object to spawn as a tail object");
		return;
	}
	
	//add new tail to follow
	CurrentLength += TailIncrement;
	for (int i = 0; i < TailIncrement; ++i)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = GetOwner();
		SpawnParameters.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		ABaseTailObj* NewTailObj = GetWorld()->SpawnActor<ABaseTailObj>
		(
			TailActorToSpawn,
			TailSpawnLocation->GetComponentLocation(),
			FRotator::ZeroRotator,
			SpawnParameters	
		);
		
		TailObjects.Add(NewTailObj);
	}
}

