// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DND_Hero_Chara.generated.h"

UCLASS()
class MOBAPROJECT_API ADND_Hero_Chara : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADND_Hero_Chara();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
