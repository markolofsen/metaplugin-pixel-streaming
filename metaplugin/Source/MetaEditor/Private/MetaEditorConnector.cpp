// Copyright 2022 Maxim Dudin. All Rights Reserved.

#include "MetaEditorConnector.h"

AMetaEditorConnector::AMetaEditorConnector()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void AMetaEditorConnector::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMetaEditorConnector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}