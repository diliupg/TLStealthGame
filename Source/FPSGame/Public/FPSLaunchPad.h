// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSLaunchPad.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UArrowComponent;

UCLASS()
class FPSGAME_API AFPSLaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSLaunchPad();

protected:

	UPROPERTY( VisibleAnywhere, Category = Components )
	UStaticMeshComponent* MeshComp;

	UPROPERTY( VisibleAnywhere, Category = Components )
	UBoxComponent* OverlapComp;

	UFUNCTION( )
	void OverlapLaunchpad( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );

	UPROPERTY( EditInstanceOnly, Category = Launchpad )
	float LaunchStrength;

	UPROPERTY( EditInstanceOnly, Category = Launchpad )
	float LaunchPitchAngle;

	UPROPERTY( EditInstanceOnly, Category = Launchpad )
	UParticleSystem* ActivateLaunchpadEffect;

};
