// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillParent.h"


// Sets default values
ASkillParent::ASkillParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkillParent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkillParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int ASkillParent::getDamage()
{
	return damage;
}

int ASkillParent::getHeal()
{
	return heal;
}

int ASkillParent::getArmor()
{
	return armor;
}

int ASkillParent::getDuration()
{
	return duration;
}

int ASkillParent::getMana()
{
	return mana;
}

int ASkillParent::getRange()
{
	return 0;
}

int ASkillParent::getRadius()
{
	return 0;
}

int ASkillParent::setDamage(int n)
{
	damage = n;
	return damage;
}

int ASkillParent::setHeal(int n)
{
	heal = n;
	return heal;
}

int ASkillParent::setArmor(int n)
{
	armor = n;
	return armor;
}

int ASkillParent::setDuration(int n)
{
	duration = n;
	return duration;
}

int ASkillParent::setMana(int n)
{
	mana = n;
	return mana;
}

int ASkillParent::setRadius(int n)
{
	radius = n;
	return radius;
}

int ASkillParent::setRange(int n)
{
	range = n;
	return range;
}
