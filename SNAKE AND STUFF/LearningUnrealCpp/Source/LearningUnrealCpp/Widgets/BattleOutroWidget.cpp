// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleOutroWidget.h"

#include "Components/TextBlock.h"

void UBattleOutroWidget::SetWinningPlayer(FString name)
{
	if (WinningPlayerNameText)
		WinningPlayerNameText->SetText(FText::FromString(name));
}
