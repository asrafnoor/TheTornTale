// Fill out your copyright notice in the Description page of Project Settings.


#include "TheTornTale/InteractiveObjects/PickUpItem.h"

// Sets default values
APickUpItem::APickUpItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(RootComponent);

	RotationRate = FRotator(0, 180, 0);

	Speed = 1.0f;

}

// Called when the game starts or when spawned
void APickUpItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUpItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(RotationRate * DeltaTime * Speed);

}

