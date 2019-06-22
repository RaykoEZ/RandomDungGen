// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonMap.h"

DungeonMap::DungeonMap()
{
	isReady = false;
}

DungeonMap::DungeonMap(
	const TArray<uint8> &_numRoom,
	const TArray<uint8> &_floorDimX,
	const TArray<uint8> &_floorDimY,
	const TArray<UintArray> &_roomDimX,
	const TArray<UintArray> &_roomDimY,
	const TArray<UintArray> &_roomPosX,
	const TArray<UintArray> &_roomPosY)
{

	
	floorDimX = _floorDimX;
	floorDimY = _floorDimY;
	roomPosX = _roomPosX;
	roomPosY = _roomPosY;
	numRoom = _numRoom;
	roomDimX = _roomDimX;
	roomDimY = _roomDimY;

	isReady = true;
}



DungeonMap::~DungeonMap()
{
}

UintArray::UintArray()
{
}

UintArray::~UintArray()
{
}

FloorMap::FloorMap()
{
}

FloorMap::~FloorMap()
{
}
