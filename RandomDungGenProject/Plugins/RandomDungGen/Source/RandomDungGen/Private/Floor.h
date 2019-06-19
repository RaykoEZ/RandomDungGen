// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Array.h"
#include "Vector.h"
#include "CoreMinimal.h"

/**
 * 
 */
struct FloorProperties 
{
	FloorProperties();
	~FloorProperties();

	///@brief number of floors
	uint8 m_numFloors;
	///@brief number of rooms in each floor
	TArray<uint8> m_numRooms;

	///@brief floor dimensions of each floor
	TArray<FVector2D> m_floorDims;

};


class Floor
{
public:
	Floor();
	~Floor();
};
