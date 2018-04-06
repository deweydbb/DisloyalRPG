// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Item.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/DataTable.h"
#include "Disloyal_ARPGCharacter.generated.h"

USTRUCT(BlueprintType)
struct FInventoryItem : public FTableRowBase {

	GENERATED_BODY()

public:

	FInventoryItem() {
		Name = FText::FromString("Item");
		Action = FText::FromString("Use");
		Description = FText::FromString("Please enter a description");
		Value = 10;
		//bEquiped = false;
	}
	UPROPERTY(Editanywhere, BlueprintReadWrite)
		FName ItemID;

	UPROPERTY(Editanywhere, BlueprintReadWrite)
		TSubclassOf<class AItem> ItemPickup;

	UPROPERTY(Editanywhere, BlueprintReadWrite)
		FText Name;

	UPROPERTY(Editanywhere, BlueprintReadWrite)
		FText Action;

	UPROPERTY(Editanywhere, BlueprintReadWrite)
		int32 Value;

	UPROPERTY(Editanywhere, BlueprintReadWrite)
		UTexture2D* Thumbnail;

	UPROPERTY(Editanywhere, BlueprintReadWrite)
		FText Description;

	UPROPERTY(Editanywhere, BlueprintReadWrite)
		bool bCanBeUsed;

	//UPROPERTY(Editanywhere, BlueprintReadWrite)
		//bool bEquiped;


	bool operator==(const FInventoryItem & Item) const {
		if (ItemID == Item.ItemID)
			return true;
		else return false;
	}

};

UCLASS(Blueprintable)
class ADisloyal_ARPGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADisloyal_ARPGCharacter();

	//Iventory related variables and functions
	UPROPERTY(BluePrintReadWrite, EditAnywhere)
	TArray<AItem*> Inventory;

	UPROPERTY(BluePrintReadWrite, EditAnywhere)
	TArray<FInventoryItem> Equiped;

	void AddToInv(AItem*);

	void RemoveFromInv(AItem*);

	void AddItemToInventoryById(FName ID);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FInventoryItem> InventoryDBArray;

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }
	//called by player controller when clicked
	void pickupItem(AItem* selectedItem);

	

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;
};



