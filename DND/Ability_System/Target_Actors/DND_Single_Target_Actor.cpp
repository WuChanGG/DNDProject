// Fill out your copyright notice in the Description page of Project Settings.


#include "DND_Single_Target_Actor.h"
#include "MOBAProject/DND/Characters/DND_Base_Character.h"

void ADND_Single_Target_Actor::ConfirmTargetingAndContinue()
{

	if (OwningAbility == NULL || UnderCursorObjectTypes.Num() == 0)
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
	bool bHitValidObject = PC->GetHitResultUnderCursorForObjects(UnderCursorObjectTypes, true, OutHitResult);
	if (!bHitValidObject)
	{
		CancelTargeting();
		return;
	}

	ADND_Base_Character *HitBaseCharacter = Cast<ADND_Base_Character>(OutHitResult.Actor);
	if (HitBaseCharacter == NULL)
	{
		CancelTargeting();
		return;
	}

	FGameplayAbilityTargetData_ActorArray *ActorArrayTargetData = new FGameplayAbilityTargetData_ActorArray();
	TArray<TWeakObjectPtr<AActor>> WeakPTRActorArray;
	WeakPTRActorArray.Add(OutHitResult.Actor);
	ActorArrayTargetData->SetActors(WeakPTRActorArray);
	FGameplayAbilityTargetDataHandle TargetDataHandle = FGameplayAbilityTargetDataHandle(ActorArrayTargetData);
	TargetDataReadyDelegate.Broadcast(TargetDataHandle);
}
