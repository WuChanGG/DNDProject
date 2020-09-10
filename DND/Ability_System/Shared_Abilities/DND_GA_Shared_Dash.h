// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBAProject/DND/Ability_System/Abilities/DND_GA_Base.h"
#include "DND_GA_Shared_Dash.generated.h"

/**
 * 
 */
UCLASS()
class MOBAPROJECT_API UDND_GA_Shared_Dash : public UDND_GA_Base
{
	GENERATED_BODY()
	
public:

	virtual void OnValidTargetData(FGameplayAbilityTargetDataHandle TargetData) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DashForceDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DashTravelTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> GE_DashingTag;

};
