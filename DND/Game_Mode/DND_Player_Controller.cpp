// Fill out your copyright notice in the Description page of Project Settings.


#include "DND_Player_Controller.h"
#include "MOBAProject/DND/Characters/DND_Base_Character.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "MOBAProject/DND/Game_Mode/DND_Player_State.h"

ADND_Player_Controller::ADND_Player_Controller()
{
	bShowMouseCursor = true;
}

void ADND_Player_Controller::PossessDNDCharacter(APawn* InCharacter)
{
	OnPossess(InCharacter);
}


void ADND_Player_Controller::SpawnDNDPawn_Implementation()
{
	if (GetWorld() == NULL || DNDPawnClass == NULL)
	{
		checkNoEntry();
		return;
	}

	FTransform SpawnTransform = FTransform(FRotator::ZeroRotator, DNDPawnSpawnLocation);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	ADND_Base_Character *TempCharacter = GetWorld()->SpawnActor<ADND_Base_Character>(DNDPawnClass, SpawnTransform, SpawnParameters);
	ADND_Player_State* DNDPS = Cast<ADND_Player_State>(PlayerState);
	// Setup ASC
	if (PlayerState == NULL || DNDPS == NULL)
	{
		checkNoEntry();
		return;
	}

	TempCharacter->AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(PlayerState);
	TempCharacter->AbilitySystemComponent->InitAbilityActorInfo(PlayerState, TempCharacter);
	TempCharacter->BaseAttributeSet = DNDPS->BaseAttributeSet;
	OnPossess(TempCharacter);
}


void ADND_Player_Controller::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADND_Player_Controller, TargetSlot);
}


