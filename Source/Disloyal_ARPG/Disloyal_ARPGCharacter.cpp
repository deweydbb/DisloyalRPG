// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Disloyal_ARPGCharacter.h"
#include"Disloyal_ARPGGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "AI/Navigation/NavigationSystem.h"
#include "SkillParent.h"
#include "NPC_Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Item.h"

ADisloyal_ARPGCharacter::ADisloyal_ARPGCharacter()
{
	time = 0.f;
	PreviousID = "";
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	maxHealth = 100;
}

void ADisloyal_ARPGCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if (CursorToWorld != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = TopDownCameraComponent->GetComponentLocation();
				FVector EndLocation = TopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}

void ADisloyal_ARPGCharacter::pickupItem(AItem * selectedItem)
{
	FVector loc = selectedItem->GetActorLocation();
	if (loc.Dist(this->GetActorLocation(), loc) < 600) {
		AddItemToInventoryById(selectedItem->ID);
		//AddToInv(selectedItem);
		selectedItem->pickUp();
		
		
	}
}

void ADisloyal_ARPGCharacter::createSkill(FName id)
{
	ADisloyal_ARPGGameMode* GameMode = Cast<ADisloyal_ARPGGameMode>(GetWorld()->GetAuthGameMode());
	UDataTable* ItemTable = GameMode->GetSkillHandlerDB();

	FSkillHandler* ItemToAdd = ItemTable->FindRow<FSkillHandler>(id, "");

	if (ItemToAdd) {
		if (ItemToAdd->type == 0) {

			UWorld* const World = GetWorld();

			FHitResult Hit;

			APlayerController* PC = Cast<APlayerController>(GetController());

			PC->GetHitResultUnderCursor(ECC_Visibility, false, Hit);

			FVector SkillLoc = Hit.ImpactPoint;

			FRotator SpawnRotation = FRotator(0, 0, 0);
			bool bNoCollisionFail = true;
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = bNoCollisionFail ? ESpawnActorCollisionHandlingMethod::AlwaysSpawn : ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			
			ASkillParent* Skill = World->SpawnActor<ASkillParent>(ItemToAdd->skill, mousePosition, SpawnRotation, ActorSpawnParams);
			Skill->SkillID = ItemToAdd->SkillID;
			//UE_LOG(LogTemp, Warning, TEXT("Skillcreated"));
		}

		if (ItemToAdd->type == 1) {
			UWorld* const World = GetWorld();

			FHitResult Hit;

			
			

			if (id == PreviousID) {
				if (UGameplayStatics::GetRealTimeSeconds(GetWorld()) - time > (ItemToAdd->duration)) {
					APlayerController* PC = Cast<APlayerController>(GetController());

					PC->GetHitResultUnderCursor(ECC_Visibility, false, Hit);

					AActor* HitActor = Hit.GetActor();

					if (HitActor->IsA(ANPC_Character::StaticClass())) {
						ANPC_Character* HitAI = Cast<ANPC_Character>(HitActor);

						HitAI->health = HitAI->health - (ItemToAdd->damage - ItemToAdd->armor * 0.2);
						PreviousID = id;
						time = UGameplayStatics::GetRealTimeSeconds(GetWorld());
					}
				}
			}
			else {
				APlayerController* PC = Cast<APlayerController>(GetController());

				PC->GetHitResultUnderCursor(ECC_Visibility, false, Hit);

				AActor* HitActor = Hit.GetActor();

				if (HitActor->IsA(ANPC_Character::StaticClass())) {
					ANPC_Character* HitAI = Cast<ANPC_Character>(HitActor);

					HitAI->health = HitAI->health - (ItemToAdd->damage - ItemToAdd->armor * 0.2);
					PreviousID = id;
					time = UGameplayStatics::GetRealTimeSeconds(GetWorld());
				}
			}					
		}
		if (ItemToAdd->type == 2) {
			UWorld* const World = GetWorld();

			FHitResult Hit;

			APlayerController* PC = Cast<APlayerController>(GetController());
			

			PC->GetHitResultUnderCursor(ECC_Visibility, false, Hit);

			FVector SkillLoc = Hit.ImpactPoint;

			FVector playerPosition = GetMesh()->GetSocketLocation("SpawnSkillShot");;

			FRotator SpawnRotation = GetActorRotation();
			bool bNoCollisionFail = true;
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = bNoCollisionFail ? ESpawnActorCollisionHandlingMethod::AlwaysSpawn : ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			ASkillParent* Skill = World->SpawnActor<ASkillParent>(ItemToAdd->skill, playerPosition, SpawnRotation, ActorSpawnParams);
			Skill->SkillID = ItemToAdd->SkillID;
			//UE_LOG(LogTemp, Warning, TEXT("Skillcreated"));
		}
	}
}


void ADisloyal_ARPGCharacter::AddItemToInventoryById(FName ID)
{
	ADisloyal_ARPGGameMode* GameMode = Cast<ADisloyal_ARPGGameMode>(GetWorld()->GetAuthGameMode());
	UDataTable* ItemTable = GameMode->GetItemDB();

	FInventoryItem* ItemToAdd = ItemTable->FindRow<FInventoryItem>(ID, "");

	if (ItemToAdd) {
		InventoryDBArray.Add(*ItemToAdd);
	}
}

