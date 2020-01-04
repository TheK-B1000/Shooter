// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SetViewTargetBlend.generated.h"

UCLASS()
class UNITEDPLANETS_API ASetViewTargetBlend : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASetViewTargetBlend();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Aim Down Camera*/
	UFUNCTION(BlueprintCallable, Category = Shooter)
		void AimDown();

	/** Stop Aiming Down*/
	UFUNCTION(BlueprintCallable, Category = Shooter)
		void StopAiming();

	// Declare Gun Actor
	UPROPERTY(EditAnywhere)
		AActor* Gun;
};
