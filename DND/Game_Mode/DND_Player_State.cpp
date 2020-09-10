// Fill out your copyright notice in the Description page of Project Settings.


#include "DND_Player_State.h"
#include "MOBAProject/DND/Characters/DND_Base_Character.h"
#include "MOBAProject/DND/Game_Mode/DND_Player_Controller.h"
#include "MOBAProject/DND/Ability_System/DND_Mixed_ASC.h"
#include "MOBAProject/DND/Ability_System/Attributes/DND_Base_Attributes.h"

ADND_Player_State::ADND_Player_State()
{
	AbilitySystemComponent = CreateDefaultSubobject<UDND_Mixed_ASC>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	BaseAttributeSet = CreateDefaultSubobject<UDND_Base_Attributes>(TEXT("BaseAttributeSet"));
}
UAbilitySystemComponent* ADND_Player_State::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ADND_Player_State::BeginPlay()
{
	Super::BeginPlay();
	// TODO: Replace for database attributes
	InitializeAttributeSet();
}


void ADND_Player_State::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ADND_Player_State::InitializeAttributeSet()
{
	if (AbilitySystemComponent == NULL)
	{
		checkNoEntry();
		return;
	}

	FGameplayEffectSpecHandle TempSpec = AbilitySystemComponent->MakeOutgoingSpec(GE_AttributeInitializer, 1.0f, AbilitySystemComponent->MakeEffectContext());
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*TempSpec.Data.Get());
}

