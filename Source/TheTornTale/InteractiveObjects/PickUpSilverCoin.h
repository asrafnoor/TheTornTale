// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheTornTale/InteractiveObjects/PickUpItem.h"
#include "PickUpSilverCoin.generated.h"

/**
 * 
 */
UCLASS()
class THETORNTALE_API APickUpSilverCoin : public APickUpItem
{
	GENERATED_BODY()

protected:
	

public:
		//virtual void InteractWithMe() override;

	bool IsCollected() const;
};
