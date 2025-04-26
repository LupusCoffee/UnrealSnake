// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BoostReciever.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LEARNINGUNREALCPP_API UBoostReciever : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBoostReciever();

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector MoveDirection;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector ThisFrameOwnerPosition;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector LastFrameOwnerPosition;

public:
	virtual void BeginPlay() override;
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;
	void Boost(float Force) const;
};
