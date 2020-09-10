// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "DND_Single_Target_Actor.generated.h"

/**
 * 
 */
UCLASS()
class MOBAPROJECT_API ADND_Single_Target_Actor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
	
public:
	
	virtual void ConfirmTargetingAndContinue() override;

	// ATTENTION: Fill this
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MOBA_A_SingleActorTargetActor)
	TArray<TEnumAsByte<EObjectTypeQuery>> UnderCursorObjectTypes;
};
