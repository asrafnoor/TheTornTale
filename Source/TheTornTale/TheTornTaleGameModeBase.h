// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TheTornTaleGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class THETORNTALE_API ATheTornTaleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void CompletedTask(AActor* CompletedTask);
	
};
