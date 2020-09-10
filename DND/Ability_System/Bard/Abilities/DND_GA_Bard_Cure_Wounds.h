// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBAProject/DND/Ability_System/Abilities/DND_GA_Base.h"
#include "DND_GA_Bard_Cure_Wounds.generated.h"

/**
 * 
 */
UCLASS()
class MOBAPROJECT_API UDND_GA_Bard_Cure_Wounds : public UDND_GA_Base
{
	GENERATED_BODY()
	
public:

	virtual void OnValidTargetData(FGameplayAbilityTargetDataHandle TargetData) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int, int> AbilityLevelAndAmountToHealMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> GE_CureWounds;
};

