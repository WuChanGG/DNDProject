// Fill out your copyright notice in the Description page of Project Settings.


#include "DND_GA_Shared_Dash.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Kismet/KismetMathLibrary.h"

void UDND_GA_Shared_Dash::OnValidTargetData(FGameplayAbilityTargetDataHandle TargetData)
{
	if (!UAbilitySystemBlueprintLibrary::TargetDataHasHitResult(TargetData, 0))
	{
		return;
	}

	ACharacter* AvatarChar = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	if (AvatarChar == NULL || DashTravelTime <= 0.0f || DashForceDistance <= 0.0f)
	{
		checkNoEntry();
		return;
	}

	FHitResult HitResult = UAbilitySystemBlueprintLibrary::GetHitResultFromTargetData(TargetData, 0);
	FVector NoZTarget = HitResult.ImpactPoint;
	NoZTarget.Z = 0.0f;
	FVector NoZOrigin = GetAvatarActorFromActorInfo()->GetActorLocation();
	NoZOrigin.Z = 0.0f;
	FVector ImpulseDirection = UKismetMathLibrary::GetDirectionUnitVector(NoZOrigin, NoZTarget);
	if (AvatarChar->GetCharacterMovement() == NULL || GetCurrentActorInfo()->PlayerController.Get() == NULL)
	{
		return;
	}

	//GetCurrentActorInfo()->PlayerController.Get()->SetIgnoreMoveInput(true);
	FRootMotionSource_ConstantForce *ConstantForce = new FRootMotionSource_ConstantForce();
	ConstantForce->Duration = DashTravelTime;
	ConstantForce->FinishVelocityParams.Mode = ERootMotionFinishVelocityMode::SetVelocity;
	ConstantForce->FinishVelocityParams.SetVelocity = FVector::ZeroVector;
	ConstantForce->Force = ImpulseDirection * DashForceDistance;
	ConstantForce->AccumulateMode = ERootMotionAccumulateMode::Override;
	ConstantForce->Priority = 1;
	ConstantForce->InstanceName = FName("SharedDashConstantForce");
	AvatarChar->GetCharacterMovement()->ApplyRootMotionSource(ConstantForce);
	//AvatarChar->SetActorRotation(UKismetMathLibrary::Conv_VectorToRotator(ImpulseDirection));
	//FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(GE_DashingTag, 1.0f);
	//ApplyGameplayEffectSpecToOwner(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), SpecHandle);
}

