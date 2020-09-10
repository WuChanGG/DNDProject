// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DND_Player_Controller.generated.h"

/**
 * 
 */
UCLASS()
class MOBAPROJECT_API ADND_Player_Controller : public APlayerController
{
	GENERATED_BODY()
	
public:
	ADND_Player_Controller();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;
	
	void PossessDNDCharacter(APawn *InCharacter);

	UFUNCTION(Server, Reliable)
	void SpawnDNDPawn();

	// Filled from database, currently manual
	// TODO:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DND_Player_Controller)
	TSubclassOf<class ADND_Base_Character> DNDPawnClass;

	// Filled from database, currently manual
	// TODO:
	FVector DNDPawnSpawnLocation = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite)
	TArray<ACharacter *> CharactersInTheSameParty;

	UPROPERTY(BlueprintReadWrite)
	bool bIsPVPCharacter = false;

	// This target slot will help UI, and also it will help abilities that are Single Target
	// use this pawn as the target
	UPROPERTY(BlueprintReadWrite, Replicated)
	APawn *TargetSlot;

};
