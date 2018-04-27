// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillParent.h"
#include "Disloyal_ARPG.h"
#include <string>
#include "Net/UnrealNetwork.h"
#include "Item.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"


// Sets default values
ASkillParent::ASkillParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(230.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Skill");
	CollisionComp->OnComponentHit.AddDynamic(this, &ASkillParent::OnHit);
	//for skill overlap
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ASkillParent::BeginComponentOverlap);

	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &ASkillParent::EndComponentOverlap);

	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	//set Root
	RootComponent = CollisionComp;

	//movement component controls
	SkillMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("SkillMoveComp"));
	SkillMovement->UpdatedComponent = CollisionComp;
	SkillMovement->InitialSpeed = 10.f;
	SkillMovement->MaxSpeed = 500.f;
	SkillMovement->bRotationFollowsVelocity = true;
	SkillMovement->bShouldBounce = false;

	//use to change duration
	InitialLifeSpan = 10.0f;

}

// Called when the game starts or when spawned

// Called every frame
void ASkillParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASkillParent::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{


}

void ASkillParent::BeginComponentOverlap(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 inter, bool booler, const FHitResult & Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("We Started"));
}

void ASkillParent::EndComponentOverlap(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 inter)
{

}

int ASkillParent::getDamage()
{
	return damage;
}

int ASkillParent::getHeal()
{
	return heal;
}

int ASkillParent::getArmor()
{
	return armor;
}

int ASkillParent::getDuration()
{
	return duration;
}

int ASkillParent::getMana()
{
	return mana;
}

int ASkillParent::getRange()
{
	return 0;
}

int ASkillParent::getRadius()
{
	return 0;
}

int ASkillParent::setDamage(int n)
{
	damage = n;
	return damage;
}

int ASkillParent::setHeal(int n)
{
	heal = n;
	return heal;
}

int ASkillParent::setArmor(int n)
{
	armor = n;
	return armor;
}

int ASkillParent::setDuration(int n)
{
	duration = n;
	return duration;
}

int ASkillParent::setMana(int n)
{
	mana = n;
	return mana;
}

int ASkillParent::setRadius(int n)
{
	radius = n;
	return radius;
}

int ASkillParent::setRange(int n)
{
	range = n;
	return range;
}
