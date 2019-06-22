// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonGenerator.h"
DEFINE_LOG_CATEGORY(RandomDungGen_DungeonGenerator);

DungeonGenerator::DungeonGenerator()
{
	dungeonProp = DungeonProperties();
	
}

DungeonGenerator::~DungeonGenerator()
{
}

void DungeonGenerator::generateDungeon()
{


	map = DungeonMap();
}

void DungeonGenerator::generateFloor(const uint8 &_floorIdx)
{
}

DungeonMap DungeonGenerator::getDungeonMap() const
{
	if (!map.isReady) 
	{
		UE_LOG(RandomDungGen_DungeonGenerator, Warning, TEXT("The map you got is empty, please call generateDungeon() to generate a map and call this again."));
	}
	return map;
}


DungeonProperties::DungeonProperties()
{
	numFloors = 1;
	numRoomMax = TArray<uint8>();
	numRoomMax.Add(1);

	numRoomMin = TArray<uint8>();
	numRoomMin.Add(1);

	roomDimMax = 5;
	roomDimMin = 3;
}

DungeonProperties::~DungeonProperties()
{
}