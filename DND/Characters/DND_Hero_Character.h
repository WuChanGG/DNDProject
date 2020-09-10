// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBAProject/DND/Characters/DND_Base_Character.h"
#include "DND_Hero_Character.generated.h"

/**
 * 
 */
UCLASS()
class MOBAPROJECT_API ADND_Hero_Character : public ADND_Base_Character
{
	GENERATED_BODY()
	
	ADND_Hero_Character();
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent *SpringArmComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent *CameraComponent;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnRep_PlayerState() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, TSubclassOf<UGameplayAbility>> ActionNameAndAbilityMap;

	void TryActivateAbilityInActionNameAndAbilityMap(FName ActionName);

	UFUNCTION(Server, Reliable)
	void TempGiveAbilitiesInActionNameAndAbilityMap();

	DECLARE_DELEGATE_OneParam(FActionNameAbilityDelegate, FName);
};
