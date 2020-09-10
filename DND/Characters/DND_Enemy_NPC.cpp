// Fill out your copyright notice in the Description page of Project Settings.


#include "DND_Enemy_NPC.h"
#include "MOBAProject/DND/Ability_System/DND_Base_ASC.h"
#include "MOBAProject/DND/Ability_System/Attributes/DND_Base_Attributes.h"

ADND_Enemy_NPC::ADND_Enemy_NPC()
{
	AbilitySystemComponent = CreateDefaultSubobject<UDND_Mixed_ASC>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	//AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal); 
	BaseAttributeSet = CreateDefaultSubobject<UDND_Base_Attributes>(TEXT("Base_Attributes"));
}

void ADND_Enemy_NPC::BeginPlay()
{
	Super::BeginPlay();
	if (AbilitySystemComponent != NULL)
	{
		check(BaseAttributeSet != NULL);
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		AbilitySystemComponent->RefreshAbilityActorInfo();
		UDND_Base_ASC* BaseASC = Cast<UDND_Base_ASC>(AbilitySystemComponent);
		//BaseASC->MakeAndApplyGameplayEffectSpecToSelf(GE_AttributeInitializer);
		FGameplayEffectSpecHandle SpecHandle = BaseASC->MakeOutgoingSpec(GE_AttributeInitializer, 1.0f, BaseASC->MakeEffectContext());
		BaseASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

void ADND_Enemy_NPC::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}
