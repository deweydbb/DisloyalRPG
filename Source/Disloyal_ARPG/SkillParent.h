// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillParent.generated.h"

UCLASS()
class DISLOYAL_ARPG_API ASkillParent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillParent();

	int getDamage();

	int getHeal();

	int getArmor();

	int getDuration();

	int getMana();

	int getRange();

	int getRadius();

	int setDamage(int n);

	int setHeal(int n);

	int setArmor(int n);

	int setDuration(int n);

	int setMana(int n);

	int setRadius(int n);

	int setRange(int n);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Editanywhere, BlueprintReadWrite)
	UTexture2D* Thumbnail;

	UPROPERTY(Editanywhere, BlueprintReadWrite)
		FName SkillID;

	UPROPERTY(Editanywhere, BlueprintReadWrite)
		int damage;

	UPROPERTY(Editanywhere, BlueprintReadWrite)
		int armor;

	UPROPERTY(Editanywhere, BlueprintReadWrite)
		int heal;

	UPROPERTY(Editanywhere, BlueprintReadWrite)
		int mana;

	UPROPERTY(Editanywhere, BlueprintReadWrite)
		int radius;

	UPROPERTY(Editanywhere, BlueprintReadWrite)
		int duration;

	UPROPERTY(Editanywhere, BlueprintReadWrite)
		int range;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
