// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "Disloyal_ARPGCharacter.h"
#include"Disloyal_ARPGGameMode.h"


// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	health = 0;
	damage = 0;
	armor = 0;
	mana = 0;
	ID = TEXT("0");
	IsPickAble = true;
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}
//called by player when gets an object
void AItem::pickUp()
{
	if (IsPickAble) {
		Destroy();
	}
}

void AItem::inheritFromDataTable(FName givenID) {
	ADisloyal_ARPGGameMode* GameMode = Cast<ADisloyal_ARPGGameMode>(GetWorld()->GetAuthGameMode());
	UDataTable* ItemTable = GameMode->GetItemDB();

	FInventoryItem* ItemToAdd = ItemTable->FindRow<FInventoryItem>(givenID, "");
	health = ItemToAdd->health;
	damage = ItemToAdd->damage;
	armor = ItemToAdd->armor;
	mana = ItemToAdd->mana;
	name = ItemToAdd->Name;
}

// Called every frame

