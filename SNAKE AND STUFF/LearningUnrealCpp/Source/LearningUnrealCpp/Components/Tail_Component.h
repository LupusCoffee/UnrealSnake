// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseTailObj.h"
#include "Tail_Component.generated.h"

class ARollaBallPlayer;

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEARNINGUNREALCPP_API UTail_Component : public UActorComponent
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this component's properties
	UTail_Component();
	
	UFUNCTION() virtual void AddTail();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* TailSpawnLocation;
	
	//Initial Variables
	UPROPERTY(EditDefaultsOnly,					   Category = "Tail Adding")
	int SpawnHeightAbovePlayer = 200;
	UPROPERTY(EditDefaultsOnly,					   Category = "Tail Adding")
	TSubclassOf<ABaseTailObj> TailActorToSpawn;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tail Adding")
	int InitialLength = 3;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tail Adding")
	int TailIncrement = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tail Behaviour")
	float HeadObjectPadding = 5.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tail Behaviour")
	float TailObjectPadding = 5.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tail Behaviour")
	float TailSpeed = 0.5f;

	//Continous Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CurrentLength = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<ABaseTailObj*> TailObjects;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector OwnerDirection = FVector(0, 0, 0);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector ThisFrameOwnerPosition;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector LastFrameOwnerPosition;

public:
	int GetTailLength();
	int GetTailIncrement();
};
