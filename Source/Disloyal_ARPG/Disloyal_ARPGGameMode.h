// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Disloyal_ARPGGameMode.generated.h"

UCLASS(minimalapi)
class ADisloyal_ARPGGameMode : public AGameModeBase
{
	GENERATED_BODY()

	
public:
	ADisloyal_ARPGGameMode();

	class UDataTable* GetItemDB() const { return ItemDB; }

	class UDataTable* GetEquipedItemDB() const { return ItemDB; }

	class UDataTable* GetSkillHandlerDB() const { return SkillHandlerDB; }
protected:
	UPROPERTY(EditDefaultsOnly)
		class UDataTable* ItemDB;

	UPROPERTY(EditDefaultsOnly)
		class UDataTable* EquipedItemDB;

	UPROPERTY(EditDefaultsOnly)
		class UDataTable* SkillHandlerDB;
};



