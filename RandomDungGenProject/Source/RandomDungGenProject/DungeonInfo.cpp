// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonInfo.h"
#include "ConstructorHelpers.h"
// Sets default values
ADungeonInfo::ADungeonInfo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_prop = FDungeonProperties(1, 10, 20, 5, 10, 200, 250);
	m_gen = DungeonGenerator(m_prop);
	m_currentFloorToRender = 0;

	m_generatedMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("RandomDungGen Floor"));
	m_generatedMesh->RegisterComponent();

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Engine/Functions/Engine_MaterialFunctions02/SupportFiles/1x1x1_Box_Pivot_-XYZ.1x1x1_Box_Pivot_-XYZ'"));
	UStaticMesh* asset = MeshAsset.Object;
	m_generatedMesh->SetStaticMesh(asset);
	RootComponent = m_generatedMesh;
	//m_generatedMap->SetFlags(RF_Transactional);
	this->AddInstanceComponent(m_generatedMesh);
	//genMap();
}

ADungeonInfo::ADungeonInfo(const FObjectInitializer& ObjectInitializer)
{

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_prop = FDungeonProperties(1, 10, 20, 5, 10, 50, 120);
	m_gen = DungeonGenerator(m_prop);
	m_currentFloorToRender = 0;
	//Make our mesh component (named 'MyMesh') and set it up to be our root component  
	m_generatedMesh = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("RandomDungGen Floor"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Engine/Functions/Engine_MaterialFunctions02/SupportFiles/1x1x1_Box_Pivot_-XYZ.1x1x1_Box_Pivot_-XYZ'"));
	UStaticMesh* asset = MeshAsset.Object;
	m_generatedMesh->SetStaticMesh(asset);
	RootComponent = m_generatedMesh;
	//m_generatedMap->SetFlags(RF_Transactional);
	this->AddInstanceComponent(m_generatedMesh);
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

#if WITH_EDITOR
void ADungeonInfo::genMap()
{
	m_generatedMesh->ClearInstances();
	m_gen = DungeonGenerator(m_prop);
	m_gen.generateDungeon();
	auto floorTiles = m_gen.getMapTileInstanceTransform(m_currentFloorToRender);
	for (int i = 0; i < floorTiles.Num(); ++i)
	{
		m_generatedMesh->AddInstance(floorTiles[i]);
	}
}
#endif
