// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API ICombatInterface
{
	GENERATED_BODY()

public:
	virtual int32 GetCharacterLevel() const;
	
	virtual FVector GetCombatSocketLocation() const;
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateWarpTarget(const FVector& TargetLocation);
};
