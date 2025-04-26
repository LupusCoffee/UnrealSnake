// Fill out your copyright notice in the Description page of Project Settings.


#include "OutroGameMode.h"
#include "SnakeGameInstance.h"

void AOutroGameMode::BeginPlay()
{
	Super::BeginPlay();

	//spawn widget
	//set text in widget

	USnakeGameInstance* GameInstance = GetGameInstance<USnakeGameInstance>();
	if (GameInstance)
	{
		
	}
}
