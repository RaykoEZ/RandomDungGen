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
	FloorMap(const TArray<bool> &_map);
	~FloorMap();

	///@brief raw flags for tile types on a floor
	///@brief true for normal traversable terrain, vice versa.
	TArray<bool> map;
	///@brief sets of tile positions to render on a floor.
	TSet<FIntVector> traversableSet;

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
		const int32 &_dimX,
		const int32 &_dimY,
		const int32 &_numAgents,
		const float &_detourRate,
		const FloorMap & _map);

	~DungGenAgent();

	///@brief reset this Agent's properties
	/// attending to be used for constructing a new floor map
	void reset(
		const int32 &_dimX,
		const int32 &_dimY,
		const int32 &_numAgents,
		const float &_detourRate,
		const FloorMap & _map);

	FloorMap createFloorMap();
	

	///@brief util methods that get the value in a floor's terrain with a an x-y grid coordinate
	///and vice versa
	bool& mapCellValue(const int32 &_x, const int32 &_y);
	FIntVector idxToVector2D(const int32 & _idx);


protected:
	///@brief initialise agent origins
	void init();
	///@brief decides agent's orientation
	void tracePaths();
	///@brief makes modification on the given floor map
	void updateMap();
	///@brief flag to show we've finished generating the floor
	bool finishedTracing;
	/// dimensions of the current floor
	int32 dimX;
	int32 dimY;
	int32 numAgents;
	float detourRate;
	float invDimX;
	float invDimY;
	///@brief The XY direction of agents (indices) on the grid
	/// 
	TSet<int32> XAgents;
	TSet<int32> YAgents;

	/// @brief displacement from agent to target claculated and store here
	TArray<int32> diffX;
	TArray<int32> diffY;

	TArray<int32> targetPosX;
	TArray<int32> targetPosY;
	TArray<int32> agentPosX;
	TArray<int32> agentPosY;

	FloorMap targetMap;

};
