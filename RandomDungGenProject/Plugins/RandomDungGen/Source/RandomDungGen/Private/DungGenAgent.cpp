// Fill out your copyright notice in the Description page of Project Settings.


#include "DungGenAgent.h"

DEFINE_LOG_CATEGORY(RandomDungGen_DungGenAgent);


DungGenAgent::DungGenAgent()
{
}

DungGenAgent::DungGenAgent(
	const int32 &_dimX,
	const int32 &_dimY,
	const int32 &_numAgents,
	const float  &_detourRate,
	const FloorMap & _map)
	:
	dimX(_dimX),
	dimY(_dimY),
	numAgents(_numAgents),
	detourRate(_detourRate), 
	targetMap(_map)
{
	init();
}

DungGenAgent::~DungGenAgent()
{
}

void DungGenAgent::reset(
	const int32 & _dimX, 
	const int32 & _dimY, 
	const int32 & _numAgents, 
	const float & _detourRate, 
	const FloorMap & _map)
{
	dimX = _dimX;
	dimY = dimY;
	numAgents = _numAgents;
	detourRate = _detourRate;
	targetMap = _map;
	init();
}

FloorMap DungGenAgent::createFloorMap()
{
	while (!finishedTracing)
	{
		tracePaths();
	}

	return targetMap;
}

void DungGenAgent::init()
{
	if (detourRate >= 1.0f) 
	{
		UE_LOG(RandomDungGen_DungGenAgent, Warning, TEXT("Detour rate is a probability of domain {0.1}, please initialize between 0 and 1."));

		detourRate = 0.0f;
	
	}
	invDimX = 1 / dimX;
	invDimY = 1 / dimY;
	bool finishedTracing = false;
	/// reserve memoory since we know the problem size
	targetPosX.Reserve(numAgents);
	targetPosY.Reserve(numAgents);
	agentPosX.Reserve(numAgents);
	agentPosY.Reserve(numAgents);
	diffX.Reserve(numAgents);
	diffY.Reserve(numAgents);
	XAgents.Reserve(numAgents);
	YAgents.Reserve(numAgents);

	/// setting init Positions for all agents
	/// We occupy all necessary rooms first and leftover agents start in random rooms
	auto traversable = targetMap.traversableSet.Array();
	for (int g = 0; g < numAgents; ++g) 
	{	
		if (g < targetMap.traversableSet.Num())
		{
			agentPosX[g] = traversable[g].X;
			agentPosY[g] = traversable[g].Y;


		}
		else
		{
			int randIdx = FMath::RandRange(0, targetMap.traversableSet.Num());
			agentPosX[g] = traversable[randIdx].X;
			agentPosY[g] = traversable[randIdx].Y;

		}

		/// initialize target positions, similar to setting positions but we remove self position
		auto targets = targetMap.traversableSet;
		targets.Remove(FIntVector(agentPosX[g], agentPosY[g], 0));
		auto targetArr = targets.Array();

		if (g < targetMap.traversableSet.Num()-1)
		{
			targetPosX[g] = targetArr[g].X;
			targetPosY[g] = targetArr[g].Y;

		}
		else
		{
			int randTargetIdx = FMath::RandRange(0, targets.Num());
			targetPosX[g] = targetArr[randTargetIdx].X;
			targetPosY[g] = targetArr[randTargetIdx].Y;
		}
	}
}




void DungGenAgent::tracePaths()
{
	/// !!!!!!!!!!!!!!!!!!!!!!!!!READ ME FUTURE ME!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	/// pick a start pos in the room pos 
	/// if all unique room pos sddressed, pick a random one
	/// if random one is it's origin, let it wander for a bit

	/// we do a normal Manhattan trace with a detour roll to simulate some chaos
	/// so normal route would be an L-shapoe
	/// a detour would make a random guess based on a coin flip
	int idleAgents = 0;
	for (int i = 0; i < numAgents; ++i) 
	{

		int32 dispX = targetPosX[i] - agentPosX[i];
		int32 dispY = targetPosY[i] - agentPosY[i];
		diffX[i] = dispX;
		diffY[i] = dispY;
		/// Why steer if we're already here?
		if (dispX != 0 && dispY != 0) 
		{
			float detourRoll = FMath::FRandRange(0.0f, 1.0f);
			/// we take a detour id we roll into detourRate
			if (detourRoll < detourRate)
			{
				/// We reuse the same roll to do a "coin flip" 
				/// using this to decide which axis to steer towards
				if (detourRoll < 0.5f * detourRate)
				{
					XAgents.Add(i);
					YAgents.Remove(i);
				}
				else
				{
					YAgents.Add(i);
					XAgents.Remove(i);
				}
			}
			/// decides to go either in X or Y
			else if (dispX != 0)
			{
				XAgents.Add(i);
				YAgents.Remove(i);
			}
			else
			{
				YAgents.Add(i);
				XAgents.Remove(i);
			}
		}
		else 
		{
			++idleAgents;
		}
	}
	updateMap();
	/// When do we stop?
	/// When target is reached
	if (idleAgents == numAgents) 
	{
		finishedTracing = true;
	}
}

void DungGenAgent::updateMap()
{

	/// For now we do this procedurally, can be potentially improved with multi-threading
	/// provess agents going in x axis
	if (XAgents.Num() > 0)
	{	
		TArray<int32> arr = XAgents.Array();

		for (int i = 0; i < arr.Num(); ++i)
		{
			int32 posX = agentPosX[arr[i]];
			if (diffX[i] < 0 && posX > 0) 
			{
				/// target X is less than agent, need to go left
				--agentPosX[arr[i]];			
			}
			else if (diffX[i] < 0 && posX < dimX - 1)
			{
				/// go right
				++agentPosX[arr[i]];
			}
			FIntVector newPos = FIntVector(agentPosX[arr[i]], agentPosY[arr[i]], 0);
			mapCellValue(newPos.X, newPos.Y) = true;
			targetMap.traversableSet.Add(newPos);

		}
	}
	/// provess agents going in y axis
	if (YAgents.Num() > 0)
	{
		TArray<int32> arr = YAgents.Array();
		for (int i = 0; i < arr.Num(); ++i)
		{
			int32 posY = agentPosY[arr[i]];

			if (diffY[i] < 0 && posY > 0)
			{
				/// target left of us, go down
				--agentPosY[arr[i]];
			}
			else if (diffY[i] < 0 && posY < dimY - 1)
			{
				/// go up
				++agentPosY[arr[i]];
			}
			FIntVector newPos = FIntVector(agentPosX[arr[i]], agentPosY[arr[i]], 0);
			mapCellValue(newPos.X, newPos.Y) = true;
			targetMap.traversableSet.Add(newPos);
		}
	}


}




bool& DungGenAgent::mapCellValue(const int32 &_x, const int32 &_y)
{
	int32 index = _y * dimX + _x;
	if (index < 0 || index > targetMap.map.Num()) 
	{
		UE_LOG(RandomDungGen_DungGenAgent, Warning, TEXT("Index on a floor is out of range, bad index: %d."), index);

		return targetMap[0];
	}
	return targetMap[index];
}

FIntVector DungGenAgent::idxToVector2D(const int32 & _idx)
{
	int32 x = _idx % dimX;
	int32 y = FMath::FloorToInt(_idx * invDimX);
	return FIntVector(x, y, 0);
}


IntArray::IntArray()
{
}

IntArray::IntArray(const TArray<int32>& _dim) : dim(_dim)
{
}

IntArray::~IntArray()
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
