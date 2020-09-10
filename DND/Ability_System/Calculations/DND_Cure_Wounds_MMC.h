// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "DND_Cure_Wounds_MMC.generated.h"

/**
 * 
 */
UCLASS()
class MOBAPROJECT_API UDND_Cure_Wounds_MMC : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
		
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
