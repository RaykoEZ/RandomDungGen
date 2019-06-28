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
	const FloorMap & _map
)
	:
	dimX(_dimX),
	dimY(_dimY),
	numAgents(_numAgents),
	detourRate(_detourRate), 
	targetMap(_map)
{

	/// reserve memoory since we know the problem size
	targetPosX.Reserve(_numAgents);
	targetPosY.Reserve(_numAgents);
	agentPosX.Reserve(_numAgents);
	agentPosY.Reserve(_numAgents);

	upAgents.Reserve(_numAgents);
	downAgents.Reserve(_numAgents);
	leftAgents.Reserve(_numAgents);
	rightAgents.Reserve(_numAgents);
}

DungGenAgent::~DungGenAgent()
{
}

void DungGenAgent::init()
{
	/// setting init Positions for all agents
	/// We occupy all necessary rooms first and leftover agents start in random rooms
	auto traversable = targetMap.traversableSet.Array();
	for (int g = 0; g < numAgents; ++g) 
	{
		if (g < targetMap.traversableSet.Num())
		{
			agentPosX[g] = (int32)traversable[g].X;
			agentPosY[g] = (int32)traversable[g].Y;
		}
		else
		{
			int randIdx = FMath::RandRange(0, targetMap.traversableSet.Num());
			agentPosX[g] = (int32)traversable[randIdx].X;
			agentPosY[g] = (int32)traversable[randIdx].Y;
		}
	
		/// All agents start facing up by default
		upAgents.Add(g);
	}


	/// initialize target positions

	// TO DO

}

FloorMap DungGenAgent::tracePaths()
{
	/// !!!!!!!!!!!!!!!!!!!!!!!!!READ ME FUTURE ME!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	/// pick a start pos in the room pos 
	/// if all unique room pos sddressed, pick a random one
	/// if random one is it's origin, let it wander for a bit

	/// we do a normal Manhattan trace with a detour roll to simulate some chaos
	/// We priortize y direction (vertical) over x (horizontal)
	/// so normal route would be an L-shapoe
	/// a detour would make a "go vertical" state become "go horizontal"




	return targetMap;
}





bool& DungGenAgent::at(const int32 &_x, const int32 &_y)
{
	int32 index = _y * dimX + _x;
	if (index < 0 || index > targetMap.map.Num()) 
	{
		UE_LOG(RandomDungGen_DungGenAgent, Warning, TEXT("Index on a floor is out of range, bad index: %d."), index);

		return targetMap[0];
	}
	return targetMap[index];
}

int32 DungGenAgent::goVertical(const bool & _up, const int32 &_currentY)
{
	int32 ret = _currentY;
	if (_up && _currentY < dimY ) 
	{
		++ret;
		return ret;
	
	}
	else if (!_up && _currentY > 0) 
	{
		--ret;
		return ret;
	}
	UE_LOG(RandomDungGen_DungGenAgent, Fatal, TEXT("Agent cannot move up or down."));
	return ret;
}

int32 DungGenAgent::goHorizontal(const bool & _right, const int32 &_currentX)
{
	int32 ret = _currentX;
	if (_right && _currentX < dimX)
	{
		++ret;
		return ret;

	}
	else if (!_right && _currentX > 0)
	{
		--ret;
		return ret;
	}
	UE_LOG(RandomDungGen_DungGenAgent, Fatal, TEXT("Agent cannot move up or down."));

	return ret;
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
