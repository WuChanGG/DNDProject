// Fill out your copyright notice in the Description page of Project Settings.


#include "DND_Hit_Result_Target_Actor.h"

void ADND_Hit_Result_Target_Actor::ConfirmTargetingAndContinue()
{
	if (OwningAbility == NULL)
	{
		checkNoEntry();
		CancelTargeting();
		return;
	}

	APlayerController *PC = OwningAbility->GetCurrentActorInfo()->PlayerController.Get();
	if (PC == NULL)
	{
		CancelTargeting();
		return;
	}

	FHitResult OutHitResult;
	bool bHitValidObject = PC->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2), true, OutHitResult);
	if (!bHitValidObject)
	{
		CancelTargeting();
		return;
	}

	FGameplayAbilityTargetData_SingleTargetHit *HitResultTargetData = new FGameplayAbilityTargetData_SingleTargetHit();
	HitResultTargetData->HitResult = OutHitResult;
	FGameplayAbilityTargetDataHandle TargetDataHandle(HitResultTargetData);
	TargetDataReadyDelegate.Broadcast(TargetDataHandle);
}
