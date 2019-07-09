// Fill out your copyright notice in the Description page of Project Settings.


#include "DungGenAgent.h"

DEFINE_LOG_CATEGORY(RandomDungGen_DungGenAgent);


DungGenAgent::DungGenAgent()
{
}

DungGenAgent::DungGenAgent(
	const int32 &_numRooms,
	const int32 &_dimX,
	const int32 &_dimY,
	const float  &_detourRate,
	const TArray<int32> &_roomDimX,
	const TArray<int32> &_roomDimY,
	const FloorMap & _map
)
	:
	numRoom(_numRooms),
	dimX(_dimX),
	dimY(_dimY),
	detourRate(_detourRate),
	roomDimX(_roomDimX),
	roomDimY(_roomDimY),
	targetMap(_map)
{
	init();
}

DungGenAgent::~DungGenAgent()
{
}

void DungGenAgent::reset(
	const int32 &_numRooms,
	const int32 & _dimX, 
	const int32 & _dimY, 
	const float & _detourRate,
	const TArray<int32> &_roomDimX,
	const TArray<int32> &_roomDimY,
	const FloorMap & _map
)
{
	numRoom = _numRooms;
	dimX = _dimX;
	dimY = dimY;
	detourRate = _detourRate;
	roomDimX = _roomDimX;
	roomDimY = _roomDimY;
	targetMap = _map;

	init();
}

FloorMap DungGenAgent::createFloorMap()
{

	insertRooms();
	tracePaths();

	return targetMap;
}

/// TO DO - Generate random cross roads for agents to converge to
void DungGenAgent::init()
{
	if (detourRate >= 1.0f) 
	{
		UE_LOG(RandomDungGen_DungGenAgent, Warning, TEXT("Detour rate is a probability of domain {0.1}, please initialize between 0 and 1."));

		detourRate = 0.0f;
	
	}
	invDimX = 1 / dimX;
	invDimY = 1 / dimY;
	/// reserve memoory since we know the problem size
	cleanup();
	/// We construct a minimal skeleton to ensure connectivity of the dungeon before tracing newer routes
	setupMinimalConnections();
	/// setting init Positions for all agents
	/// We occupy all necessary rooms first and leftover agents start in random rooms


	numAgents = targetMap.roomPosSet.Num();
	UE_LOG(RandomDungGen_DungGenAgent, Warning, TEXT("Number of agents in this parse : %d."), numAgents);
	targetPosX.SetNum(numAgents);
	targetPosY.SetNum(numAgents);
	agentPosX.SetNum(numAgents);
	agentPosY.SetNum(numAgents);
	diffX.SetNum(numAgents);
	diffY.SetNum(numAgents);
	idleAgents.Reserve(numAgents);
	XAgents.Reserve(numAgents);
	YAgents.Reserve(numAgents);

	if (targetMap.roomPosSet.Num() > 0)
	{
		auto traversable = targetMap.roomPosSet.Array();
		for (int g = 0; g < numAgents; ++g)
		{
			/// initialize target positions, similar to setting positions but we remove self position
			auto otherRooms = targetMap.roomPosSet.Array();
			/// removeyourself from potential seeking targets, you know, don't chase your tails

			if (g < otherRooms.Num())
			{

				agentPosX[g] = traversable[g].X;
				agentPosY[g] = traversable[g].Y;
			}
			else
			{
				int randIdx = FMath::RandRange(0, otherRooms.Num() - 1);

				agentPosX[g] = traversable[randIdx].X;
				agentPosY[g] = traversable[randIdx].Y;

			}

			int randTargetIdx = FMath::RandRange(0, otherRooms.Num() - 1);
			int randXOffset = FMath::RandRange(0, roomDimX[randTargetIdx] - 1);
			int randYOffest = FMath::RandRange(0, roomDimY[randTargetIdx] - 1);
			targetPosX[g] = otherRooms[randTargetIdx].X + randXOffset;
			targetPosY[g] = otherRooms[randTargetIdx].Y + randYOffest;

		}
	}
	
}


void DungGenAgent::setupMinimalConnections()
{

	numAgents = 1;
	int numRoom = targetMap.roomPosSet.Num();
	UE_LOG(RandomDungGen_DungGenAgent, Warning, TEXT("Number of agents in this parse : %d."), numAgents);
	targetPosX.SetNum(numRoom-1);
	targetPosY.SetNum(numRoom-1);
	agentPosX.SetNum(numAgents);
	agentPosY.SetNum(numAgents);
	diffX.SetNum(numAgents);
	diffY.SetNum(numAgents);
	XAgents.Reserve(numAgents);
	YAgents.Reserve(numAgents);



	/// setting init Positions for all agents
	/// We occupy all necessary rooms first and leftover agents start in random rooms
	if (targetMap.roomPosSet.Num() > 0)
	{
		auto roomPos = targetMap.roomPosSet.Array();
		TSet<FIntVector> targetRooms;
		targetRooms.Reserve(numRoom);



		/// get a random initial position for an agent
		int roomIdx = FMath::RandRange(0, roomPos.Num() - 1);
		auto pos = roomPos[roomIdx];
		agentPosX[0] = pos.X;
		agentPosY[0] = pos.Y;


		//targetRooms.Add(pos);
		roomPos.RemoveSingle(pos);
		roomPos.Shrink();

		/// fill in the from and to table and a traversal log
		/// this will be used to set agent positions and targets
		for (int i = 0; i < roomPos.Num(); ++i)
		{
			int randXOffset = FMath::RandRange(0, roomDimX[i] - 1);
			int randYOffest = FMath::RandRange(0, roomDimY[i] - 1);
			auto offset = FIntVector(randXOffset, randYOffest, 0);
			auto pos = roomPos[i];
			
			targetPosX[i] = pos.X + offset.X;
			targetPosY[i] = pos.Y + offset.Y;
		}	
		traceSpanningTree();

		cleanup();
	}

}


