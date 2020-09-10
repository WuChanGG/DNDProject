// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "DND_Base_Character.generated.h"


UCLASS()
class MOBAPROJECT_API ADND_Base_Character : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADND_Base_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void MoveRight(float Scale);
	virtual void MoveUp(float Scale);

	UPROPERTY()
	class UAbilitySystemComponent *AbilitySystemComponent;
	
	UFUNCTION()
	virtual UAbilitySystemComponent *GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable)
	TArray<AActor*> SocketSphereCollisionForActors();

	FName WeaponSocketName = FName("HammerCenter");
	
	float SocketSphereCollisionRadius = 34.0f;

	TArray<TEnumAsByte<EObjectTypeQuery>> SocketSphereCollisionObjectTypes;

	// Will send an event to this actor that activated the melee ability
	// the event will send all actors hit, which will be stored in an array in the ability
	// Bind this in the blueprint
	UFUNCTION(BlueprintCallable)
	void OnMeleeAttackOverlap(AActor *HitActor);

	// Fill in blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag MeleeAttackEventTag;

	UPROPERTY(BlueprintReadWrite)
	bool IsMeleeAttacking;

	UPROPERTY()
	class UDND_Base_Attributes *BaseAttributeSet;

	bool IsAlive();
};
