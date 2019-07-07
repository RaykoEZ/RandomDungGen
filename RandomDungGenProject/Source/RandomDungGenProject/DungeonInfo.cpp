// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonInfo.h"
#include "ConstructorHelpers.h"
// Sets default values
ADungeonInfo::ADungeonInfo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_prop = DungeonProperties(1, 3, 5, 4, 15, 90, 100);
	m_gen = DungeonGenerator(m_prop);


	m_generatedMesh = NewObject<UInstancedStaticMeshComponent>(this,TEXT("RandomDungGen Floor"));
	m_generatedMesh->RegisterComponent();

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Engine/Functions/Engine_MaterialFunctions02/SupportFiles/1x1x1_Box_Pivot_-XYZ.1x1x1_Box_Pivot_-XYZ'"));
	UStaticMesh* asset = MeshAsset.Object;
	m_generatedMesh->SetStaticMesh(asset);
	RootComponent = m_generatedMesh;
	//m_generatedMap->SetFlags(RF_Transactional);
	this->AddInstanceComponent(m_generatedMesh);
	//genMap();
}

// Called when the game starts or when spawned
void ADungeonInfo::BeginPlay()
{
	Super::BeginPlay();



	/*
	m_generatedMesh->AddInstance(FTransform(FVector(0.0f,0.0f,0.0f)));
	m_generatedMesh->AddInstance(FTransform(FVector(0.0f,1.0f, 0.0f)));
	m_generatedMesh->AddInstance(FTransform(FVector(1.0f, 0.0f, 0.0f)));	
	m_generatedMesh->AddInstance(FTransform(FVector(0.0f, -1.0f, 0.0f)));
	m_generatedMesh->AddInstance(FTransform(FVector(-1.0f, 0.0f, 0.0f)));
	*/

}



void ADungeonInfo::OnConstruction(const FTransform & Transform)
{
	genMap();
}

// Called every frame
void ADungeonInfo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADungeonInfo::genMap()
{
	m_generatedMesh->ClearInstances();
	m_gen.generateDungeon();
	auto floorTiles = m_gen.getMapTileInstanceTransform(0);
	for (int i = 0; i < floorTiles.Num(); ++i)
	{
		m_generatedMesh->AddInstance(floorTiles[i]);
	}
}

