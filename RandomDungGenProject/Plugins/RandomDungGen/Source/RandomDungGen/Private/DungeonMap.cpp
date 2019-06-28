// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonMap.h"


DEFINE_LOG_CATEGORY(RandomDungGen_DungeonMap);

DungeonMap::DungeonMap()
{
	isReady = false;
}

DungeonMap::DungeonMap(
	const TArray<int32> &_numRoom,
	const TArray<int32> &_floorDimX,
	const TArray<int32> &_floorDimY,
	const TArray<IntArray> &_roomDimX,
	const TArray<IntArray> &_roomDimY,
	const TArray<IntArray> &_roomPosX,
	const TArray<IntArray> &_roomPosY)
{

	
	floorDimX = _floorDimX;
	floorDimY = _floorDimY;
	roomPosX = _roomPosX;
	roomPosY = _roomPosY;
	numRoom = _numRoom;
	roomDimX = _roomDimX;
	roomDimY = _roomDimY;

	/// this reserves mem of rooms and spaces in each floor
	/// doesnot factor paths as they have not been generated
	/// but it still means less mallocs overall
	/// whether an extra two for loops is worth it, we'll see 
	for (int i = 0; i < floorMap.Num(); ++i)
	{

		int32 floorArea = floorDimX[i] * floorDimY[i];

		int32 roomArea = 0;

		for (int j = 0; j < numRoom[i]; ++j)
		{
			roomArea += roomDimX[i].dim[j] * roomDimY[i].dim[j];
		}


		floorMap[i].traversableSet.Reserve(roomArea);
		floorMap[i].untraversableSet.Reserve(floorArea - roomArea);
	}




	isReady = true;
}



void DungeonMap::insertRooms()
{

	/// for each floor, each room's origiin corner is appended to a set of traversable positions 
	/// This prepares for the initialisation of "digging" agents
	for (int i = 0; i < floorMap.Num(); ++i) 
	{
		for (int j = 0; j < numRoom[i]; ++j)
		{
			FVector temp =
					FVector(
					(float)roomPosX[i].dim[j], 
					(float)roomPosY[i].dim[j], 0.0f);

			floorMap[i].traversableSet.Add(temp);

		}
	}



}

void DungeonMap::insertPaths()
{
}


DungeonMap::~DungeonMap()
{
}

