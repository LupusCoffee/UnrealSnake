// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OutroGameMode.generated.h"

/**
 * 
 */
UCLASS()
class LEARNINGUNREALCPP_API AOutroGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	
};
