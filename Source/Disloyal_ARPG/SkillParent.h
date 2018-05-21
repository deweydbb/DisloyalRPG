// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "GameFramework/Actor.h"
#include "SkillParent.generated.h"

UCLASS(config=Game)
class ASkillParent : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Skill)
		class USphereComponent* CollisionComp;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* SkillMovement;

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

	UFUNCTION(BlueprintCallable, Category = "Skills")
		void inheritVarFromDB(FName id);

	// Called when the game starts or when spawned

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

	UPROPERTY(Editanywhere, BlueprintReadWrite)
		int SkillType;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void BeginComponentOverlap(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 inter, bool booler, const FHitResult & Hit);

	UFUNCTION()
		void EndComponentOverlap(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 inter);

	/** Returns CollisionComp subobject **/
	FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return SkillMovement; }

	
};
