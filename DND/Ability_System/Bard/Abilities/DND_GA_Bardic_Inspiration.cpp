// Fill out your copyright notice in the Description page of Project Settings.


#include "DND_GA_Bardic_Inspiration.h"
#include "AbilitySystemBlueprintLibrary.h"

void UDND_GA_Bardic_Inspiration::OnValidTargetData(FGameplayAbilityTargetDataHandle TargetData)
{
	if (!UAbilitySystemBlueprintLibrary::TargetDataHasActor(TargetData, 0))
	{
		checkNoEntry();
		return;
	}

	TArray<AActor *> ActorArray = UAbilitySystemBlueprintLibrary::GetActorsFromTargetData(TargetData, 0);
	for (AActor* SingleActor : ActorArray)
	{
		if (IsTargetActorFriendly(SingleActor) && bIsFriendlyAbility)
		{
			FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(GE_Buff->GetClass(), GetAbilityLevel());
			int AttackModifier = *AbilityLevelAndAttackModifierMap.Find((int)GetAbilityLevel());
			SpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(GTAttackModifier.GetTagName()), AttackModifier);
			FGameplayAbilityTargetData_ActorArray *ActorArrayTargetData = new FGameplayAbilityTargetData_ActorArray();
			TArray<TWeakObjectPtr<AActor>> TempActorArray;
			TempActorArray.Add(SingleActor);
			ActorArrayTargetData->SetActors(TempActorArray);
			FGameplayAbilityTargetDataHandle DataHandle(ActorArrayTargetData);
			ApplyGameplayEffectSpecToTarget(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), SpecHandle, DataHandle);
			// TODO: UI Indicate buffs
		}
	}
}

void UDND_GA_Bardic_Inspiration::OnValidTargetDataBP(FGameplayAbilityTargetDataHandle TargetData, FGameplayEffectSpecHandle SpecHandle)
{

	if (!UAbilitySystemBlueprintLibrary::TargetDataHasActor(TargetData, 0))
	{
		checkNoEntry();
		return;
	}

	TArray<AActor *> ActorArray = UAbilitySystemBlueprintLibrary::GetActorsFromTargetData(TargetData, 0);
	for (AActor* SingleActor : ActorArray)
	{
		if (IsTargetActorFriendly(SingleActor) && bIsFriendlyAbility)
		{
			FGameplayAbilityTargetData_ActorArray *ActorArrayTargetData = new FGameplayAbilityTargetData_ActorArray();
			TArray<TWeakObjectPtr<AActor>> TempActorArray;
			TempActorArray.Add(SingleActor);
			ActorArrayTargetData->SetActors(TempActorArray);
			FGameplayAbilityTargetDataHandle DataHandle(ActorArrayTargetData);
			ApplyGameplayEffectSpecToTarget(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), SpecHandle, DataHandle);
			// TODO: UI Indicate buffs
		}
	}
}

