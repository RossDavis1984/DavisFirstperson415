// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileDMIMod.h"
#include "DavisFirstperson415.h"
#include "Kismet/KismetMathLibrary.h"
#include "DavisFirstperson415Projectile.h"

// Sets default values
AProjectileDMIMod::AProjectileDMIMod()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//set up subobjects
	sphereComp = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	projectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("Projectile Mesh");

	//set up attachments to allow the classes to function properly
	RootComponent = sphereComp;
	projectileMesh->SetupAttachment(sphereComp);
}

// Called when the game starts or when spawned
void AProjectileDMIMod::BeginPlay()
{
	Super::BeginPlay();
	//set up the sphere component to call the OnOverlapBegin function when it overlaps with something
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &AProjectileDMIMod::OnOverlapBegin);

	//set up the sphere component to be a trigger
	if (baseMat)
	{
		//create the dynamic material instance
		dmiMat = UMaterialInstanceDynamic::Create(baseMat, this);
	}

	//check if the projectile Mesh is valid
	if (projectileMesh)
	{
		projectileMesh->SetMaterial(0, dmiMat);
	}
}

// Called every frame
void AProjectileDMIMod::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileDMIMod::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//cast to AProjectileDMIMod
	ADavisFirstperson415Projectile* OverlappedActor = Cast<ADavisFirstperson415Projectile>(OtherActor);

	if (OverlappedActor)
	{
		float ranNumX = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
		float ranNumY = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
		float ranNumZ = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);

		FVector4 randColor = FVector4(ranNumX, ranNumY, ranNumZ, 1.f);
	}
		//check if the dmiMat is valid
	if (dmiMat)
	{
		//set the color to the dmiMat
		float ranNumX = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
		float ranNumY = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
		float ranNumZ = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
		FVector4 randColor = FVector4(UKismetMathLibrary::RandomFloatInRange(0.f, 1.f), UKismetMathLibrary::RandomFloatInRange(0.f, 1.f), UKismetMathLibrary::RandomFloatInRange(0.f, 1.f), 1.f);
		dmiMat->SetVectorParameterValue("DMIProjColor", randColor);
		dmiMat->SetScalarParameterValue("Darkness", ranNumX);
		
	}

}

