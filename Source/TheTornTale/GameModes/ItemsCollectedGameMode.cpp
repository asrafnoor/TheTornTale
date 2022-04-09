// Fill out your copyright notice in the Description page of Project Settings.


#include "TheTornTale/GameModes/ItemsCollectedGameMode.h"
#include "EngineUtils.h"
#include "TheTornTale/InteractiveObjects/PickUpSilverCoin.h"

void AItemsCollectedGameMode::CompletedTask(AActor* CompletedTask)
{
	for (APickUpSilverCoin* CollectItems : TActorRange<APickUpSilverCoin>(GetWorld()))
	{
		int32 totalitems = 4;

	}
}

void AItemsCollectedGameMode::EndGame(bool bIsPlayerWinner)
{
	for (APickUpSilverCoin* CollectItems : TActorRange<APickUpSilverCoin>(GetWorld()))
	{
		bool bIsCollectItems = CollectItems->IsA(UBlueprint::GetBlueprintClass);
		if (bIsCollectItems)
		{
			
		}
	}
}
