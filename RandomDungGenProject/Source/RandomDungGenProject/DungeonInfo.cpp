// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonInfo.h"
#include "ConstructorHelpers.h"
// Sets default values
ADungeonInfo::ADungeonInfo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_prop = DungeonProperties(1, 2, 5, 4, 5, 30, 100);
	m_gen = DungeonGenerator(m_prop);


	m_generatedMesh = NewObject<UInstancedStaticMeshComponent>(this,TEXT("RandomDungGen Floor"));
	m_generatedMesh->RegisterComponent();

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Engine/Functions/Engine_MaterialFunctions02/SupportFiles/1x1x1_Box_Pivot_-XYZ.1x1x1_Box_Pivot_-XYZ'"));
	UStaticMesh* asset = MeshAsset.Object;
	m_generatedMesh->SetStaticMesh(asset);
	//m_generatedMap->SetFlags(RF_Transactional);
	this->AddInstanceComponent(m_generatedMesh);

}

// Called when the game starts or when spawned
void ADungeonInfo::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADungeonInfo::OnConstruction(const FTransform & Transform)
{
	
	m_generatedMesh->ClearInstances();
	m_gen.generateDungeon();
	auto floorTiles = m_gen.getMapTileInstanceTransform(0);

	for( int i = 0; i < floorTiles.Num(); ++i)
	{
		m_generatedMesh->AddInstance(floorTiles[i]);
	}

}

// Called every frame
void ADungeonInfo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

