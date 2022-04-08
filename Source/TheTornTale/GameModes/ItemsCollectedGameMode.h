// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheTornTale/TheTornTaleGameModeBase.h"
#include "ItemsCollectedGameMode.generated.h"

/**
 * 
 */
UCLASS()
class THETORNTALE_API AItemsCollectedGameMode : public ATheTornTaleGameModeBase
{
	GENERATED_BODY()

public:
	virtual void CompletedTask(AActor* CompletedTask) override;

private:
	void EndGame(bool bIsPlayerWinner);
};
