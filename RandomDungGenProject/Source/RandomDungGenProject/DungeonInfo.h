// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonGenerator.h"
#include "Runtime/Engine/Classes/Components/InstancedStaticMeshComponent.h"
#include "DungeonInfo.generated.h"


UCLASS()
class RANDOMDUNGGENPROJECT_API ADungeonInfo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADungeonInfo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/// called when constructed in editor
	virtual void OnConstruction(const FTransform & Transform) override;
	DungeonGenerator m_gen;
	DungeonProperties m_prop;
	UPROPERTY(EditAnywhere)
	UInstancedStaticMeshComponent* m_generatedMesh;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
