// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonGenerator.h"
#include "DungeonInfo.generated.h"


UCLASS()
class RANDOMDUNGGENPROJECT_API ADungeonInfo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADungeonInfo();
	DungeonGenerator m_gen;
	DungeonProperties m_prop;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
