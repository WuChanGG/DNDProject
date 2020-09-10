// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "C_BTTask_MoveIfTooClose.generated.h"

/**
 * 
 */
UCLASS()
class MOBAPROJECT_API UC_BTTask_MoveIfTooClose : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	FVector MoveVectorIfTooClose(AActor* InTarget, AActor* ControlledPawn);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DistanceToBeInFrontOfTarget = 100.0f;
};
