// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CubeDMIMod.generated.h"

UCLASS()
class DAVISFIRSTPERSON415_API ACubeDMIMod : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACubeDMIMod();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//set up box component
	UPROPERTY(EditAnywhere)
	UBoxComponent* boxComp;

	//set up static mesh component
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* cubeMesh;

	// the base material to create the dynamic instance from DMI1Mat
	UPROPERTY(EditAnywhere)
	UMaterialInterface* baseMat;

	UPROPERTY()
	UMaterialInstanceDynamic* dmiMat;

	//Overlap event
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};
