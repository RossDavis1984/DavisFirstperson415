// Copyright Epic Games, Inc. All Rights Reserved.

#include "DavisFirstperson415Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/KismetMathLibrary.h" // Corrected include path for UKismetMathLibrary
#include "Kismet/GameplayStatics.h"
//including function library to allow us to call the Niagara spawn function
#include "NiagaraFunctionLibrary.h"
//this reference allows us to cast to it 
#include "NiagaraComponent.h"
#include "PerlinProcTerrain.h"

ADavisFirstperson415Projectile::ADavisFirstperson415Projectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ADavisFirstperson415Projectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	ballMesh = CreateDefaultSubobject<UStaticMeshComponent>("Ball Mesh");

	// Set as root component
	RootComponent = CollisionComp;
	// Add attachment to the root component
	ballMesh->SetupAttachment(CollisionComp);


	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void ADavisFirstperson415Projectile::BeginPlay()
{
	Super::BeginPlay();
	//taking randColor variable and setting radnomfloatinrange for XYZ and alpha, 4vector
	randColor = FLinearColor(UKismetMathLibrary::RandomFloatInRange(0.f, 1.f), UKismetMathLibrary::RandomFloatInRange(0.f, 1.f), UKismetMathLibrary::RandomFloatInRange(0.f, 1.f), 1.f);

	dmiMat = UMaterialInstanceDynamic::Create(projMat, this);

	ballMesh->SetMaterial(0, dmiMat);

	dmiMat->SetVectorParameterValue("ProjColor", randColor);
	
}


//On hit function
void ADavisFirstperson415Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // Only add impulse and destroy projectile if we hit a physics
    if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
    {
        OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

        Destroy();
    }

    // If projectile hits something other than a physics object, spawn a decal
    if (OtherActor != nullptr)
    {
        if (colorP)
        {
            UNiagaraComponent* particleComp = UNiagaraFunctionLibrary::SpawnSystemAttached(colorP, HitComp, NAME_None, FVector(-20.f, 0.f, 0.f), FRotator(0.f), EAttachLocation::KeepRelativeOffset, true);
            particleComp->SetNiagaraVariableLinearColor(FString("RandomColor"), randColor);
            ballMesh->DestroyComponent();
            CollisionComp->BodyInstance.SetCollisionProfileName("NoCollision");
        }

        float frameNum = UKismetMathLibrary::RandomFloatInRange(0.f, 3.f); // Random float in range for frame number
        // Create a decal at the hit location
        auto Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), baseMat, FVector(UKismetMathLibrary::RandomFloatInRange(20.f, 40.f)), Hit.Location, Hit.Normal.Rotation(), 0.f);
        // Creating a dynamic material instance
        auto MatInstance = Decal->CreateDynamicMaterialInstance();

        // setting vector parameter values for color and frame
        MatInstance->SetVectorParameterValue("Color", randColor);
		MatInstance->SetScalarParameterValue("FrameNum", frameNum);

		APerlinProcTerrain* procTerrain = Cast<APerlinProcTerrain>(OtherActor);
		if (procTerrain)
		{
			procTerrain->AlterMesh(Hit.ImpactPoint);
		}
    }
}