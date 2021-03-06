// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UnitedPlanetsCharacter.generated.h"

class UInputComponent;

UCLASS(config=Game)
class AUnitedPlanetsCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AUnitedPlanetsCharacter();

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Shooter)
		class USkeletalMeshComponent* Arms;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Shooter)
		class UChildActorComponent* Gun;

protected:
	virtual void BeginPlay();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Maximum JetPack Rise Speed */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float maxRiseSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shooter")
	TSubclassOf<class AGunParent> GunBlueprint;

private:

	AGunParent* GunParent;

protected:

	/** Override Jump class from ACharacter and creating our own for Jetpack*/
	void Jump() override;

	/**  Override StopJumping class from ACharacter and creating our own for Jetpack */
	void StopJumping() override;

	/**  Check if SpaceBar pressed or released */
	bool bIsSpaceBarDown;

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
};

