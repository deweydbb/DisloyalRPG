// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Item.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Disloyal_ARPGCharacter.h"
#include "Disloyal_ARPGPlayerController.generated.h"

UCLASS()
class ADisloyal_ARPGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADisloyal_ARPGPlayerController();

	UFUNCTION(BlueprintImplementableEvent)
		void clickOnObject();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* actorHit;

	void InteractStart();


protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	
};


