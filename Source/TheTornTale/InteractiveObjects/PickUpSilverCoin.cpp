// Fill out your copyright notice in the Description page of Project Settings.


#include "TheTornTale/InteractiveObjects/PickUpSilverCoin.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "TheTornTale/Characters/Torei.h"


//void APickUpSilverCoin::InteractWithMe()
//{
	//FString pickUp = FString::Printf(TEXT("Picked up: %s"), *Name);

	////Hide Item and Add it to Inventory
	//ATorei* player = Cast<ATorei>(UGameplayStatics::GetPlayerCharacter(this, 0));

	//if (player)
	//{
	//	player->AddToInventory(this);
	//}

	//GEngine->AddOnScreenDebugMessage(1, 3, FColor::Red, pickUp);

	//Destroy();
//}

bool APickUpSilverCoin::IsCollected() const
{

	return false;
}
