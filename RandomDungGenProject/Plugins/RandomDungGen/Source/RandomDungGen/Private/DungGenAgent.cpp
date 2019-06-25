// Fill out your copyright notice in the Description page of Project Settings.


#include "DungGenAgent.h"

DungGenAgent::DungGenAgent()
{
}

DungGenAgent::DungGenAgent(
	const FloorMap & _map,
	const TArray<uint8> &_startPosX,
	const TArray<uint8> &_startPosY,
	const TArray<float>& _randTraceRate
)
	:
	randomTraceRate(_randTraceRate),
	targetMap(_map),
	agentPosX(_startPosX),
	agentPosY(_startPosY)
{
}

DungGenAgent::~DungGenAgent()
{
}

FloorMap DungGenAgent::tracePaths()
{
	return targetMap;
}

UintArray::UintArray()
{
}

UintArray::UintArray(const TArray<uint8>& _dim) : dim(_dim)
{
}

UintArray::~UintArray()
{
}

FloorMap::FloorMap()
{
}

FloorMap::FloorMap(const TArray<bool>& _map) : map(_map)
{
}

FloorMap::~FloorMap()
{
}
