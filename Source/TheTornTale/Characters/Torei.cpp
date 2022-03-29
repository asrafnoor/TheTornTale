// Fill out your copyright notice in the Description page of Project Settings.


#include "TheTornTale/Characters/Torei.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"
#include "TheTornTale/InteractionInterface.h"

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

	//Adjust Overlap object inside the Interaction Box Component
	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &ATorei::OnBoxBeginOverlap);
}

// Called every frame
void ATorei::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Jumping)
	{
		Jump();
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

void ATorei::OnBoxBeginOverlap(UPrimitiveComponent* OveralappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Interface = Cast<IInteractionInterface>(OtherActor);
	
}

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

