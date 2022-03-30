// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Torei.generated.h"

class UBoxComponent;
class IInteractionInterface;
UCLASS()
class THETORNTALE_API ATorei : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATorei();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Landed(const FHitResult& Hit) override;

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
