// Fill out your copyright notice in the Description page of Project Settings.


#include "DND_Base_ASC.h"

void UDND_Base_ASC::MakeAndApplyGameplayEffectSpecToSelf(TSubclassOf<UGameplayEffect> InEffect, float EffectLevel, FGameplayEffectContextHandle EffectContext)
{
	FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(InEffect, EffectLevel, EffectContext);
	ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}
