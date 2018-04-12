// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Character.h"

/**
 * 
 */
class DISLOYAL_ARPG_API AbilityParent
{
public:
	AbilityParent();

	int getDamage();

	int getHeal();

	int getArmor();

	int getDuration();

	int setDamage(int n);

	int setHeal(int n);

	int setArmor(int n);

	int setDuration(int n);


private:
	int damage;

	int heal;

	UTexture2D* Thumbnail;

	int armor;

	int duration;

};
