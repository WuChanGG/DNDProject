// Fill out your copyright notice in the Description page of Project Settings.


#include "DND_Hero_Character.h"
#include "MOBAProject/DND/Game_Mode/DND_Player_State.h"

ADND_Hero_Character::ADND_Hero_Character()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	if (SpringArmComponent == NULL || CameraComponent == NULL)
	{
		checkNoEntry();
		return;
	}

	SpringArmComponent->SetupAttachment(GetRootComponent());
	CameraComponent->SetupAttachment(SpringArmComponent, SpringArmComponent->SocketName);

}

void ADND_Hero_Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADND_Base_Character::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &ADND_Base_Character::MoveUp);
	for (TPair<FName, TSubclassOf<UGameplayAbility>> SinglePair : ActionNameAndAbilityMap)
	{
		PlayerInputComponent->BindAction<FActionNameAbilityDelegate>(SinglePair.Key, EInputEvent::IE_Pressed,
			this, &ADND_Hero_Character::TryActivateAbilityInActionNameAndAbilityMap, SinglePair.Key);
	}
}

void ADND_Hero_Character::OnRep_PlayerState()
{
	ADND_Player_State *PS = Cast<ADND_Player_State>(GetPlayerState());
	if (PS == NULL)
	{
		checkNoEntry();
		return;
	}

	AbilitySystemComponent = PS->GetAbilitySystemComponent();
	BaseAttributeSet = PS->BaseAttributeSet;
	if (AbilitySystemComponent != NULL)
	{
		TempGiveAbilitiesInActionNameAndAbilityMap();
	}
}

void ADND_Hero_Character::TryActivateAbilityInActionNameAndAbilityMap(FName ActionName)
{
	if (AbilitySystemComponent == NULL)
	{
		return;
	}

	TSubclassOf<UGameplayAbility> *AbilityToActivate = ActionNameAndAbilityMap.Find(ActionName);
	if (AbilityToActivate == NULL)
	{
		return;
	}

	AbilitySystemComponent->TryActivateAbilityByClass(*AbilityToActivate);
}

void ADND_Hero_Character::TempGiveAbilitiesInActionNameAndAbilityMap_Implementation()
{
	if (AbilitySystemComponent == NULL)
	{
		checkNoEntry();
		return;
	}

	for (auto SinglePair : ActionNameAndAbilityMap)
	{
		TSubclassOf<UGameplayAbility> AbilityToGive = SinglePair.Value;
		if (AbilityToGive == NULL)
		{
			continue;
		}

		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(AbilityToGive));
	}
}
