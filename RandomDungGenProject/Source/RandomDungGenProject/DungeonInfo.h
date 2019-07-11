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
	ADungeonInfo(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/// called when constructed in editor
	virtual void OnConstruction(const FTransform & Transform) override;
	///@nrief the generator to generate levels
	DungeonGenerator m_gen;
	UPROPERTY(EditAnywhere)
	FDungeonProperties m_prop;
	/// @brief Choose which floor to render
	UPROPERTY(EditAnywhere)
	int32 m_currentFloorToRender;
public:	
	///@brief This contains all instances of floor tile meshes of the current level
	UPROPERTY(BlueprintReadOnly)
	UInstancedStaticMeshComponent* m_generatedMesh;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
#if WITH_EDITOR
	///@brief call this to generate levels after setting up your m_prop
	UFUNCTION(BlueprintCallable, Category = "RandomDungGen")
	void genMap();
#endif
};
