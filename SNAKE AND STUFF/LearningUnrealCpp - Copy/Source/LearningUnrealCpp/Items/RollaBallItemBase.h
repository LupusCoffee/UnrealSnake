// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RollaBallItemBase.generated.h"

class ABattleGameState;
class ABattleGameMode;
class AHighScoreGameState;

UCLASS()
class LEARNINGUNREALCPP_API ARollaBallItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARollaBallItemBase();

public:
	UFUNCTION()
	float GetCurrentCooldown();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	//Definite Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Pole1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Pole2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* Trigger;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* TriggerMesh;

	// VARIABLES
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Cooldown = 15.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CurrentCooldown = 0.0f;
	int RepeatingCallsRemaining;
	FTimerHandle MemberTimerHandle;

	// FUNCTIONS
	UFUNCTION()
	void SetGameState();
	UFUNCTION()
	virtual void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintImplementableEvent)
	void OnTailOverlap();

	//Others
	UPROPERTY()
	AHighScoreGameState* HighScoreGameState;
	UPROPERTY()
	ABattleGameState* BattleGameState;
};
