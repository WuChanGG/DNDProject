// Fill out your copyright notice in the Description page of Project Settings.


#include "DND_Base_Attributes.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "MOBAProject/DND/Characters/DND_Base_Character.h"
#include "Kismet/KismetSystemLibrary.h"

void UDND_Base_Attributes::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UDND_Base_Attributes, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDND_Base_Attributes, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDND_Base_Attributes, AttackDice, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDND_Base_Attributes, ArmorClass, COND_None, REPNOTIFY_Always);
}

void UDND_Base_Attributes::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDND_Base_Attributes, Health, OldHealth);
}

void UDND_Base_Attributes::OnRep_MaxHealth(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDND_Base_Attributes, MaxHealth, OldHealth);
}

void UDND_Base_Attributes::OnRep_AttackDice(const FGameplayAttributeData& OldAttackDice)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDND_Base_Attributes, AttackDice, OldAttackDice);
}

void UDND_Base_Attributes::OnRep_ArmorClass(const FGameplayAttributeData& OldArmorClass)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDND_Base_Attributes, ArmorClass, OldArmorClass);
}

void UDND_Base_Attributes::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	FGameplayEffectContextHandle ContextHandle = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = ContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	FGameplayTagContainer SpecAssetTags;
	Data.EffectSpec.GetAllAssetTags(SpecAssetTags);

	AActor *TargetActor = nullptr;
	// Attention to how you handle the controller, no checks for null in case it's an AI character
	AController* TargetController = nullptr;
	ADND_Base_Character* TargetCharacter = nullptr;
	if (Data.Target.AbilityActorInfo != NULL && Data.Target.AbilityActorInfo->AvatarActor != NULL)
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetCharacter = Cast<ADND_Base_Character>(Data.Target.AbilityActorInfo->AvatarActor.Get());
	}

	AActor *SourceActor = NULL;
	// Attention to how you handle the controller, no checks for null in case it's an AI character
	AController *SourceController = NULL;
	ADND_Base_Character *SourceCharacter = NULL;
	if (Source != NULL && Source->AbilityActorInfo != NULL && Source->AbilityActorInfo.Get()->AvatarActor != NULL)
	{
		SourceActor = Source->AbilityActorInfo.Get()->AvatarActor.Get();
		SourceController = Source->AbilityActorInfo.Get()->PlayerController.Get();
		SourceCharacter = Cast<ADND_Base_Character>(Source->AbilityActorInfo->AvatarActor.Get());
	}

	// It is hard to implement this checks if they are going to fail when setting Player State up, handle case by case
	//if (SourceActor == NULL || SourceCharacter == NULL
	//	|| TargetActor == NULL || TargetCharacter == NULL)
	//{
	//	checkNoEntry();
	//	return;
	//}

	if (Data.EvaluatedData.Attribute == GetDamageAttribute() && TargetCharacter != NULL)
	{
		bool WasAlive = TargetCharacter->IsAlive();

		const float LocalDamageDone = GetDamage();
		SetDamage(0.0f);
		
		if (LocalDamageDone > 0.0f && WasAlive)
		{
			#if (!UE_BUILD_SHIPPING || UE_BUILD_TEST)
				UE_LOG(LogTemp, Warning, TEXT("Character %s is taking %f damage @%s"), *TargetCharacter->GetName(), LocalDamageDone, TEXT(__FUNCTION__));
			#endif
			const float NewHealth = GetHealth() - LocalDamageDone;
			SetHealth(FMath::Clamp(NewHealth, 0.0f, GetMaxHealth()));

			// Handle death
			if (!TargetCharacter->IsAlive())
			{
				#if (!UE_BUILD_SHIPPING || UE_BUILD_TEST)
					UE_LOG(LogTemp, Warning, TEXT("Character %s died @%s"), *TargetCharacter->GetName(), TEXT(__FUNCTION__));
				#endif
			}
		}
		else if (!WasAlive)
		{
			// Target not alive do nothing
		}
	}
	else if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
}


void UDND_Base_Attributes::MaxAttributeChanged(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		// Change current value to maintain the current Val / Max percent
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}

void UDND_Base_Attributes::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		MaxAttributeChanged(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
}
