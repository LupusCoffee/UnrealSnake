// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Tail_Component.generated.h"


UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEARNINGUNREALCPP_API UTail_Component : public UActorComponent
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this component's properties
	UTail_Component();

	UFUNCTION() void AddTail();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Mesh2;
	
	// VARIABLES //
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int InitialLength = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TailIncrement = 1;

	UPROPERTY(BlueprintReadOnly)
	int CurrentLength = 0;
};
