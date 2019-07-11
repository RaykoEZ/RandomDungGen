// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DungeonProperties.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct RANDOMDUNGGEN_API FDungeonProperties
{

	GENERATED_BODY()


	///@brief number of floors to proceduraly generate
	UPROPERTY(EditAnywhere)
	int32 numFloors;

	///@brief number of rooms in each floor
	UPROPERTY(EditAnywhere)
	int32 numRoomMin;
	UPROPERTY(EditAnywhere)
	int32 numRoomMax;

	///@brief room min/max dimensions of each floor
	UPROPERTY(EditAnywhere)
	int32 roomDimMin;
	UPROPERTY(EditAnywhere)
	int32 roomDimMax;
	UPROPERTY(EditAnywhere)
	int32 floorDimMin;
	UPROPERTY(EditAnywhere)
	int32 floorDimMax;

	/// ctor and dtor
	FDungeonProperties() :
		numFloors(1),
		numRoomMin(1),
		numRoomMax(1),
		roomDimMin(1),
		roomDimMax(1),
		floorDimMin(1),
		floorDimMax(2)
	{}

	///@brief ctor uses integers to avoid type casting, please DO NOT initialize int values below 1
	FDungeonProperties(
		const int32 & _numFloor,
		const int32 & _numRoomMin,
		const int32 & _numRoomMax,
		const int32 & _roomDimMin,
		const int32 & _roomDimMax,
		const int32 & _floorDimMin,
		const int32 & _floorDimMax) :
		numFloors(_numFloor),
		numRoomMin(_numRoomMin),
		numRoomMax(_numRoomMax),
		roomDimMin(_roomDimMin),
		roomDimMax(_roomDimMax),
		floorDimMin(_floorDimMin),
		floorDimMax(_floorDimMax)
	{
		
		int32 maxRoomArea = numRoomMax * roomDimMax* roomDimMax;
		int32 minFloorArea = (floorDimMin - 1) * (floorDimMin - 1);
		if (maxRoomArea > minFloorArea)
		{
			roomDimMax = 1;
			roomDimMin = 1;
		}
	}




};