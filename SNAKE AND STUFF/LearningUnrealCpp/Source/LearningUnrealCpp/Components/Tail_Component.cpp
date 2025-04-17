// Fill out your copyright notice in the Description page of Project Settings.


#include "Tail_Component.h"

// Sets default values for this component's properties
UTail_Component::UTail_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh1"));
	Mesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh2"));

	Mesh2->SetupAttachment(Mesh);
}


// Called when the game starts
void UTail_Component::BeginPlay()
{
	Super::BeginPlay();

	CurrentLength = InitialLength;
}


// Called every frame
void UTail_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//move each tail mesh like a train
}

void UTail_Component::AddTail()
{
	CurrentLength += TailIncrement;
	//add new tail to follow
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f,
		FColor::Red, FString::SanitizeFloat(CurrentLength));
}