void::DungGenAgent::traceSpanningTree() 
{
	bool finishedTracing;
	/// Why steer if we're already here?
	for (int i = 0; i < targetPosX.Num(); ++i) 
	{
		finishedTracing = false;
		while (!finishedTracing)
		{
			int32 dispX = targetPosX[i] - agentPosX[0];
			int32 dispY = targetPosY[i] - agentPosY[0];
			diffX[0] = dispX;
			diffY[0] = dispY;
			int32 distX = FMath::Abs(dispX);
			int32 distY = FMath::Abs(dispY);
			if (distX > 0 || distY > 0)
			{
				/// we take a detour id we roll into detourRate
				if (dispX != 0)
				{
					XAgents.Add(0);
				}
				else
				{
					YAgents.Add(0);
				}
			}
			else
			{
				finishedTracing = true;
			}
			updateMap();	
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
	UE_LOG(RandomDungGen_DungGenAgent, Warning, TEXT("num agents: %d."), numAgents);
	
	while (idleAgents.Num() < numAgents)
	{
		
		for (int i = 0; i < numAgents; ++i)
		{

			int32 dispX = targetPosX[i] - agentPosX[i];
			int32 dispY = targetPosY[i] - agentPosY[i];
			diffX[i] = dispX;
			diffY[i] = dispY;
			int32 distX = FMath::Abs(dispX);
			int32 distY = FMath::Abs(dispY);
			/// Why steer if we're already here?
			if (distX > 0 || distY > 0)
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
					}
					else
					{
						YAgents.Add(i);
					}
				}
				/// decides to go either in X or Y
				else if (dispX != 0)
				{
					XAgents.Add(i);
				}
				else
				{
					YAgents.Add(i);
				}
			}
			else 
			{

				idleAgents.Add(i);
				UE_LOG(RandomDungGen_DungGenAgent, Warning, TEXT("numfinished : %d."), idleAgents.Num());
			}
			
		}
		updateMap();


	}

	
	/// When do we stop?
	/// When target is reached

}

void DungGenAgent::insertRooms()
{
	auto arr = targetMap.roomPosSet.Array();
	for (int i = 0; i < arr.Num(); ++i)
	{
		int32 x = agentPosX[i];
		int32 y = agentPosY[i];
		for (int j = 0; j < roomDimX[i]; ++j)
		{
			for (int k = 0 ; k < roomDimY[i]; ++k)
			{
				int32 newX = x + j;
				int32 newY = y + k;
				if (newX < dimX && newY < dimY) 
				{
					mapCellValue(newX, newY) = true;
					targetMap.traversableSet.Add(FIntVector(newX, newY, 0));
				}

			}
		}


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
			if (diffX[arr[i]] > 0 && posX < dimX - 1)
			{
				/// target X is less than agent, need to go right
				agentPosX[arr[i]] += 1;	
				FIntVector newPos = FIntVector(agentPosX[arr[i]], agentPosY[arr[i]], 0);
				mapCellValue(newPos.X, newPos.Y) = true;
				targetMap.traversableSet.Add(newPos);
			}
			else if (diffX[arr[i]] < 0 && posX > 0)
			{
				/// go left
				agentPosX[arr[i]] -= 1;
				FIntVector newPos = FIntVector(agentPosX[arr[i]], agentPosY[arr[i]], 0);
				mapCellValue(newPos.X, newPos.Y) = true;
				targetMap.traversableSet.Add(newPos);
			}
			else 
			{
				YAgents.Add(arr[i]);
			}


		}
	}
	/// provess agents going in y axis
	if (YAgents.Num() > 0)
	{
		TArray<int32> arr = YAgents.Array();
		for (int i = 0; i < arr.Num(); ++i)
		{
			int32 posY = agentPosY[arr[i]];

			if (diffY[arr[i]] > 0 && posY < dimY - 1)
			{
				/// target above of us, go up
				agentPosY[arr[i]] += 1;
				FIntVector newPos = FIntVector(agentPosX[arr[i]], agentPosY[arr[i]], 0);
				mapCellValue(newPos.X, newPos.Y) = true;
				targetMap.traversableSet.Add(newPos);
			}
			else if (diffY[arr[i]] < 0 && posY > 0)
			{
				/// go doen
				agentPosY[arr[i]] -= 1;
				FIntVector newPos = FIntVector(agentPosX[arr[i]], agentPosY[arr[i]], 0);
				mapCellValue(newPos.X, newPos.Y) = true;
				targetMap.traversableSet.Add(newPos);
			}

		}
	}

	XAgents.Empty();
	YAgents.Empty();
}

void DungGenAgent::cleanup()
{
	targetPosX.Empty();
	targetPosY.Empty();
	agentPosX.Empty();
	agentPosY.Empty();
	XAgents.Empty();
	YAgents.Empty();
	diffX.Empty();
	diffY.Empty();
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




FloorMap::FloorMap()
{
}

FloorMap::FloorMap(const TArray<bool>& _map, const TSet<FIntVector> &_roomPos)
	: 
map(_map), 
roomPosSet(_roomPos)
{
}

FloorMap::~FloorMap()
{
}
