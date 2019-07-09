// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"

/**
 * 
 */
DECLARE_LOG_CATEGORY_EXTERN(RandomDungGen_DungGenAgent, Warning, All);



struct RANDOMDUNGGEN_API FloorMap
{
	/// ctor and dtor
	FloorMap();
	FloorMap(const TArray<bool> &_map, const TSet<FIntVector> &_roomPos);
	~FloorMap();

	///@brief raw flags for tile types on a floor
	///@brief true for normal traversable terrain, vice versa.
	TArray<bool> map;
	///@brief sets of tile positions to render on a floor.
	TSet<FIntVector> traversableSet;
	TSet<FIntVector> roomPosSet;
	bool& operator[] (const int32 &_i)
	{
		return map[_i];
	}
};


class RANDOMDUNGGEN_API DungGenAgent
{
public:
	DungGenAgent();

	DungGenAgent(
		const int32 &_numRooms,
		const int32 &_dimX,
		const int32 &_dimY,
		const float &_detourRate,
		const TArray<int32> &_roomDimX,
		const TArray<int32> &_roomDimY,
		const FloorMap & _map);

	~DungGenAgent();

	///@brief reset this Agent's properties
	/// attending to be used for constructing a new floor map
	void reset(
		const int32 &_numRooms,
		const int32 &_dimX,
		const int32 &_dimY,
		const float &_detourRate,
		const TArray<int32> &_roomDimX,
		const TArray<int32> &_roomDimY,
		const FloorMap & _map);

	FloorMap createFloorMap();


	///@brief util methods that get the value in a floor's terrain with a an x-y grid coordinate
	///and vice versa
	bool& mapCellValue(const int32 &_x, const int32 &_y);
	FIntVector idxToVector2D(const int32 & _idx);


protected:
	///@brief initialise agent origins
	void init();
	/// @brief we use one agent to define a main route to connect each rooms, 
	/// avoiding disconnectivity in the maps
	void traceSpanningTree();
	///@brief decides agent's orientation
	void tracePaths();
	///@brief put rooms into the map
	void insertRooms();
	///@brief method to select target rooms of each agent, 
	/// this implements a randomized spanning tree for the dungeon network
	void setupMinimalConnections();
	///@brief makes modification on the given floor map
	void updateMap();
	///@brief clear used data (The agent state values shown below) for new cycle
	void cleanup();

	int32 numRoom;
	/// dimensions of the current floor
	int32 dimX;
	int32 dimY;
	int32 numAgents;
	float detourRate;
	float invDimX;
	float invDimY;
	///@brief The XY/idle direction of agents (indices) on the grid
	///  ---AGENT STATE VALUES - EMPTY THESE WHEN A TRACE IS DONE for sanity-------a
	TSet<int32> idleAgents;
	TSet<int32> XAgents;
	TSet<int32> YAgents;
	/// @brief displacement from agent to target claculated and store here
	TArray<int32> diffX;
	TArray<int32> diffY;
	TArray<int32> roomDimX;
	TArray<int32> roomDimY;
	TArray<int32> targetPosX;
	TArray<int32> targetPosY;
	TArray<int32> agentPosX;
	TArray<int32> agentPosY;

	FloorMap targetMap;
};
