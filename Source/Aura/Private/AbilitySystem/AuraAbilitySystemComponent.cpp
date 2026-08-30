// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::OnAbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::OnEffectApplied);
}

void UAuraAbilitySystemComponent::OnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                  const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer AssetTagsContainer;
	EffectSpec.GetAllAssetTags(AssetTagsContainer);
	for (const FGameplayTag& Tag : AssetTagsContainer)
	{
		// TODO: Broadcast these tags to the Widget Controller.	
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Green, 
		                                 FString::Printf(TEXT("Effect Applied with asset tag : %s"), *Tag.ToString()));
	}
}
