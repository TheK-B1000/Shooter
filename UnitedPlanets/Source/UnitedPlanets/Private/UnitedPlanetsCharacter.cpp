// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UnitedPlanetsCharacter.h"
#include "UnitedPlanetsProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "GunParent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AUnitedPlanetsCharacter

AUnitedPlanetsCharacter::AUnitedPlanetsCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Set child actor
	Gun = CreateDefaultSubobject<UChildActorComponent>(TEXT("Gun"));
	Gun->SetupAttachment(GetMesh());

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create Arms Skeletal Mesh Componenet
	Arms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arms"));
	Arms->SetupAttachment(FirstPersonCameraComponent);
	Arms->bCastDynamicShadow = false;
	Arms->CastShadow = false;
	Arms->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Arms->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);


	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P are set in the
	// derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void AUnitedPlanetsCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	if (GunBlueprint == NULL) {
		UE_LOG(LogTemp, Warning, TEXT("Gun blueprint missing."));
		return;
	}

	GunParent = GetWorld()->SpawnActor<AGunParent>(GunBlueprint);
	GunParent->AttachToComponent(Arms, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint")); //Attach gun mesh component to Skeleton, doing it here because the skelton is not yet created in the constructor
	GunParent->AnimInstance = Arms->GetAnimInstance();

	InputComponent->BindAction("Fire", IE_Pressed, GunParent, &AGunParent::OnFire);
	InputComponent->BindAction("Reload", IE_Pressed, GunParent, &AGunParent::ReloadGun);
	InputComponent->BindAction("AimDown", IE_Pressed, GunParent, &AGunParent::SwitchSights);
	InputComponent->BindAction("AimDown", IE_Released, GunParent, &AGunParent::SwitchBack);

	}

//////////////////////////////////////////////////////////////////////////
// Input

void AUnitedPlanetsCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AUnitedPlanetsCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUnitedPlanetsCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AUnitedPlanetsCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AUnitedPlanetsCharacter::LookUpAtRate);
}

void AUnitedPlanetsCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AUnitedPlanetsCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AUnitedPlanetsCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AUnitedPlanetsCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

