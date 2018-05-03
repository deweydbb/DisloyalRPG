// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "NPC_Character.generated.h"

UCLASS()
class DISLOYAL_ARPG_API ANPC_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC_Character();

	UPROPERTY(EditAnywhere, Category = Behavior)
		class UBehaviorTree* BehaviorTree;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
};
