// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "DND_Hit_Result_Target_Actor.generated.h"

/**
 * 
 */
UCLASS()
class MOBAPROJECT_API ADND_Hit_Result_Target_Actor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:
	virtual void ConfirmTargetingAndContinue() override;

};
