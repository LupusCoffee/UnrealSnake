// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTailObj.generated.h"

class UPointLightComponent;

UCLASS()
class LEARNINGUNREALCPP_API ABaseTailObj : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseTailObj();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector Direction = FVector(0, 0, 0);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector ThisFramePosition;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector LastFramePosition;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	FVector GetDirection();
};
