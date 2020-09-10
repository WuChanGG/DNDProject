// Fill out your copyright notice in the Description page of Project Settings.


#include "DND_GA_Bard_Melee_Attack.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "MOBAProject/DND/Ability_System/DND_Base_ASC.h"

void UDND_GA_Bard_Melee_Attack::OnMeleeAttackEventReceived(FGameplayEventData EventData)
{
	if (EventData.Target == NULL)
	{
		return;
	}

	// WARNING TODO: this could not be safe
	if (IsOverlapedCharacterUnique(const_cast<AActor*>(EventData.Target)))
	{
		MeleeAttackHitActors.Add(const_cast<AActor*>(EventData.Target));
	}
	//MeleeAttackHitActors.Add(EventData.Target);
}

void UDND_GA_Bard_Melee_Attack::FilterMeleeHitActors()
{
	if (MeleeAttackHitActors.Num() <= 0)
	{
		return;
	}

	TArray<AActor*> FilteredArray;
	for (AActor* SingleActor : MeleeAttackHitActors)
	{
		// Is friendly?
		if (!IsTargetActorFriendly(SingleActor) && SingleActor != GetAvatarActorFromActorInfo())
		{
			FilteredArray.Add(SingleActor);
		}
	}

	MeleeAttackHitActors.Empty();
	MeleeAttackHitActors.Append(FilteredArray);
}

void UDND_GA_Bard_Melee_Attack::DamageMeleeHitActors()
{
	if (MeleeAttackHitActors.Num() <= 0)
	{
		return;
	}

	for (AActor* SingleHitActor : MeleeAttackHitActors) 
	{
		UDND_Base_ASC* HitActorASC = Cast<UDND_Base_ASC>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SingleHitActor));
		if (HitActorASC == NULL)
		{
			continue;
		}

		FGameplayEffectContextHandle ContextHandle = MakeEffectContext(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo());
		HitActorASC->MakeAndApplyGameplayEffectSpecToSelf(GE_DamageEffect, 1.0f, ContextHandle);
	}
}

bool UDND_GA_Bard_Melee_Attack::IsOverlapedCharacterUnique(AActor* NewCharacter)
{
	for (AActor* SingleActor : MeleeAttackHitActors)
	{
		if (SingleActor == NewCharacter)
		{
			return false;
		}
	}

	return true;
}

