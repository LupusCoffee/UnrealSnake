// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/Pawn.h"
#include "LearningUnrealCpp/Components/Tail_Component.h"
#include "LearningUnrealCpp/Interfaces/TailInterface.h"
#include "RollaBallPlayer.generated.h"

// Forward declarations
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UBaseMovementDataConfig;

UCLASS()
class LEARNINGUNREALCPP_API ARollaBallPlayer : public APawn, public ITailInterface
{
	GENERATED_BODY()


public:
	// Sets default values for this pawn's properties
	ARollaBallPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	//Definite Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArm2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* Camera;

	//Added Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTail_Component* TailComponent;

	// VARIABLES //
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveForce = 5000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float JumpForce = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxJumpCount = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GravityForce = 3000.0f;

	// INPUTS //
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	UInputMappingContext* InputMapping;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	UBaseMovementDataConfig* InputActions;

	
public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// FUNCTIONS //
	//Inputs
	UFUNCTION() void RotateCamera(const FInputActionValue& Value);
	UFUNCTION() void MoveRight(const FInputActionValue& Value);
	UFUNCTION() void MoveForward(const FInputActionValue& Value);
	UFUNCTION() void Jump();

	//Others
	UFUNCTION() void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		FVector NormalImpulse, const FHitResult& Hit);

	int32 JumpCount = 0;

	
public:
	virtual UTail_Component* GetTailComponent_Implementation() override;
};
