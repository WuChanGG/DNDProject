// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBAProject/DND/Ability_System/DND_Spellcaster_ASC.h"
#include "DND_Mixed_ASC.generated.h"

/**
 * Every character will have a mixed ASC that will consist
 * of spell caster, melee and maybe ranged ASC
 * Still early to tell if this will be ever modified
 */
UCLASS()
class MOBAPROJECT_API UDND_Mixed_ASC : public UDND_Spellcaster_ASC
{
	GENERATED_BODY()

public:
};
