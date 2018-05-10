// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#include "Disloyal_ARPGPlayerController.h"
#include "Item.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Disloyal_ARPGCharacter.h"

ADisloyal_ARPGPlayerController::ADisloyal_ARPGPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ADisloyal_ARPGPlayerController::InteractStart()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		//cast the thing hit to a string ofr printing

		actorHit = Hit.GetActor();

		if (actorHit->IsA(AItem::StaticClass())) {
			//go to player and cal pickup item on player
			if (ADisloyal_ARPGCharacter* MyPawn = Cast<ADisloyal_ARPGCharacter>(GetPawn())) {
				//tell player to call the titems pickup() fucntion
				MyPawn->pickupItem(Cast<AItem>(actorHit));				
			}
			
		}
	}
}

AActor* ADisloyal_ARPGPlayerController::GetMousedOverPawn()
{
	InteractStart();
	if (actorHit) {
		return actorHit;
	}
	else {
		return NULL;
	}
}



void ADisloyal_ARPGPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void ADisloyal_ARPGPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ADisloyal_ARPGPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ADisloyal_ARPGPlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ADisloyal_ARPGPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ADisloyal_ARPGPlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &ADisloyal_ARPGPlayerController::OnResetVR);
	InputComponent->BindAction("Interact", IE_Pressed, this, &ADisloyal_ARPGPlayerController::InteractStart);

}

void ADisloyal_ARPGPlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}
//when player clicks somehwere
void ADisloyal_ARPGPlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (ADisloyal_ARPGCharacter* MyPawn = Cast<ADisloyal_ARPGCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UNavigationSystem::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void ADisloyal_ARPGPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ADisloyal_ARPGPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ADisloyal_ARPGPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
	clickOnObject();
}

void ADisloyal_ARPGPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

