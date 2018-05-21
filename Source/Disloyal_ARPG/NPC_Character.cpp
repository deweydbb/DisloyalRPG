// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC_Character.h"
#include "NPC_Parent.h"
#include "Disloyal_ARPGCharacter.h"

// Sets default values
ANPC_Character::ANPC_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	health = 50;
	maxHealth = 50;
}

// Called when the game starts or when spawned
void ANPC_Character::BeginPlay()
{
	Super::BeginPlay();
	
	ANPC_Parent* AIController = Cast<ANPC_Parent>(GetController());

	ADisloyal_ARPGCharacter* Character = Cast<ADisloyal_ARPGCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	

	if (AIController) {
		AIController->SetPlayerToFollow(Character);
	}
}

