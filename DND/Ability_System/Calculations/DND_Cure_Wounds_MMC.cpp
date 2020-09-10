// Fill out your copyright notice in the Description page of Project Settings.


#include "DND_Cure_Wounds_MMC.h"
#include "MOBAProject/DND/Ability_System/Bard/Abilities/DND_GA_Bard_Cure_Wounds.h"
#include "Kismet/KismetMathLibrary.h"

float UDND_Cure_Wounds_MMC::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const UDND_GA_Bard_Cure_Wounds *CureWoundsGA = Cast<UDND_GA_Bard_Cure_Wounds>(Spec.GetContext().GetAbility());
	if (CureWoundsGA == NULL)
	{
		checkNoEntry();
		return 0.0f;
	}

	// 1d8 for cure wounds
	int HealingDice = 8;
	int NumberOfDiceToRoll = (int)CureWoundsGA->GetAbilityLevel();
	int TotalToHeal = 0;
	for (int i = 0; i < NumberOfDiceToRoll; i = i + 1)
	{
		TotalToHeal = TotalToHeal + UKismetMathLibrary::RandomIntegerInRange(1, HealingDice);
	}

	return TotalToHeal;
}
