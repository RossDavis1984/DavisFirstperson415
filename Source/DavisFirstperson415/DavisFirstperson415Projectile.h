// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DavisFirstperson415Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS(config=Game)
class ADavisFirstperson415Projectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	//Reference to our staticMesh ballMesh
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ballMesh;

	//Reference to Umaterial baseMat
	UPROPERTY(EditAnywhere)
	UMaterial* baseMat;

	//calls random color
	UPROPERTY()
	FLinearColor randColor;

	//set up Projectile material
	UPROPERTY(EditAnywhere)
	UMaterialInterface* projMat;

	//set up dynamic material instance dmiMat
	UPROPERTY()
	UMaterialInstanceDynamic* dmiMat;

public:
	ADavisFirstperson415Projectile();
	
	//Called when projectile is spawned
protected:	
	virtual void BeginPlay();

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};

