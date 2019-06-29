// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DungGenAgent.h"

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
		const TArray<int32> &_numRoom,
		const TArray<int32> &_floorDimX,
		const TArray<int32> &_floorDimY,
		const TArray<IntArray> &_roomDimX,
		const TArray<IntArray> &_roomDimY,
		const TArray<IntArray> &_roomPosX,
		const TArray<IntArray> &_roomPosY);

	~DungeonMap();

	bool isReady;


	

	/// getters 
	int32 getNumRoom(const int32 &_floor) const { return numRoom[_floor]; }
	int32 getFloorDimX(const int32 &_floor) const { return floorDimX[_floor]; }
	int32 getFloorDimY(const int32 &_floor) const { return floorDimY[_floor]; }
	IntArray getRoomDimX(const int32 &_floor) const { return roomDimX[_floor]; }
	IntArray getRoomDimY(const int32 &_floor) const { return roomDimY[_floor]; }
	IntArray getRoomPosX(const int32 &_floor) const { return roomPosX[_floor]; }
	IntArray getRoomPosY(const int32 &_floor) const { return roomPosY[_floor]; }
	FloorMap getFloorMap(const int32 &_floor) const { return floorMap[_floor]; }

	/// setters/adders
	void addFloorDimX(const int32 &_floor, const int32 &_x) { floorDimX[_floor] = _x; }
	void addFloorDimY(const int32 &_floor, const int32 &_y) { floorDimY[_floor] = _y; }
	void addRoomDimX(const int32 &_floor, const int32 &_x) { roomDimX[_floor].dim.Add(_x); }
	void addRoomDimY(const int32 &_floor, const int32 &_y) { roomDimY[_floor].dim.Add(_y); }
	void addRoomPosX(const int32 &_floor, const int32 &_x) { roomPosX[_floor].dim.Add(_x); }
	void addRoomPosY(const int32 &_floor, const int32 &_y) { roomPosY[_floor].dim.Add(_y); }
	void addFloorMap(const int32 &_floor, const bool &_map) { floorMap[_floor].map.Add(_map); }
	
	
	/// apply changes to the current map
	void insertRooms();
	void insertPaths();


protected:

	/// @brief number of rooms in each floor
	TArray<int32> numRoom;
	///@brief floor dimansion limits
	TArray<int32> floorDimX;
	TArray<int32> floorDimY;

	/// @brief dimension of rooms  on each floor
	TArray<IntArray> roomDimX;
	TArray<IntArray> roomDimY;

	///@brief positions of rooms (bottom-left corners) on each floor
	TArray<IntArray> roomPosX;
	TArray<IntArray> roomPosY;

	///@floor plan of each floor
	TArray<FloorMap> floorMap;

};
