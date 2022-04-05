// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TheTornTale/InteractionInterface.h"
#include "PickUpItem.generated.h"

class UWidgetComponent;
UCLASS()
class THETORNTALE_API APickUpItem : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Show(bool visible);

public:	
	// Sets default values for this actor's properties
	APickUpItem();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp")
		FRotator RotationRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp")
		float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp")
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp")
		UTexture2D* Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp")
		USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp")
		UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp")
		UWidgetComponent* InteractionWidget;

	UFUNCTION()
		virtual void InteractWithMe() override;

	virtual void ShowInteractionWidget() override;
	virtual void HideInteractionWidget() override;

private:

};
