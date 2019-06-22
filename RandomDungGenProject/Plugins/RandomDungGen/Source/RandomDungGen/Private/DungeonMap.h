// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Array.h"
#include "Map.h"
#include "Vector.h"
#include "CoreMinimal.h"

/**
 * 
 */

///@file Handles layout operations withn a floor map

struct UintArray
{
	/// ctor and dtor
	UintArray();
	~UintArray();

	TArray<uint8> dim;
	uint8& operator[] (const int32 &_i) 
	{
		return dim[_i];
	}
};

struct FloorMap 
{
	/// ctor and dtor
	FloorMap();
	~FloorMap();

	TMap<uint8, bool> map;
	bool& operator[] (const int32 &_i) 
	{
		return map.FindOrAdd(_i);
	}
};


class DungeonMap
{
public:
	DungeonMap();

	DungeonMap(
		const TArray<uint8> &_numRoom, 
		const TArray<uint8> &_floorDimX,
		const TArray<uint8> &_floorDimY,
		const TArray<UintArray> &_roomDimX,
		const TArray<UintArray> &_roomDimY,
		const TArray<UintArray> &_roomPosX,
		const TArray<UintArray> &_roomPosY
);

	~DungeonMap();

	bool isReady;

	///@brief floor dimansion limits
	TArray<uint8> floorDimX;
	TArray<uint8> floorDimY;


	/// @brief dimension of rooms
	TArray<UintArray> roomDimX;
	TArray<UintArray> roomDimY;

	///@brief positions of rooms (bottom-left corners)
	TArray<UintArray> roomPosX;
	TArray<UintArray> roomPosY;

	TArray<FloorMap> floorMap;

	TArray<uint8> getNumRoom() const { return numRoom; }
protected:

	/// @brief number of rooms in each floor
	TArray<uint8> numRoom;

};
