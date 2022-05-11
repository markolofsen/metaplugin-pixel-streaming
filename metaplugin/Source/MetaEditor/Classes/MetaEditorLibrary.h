// Copyright 2022 Maxim Dudin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MetaEditorLibrary.generated.h"

UENUM(BlueprintType)
enum class EMetaEditorJsonType : uint8
{
	None,
	Null,
	String,
	Number,
	Boolean,
	Array,
	Object
};

USTRUCT(BlueprintType, meta = (HasNativeMake = "MetaEditor.MetaEditorLibrary.JsonMake", HasNativeBreak = "MetaEditor.MetaEditorLibrary.Conv_JsonObjectToString"))
struct FMetaEditorJsonObject
{
	GENERATED_USTRUCT_BODY()

	TSharedPtr<class FJsonObject> Object;
};

USTRUCT(BlueprintType, meta = (HasNativeMake = "MetaEditor.MetaEditorLibrary.JsonMakeString"))
struct FMetaEditorJsonValue
{
	GENERATED_USTRUCT_BODY()

	TSharedPtr<class FJsonValue> Value;
};


UCLASS()
class METAEDITOR_API UMetaEditorLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "MetaEditor|Json", meta = (NativeMakeFunc))
	static FMetaEditorJsonObject JsonMake();

	UFUNCTION(BlueprintPure, Category = "MetaEditor|Json")
	static const FMetaEditorJsonObject& JsonMakeField(const FMetaEditorJsonObject& JsonObject, const FString& FieldName, const FMetaEditorJsonValue& Value);

	UFUNCTION(BlueprintCallable, Category = "MetaEditor|Json")
	static const FMetaEditorJsonObject& JsonSetField(const FMetaEditorJsonObject& JsonObject, const FString& FieldName, const FMetaEditorJsonValue& JsonValue);

	UFUNCTION(BlueprintPure, Category = "MetaEditor|Json")
	static bool JsonHasField(const FMetaEditorJsonObject& JsonObject, const FString& FieldName);

	UFUNCTION(BlueprintPure, Category = "MetaEditor|Json")
	static bool JsonHasTypedField(const FMetaEditorJsonObject& JsonObject, const FString& FieldName, EMetaEditorJsonType Type);

	UFUNCTION(BlueprintCallable, Category = "MetaEditor|Json")
	static const FMetaEditorJsonObject& JsonRemoveField(const FMetaEditorJsonObject& JsonObject, const FString& FieldName);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToJsonValue (JsonObject)", CompactNodeTitle = "ToValue", BlueprintAutocast, NativeBreakFunc), Category = "MetaEditor|Json|Convert")
	static FMetaEditorJsonValue Conv_JsonObjectToJsonValue(const FMetaEditorJsonObject& JsonObject, const FString& FieldName);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToString (JsonObject)", CompactNodeTitle = "ToString", BlueprintAutocast, NativeBreakFunc), Category = "MetaEditor|Json|Convert")
	static FString Conv_JsonObjectToString(const FMetaEditorJsonObject& JsonObject);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToPrettyString (JsonObject)", CompactNodeTitle = "ToPrettyString", NativeBreakFunc), Category = "MetaEditor|Json|Convert")
	static FString Conv_JsonObjectToPrettyString(const FMetaEditorJsonObject& JsonObject);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToJsonObject (String)", CompactNodeTitle = "ToJson"), Category = "MetaEditor|Json|Convert")
	static FMetaEditorJsonObject Conv_StringToJsonObject(const FString& JsonString);	

	UFUNCTION(BlueprintPure, Category = "MetaEditor|Json|Make", meta=(NativeMakeFunc))
	static FMetaEditorJsonValue JsonMakeString(const FString& Value);

	UFUNCTION(BlueprintPure, Category = "MetaEditor|Json|Make", meta = (NativeMakeFunc))
	static FMetaEditorJsonValue JsonMakeInt(int Value);

	UFUNCTION(BlueprintPure, Category = "MetaEditor|Json|Make", meta = (NativeMakeFunc))
	static FMetaEditorJsonValue JsonMakeFloat(float Value);

	UFUNCTION(BlueprintPure, Category = "MetaEditor|Json|Make", meta = (NativeMakeFunc))
	static FMetaEditorJsonValue JsonMakeBool(bool Value);

	UFUNCTION(BlueprintPure, Category = "MetaEditor|Json|Make", meta = (NativeMakeFunc))
	static FMetaEditorJsonValue JsonMakeArray(const TArray<FMetaEditorJsonValue>& Value);

	UFUNCTION(BlueprintPure, Category = "MetaEditor|Json|Make", meta = (NativeMakeFunc))
	static FMetaEditorJsonValue JsonMakeObject(const FMetaEditorJsonObject& Value);

	UFUNCTION(BlueprintPure, Category = "MetaEditor|Json|Make", meta = (NativeMakeFunc))
	static FMetaEditorJsonValue JsonMakeNull();

	UFUNCTION(BlueprintPure, Category = "MetaEditor|Json|Value")
	static EMetaEditorJsonType JsonType(const FMetaEditorJsonValue& JsonValue);

	UFUNCTION(BlueprintPure, Category = "MetaEditor|Json|Value")
	static bool JsonIsNull(const FMetaEditorJsonValue& JsonValue);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (JsonValue)", CompactNodeTitle = "=="), Category = "MetaEditor|Json|Value")
	static bool EquaEqual_JsonValue(const FMetaEditorJsonValue& A, const FMetaEditorJsonValue& B);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "NotEqual (JsonValue)", CompactNodeTitle = "!="), Category = "MetaEditor|Json|Value")
	static bool NotEqual_JsonValue(const FMetaEditorJsonValue& A, const FMetaEditorJsonValue& B);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToString (JsonValue)", CompactNodeTitle = "->", BlueprintAutocast, NativeBreakFunc), Category = "MetaEditor|Json|Value")
	static FString Conv_JsonValueToString(const FMetaEditorJsonValue& JsonValue);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToInteger (JsonValue)", CompactNodeTitle = "->", BlueprintAutocast, NativeBreakFunc), Category = "MetaEditor|Json|Value")
	static int Conv_JsonValueToInteger(const FMetaEditorJsonValue& JsonValue);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToFloat (JsonValue)", CompactNodeTitle = "->", BlueprintAutocast, NativeBreakFunc), Category = "MetaEditor|Json|Value")
	static float Conv_JsonValueToFloat(const FMetaEditorJsonValue& JsonValue);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToBool (JsonValue)", CompactNodeTitle = "->", BlueprintAutocast, NativeBreakFunc), Category = "MetaEditor|Json|Value")
	static bool Conv_JsonValueToBool(const FMetaEditorJsonValue& JsonValue);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToArray (JsonValue)", CompactNodeTitle = "->", BlueprintAutocast, NativeBreakFunc), Category = "MetaEditor|Json|Value")
	static TArray<FMetaEditorJsonValue> Conv_JsonValueToArray(const FMetaEditorJsonValue& JsonValue);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToJsonObject (JsonValue)", CompactNodeTitle = "->", BlueprintAutocast, NativeBreakFunc), Category = "MetaEditor|Json|Value")
	static FMetaEditorJsonObject Conv_JsonValueToObject(const FMetaEditorJsonValue& JsonValue);	
};