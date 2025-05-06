// Copyright Epic Games, Inc. All Rights Reserved.

#include "DavisFirstperson415PickUpComponent.h"

UDavisFirstperson415PickUpComponent::UDavisFirstperson415PickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UDavisFirstperson415PickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UDavisFirstperson415PickUpComponent::OnSphereBeginOverlap);
}

void UDavisFirstperson415PickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	ADavisFirstperson415Character* Character = Cast<ADavisFirstperson415Character>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
