// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HighScoreOutroWidget.generated.h"

class UTextBlock;

UCLASS()
class LEARNINGUNREALCPP_API UHighScoreOutroWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable) void SetHighScore(int score);
	UFUNCTION(BlueprintCallable) void SetWinningPlayer(FString name);
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ScoreText;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* WinningPlayerNameText;
};
