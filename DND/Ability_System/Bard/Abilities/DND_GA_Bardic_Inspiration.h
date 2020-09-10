// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBAProject/DND/Ability_System/Abilities/DND_GA_Target_Buff.h"
#include "DND_GA_Bardic_Inspiration.generated.h"

/**
 * 
 */
UCLASS()
class MOBAPROJECT_API UDND_GA_Bardic_Inspiration : public UDND_GA_Target_Buff
{
	GENERATED_BODY()

public:

	virtual void OnValidTargetData(FGameplayAbilityTargetDataHandle TargetData) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DND_GA_Bardic_Inspiration)
	FGameplayTag GTAttackModifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DND_GA_Bardic_Inspiration)
	TMap<int, int> AbilityLevelAndAttackModifierMap;

	UFUNCTION(BlueprintCallable)
	virtual void OnValidTargetDataBP(FGameplayAbilityTargetDataHandle TargetData, FGameplayEffectSpecHandle SpecHandle);
};
