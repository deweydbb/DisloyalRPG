// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "NPC_Parent.generated.h"

/**
 * 
 */
UCLASS()
class DISLOYAL_ARPG_API ANPC_Parent : public AAIController
{
	GENERATED_BODY()

public:

	ANPC_Parent();

	virtual void Possess(APawn* Pawn) override;

	void SetPlayerToFollow(APawn* Pawn);

protected:

	UBehaviorTreeComponent* BehaviorComp;
	UBlackboardComponent* BlackboardComp;
	
};
