// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Array.h"
#include "Vector.h"
#include "Set.h"
#include "CoreMinimal.h"

/**
 * 
 */
DECLARE_LOG_CATEGORY_EXTERN(RandomDungGen_DungGenAgent, Warning, All);

struct RANDOMDUNGGEN_API IntArray
{
	/// ctor and dtor
	IntArray();
	IntArray(const TArray<int32> &_dim);
	~IntArray();

	TArray<int32> dim;
	int32& operator[] (const int32 &_i)
	{
		return dim[_i];
	}
};

struct RANDOMDUNGGEN_API FloorMap
{
	/// ctor and dtor
	FloorMap();
	FloorMap(const TArray<bool> &_map);
	~FloorMap();

	///@brief raw flags for tile types on a floor
	TArray<bool> map;
	///@brief sets of tile positions to render on a floor.
	TSet<FVector> traversableSet;
	TSet<FVector> untraversableSet;

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


	void init();

	FloorMap tracePaths();

	///@brief gets the value in a floor's terrain with a an x-y grid coordinate
	bool& at(const int32 &_x, const int32 &_y);
	/// traversing through the floor indices
	int32 goVertical( const bool &_up, const int32 &_currentY);
	int32 goHorizontal( const bool &_right, const int32 &_currentX);

	//void setDim() {}

protected:


	/// dimensions of the current floor
	int32 dimX;
	int32 dimY;
	int32 numAgents;

	///@brief The XY direction of agents on the grid
	/// 
	TSet<int32> upAgents;
	TSet<int32> downAgents;
	TSet<int32> leftAgents;
	TSet<int32> rightAgents;

	TArray<int32> targetPosX;
	TArray<int32> targetPosY;
	TArray<int32> agentPosX;
	TArray<int32> agentPosY;
	float detourRate;
	FloorMap targetMap;

};
