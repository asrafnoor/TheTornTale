// Fill out your copyright notice in the Description page of Project Settings.


#include "TheTornTale/InteractiveObjects/LightSwitch.h"
#include "Components/WidgetComponent.h"

// Sets default values
ALightSwitch::ALightSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = _RootComponent;

	LightSwitchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Light Switch Mesh"));
	LightSwitchMesh->SetupAttachment(RootComponent);

	WallLamp = CreateDefaultSubobject<UPointLightComponent>(TEXT("Wall Lamp Bulb"));
	WallLamp->SetupAttachment(RootComponent);

	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interaction Widget"));
	InteractionWidget->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ALightSwitch::BeginPlay()
{
	Super::BeginPlay();
	WallLamp->SetIntensity(0);
	InteractionWidget->SetVisibility(false);
	
}

// Called every frame
void ALightSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALightSwitch::InteractWithMe()
{
	UE_LOG(LogTemp, Warning, TEXT("You have interacted with me!"));
	if (bIsLightOn)
	{
		WallLamp->SetIntensity(0);
		bIsLightOn = false;
	}
	else
	{
		WallLamp->SetIntensity(10000);
		bIsLightOn = true;
	}
}

void ALightSwitch::ShowInteractionWidget()
{
	InteractionWidget->SetVisibility(true);
}

void ALightSwitch::HideInteractionWidget()
{
	InteractionWidget->SetVisibility(false);
}

