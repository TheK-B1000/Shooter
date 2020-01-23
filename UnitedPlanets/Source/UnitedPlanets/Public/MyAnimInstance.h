// K-B Enterprises

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNITEDPLANETS_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	/*Holds a reference to the character's movement forward or backwards*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		float MovementForward;

	/*Holds a reference to the character's movement right or left*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		float MovementRight;

	/*Holds a reference to the character's movement speed*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		float MovementSpeed;

	/*The attack montage*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UAnimMontage* MeleeAttackMontage;

	/*Updates the Movement Speed variable*/
	UFUNCTION(BlueprintCallable, Category = "AnimationUpdates")
		void UpdateMovementSpeed();

	/*True if the character can perform a second attack*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bAcceptsSecondAttackInput;

	/*Ture if the character can perform a third attack*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bAcceptsThirdAttackInput;

public:
	/*Determines which attack animation will be played*/
	void Attack();

	/*Determines which deflect animation will be played*/
	void Block();

};