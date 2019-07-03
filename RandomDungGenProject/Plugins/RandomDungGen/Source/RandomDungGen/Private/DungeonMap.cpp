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

	floorMap.SetNum(floorDimX.Num());
	/// this reserves mem of rooms and spaces in each floor
	/// doesnot factor paths as they have not been generated
	/// but it still means less mallocs overall
	/// whether an extra two for loops is worth it, we'll see 
	for (int i = 0; i < floorMap.Num(); ++i)
	{

		//int32 floorArea = floorDimX[i] * floorDimY[i];

		int32 roomArea = 0;
		
		for (int j = 0; j < numRoom[i]; ++j)
		{
			roomArea += roomDimX[i].dim[j] * roomDimY[i].dim[j];
		}
		floorMap[i].map.SetNum(floorDimX[i] * floorDimY[i]);
		floorMap[i].traversableSet.Reserve(roomArea);
	}




	isReady = false;
}



void DungeonMap::genFloors()
{

	/// for each floor, each room's origiin corner is appended to a set of traversable positions 
	/// This prepares for the initialisation of "digging" agents


	for (int i = 0; i < floorMap.Num(); ++i) 
	{
		for (int j = 0; j < numRoom[i]; ++j)
		{
			FIntVector temp =
					FIntVector(
					roomPosX[i].dim[j], 
					roomPosY[i].dim[j], 0);

			floorMap[i].traversableSet.Add(temp);

		}
		/// Now we trace paths for each floor
			DungGenAgent agent = DungGenAgent(
			floorDimX[i],
			floorDimY[i],
			numRoom[i],
			0.5f,
			floorMap[i]);

			floorMap[i] = agent.createFloorMap();

	}

	/// We've finished generating all floors
	isReady = true;
}




DungeonMap::~DungeonMap()
{
}

IntArray::IntArray()
{
}

IntArray::IntArray(const TArray<int32>& _dim) : dim(_dim)
{
}

IntArray::~IntArray()
{
}