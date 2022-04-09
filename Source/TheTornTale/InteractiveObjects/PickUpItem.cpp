// Fill out your copyright notice in the Description page of Project Settings.


#include "TheTornTale/InteractiveObjects/PickUpItem.h"
#include "Components/WidgetComponent.h"
#include "TheTornTale/Characters/Torei.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APickUpItem::APickUpItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(RootComponent);

	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interaction Widget"));
	InteractionWidget->SetupAttachment(RootComponent);

	RotationRate = FRotator(0, 180, 0);

	Speed = 1.0f;

}

// Called when the game starts or when spawned
void APickUpItem::BeginPlay()
{
	Super::BeginPlay();
	InteractionWidget->SetVisibility(false);
	
}

void APickUpItem::Show(bool visible)
{
	ECollisionEnabled::Type collision = visible ?
		ECollisionEnabled::QueryAndPhysics :
		ECollisionEnabled::NoCollision;

	SetActorTickEnabled(visible);

	ItemMesh->SetVisibility(visible);
	ItemMesh->SetCollisionEnabled(collision);
}

// Called every frame
void APickUpItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(RotationRate * DeltaTime * Speed);

}

void APickUpItem::InteractWithMe()
{
	FString pickUp = FString::Printf(TEXT("Picked up: %s"), *Name);

	//Hide Item and Add it to Inventory
	ATorei* player = Cast<ATorei>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (player)
	{
		Show(false);

		player->AddToInventory(this);
	}

	GEngine->AddOnScreenDebugMessage(1, 3, FColor::Red, pickUp);

	//Destroy();
}

void APickUpItem::ShowInteractionWidget()
{
	InteractionWidget->SetVisibility(true);
}

void APickUpItem::HideInteractionWidget()
{
	InteractionWidget->SetVisibility(false);
}

