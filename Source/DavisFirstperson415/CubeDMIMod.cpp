// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeDMIMod.h"
//to be able to cast to DavisFirstperson415Character
#include "DavisFirstperson415Character.h"
//to use random function to get random color
#include "Kismet/KismetMathLibrary.h"

//this reference allows us to cast to it 
#include "NiagaraComponent.h"
//including function library to allow us to call the Niagara spawn function
#include "NiagaraFunctionLibrary.h"

// Sets default values
ACubeDMIMod::ACubeDMIMod()
{
    // Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Set up subobjects
    boxComp = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
    cubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("Cube Mesh"); // Ensure this line ends with a semicolon

    // Set up attachments to allow the classes to function properly
    RootComponent = boxComp;
    cubeMesh->SetupAttachment(boxComp);

}

// Called when the game starts or when spawned
void ACubeDMIMod::BeginPlay()
{
    Super::BeginPlay();
    
    //call Overlap on begin play
    boxComp->OnComponentBeginOverlap.AddDynamic(this, &ACubeDMIMod::OnOverlapBegin);

    //CHeck if base material is valid
    if (baseMat)
    {
        //create the dynamic material instance
        dmiMat = UMaterialInstanceDynamic::Create(baseMat, this);
    }
    //check if the cube Mesh is valid
    if (cubeMesh)
    {
        cubeMesh->SetMaterial(0, dmiMat);
    }
    
}

// Called every frame
void ACubeDMIMod::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void ACubeDMIMod::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)  
{  
    // Cast to DavisFirstperson415Character  
    ADavisFirstperson415Character* OverlappedActor = Cast<ADavisFirstperson415Character>(OtherActor);  

    if (OverlappedActor)  
    {  
        float ranNumX = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);  
        float ranNumY = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);  
        float ranNumZ = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);  

        // Changed FVector4 to FLinearColor to match  
        FLinearColor randColor = FLinearColor(ranNumX, ranNumY, ranNumZ, 1.f);  
        // Check if the dmiMat is valid  
        if (dmiMat)  
        {  
            // Set the color to the dmiMat  
            dmiMat->SetVectorParameterValue("Color", randColor);  
            dmiMat->SetScalarParameterValue("Darkness", ranNumX);  
            // Setting a check to see if colorP is set  
            if (colorP)  
            {  
                // Creating new Niagara Component particleComp and setting its attachments  
                UNiagaraComponent* particleComp = UNiagaraFunctionLibrary::SpawnSystemAttached(colorP, OtherComp, NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::KeepRelativeOffset, true);  
                // Sets Niagara variable  
                particleComp->SetNiagaraVariableLinearColor("RandColor", randColor);  
            }  

        }  
    }  
}

