// K-B Enterprises


#include "SetViewTargetBlend.h"
#include "Kismet/GameplayStatics.h"
#include "GunParent.h"
#include "UnitedPlanetsCharacter.h"

// Sets default values
ASetViewTargetBlend::ASetViewTargetBlend()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASetViewTargetBlend::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASetViewTargetBlend::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASetViewTargetBlend::AimDown()
{
	//Find the actor that handles control for the local player.
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);

	//Smoothly transition to our actor on begin play.
	OurPlayerController->SetViewTargetWithBlend(Gun, 0.1f);
}

void ASetViewTargetBlend::StopAiming()
{
	//Find the actor that handles control for the local player.
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);

	//Smoothly transition to our actor on begin play.
	OurPlayerController->SetViewTargetWithBlend(Gun, 0.1f);
}


