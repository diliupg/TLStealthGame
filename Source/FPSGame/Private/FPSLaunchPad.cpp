// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSLaunchPad.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSLaunchPad::AFPSLaunchPad()
{
	OverlapComp = CreateDefaultSubobject<UBoxComponent>( TEXT( "OverlapComp" ) );
	OverlapComp->SetBoxExtent( FVector( 75.f, 75.f, 50.f ) );
	RootComponent = OverlapComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "MeshComp" ) );
	MeshComp->SetupAttachment( RootComponent );

	// Bind to event  
	OverlapComp->OnComponentBeginOverlap.AddDynamic( this, &AFPSLaunchPad::OverlapLaunchpad );

	LaunchStrength = 1500;
	LaunchPitchAngle = 35.f;
}

void AFPSLaunchPad::OverlapLaunchpad( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult )
{
	FRotator LaunchDirection = GetActorRotation( );
	LaunchDirection.Pitch += LaunchPitchAngle;
	FVector LaunchVelocity = LaunchDirection.Vector( ) * LaunchStrength;

	ACharacter* OtherCharacter = Cast<ACharacter>( OtherActor );
	if ( OtherCharacter )
	{
		// Launch Player. Booleans give consistent Launch velocity by ignoring the current player velocity
		OtherCharacter->LaunchCharacter( LaunchVelocity, true, true );

		//spawn FX
		UGameplayStatics::SpawnEmitterAtLocation( GetWorld( ), ActivateLaunchpadEffect, GetActorLocation( ) );
	}
	// not the player does it have Physics simulation? if so launch!
	else if ( OtherComp && OtherComp->IsSimulatingPhysics( ) )
	{
		OtherComp->AddImpulse( LaunchVelocity, NAME_None, true );

		//spawn FX
		UGameplayStatics::SpawnEmitterAtLocation( GetWorld( ), ActivateLaunchpadEffect, GetActorLocation( ) );
	}
}

