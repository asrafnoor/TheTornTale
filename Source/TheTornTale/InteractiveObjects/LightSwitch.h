// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TheTornTale/InteractionInterface.h"
#include "Components/PointLightComponent.h"
#include "LightSwitch.generated.h"

class UWidgetComponent;
UCLASS()
class THETORNTALE_API ALightSwitch : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightSwitch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void InteractWithMe() override;
	virtual void ShowInteractionWidget() override;
	virtual void HideInteractionWidget() override;

private:
	//Visual Representation in Scene components
	UPROPERTY(EditAnywhere)
		USceneComponent* _RootComponent;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* LightSwitchMesh;

	UPROPERTY(EditAnywhere)
		UPointLightComponent* WallLamp;

	UPROPERTY(EditAnywhere)
		UWidgetComponent* InteractionWidget;

	bool bIsLightOn = false;

	
};
