// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

	///@brief ctor uses integers to avoid type casting, please DO NOT initialize int values below 1
	DungeonProperties(
		const int32 & _numFloor,
		const int32 & _numRoomMin,
		const int32 & _numRoomMax,
		const int32 & _roomDimMin,
		const int32 & _roomDimMax,
		const int32 & _floorDimMin,
		const int32 & _floorDimMax);

	~DungeonProperties();

	///@brief number of floors
	int32 numFloors;

	///@brief number of rooms in each floor
	int32 numRoomMin;
	int32 numRoomMax;

	///@brief room min/max dimensions of each floor
	int32 roomDimMin;
	int32 roomDimMax;

	int32 floorDimMin;
	int32 floorDimMax;


};

class RANDOMDUNGGEN_API DungeonGenerator
{
public:
	DungeonGenerator();
	DungeonGenerator(const DungeonProperties &_properties);
	~DungeonGenerator();

	void generateDungeon();


	void setNumFloors(const int32 &_numFloor)
	{ 
		dungeonProp.numFloors = _numFloor; 
	}
	void setNumRooms(const int32 &_min, const int32 &_max)
	{ 
		dungeonProp.numRoomMin = _min;
		dungeonProp.numRoomMax = _max;
	}
	void setRoomDims(const int32 &_min, const int32 &_max)
	{ 
		dungeonProp.roomDimMin = _min;
		dungeonProp.roomDimMax = _max;
	}

	void setFloorDims(const int32 &_min, const int32 &_max)
	{
		dungeonProp.floorDimMin = _min;
		dungeonProp.floorDimMax = _max;
	}

	DungeonMap getDungeonMap() const;
	FloorMap getFloorMap( const int32 &_floorIdx) const;
	TArray<FloorMap> getFloorMaps() const;
	TArray<FTransform> getMapTileInstanceTransform(const int32 &_floorIdx) const;
protected:

	///@brief the properties to use when generating the dungeon floors
	DungeonProperties dungeonProp;
	///@brief data tables for the terrain layout of the generated floors
	DungeonMap map;

};
