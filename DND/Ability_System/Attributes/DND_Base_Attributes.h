// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "DND_Base_Attributes.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class MOBAPROJECT_API UDND_Base_Attributes : public UAttributeSet
{
	GENERATED_BODY()

public:		

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UDND_Base_Attributes, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UDND_Base_Attributes, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "AttackDice", ReplicatedUsing = OnRep_AttackDice)
	FGameplayAttributeData AttackDice;
	ATTRIBUTE_ACCESSORS(UDND_Base_Attributes, AttackDice)

	UPROPERTY(BlueprintReadOnly, Category = "ArmorClass", ReplicatedUsing = OnRep_ArmorClass)
	FGameplayAttributeData ArmorClass;
	ATTRIBUTE_ACCESSORS(UDND_Base_Attributes, ArmorClass)

	// Damage is a meta attribute used by the DamageExecution to calculate final damage, which then turns into -Health
	// Temporary value that only exists on the Server. Not replicated.
	UPROPERTY(BlueprintReadOnly, Category = "Damage", meta = (HideFromLevelInfos))
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UDND_Base_Attributes, Damage)

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	void OnRep_AttackDice(const FGameplayAttributeData& OldAttackDice);

	UFUNCTION()
	void OnRep_ArmorClass(const FGameplayAttributeData& OldArmorClass);

	void MaxAttributeChanged(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
};
