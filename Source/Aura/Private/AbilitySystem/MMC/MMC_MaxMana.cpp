// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MMC/MMC_MaxMana.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligenceDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.bSnapshot = false;
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	
	RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluationParams;
	EvaluationParams.SourceTags = SourceTags;
	EvaluationParams.TargetTags = TargetTags;
	
	float Intelligence = 0.f;
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaluationParams, Intelligence);
	Intelligence = FMath::Max<float>(0.f, Intelligence);
	
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetEffectContext().GetSourceObject());
	int32 CharacterLevel = 0;
	if (CombatInterface)
	{
		CharacterLevel = CombatInterface->GetCharacterLevel();
	}
	return 50.f + Intelligence * 2.5f + CharacterLevel * 15.f;
}
