// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBAProject/DND/Characters/DND_Base_Character.h"
#include "DND_Enemy_NPC.generated.h"

/**
 * 
 */
UCLASS()
class MOBAPROJECT_API ADND_Enemy_NPC : public ADND_Base_Character
{
	GENERATED_BODY()
	
public:
	ADND_Enemy_NPC();

	UPROPERTY()
	class UDND_Base_Attributes *BaseAttributes;

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> GE_AttributeInitializer;

	virtual void PossessedBy(AController* NewController) override;
};
