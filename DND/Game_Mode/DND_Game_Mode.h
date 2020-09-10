// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DND_Game_Mode.generated.h"

/**
 * 
 */
UCLASS()
class MOBAPROJECT_API ADND_Game_Mode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
