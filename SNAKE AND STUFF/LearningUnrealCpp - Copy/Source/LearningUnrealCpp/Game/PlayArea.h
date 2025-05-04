// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayArea.generated.h"

UCLASS()
class LEARNINGUNREALCPP_API APlayArea : public AActor
{
	GENERATED_BODY()

public:
	APlayArea();
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Plane;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generation")
	FString LevelFile;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generation")
	TSubclassOf<AActor> ObjectA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generation")
	int ALength = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generation")
	TSubclassOf<AActor> ObjectB;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generation")
	int BLength = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generation")
	TSubclassOf<AActor> ObjectC;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generation")
	int CLength = 3;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generation") int TileSizeX = 5000;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generation") int TileSizeY = 5000;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generation") int TileSizeZ = 5000;
	
protected:
	UFUNCTION() void CreateWorld(FString WorldFile);
	UFUNCTION() void SpawnObject(TSubclassOf<AActor> ObjectToSpawn, int X, int Y, int Z, int RotationYaw = 0);
};
