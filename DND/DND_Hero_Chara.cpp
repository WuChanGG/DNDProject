// Fill out your copyright notice in the Description page of Project Settings.


#include "DND_Hero_Chara.h"

// Sets default values
ADND_Hero_Chara::ADND_Hero_Chara()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADND_Hero_Chara::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADND_Hero_Chara::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADND_Hero_Chara::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

