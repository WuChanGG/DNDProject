// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBAProject/DND/Ability_System/Abilities/DND_GA_Base.h"
#include "DND_GA_Bard_Melee_Attack.generated.h"

/**
 * 
 */
UCLASS()
class MOBAPROJECT_API UDND_GA_Bard_Melee_Attack : public UDND_GA_Base
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> GE_DamageEffect;

	UFUNCTION(BlueprintCallable)
	void OnMeleeAttackEventReceived(FGameplayEventData EventData);

	UFUNCTION(BlueprintCallable)
	void FilterMeleeHitActors();

	UFUNCTION(BlueprintCallable)
	void DamageMeleeHitActors();
	
	bool IsOverlapedCharacterUnique(AActor *NewCharacter);

	TArray<AActor*> MeleeAttackHitActors;
};
