// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "RandomDungGen.h"

DEFINE_LOG_CATEGORY(RandomDungGenModule);
#define LOCTEXT_NAMESPACE "FRandomDungGenModule"

void FRandomDungGenModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	UE_LOG(RandomDungGenModule, Warning, TEXT("RandomDungGenModule module started."));
}

void FRandomDungGenModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	UE_LOG(RandomDungGenModule, Warning, TEXT("RandomDungGenModule module shutting down."));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FRandomDungGenModule, RandomDungGen)