// Fill out your copyright notice in the Description page of Project Settings.


#include "DND_Base_AI_Controller.h"

FVector ADND_Base_AI_Controller::GetVectorToBeInFrontOfTarget(AActor* InTarget)
{
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn == NULL)
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
		return InTargetLocation + (NormalizedTargetToPawnVector * DistanceToBeInFrontOfTarget);
	}
}
