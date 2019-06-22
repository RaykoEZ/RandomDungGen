// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonMap.h"
/**
 * 
 */
///@file Generate dungeon description
DECLARE_LOG_CATEGORY_EXTERN(RandomDungGen_DungeonGenerator, Warning, All);

struct RANDOMDUNGGEN_API DungeonProperties
{
	/// ctor and dtor
	DungeonProperties();
	~DungeonProperties();

	///@brief number of floors
	uint8 numFloors;
	///@brief number of rooms in each floor
	TArray<uint8> numRoomMax;
	TArray<uint8> numRoomMin;
	///@brief room min/max dimensions of each floor
	uint8 roomDimMax;
	uint8 roomDimMin;

};

class RANDOMDUNGGEN_API DungeonGenerator
{
public:
	DungeonGenerator();
	~DungeonGenerator();

	void generateDungeon();
	void generateFloor(const uint8 &_floorIdx);
	DungeonMap getDungeonMap() const;
protected:
	///@brief the properties to use when generating the dungeon floors
	DungeonProperties dungeonProp;
	///@brief data tables for the terrain layout of the generated floors
	DungeonMap map;
};
