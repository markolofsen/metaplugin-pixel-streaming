// Copyright 2022 Maxim Dudin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MetaEditorConnector.generated.h"

UCLASS()
class METAEDITOR_API AMetaEditorConnector : public AActor
{
	GENERATED_BODY()
	
public:	
	AMetaEditorConnector();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};