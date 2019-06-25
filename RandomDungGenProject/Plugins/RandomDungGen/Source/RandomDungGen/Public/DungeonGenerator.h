// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Private/DungeonMap.h"
/**
 * 
 */
///@file Generate dungeon description
DECLARE_LOG_CATEGORY_EXTERN(RandomDungGen_DungeonGenerator, Warning, All);

struct RANDOMDUNGGEN_API DungeonProperties
{
	/// ctor and dtor
	DungeonProperties();
	DungeonProperties(
		const uint8 & _numFloor, 
		const uint8 & _numRoomMin, 
		const uint8 & _numRoomMax,
		const uint8 & _roomDimMin,
		const uint8 & _roomDimMax,
		const uint8 & _floorDimMin,
		const uint8 & _floorDimMax);

	~DungeonProperties();

	///@brief number of floors
	uint8 numFloors;

	///@brief number of rooms in each floor
	uint8 numRoomMin;
	uint8 numRoomMax;

	///@brief room min/max dimensions of each floor
	uint8 roomDimMin;
	uint8 roomDimMax;

	uint8 floorDimMin;
	uint8 floorDimMax;


};

class RANDOMDUNGGEN_API DungeonGenerator
{
public:
	DungeonGenerator();
	DungeonGenerator(const DungeonProperties &_properties);
	~DungeonGenerator();

	void generateDungeon();


	void setNumFloors(const uint8 &_numFloor) 
	{ 
		dungeonProp.numFloors = _numFloor; 
	}
	void setNumRooms(const uint8 &_min, const uint8 &_max) 
	{ 
		dungeonProp.numRoomMin = _min;
		dungeonProp.numRoomMax = _max;
	}
	void setRoomDims(const uint8 &_min, const uint8 &_max)
	{ 
		dungeonProp.roomDimMin = _min;
		dungeonProp.roomDimMax = _max;
	}

	void setFloorDims(const uint8 &_min, const uint8 &_max)
	{
		dungeonProp.floorDimMin = _min;
		dungeonProp.floorDimMax = _max;
	}

	DungeonMap getDungeonMap() const;

protected:

	void generateRooms();

	///@brief the properties to use when generating the dungeon floors
	DungeonProperties dungeonProp;
	///@brief data tables for the terrain layout of the generated floors
	DungeonMap map;

};
