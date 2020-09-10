// Fill out your copyright notice in the Description page of Project Settings.


#include "DND_Base_MMC.h"
#include "Kismet/KismetMathLibrary.h"


UDND_Base_MMC::UDND_Base_MMC()
{
	AttackDiceDef.AttributeToCapture = UDND_Base_Attributes::GetAttackDiceAttribute();
	AttackDiceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	AttackDiceDef.bSnapshot = false;

	ArmorClassDef.AttributeToCapture = UDND_Base_Attributes::GetArmorClassAttribute();
	ArmorClassDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	ArmorClassDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(AttackDiceDef);
	RelevantAttributesToCapture.Add(ArmorClassDef);
}

float UDND_Base_MMC::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Get the current value of the Attack Roll
	float AttackDice = 1.0f;
	GetCapturedAttributeMagnitude(AttackDiceDef, Spec, EvaluationParameters, AttackDice);
	AttackDice = FMath::Max<float>(AttackDice, 1.0f);
	// Target Armor Class
	float TargetArmorClass;
	GetCapturedAttributeMagnitude(ArmorClassDef, Spec, EvaluationParameters, TargetArmorClass);
	// TODO: Should AC be => 0 ?
	TargetArmorClass = FMath::Max<float>(TargetArmorClass, 0.0f);
	// Calculate the damage with the current Attack Dice
	int AttackRoll = UKismetMathLibrary::RandomIntegerInRange(1, (int)AttackDice);
	int TagAlteredAttackRoll = AttackRoll + GetSourceAttackDiceModifiers(Spec);
	if (TagAlteredAttackRoll >= (int)TargetArmorClass)
	{
		// TODO: Broadcast successful damage roll and attack roll to client
		const UDND_GA_Base *DamagingAbility = Cast<UDND_GA_Base>(Spec.GetContext().GetAbility());
		if (DamagingAbility == NULL)
		{
			checkNoEntry();
			return 0.0f;
		}

		if (DamagingAbility->DamageDice <= 0 || DamagingAbility->NumberOfDamageDice <= 0)
		{
			checkNoEntry();
			return 0.0f;
		}
		// TODO: Get Source
		int TempDamage = 0;
		for (int i = 0; i < DamagingAbility->NumberOfDamageDice; i = i + 1)
		{
			TempDamage = TempDamage + UKismetMathLibrary::RandomIntegerInRange(1, DamagingAbility->DamageDice);
		}
		int Damage = TempDamage + GetSourceDamageDiceModifiers(Spec);
		return (float)Damage;
	}
	else
	{
		// TODO: Broadcast failed attack roll to client
		return 0.0f;
	}
}
	

int UDND_Base_MMC::GetSourceAttackDiceModifiers(const FGameplayEffectSpec& Spec) const
{
	if (Spec.GetEffectContext().GetInstigatorAbilitySystemComponent() == NULL)
	{
		checkNoEntry();
		return 0;
	}

	int TempAttackModifier = 0;

	for (FGameplayTag SinglePair : AttackModifierTagList)
	{

		TArray<FGameplayEffectSpec> OutEffectSpecs;
		Spec.GetEffectContext().GetInstigatorAbilitySystemComponent()->GetAllActiveGameplayEffectSpecs(OutEffectSpecs);
		for (FGameplayEffectSpec SingleEffectSpec : OutEffectSpecs)
		{
			FGameplayTagContainer OutTagContainer;
			SingleEffectSpec.GetAllGrantedTags(OutTagContainer);
			// Means the effect applied SinglePair tag to the Instigator ASC
			if (OutTagContainer.HasTag(SinglePair))
			{
				TempAttackModifier = TempAttackModifier + (int)SingleEffectSpec.GetSetByCallerMagnitude(GT_AttackModifier);
			}
		}
	}
	return TempAttackModifier;
}


int UDND_Base_MMC::GetSourceDamageDiceModifiers(const FGameplayEffectSpec& Spec) const
{
	if (Spec.GetEffectContext().GetInstigatorAbilitySystemComponent() == NULL)
	{
		checkNoEntry();
		return 0;
	}

	int TempDamageModifier = 0;

	for (FGameplayTag SinglePair : DamageModifierTagList)
	{

		TArray<FGameplayEffectSpec> OutEffectSpecs;
		Spec.GetEffectContext().GetInstigatorAbilitySystemComponent()->GetAllActiveGameplayEffectSpecs(OutEffectSpecs);
		for (FGameplayEffectSpec SingleEffectSpec : OutEffectSpecs)
		{
			FGameplayTagContainer OutTagContainer;
			SingleEffectSpec.GetAllGrantedTags(OutTagContainer);
			// Means the effect applied SinglePair tag to the Instigator ASC
			if (OutTagContainer.HasTag(SinglePair))
			{
				TempDamageModifier = TempDamageModifier + (int)SingleEffectSpec.GetSetByCallerMagnitude(GT_DamageModifier);
			}
		}
	}
	return TempDamageModifier;
}
