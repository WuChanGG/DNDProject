// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DND_GA_Base.generated.h"

/**
 * 
 */
UCLASS()
class MOBAPROJECT_API UDND_GA_Base : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UDND_GA_Base();

	bool IsAvatarActorAuthority();

	UFUNCTION(BlueprintCallable)
	virtual void OnValidTargetData(FGameplayAbilityTargetDataHandle TargetData);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DND_GA_Base)
	int DamageDice = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DND_GA_Base)
	int NumberOfDamageDice = 0;

	UFUNCTION(BlueprintCallable)
	bool IsTargetSlotValid();

	UFUNCTION(BlueprintCallable)
	bool IsValidTargetSlotFriendly();

	UFUNCTION(BlueprintCallable)
	bool CanEffectBeAppliedToTargetSlotDirectly(bool bIsTargetFriendly);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DND_GA_Base)
	bool bIsFriendlyAbility = false;

	// TODO: Extend to more conditions
	// Currently any other actor is non-friendly
	UFUNCTION(BlueprintCallable)
	bool IsTargetActorFriendly(AActor *TargetActor);

	UFUNCTION(BlueprintCallable)
	void MakeAndApplySpecToTarget(AActor *InTarget, TSubclassOf<UGameplayEffect> InGameplayEffect, float EffectLevel);
};
