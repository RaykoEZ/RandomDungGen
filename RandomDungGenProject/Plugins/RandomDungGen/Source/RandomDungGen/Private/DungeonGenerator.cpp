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

	TArray<uint8> numRoom;
	TArray<uint8> floorDimX;
	TArray<uint8> floorDimY;
	numRoom.Reserve(dungeonProp.numFloors);
	floorDimX.Reserve(dungeonProp.numFloors);
	floorDimY.Reserve(dungeonProp.numFloors);
	uint8 totalRooms = 0;

	/// generate random number of rooms per floor and their dimensions
	for (uint8 i = 0; i < dungeonProp.numFloors; ++i) 
	{
		uint8 numRoomTemp = (uint8)FMath::RandRange(dungeonProp.numRoomMin, dungeonProp.numRoomMax);
		numRoom.Add(numRoomTemp);	
		totalRooms += numRoomTemp;
		floorDimX.Add((uint8)FMath::RandRange(dungeonProp.floorDimMin, dungeonProp.floorDimMax));
		floorDimY.Add((uint8)FMath::RandRange(dungeonProp.floorDimMin, dungeonProp.floorDimMax));

	}
	UE_LOG(RandomDungGen_DungeonGenerator, Warning,TEXT("Total room in Dungeon: %d."), totalRooms);
	
	TArray<UintArray> roomDimX;
	TArray<UintArray> roomDimY;
	TArray<UintArray> roomPosX;
	TArray<UintArray> roomPosY;

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
	for (uint8 i = 0; i < dungeonProp.numFloors; ++i) 
	{
		/// We don't want rooms on the edge/corners of a floor, so we make a border
		uint8 roomPosXMax = map.getFloorDimX(i) - dungeonProp.roomDimMax;
		uint8 roomPosXMin = 1;
		uint8 roomPosYMax = map.getFloorDimY(i) - dungeonProp.roomDimMax;
		uint8 roomPosYMin = 1;
		uint8 numRoomThisFloor = map.getNumRoom(i);
		///Attempt to insert these rooms in
		for (uint8 j = 0; j < numRoomThisFloor; ++j)
		{
			uint8 roomPosX = (uint8)FMath::RandRange(roomPosXMin, roomPosXMax);
			uint8 roomPosY = (uint8)FMath::RandRange(roomPosYMin, roomPosYMax);

			uint8 roomDimX = (uint8)FMath::RandRange(dungeonProp.roomDimMin, dungeonProp.roomDimMax);
			uint8 roomDimY = (uint8)FMath::RandRange(dungeonProp.roomDimMin, dungeonProp.roomDimMax);
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
	const uint8 & _numFloor, 
	const uint8 & _numRoomMin, 
	const uint8 & _numRoomMax, 
	const uint8 & _roomDimMin, 
	const uint8 & _roomDimMax,
	const uint8 & _floorDimMin,
	const uint8 & _floorDimMax
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