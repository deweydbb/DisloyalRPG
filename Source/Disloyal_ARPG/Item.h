// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class DISLOYAL_ARPG_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame

	bool IsPickAble;

	void pickUp();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int health;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int damage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int armor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int mana;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName ID;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "OnUsed")
		void used();
	
};
