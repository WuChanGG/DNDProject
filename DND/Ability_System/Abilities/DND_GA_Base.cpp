// Fill out your copyright notice in the Description page of Project Settings.


#include "DND_GA_Base.h"
#include "MOBAProject/DND/Game_Mode/DND_Player_Controller.h"
#include "MOBAProject/DND/Characters/DND_Hero_Character.h"
#include "AbilitySystemBlueprintLibrary.h"
bool UDND_GA_Base::IsAvatarActorAuthority()
{
	if (GetAvatarActorFromActorInfo() && GetAvatarActorFromActorInfo()->GetLocalRole() == ROLE_Authority)
	{
		return true;
	}

	return false;
}

void UDND_GA_Base::OnValidTargetData(FGameplayAbilityTargetDataHandle TargetData)
{

}

UDND_GA_Base::UDND_GA_Base()
{
}

bool UDND_GA_Base::IsTargetSlotValid()
{
	ADND_Player_Controller *PC = Cast<ADND_Player_Controller>(GetCurrentActorInfo()->PlayerController.Get());
	if (PC == NULL)
	{
		checkNoEntry();
		return false;
	}

	if (PC->TargetSlot == NULL)
	{
		return false;
	}

	return true;
}

bool UDND_GA_Base::IsValidTargetSlotFriendly()
{
	ADND_Player_Controller *PC = Cast<ADND_Player_Controller>(GetCurrentActorInfo()->PlayerController.Get());
	if (PC == NULL)
	{
		checkNoEntry();
		return false;
	}

	ADND_Hero_Character *TargetCharacter = Cast<ADND_Hero_Character>(PC->TargetSlot);
	if (TargetCharacter != NULL)
	{
		return true;
	}

	return false;
}

bool UDND_GA_Base::CanEffectBeAppliedToTargetSlotDirectly(bool bIsTargetFriendly)
{
	if (bIsFriendlyAbility && bIsTargetFriendly)
	{
		return true;
	}
	else if (!bIsTargetFriendly && !bIsFriendlyAbility)
	{
		return true;
	}

	else return false;
}

bool UDND_GA_Base::IsTargetActorFriendly(AActor *TargetActor)
{
	ADND_Hero_Character *HeroCharacter = Cast<ADND_Hero_Character>(TargetActor);
	if (HeroCharacter != NULL)
	{
		return true;
	}

	return false;
}

void UDND_GA_Base::MakeAndApplySpecToTarget(AActor* InTarget, TSubclassOf<UGameplayEffect> InGameplayEffect, float EffectLevel)
{
	UAbilitySystemComponent *TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InTarget);
	if (TargetASC == NULL)
	{
		return;
	}

	FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(InGameplayEffect, EffectLevel);
	TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}
