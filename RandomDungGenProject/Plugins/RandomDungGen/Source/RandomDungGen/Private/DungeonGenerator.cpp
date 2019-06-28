// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonGenerator.h"
#include "RandomStream.h"

DEFINE_LOG_CATEGORY(RandomDungGen_DungeonGenerator);

DungeonGenerator::DungeonGenerator()
{
	dungeonProp = DungeonProperties();	
}

DungeonGenerator::DungeonGenerator(const DungeonProperties & _properties) 
	: dungeonProp(_properties)
{
}

DungeonGenerator::~DungeonGenerator()
{
}



void DungeonGenerator::generateDungeon()
{
	/// We generate a floormap for each floor:
	/// 1. Generate number of rooms
	/// 2. Call generateFloor to append floor data into our map

	TArray<int32> numRoom;
	TArray<int32> floorDimX;
	TArray<int32> floorDimY;
	numRoom.Reserve(dungeonProp.numFloors);
	floorDimX.Reserve(dungeonProp.numFloors);
	floorDimY.Reserve(dungeonProp.numFloors);
	int32 totalRooms = 0;

	/// generate random number of rooms per floor and their dimensions
	for (int32 i = 0; i < dungeonProp.numFloors; ++i)
	{
		int32 numRoomTemp = FMath::RandRange(dungeonProp.numRoomMin, dungeonProp.numRoomMax);
		numRoom.Add(numRoomTemp);	
		totalRooms += numRoomTemp;
		floorDimX.Add(FMath::RandRange(dungeonProp.floorDimMin, dungeonProp.floorDimMax));
		floorDimY.Add(FMath::RandRange(dungeonProp.floorDimMin, dungeonProp.floorDimMax));

	}
	UE_LOG(RandomDungGen_DungeonGenerator, Warning,TEXT("Total room in Dungeon: %d."), totalRooms);
	
	TArray<IntArray> roomDimX;
	TArray<IntArray> roomDimY;
	TArray<IntArray> roomPosX;
	TArray<IntArray> roomPosY;

	roomDimX.Reserve(dungeonProp.numFloors);
	roomDimY.Reserve(dungeonProp.numFloors);
	roomPosX.Reserve(dungeonProp.numFloors);
	roomPosY.Reserve(dungeonProp.numFloors);
	map = DungeonMap(numRoom, floorDimX, floorDimY, roomDimX, roomDimY, roomPosX, roomPosY);
	generateRooms();
}

void DungeonGenerator::generateRooms()
{
	/// 1. Generate floor map XY dimensions
	/// 2. Generate room XY dimensions for each room
	/// Then we fit a room into the floor map one at a random position 
	/// check if it fits nto the floor dims and doesn't overlap/merge with other previous rooms
	for (int32 i = 0; i < dungeonProp.numFloors; ++i)
	{
		/// We don't want rooms on the edge/corners of a floor, so we make a border
		int32 roomPosXMax = map.getFloorDimX(i) - dungeonProp.roomDimMax;
		int32 roomPosXMin = 1;
		int32 roomPosYMax = map.getFloorDimY(i) - dungeonProp.roomDimMax;
		int32 roomPosYMin = 1;
		int32 numRoomThisFloor = map.getNumRoom(i);
		///Attempt to insert these rooms in
		for (int32 j = 0; j < numRoomThisFloor; ++j)
		{
			int32 roomPosX = FMath::RandRange(roomPosXMin, roomPosXMax);
			int32 roomPosY = FMath::RandRange(roomPosYMin, roomPosYMax);

			int32 roomDimX = FMath::RandRange(dungeonProp.roomDimMin, dungeonProp.roomDimMax);
			int32 roomDimY = FMath::RandRange(dungeonProp.roomDimMin, dungeonProp.roomDimMax);
			/// Now imagine we make rooms like we punch holes into cardboard sheets
			/// We want to use agents to generate some paths next
			map.addRoomPosX(i, roomPosX);
			map.addRoomPosY(i, roomPosY);
		}

	}

	map.insertRooms();
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
	numRoomMax = 1;
	numRoomMin = 1;
	roomDimMax = 5;
	roomDimMin = 3;
	floorDimMin = 1;
	floorDimMax = 2;
}

DungeonProperties::DungeonProperties(
	const int32 & _numFloor,
	const int32 & _numRoomMin,
	const int32 & _numRoomMax,
	const int32 & _roomDimMin,
	const int32 & _roomDimMax,
	const int32 & _floorDimMin,
	const int32 & _floorDimMax
	):
	numFloors(_numFloor),
	numRoomMin(_numRoomMin),
	numRoomMax(_numRoomMax),
	roomDimMin(_roomDimMin),
	roomDimMax(_roomDimMax),
	floorDimMin(_floorDimMin),
	floorDimMax(_floorDimMax)
{
}

DungeonProperties::~DungeonProperties()
{
}