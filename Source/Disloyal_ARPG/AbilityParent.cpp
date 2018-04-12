// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityParent.h"

AbilityParent::AbilityParent()
{
	damage = 0;
	heal = 0;
	armor = 0;
	duration = 0;
}

int AbilityParent::getDamage()
{
	return damage;
}

int AbilityParent::getHeal()
{
	return heal;
}

int AbilityParent::getArmor()
{
	return armor;
}

int AbilityParent::getDuration()
{
	return duration;
}

int AbilityParent::setDamage(int n)
{
	damage += n;
	return damage;
}

int AbilityParent::setHeal(int n)
{
	heal += n;
	return heal;
}

int AbilityParent::setArmor(int n)
{
	armor += n;
	return armor;
}

int AbilityParent::setDuration(int n)
{
	duration += n;
	return duration;
}
