// K-B Enterprises

#include "GunParent.h"
#include "GunParentProjectile.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "UnitedPlanetsCharacter.h"
#include "Components/ArrowComponent.h"
#include "SetViewTargetBlend.h"




// Sets default values
AGunParent::AGunParent()
{
	// Create Guns Skeletal Mesh Component
	Guns = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Guns->bCastDynamicShadow = false;
	Guns->CastShadow = false;

	// Create Barrel_refpoint Scene Componenet
	Barrel_refpoint = CreateDefaultSubobject<USceneComponent>(TEXT("Socket"));
	Barrel_refpoint->SetupAttachment(Guns);
	Barrel_refpoint->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Create GunSight Camera Componenet
	GunSight = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	GunSight->SetupAttachment(Guns);
	GunSight->SetRelativeLocation(FVector(0.35f, 30.0f, 22.0f)); // Position the camera
	GunSight->bUsePawnControlRotation = true;

	// Create Arrow Component
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Guns);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

		// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 30.0f, 10.0f);
}

// Called when the game starts or when spawned
void AGunParent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGunParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGunParent::OnFire()
{
	if(AmmoCurrent >= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Firing"));
		// try and fire a projectile
		if (ProjectileClass != NULL)
		{

			UWorld* const World = GetWorld();
			if (World != NULL)
			{
				const FRotator SpawnRotation = Barrel_refpoint->GetComponentRotation();
				const FVector SpawnLocation = Barrel_refpoint->GetComponentLocation();

				// Spawn the projectile at the Barrel
				World->SpawnActor<AGunParentProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
				UE_LOG(LogTemp, Warning, TEXT("Spawn Projectile"));
			}
		}

		// try and play the sound if specified
		if (FireSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}

		// try and play a firing animation if specified
		if (FireAnimation != NULL)
		{
			// Get the animation object for the arms mesh
			if (AnimInstance != NULL)
			{
				AnimInstance->Montage_Play(FireAnimation, 1.f);
			}
		}
	}
}

void AGunParent::ReloadGun()
{
	UE_LOG(LogTemp, Warning, TEXT("Reload"));


	BulletDifference = ClipSize - AmmoCurrent;
	if(AmmoMax >= BulletDifference)
	{
		AmmoCurrent = ClipSize;
		AmmoMax = AmmoMax - BulletDifference;
	}
	else
	{
		AmmoCurrent = AmmoCurrent + AmmoMax;
		AmmoMax = 0;
	}

}

void AGunParent::SwitchSights()
{
	GetWorld()->SpawnActor<ASetViewTargetBlend>()->AimDown();
	UE_LOG(LogTemp, Warning, TEXT("Aiming Down Sights"));
}

void AGunParent::SwitchBack()
{
	GetWorld()->SpawnActor<ASetViewTargetBlend>()->StopAiming();
	UE_LOG(LogTemp, Warning, TEXT("Aiming Hip Fire"));
}



