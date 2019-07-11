// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Private/DungeonMap.h"
#include "DungeonProperties.h"

/**
 * 
 */
///@file Generate dungeon descriptionA
DECLARE_LOG_CATEGORY_EXTERN(RandomDungGen_DungeonGenerator, Warning, All);



class RANDOMDUNGGEN_API DungeonGenerator
{
public:
	DungeonGenerator();
	DungeonGenerator(const FDungeonProperties &_properties);
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
	FDungeonProperties dungeonProp;
	///@brief data tables for the terrain layout of the generated floors
	DungeonMap map;

};
