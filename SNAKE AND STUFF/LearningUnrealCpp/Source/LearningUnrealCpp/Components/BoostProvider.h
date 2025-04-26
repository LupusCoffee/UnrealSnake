// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BoostProvider.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LEARNINGUNREALCPP_API UBoostProvider : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBoostProvider();

protected:
	//Variables
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Boost")
	float BoostForce = 1000.0f;

public:
	virtual void BeginPlay() override;
	
	UFUNCTION() virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
