// Fill out your copyright notice in the Description page of Project Settings.


#include "DND_GA_Bard_Cure_Wounds.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "MobaProject/DND/Ability_System/DND_Base_ASC.h"

void UDND_GA_Bard_Cure_Wounds::OnValidTargetData(FGameplayAbilityTargetDataHandle TargetData)
{
	if (!UAbilitySystemBlueprintLibrary::TargetDataHasActor(TargetData, 0))
	{
		return;
	}

	if (GE_CureWounds == NULL)
	{
		checkNoEntry();
		return;
	}

	UDND_Base_ASC* BaseASC = Cast<UDND_Base_ASC>(GetAbilitySystemComponentFromActorInfo());
	if (BaseASC == NULL)
	{
		return;
	}

	TArray<AActor*> ActorToCure = UAbilitySystemBlueprintLibrary::GetActorsFromTargetData(TargetData, 0);
	TArray<TWeakObjectPtr<AActor>> ActorArrayForTargetData;
	ActorArrayForTargetData.Append(ActorToCure);
	FGameplayAbilityTargetData_ActorArray *ActorArrayTargetData = new FGameplayAbilityTargetData_ActorArray();
	ActorArrayTargetData->SetActors(ActorArrayForTargetData);
	FGameplayAbilityTargetDataHandle TargetDataHandle(ActorArrayTargetData);
	FGameplayEffectSpecHandle CureWoundsSpec = MakeOutgoingGameplayEffectSpec(GE_CureWounds, 1.0);
	ApplyGameplayEffectSpecToTarget(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), CureWoundsSpec, TargetDataHandle);
}
