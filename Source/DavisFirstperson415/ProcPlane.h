// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProcPlane.generated.h"

// This class represents a procedural plane actor in the game
class UProceduralMeshComponent;

UCLASS()
class DAVISFIRSTPERSON415_API AProcPlane : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProcPlane();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//allows us to call the create mesh function beofre it is used
	virtual void PostActorCreated() override;

	virtual void PostLoad() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//adding varialbe for Array of vectors to hold the vertices of the plane
	UPROPERTY(EditAnywhere)
	TArray<FVector> Vertices;

	//adding variable for Array of integers called Triangles to hold the indices of the vertices that form triangles
	UPROPERTY(EditAnywhere)
	TArray<int> Triangles;


	UPROPERTY()
	TArray<FVector2D>UV0;

	//pointer to the procedural mesh component
	UPROPERTY(EditAnywhere)
	UMaterialInterface* PlaneMat;



	//adding Fnction to generate the procedural mesh
	UFUNCTION()
	void CreateMesh();

private:
	UProceduralMeshComponent* procMesh; // Pointer to the procedural mesh component

};
