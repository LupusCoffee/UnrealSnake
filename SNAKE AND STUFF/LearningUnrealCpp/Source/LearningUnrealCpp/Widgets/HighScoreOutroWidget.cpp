// Fill out your copyright notice in the Description page of Project Settings.


#include "HighScoreOutroWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UHighScoreOutroWidget::SetHighScore(int score)
{
	if (ScoreText)
		ScoreText->SetText(FText::FromString(FString::FromInt(score)));
}

void UHighScoreOutroWidget::SetWinningPlayer(FString name)
{
	if (WinningPlayerNameText)
		WinningPlayerNameText->SetText(FText::FromString(name));
}
