// K-B Enterprises

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunParent.generated.h"

UCLASS()
class UNITEDPLANETS_API AGunParent : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AGunParent();

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = Shooter)
		class USkeletalMeshComponent* Guns;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = Shooter)
		class USceneComponent* Barrel_refpoint;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Fires a projectile. */
	UFUNCTION(BlueprintCallable, Category = Shooter)
		void OnFire();

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shooter)
		FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AGunParentProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shooter)
		class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shooter)
		class UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimInstance* AnimInstance;

	/** bool to check if is firing */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Shooter)
		bool bIsFiring;

	/** The ammount of ammo in the gun at the current moment */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Shooter)
		int AmmoCurrent = 15;

	/** The maximum ammout of ammo the gun can hold */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Shooter)
		int AmmoMax = 100;

	/** The maximum ammout of ammo the gun clip size can hold */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Shooter)
		int ClipSize = 15;

	/** The fire rate of the gun */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Shooter)
		float FireRate = 0.15f;
};
