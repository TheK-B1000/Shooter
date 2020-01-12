// K-B Enterprises


#include "MyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMyAnimInstance::UpdateMovementSpeed()

{
	//Get the pawn and if it's valid, update the movement speed to update
	//the movement animation
	APawn* Pawn = TryGetPawnOwner();

	if (Pawn)
	{
		MovementSpeed = Pawn->GetVelocity().Size();
	}
}

void UMyAnimInstance::Attack()
{
	GLog->Log("//TODO attack moves");
}

void UMyAnimInstance::Block()
{
	GLog->Log("//TODO block moves");
}