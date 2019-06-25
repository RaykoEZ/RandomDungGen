// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Array.h"
#include "Vector.h"
#include "CoreMinimal.h"

/**
 * 
 */

struct RANDOMDUNGGEN_API UintArray
{
	/// ctor and dtor
	UintArray();
	UintArray(const TArray<uint8> &_dim);
	~UintArray();

	TArray<uint8> dim;
	uint8& operator[] (const int32 &_i)
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
	TSet<FTransform> traversableList;
	TSet<FTransform> untraversableList;

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
		const FloorMap &_map, 
		const TArray<uint8> &_startPosX,
		const TArray<uint8> &_startPosY, 
		const TArray<float> &_randTraceRate);

	~DungGenAgent();

	FloorMap tracePaths();

protected:
	TArray<uint8> agentPosX;
	TArray<uint8> agentPosY;

	TArray<uint8> targetPosX;
	TArray<uint8> targetPosY;

	TArray<float> randomTraceRate;
	FloorMap targetMap;
};
