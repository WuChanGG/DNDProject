// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BTTask_MoveIfTooClose.h"

FVector UC_BTTask_MoveIfTooClose::MoveVectorIfTooClose(AActor* InTarget, AActor *ControlledPawn)
{
	if (ControlledPawn == NULL || InTarget == NULL)
	{
		checkNoEntry();
		return FVector::ZeroVector;
	}

	FVector InTargetLocation = InTarget->GetActorLocation();
	FVector PawnLocation = ControlledPawn->GetActorLocation();
	FVector NormalizedTargetToPawnVector = (PawnLocation - InTargetLocation).GetSafeNormal();
	if (NormalizedTargetToPawnVector == FVector::ZeroVector)
	{
		return PawnLocation - (ControlledPawn->GetActorForwardVector() * DistanceToBeInFrontOfTarget);
	}
	else
	{
		return InTargetLocation + (NormalizedTargetToPawnVector * (DistanceToBeInFrontOfTarget));
	}
}
