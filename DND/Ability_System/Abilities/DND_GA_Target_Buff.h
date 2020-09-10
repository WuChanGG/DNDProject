// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBAProject/DND/Ability_System/Abilities/DND_GA_Base.h"
#include "DND_GA_Target_Buff.generated.h"

/**
 * This is intended to be used as buff / debuff abilities, these are
 * mostly gameplay effects applied to a character
 */
UCLASS()
class MOBAPROJECT_API UDND_GA_Target_Buff : public UDND_GA_Base
{
	GENERATED_BODY()

public:

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DND_GA_Target_Buff)
	TSubclassOf<UGameplayEffect> GE_Buff;
};
