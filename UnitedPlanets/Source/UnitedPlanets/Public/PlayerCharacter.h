// K-B Enterprises

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class UNITEDPLANETS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;

	UPROPERTY(BlueprintReadWrite, Category = AnimationState)
	bool AttackStarted;

	UPROPERTY(BlueprintReadWrite, Category = AnimationState)
	bool BlockStarted;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Handles Attack*/
	void Attack();

	/** Stops Attack Animation*/
	void StopAttackAnimation();

	/** Handles Deflect*/
	void Block();

	/** Override Jump class from ACharacter*/
	void Jump() override;

	/**  Override StopJumping class from ACharacter */
	void StopJumping() override;

	/**  Check if SpaceBar pressed or released */
	bool bIsSpaceBarDown;

	/** Handles moving forward/backward */
	void MoveForward(float Value);

	/** Handles stafing movement, left and right */
	void MoveRight(float Value);

	FTimerHandle AttackTimerHandle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
