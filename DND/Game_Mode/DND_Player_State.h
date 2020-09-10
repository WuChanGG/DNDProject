// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "DND_Player_State.generated.h"

/**
 * 
 */
UCLASS()
class MOBAPROJECT_API ADND_Player_State : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ADND_Player_State();
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;

	virtual UAbilitySystemComponent *GetAbilitySystemComponent() const override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDND_Base_Attributes *BaseAttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAbilitySystemComponent *AbilitySystemComponent;

	void InitializeAttributeSet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DND_Player_State)
	TSubclassOf<UGameplayEffect> GE_AttributeInitializer;
};
