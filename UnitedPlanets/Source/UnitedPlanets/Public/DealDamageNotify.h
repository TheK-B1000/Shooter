// K-B Enterprises

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "DealDamageNotify.generated.h"

/**
 * 
 */
UCLASS()
class UNITEDPLANETS_API UDealDamageNotify : public UAnimNotifyState
{
	GENERATED_BODY()

	bool Received_NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) const;
};
