// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonMap.h"


DEFINE_LOG_CATEGORY(RandomDungGen_DungeonMap);

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

bool DungeonMap::at(const int32 &_floor, const int32 &_x, const int32 &_y) const 
{
	if (_floor > numRoom.Num()) 
	{
		UE_LOG(RandomDungGen_DungeonMap, Warning, TEXT("Floor index: &d, does not exist in this dungeon."), _floor);
		return false;
	}

	FloorMap temp = floorMap[_floor];
	return temp[_y * floorDimX[_floor] + _x];
}

void DungeonMap::insertRooms()
{
}

void DungeonMap::insertPaths()
{
}


DungeonMap::~DungeonMap()
{
}

