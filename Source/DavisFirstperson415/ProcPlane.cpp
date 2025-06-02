// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcPlane.h"
// Sets default values
#include "ProceduralMeshComponent.h"

// Sets default values
AProcPlane::AProcPlane()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//create subobject for the mesh
	procMesh = CreateDefaultSubobject<UProceduralMeshComponent>("Proc Mesh");


}

// Called when the game starts or when spawned
void AProcPlane::BeginPlay()
{
	Super::BeginPlay();
	
}
//calling to create the mesh after the actor is created
void AProcPlane::PostActorCreated()
{
	Super::PostActorCreated();
	CreateMesh();
	//sets PlaneMesh as material for the procMesh
	if (PlaneMat)
	{
		procMesh->SetMaterial(0, PlaneMat);
	}
}
// Called when the actor is loaded
void AProcPlane::PostLoad()
{
	Super::PostLoad();
	CreateMesh();
	if (PlaneMat)
	{
		procMesh->SetMaterial(0, PlaneMat);
	}
}

// Called every frame
void AProcPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
// Function to create the mesh section with vertices and triangles
void AProcPlane::CreateMesh()
{
	procMesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), UV0, TArray<FColor>(), TArray<FProcMeshTangent>(), true);
}

