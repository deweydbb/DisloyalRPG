// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC_Parent.h"
#include "NPC_Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"

ANPC_Parent::ANPC_Parent()
{
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(FName("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(FName("BlackboardComp"));
}

void ANPC_Parent::Possess(APawn * Pawn)
{
	Super::Possess(Pawn);

	ANPC_Character* AICharacter = Cast<ANPC_Character>(Pawn);

	if (AICharacter) {
		if (AICharacter->BehaviorTree->BlackboardAsset) {
			BlackboardComp->InitializeBlackboard(*(AICharacter->BehaviorTree->BlackboardAsset));
			BehaviorComp->StartTree(*AICharacter->BehaviorTree);
		}
	}
}

void ANPC_Parent::SetPlayerToFollow(APawn * Pawn)
{
	if (BlackboardComp) {
		BlackboardComp->SetValueAsObject(FName("PlayerToFollow"), Pawn);
	}
}
