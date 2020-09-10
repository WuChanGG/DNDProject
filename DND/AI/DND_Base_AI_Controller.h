// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DND_Base_AI_Controller.generated.h"

/**
 * 
 */
UCLASS()
class MOBAPROJECT_API ADND_Base_AI_Controller : public AAIController
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	FVector GetVectorToBeInFrontOfTarget(AActor* InTarget);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DistanceToBeInFrontOfTarget = 500.0f;
};
