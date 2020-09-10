// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "DND_Base_MMC.generated.h"

/**
 * 
 */
UCLASS()
class MOBAPROJECT_API UDND_Base_MMC : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:

	UDND_Base_MMC();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

	FGameplayEffectAttributeCaptureDefinition AttackDiceDef;

	FGameplayEffectAttributeCaptureDefinition ArmorClassDef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DND_Base_MMC)
	FGameplayTag GT_AttackModifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DND_Base_MMC)
	FGameplayTag GT_DamageModifier;

	int GetSourceAttackDiceModifiers(const FGameplayEffectSpec& Spec) const;

	int GetSourceDamageDiceModifiers(const FGameplayEffectSpec& Spec) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DND_Base_MMC)
	TArray<FGameplayTag> AttackModifierTagList;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DND_Base_MMC)
	TArray<FGameplayTag> DamageModifierTagList;

};
