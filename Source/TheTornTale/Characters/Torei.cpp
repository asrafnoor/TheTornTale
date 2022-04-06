// Fill out your copyright notice in the Description page of Project Settings.


#include "TheTornTale/Characters/Torei.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"
#include "TheTornTale/InteractionInterface.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/InputSettings.h"
#include "Components/InputComponent.h"


// Sets default values
ATorei::ATorei()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Jumping = false;
	jumpCount = 0;
	
	speed = 0.5f;
	walking = true;

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Box"));
	InteractionBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATorei::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* playerController = Cast<APlayerController>(GetController());
	if (playerController)
	{
		playerController->bShowMouseCursor = true;
		playerController->bEnableClickEvents = true;
		playerController->bEnableMouseOverEvents = true;
	}

	//Adjust Overlap object inside the Interaction Box Component
	/*InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &ATorei::OnBoxBeginOverlap);
	InteractionBox->OnComponentEndOverlap.AddDynamic(this, &ATorei::OnBoxEndOverlap);*/

}

// Called every frame
void ATorei::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Jumping)
	{
		Jump();
	}

	TArray<AActor*> OverlappingActors;

	InteractionBox->GetOverlappingActors(OverlappingActors);

	if (OverlappingActors.Num() == 0)
	{
		if (Interface)
		{
			Interface->HideInteractionWidget();
			Interface = nullptr;
		}
		return;
	}

	AActor* ClosestActor = OverlappingActors[0];

	for (auto CurrentActor : OverlappingActors)
	{
		if (GetDistanceTo(CurrentActor) < GetDistanceTo(ClosestActor))
		{
			ClosestActor = CurrentActor;
		}
	}

	if (Interface)
	{
		Interface->HideInteractionWidget();
	}

	Interface = Cast<IInteractionInterface>(ClosestActor);

	if (Interface)
	{
		Interface->ShowInteractionWidget();
	}


}

// Called to bind functionality to input
void ATorei::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &ATorei::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &ATorei::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &ATorei::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &ATorei::LookRightRate);


	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ATorei::CheckJump);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Released, this, &ATorei::CheckJump);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Pressed, this, &ATorei::Sprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Released, this, &ATorei::Sprint);
	PlayerInputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Pressed, this, &ATorei::Interacting);
	PlayerInputComponent->BindAction(TEXT("UseItem"), EInputEvent::IE_Pressed, this, &ATorei::UseItem);
}

void ATorei::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	
	jumpCount = 0;
}

void ATorei::Sprint()
{
	walking = !walking;
	if (walking)
	{
		speed = 0.5f;
	}
	else
	{
		speed = 1;
	}
}

void ATorei::CheckJump()
{
	if (Jumping)
	{
		Jumping = false;
	}
	else
	{
		Jumping = true;
		jumpCount++;
		if (jumpCount == 2)
		{
			LaunchCharacter(FVector(0, 0, launchValueZ), false, true);
		}
	}
}

// WIDGET TOGGLE ON/OFF without selecting nearest
//void ATorei::OnBoxBeginOverlap(UPrimitiveComponent* OveralappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	Interface = Cast<IInteractionInterface>(OtherActor);
//
//	if (Interface)
//	{
//		Interface->ShowInteractionWidget();
//	}
//}
//
//void ATorei::OnBoxEndOverlap(UPrimitiveComponent* OveralappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	if (Interface)
//	{
//		Interface->HideInteractionWidget();
//		Interface = nullptr;
//	}
//}

void ATorei::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue * speed);
}


void ATorei::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void ATorei::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void ATorei::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void ATorei::crouch()
{

}

void ATorei::Interacting()
{
	if (Interface)
	{
		Interface->InteractWithMe();
	}
}

void ATorei::AddToInventory(APickUpItem* actor)
{
	actionbar.Add(actor);

	OnAddInventoryItem.Broadcast(actor, actionbar);
}

void ATorei::RemoveInventoryItem(APickUpItem* actor)
{
	if (actor != nullptr)
	{
		if (actionbar.Remove(actor) > 0)
		{
			OnRemoveInventoryItem.Broadcast(actor, actionbar);
		}
	}
}

//void ATorei::UpdateInventory()
//{
//	/*FString sInventory = "";
//
//	for (APickUpItem* actor : inventory)
//	{
//		sInventory.Append(actor->Name);
//		sInventory.Append(" | ");
//	}
//
//	GEngine->AddOnScreenDebugMessage(1, 3, FColor::White, *sInventory);*/
//
//	//Call UpdateEvent
//	OnUpdateInventory.Broadcast(inventory);
//}

//void ATorei::DropToActionBar(APickUpItem* pickup, int32 maxItems)
//{
//	//Check if Action Bar is full
//	if (actionbar.Num() == maxItems)
//	{
//		return;
//	}
//
//	// Remove item from inventory and add to actionbar
//	inventory.Remove(pickup);
//	actionbar.Add(pickup);
//
//	OnUpdateActionBar.Broadcast(actionbar);
//}

void ATorei::UseItem(FKey key)
{
	//FText name = key.GetDisplayName(false);
	//int32 number = FCString::Atoi(*name.ToString());

	//if (number >= 1 && number <= actionbar.Num())
	//{
	//	auto selected_item = actionbar[number - 1];

	//	for (auto actor : actionbar)
	//	{
	//		actor->InUse = false;
	//	}
	//	selected_item->InUse = true;

	//	OnUseInventoryItem.Broadcast(selected_item);
	//}
}

