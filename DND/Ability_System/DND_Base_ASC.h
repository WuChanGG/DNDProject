// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DND_Base_ASC.generated.h"

/**
 * 
 */
UCLASS()
class MOBAPROJECT_API UDND_Base_ASC : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	// Warning, the context created this way may be bad
	void MakeAndApplyGameplayEffectSpecToSelf(TSubclassOf<UGameplayEffect> InEffect, float EffectLevel = 1.0f, FGameplayEffectContextHandle EffectContext = FGameplayEffectContextHandle());
};
