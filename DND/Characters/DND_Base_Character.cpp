// Fill out your copyright notice in the Description page of Project Settings.


#include "DND_Base_Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "MOBAProject/DND/Ability_System/Attributes/DND_Base_Attributes.h"

// Sets default values
ADND_Base_Character::ADND_Base_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADND_Base_Character::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADND_Base_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADND_Base_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADND_Base_Character::MoveRight(float Scale)
{
	if (Scale == 0)
		return;

	FVector RightVector(1.0f, 0.0f, 0.0f);
	AddMovementInput(RightVector, Scale);
}

void ADND_Base_Character::MoveUp(float Scale)
{
	if (Scale == 0)
		return;

	FVector UpVector(0.0f, 1.0f, 0.0f);
	AddMovementInput(UpVector, Scale);
}

UAbilitySystemComponent* ADND_Base_Character::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


TArray<AActor*> ADND_Base_Character::SocketSphereCollisionForActors()
{
	TArray<AActor*> OutActors;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	FVector SocketLocation = GetMesh()->GetSocketLocation(WeaponSocketName);
	UKismetSystemLibrary::SphereOverlapActors(this, SocketLocation, SocketSphereCollisionRadius, SocketSphereCollisionObjectTypes, ADND_Base_Character::GetClass(), ActorsToIgnore, OutActors);
	UKismetSystemLibrary::DrawDebugSphere(this, SocketLocation, SocketSphereCollisionRadius, 12, FLinearColor::Red, 10.0f);
	return OutActors;
}

void ADND_Base_Character::OnMeleeAttackOverlap(AActor *HitActor)
{
	ADND_Base_Character* BaseHitActor = Cast<ADND_Base_Character>(HitActor);
	if (BaseHitActor == NULL)
	{
		return;
	}

	FGameplayEventData EventData;
	EventData.Target = BaseHitActor;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, MeleeAttackEventTag, EventData);
}

bool ADND_Base_Character::IsAlive()
{
	if (BaseAttributeSet == NULL)
	{
		checkNoEntry();
		return false;
	}

	return BaseAttributeSet->GetHealth() > 0.0f;
}
