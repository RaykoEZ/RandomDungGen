// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonInfo.h"

// Sets default values
ADungeonInfo::ADungeonInfo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_prop = DungeonProperties();
	m_gen = DungeonGenerator(m_prop);
	

}

// Called when the game starts or when spawned
void ADungeonInfo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADungeonInfo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

