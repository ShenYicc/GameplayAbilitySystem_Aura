// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraEnemy.h"

AAuraEnemy::AAuraEnemy()
{
	
}

void AAuraEnemy::HighlightActor()
{
	UE_LOG(LogTemp, Warning, TEXT("Highlight : %s"), *GetNameSafe(this));
}

void AAuraEnemy::UnHighlightActor()
{
	UE_LOG(LogTemp, Warning, TEXT("UnHighlight : %s"), *GetNameSafe(this));
}
