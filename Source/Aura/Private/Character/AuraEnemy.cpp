// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraEnemy.h"
#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetRenderCustomDepth(false);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	Weapon->SetRenderCustomDepth(false);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AAuraEnemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);
}

void AAuraEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}
