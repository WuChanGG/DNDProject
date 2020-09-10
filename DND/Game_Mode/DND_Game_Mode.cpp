// Fill out your copyright notice in the Description page of Project Settings.


#include "DND_Game_Mode.h"
#include "MOBAProject/DND/Game_Mode/DND_Player_Controller.h"

void ADND_Game_Mode::PostLogin(APlayerController* NewPlayer)
{
	ADND_Player_Controller *PC = Cast<ADND_Player_Controller>(NewPlayer);
	if (PC != NULL)
	{
		PC->SpawnDNDPawn();
	}
}
