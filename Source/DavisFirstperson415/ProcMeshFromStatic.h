// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//added to be abe to recognize FProcMeshTangent
#include "ProceduralMeshComponent.h"

#include "ProcMeshFromStatic.generated.h"

UCLASS()
class DAVISFIRSTPERSON415_API AProcMeshFromStatic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProcMeshFromStatic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostActorCreated() override;

	virtual void PostLoad() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//setting variables to be editable in the editor
	UPROPERTY()
	TArray<FVector> Vertices;

	UPROPERTY()
	TArray<int> Triangles;

	UPROPERTY()
		TArray<FVector> Normals;

	TArray<FVector2D> UV0;

	UPROPERTY()
		TArray<FLinearColor> VertexColors;

	TArray<FColor>UpVertexColors;

	TArray<FProcMeshTangent> Tangents;

	//adding a static mesh component to the actor so we can use it in the editor
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* baseMesh;

private:
	UProceduralMeshComponent* procMesh;
	void GetMeshData();
	void CreateMesh();

};
