// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayArea.h"

APlayArea::APlayArea()
{
	PrimaryActorTick.bCanEverTick = false;

	Plane = CreateDefaultSubobject<UStaticMeshComponent>("Plane");
}

void APlayArea::BeginPlay()
{
	Super::BeginPlay();

	CreateWorld(LevelFile);
}

//this is so bad lmao. Should make a struct for letter, length, rotation randomization, and actor to spawn. call it "GenObject"
void APlayArea::CreateWorld(FString WorldFile)
{
	FString FileString = "NONE";
	FString FullFilePath = FPaths::ProjectDir() + "Source/LearningUnrealCpp/Levels/" + WorldFile;
	FFileHelper::LoadFileToString(FileString, *FullFilePath);
	if (FileString == "NONE") return;
	
	int FileX = 0;
	int FileY = 0;
	for (auto Char : FileString)
	{
		if (Char == '.' || Char == '\r') continue;
		
		if (Char == 'A')
		{
			for (int i = 0; i < ALength; ++i)
				SpawnObject(ObjectA, FileX, FileY, i);
		}
		else if (Char == 'B')
		{
			for (int i = 0; i < BLength; ++i)
				SpawnObject(ObjectB, FileX, FileY, i, rand() % 360);
		}
		else if (Char == 'C')
		{
			for (int i = 0; i < CLength; ++i)
				SpawnObject(ObjectC, FileX, FileY, i, rand() % 360);
		}
		else if (Char == '\n')
		{
			FileX = 0;
			FileY++;
			continue;
		}
		
		FileX++;
	}
}

void APlayArea::SpawnObject(TSubclassOf<AActor> ObjectToSpawn, int X, int Y, int Z, int RotationYaw)
{
	if (!ObjectToSpawn) return;
	
	FVector Location(
		Plane->GetComponentLocation().X + X*TileSizeX,
		Plane->GetComponentLocation().Y + Y*TileSizeY,
		Plane->GetComponentLocation().Z + Z*TileSizeZ //+ half of object length?
    );
	FRotator Rotation(0.0f, RotationYaw, 0.0f); //add as part of the function
	
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = GetOwner();
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AActor>
	(
		ObjectToSpawn,
		Location,
		Rotation,
		SpawnInfo
	);
}

