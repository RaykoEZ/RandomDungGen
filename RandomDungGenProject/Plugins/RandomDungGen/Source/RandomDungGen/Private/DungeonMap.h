// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DungGenAgent.h"
#include "CoreMinimal.h"

/**
 * 
 */

///@file Handles layout operations withn a floor map
DECLARE_LOG_CATEGORY_EXTERN(RandomDungGen_DungeonMap, Warning, All);



class RANDOMDUNGGEN_API DungeonMap
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
		const TArray<UintArray> &_roomPosY);

	~DungeonMap();

	bool isReady;


	///@brief gets the value in a floor's terrain with a an x-y grid coordinate and a floor number
	bool at(const int32 &_floor, const int32 &_x, const int32 &_y) const;

	/// getters 
	uint8 getNumRoom(const int32 &_floor) const { return numRoom[_floor]; }
	uint8 getFloorDimX(const int32 &_floor) const { return floorDimX[_floor]; }
	uint8 getFloorDimY(const int32 &_floor) const { return floorDimY[_floor]; }
	UintArray getRoomDimX(const int32 &_floor) const { return roomDimX[_floor]; }
	UintArray getRoomDimY(const int32 &_floor) const { return roomDimY[_floor]; }
	UintArray getRoomPosX(const int32 &_floor) const { return roomPosX[_floor]; }
	UintArray getRoomPosY(const int32 &_floor) const { return roomPosY[_floor]; }
	FloorMap getFloorMap(const int32 &_floor) const { return floorMap[_floor]; }

	/// setters/adders
	void addFloorDimX(const int32 &_floor, const uint8 &_x) { floorDimX[_floor] = _x; }
	void addFloorDimY(const int32 &_floor, const uint8 &_y) { floorDimY[_floor] = _y; }
	void addRoomDimX(const int32 &_floor, const uint8 &_x) { roomDimX[_floor].dim.Add(_x); }
	void addRoomDimY(const int32 &_floor, const uint8 &_y) { roomDimY[_floor].dim.Add(_y); }
	void addRoomPosX(const int32 &_floor, const uint8 &_x) { roomPosX[_floor].dim.Add(_x); }
	void addRoomPosY(const int32 &_floor, const uint8 &_y) { roomPosY[_floor].dim.Add(_y); }
	void addFloorMap(const int32 &_floor, const bool &_map) { floorMap[_floor].map.Add(_map); }
	
	
	/// apply changes to the current map
	void insertRooms();
	void insertPaths();


protected:

	/// @brief number of rooms in each floor
	TArray<uint8> numRoom;
	///@brief floor dimansion limits
	TArray<uint8> floorDimX;
	TArray<uint8> floorDimY;

	/// @brief dimension of rooms  on each floor
	TArray<UintArray> roomDimX;
	TArray<UintArray> roomDimY;

	///@brief positions of rooms (bottom-left corners) on each floor
	TArray<UintArray> roomPosX;
	TArray<UintArray> roomPosY;

	///@floor plan of each floor
	TArray<FloorMap> floorMap;

};
