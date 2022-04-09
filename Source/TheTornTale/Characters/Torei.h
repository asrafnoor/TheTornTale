// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TheTornTale/InteractiveObjects/PickUpItem.h"
#include "Torei.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInventoryDelegate, APickUpItem*, Item, const TArray<APickUpItem*>&, InventoryItems);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryDelegateSingle, APickUpItem*, Item);

class UBoxComponent;
class IInteractionInterface;
UCLASS()
class THETORNTALE_API ATorei : public ACharacter
{
	GENERATED_BODY()


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void UseItem(FKey key);

public:	
	// Sets default values for this character's properties
	ATorei();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Landed(const FHitResult& Hit) override;

	//Inventory functions

	void AddToInventory(APickUpItem* actor);

	//UFUNCTION(BlueprintCallable)
	//	void UpdateInventory();

	//UFUNCTION(BlueprintCallable)
	//	void DropToActionBar(APickUpItem* pickup, int32 maxItems);

	UFUNCTION(BlueprintCallable)
		void RemoveInventoryItem(APickUpItem* actor);

	UPROPERTY(BlueprintAssignable, Category = "PickUp")
		FInventoryDelegate OnAddInventoryItem;

	UPROPERTY(BlueprintAssignable, Category = "PickUp")
		FInventoryDelegate OnRemoveInventoryItem;

	UPROPERTY(BlueprintAssignable, Category = "PickUp")
		FInventoryDelegate OnCollectInventoryItem;

	UPROPERTY(BlueprintAssignable, Category = "PickUp")
		FInventoryDelegateSingle OnUseInventoryItem;

private:
	UPROPERTY(EditAnyWhere)
	float RotationRate = 10;
	UPROPERTY()
	bool Jumping;
	UPROPERTY()
		int jumpCount;
	UPROPERTY()
	bool FirstPerson;
	UPROPERTY()
		float speed;
	UPROPERTY()
		bool walking;
	UPROPERTY(EditAnywhere)
		int launchValueZ = 500;
	UPROPERTY(EditAnywhere)
		UBoxComponent* InteractionBox;

	//Lists
	//TArray<APickUpItem*> inventory;

	TArray<APickUpItem*> actionbar;


	/*UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OveralappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnBoxEndOverlap(UPrimitiveComponent* OveralappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);*/

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);

	void CheckJump();
	void crouch();
	void Sprint();
	
	void Interacting();
	
	IInteractionInterface* Interface = nullptr;

};
