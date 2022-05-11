// Copyright 2022 Maxim Dudin. All Rights Reserved.

#include "MetaEditorLibrary.h"

#include "Dom/JsonObject.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Policies/CondensedJsonPrintPolicy.h"

typedef TSharedPtr<FJsonObject> FJsonObjectPtr;
typedef TSharedPtr<FJsonValue> FJsonValuePtr;

FMetaEditorJsonObject UMetaEditorLibrary::JsonMake()
{
	FMetaEditorJsonObject Object;
	Object.Object = MakeShareable(new FJsonObject);
	return Object;
}

const FMetaEditorJsonObject& UMetaEditorLibrary::JsonSetField(const FMetaEditorJsonObject& JsonObject, const FString& FieldName, const FMetaEditorJsonValue& JsonValue)
{
	if (JsonObject.Object.IsValid() && JsonValue.Value.IsValid())
	{
		JsonObject.Object->SetField(FieldName, JsonValue.Value);
	}
	return JsonObject;
}

bool UMetaEditorLibrary::JsonHasField(const FMetaEditorJsonObject& JsonObject, const FString& FieldName)
{
	if (JsonObject.Object.IsValid())
	{
		return JsonObject.Object->HasField(FieldName);
	}
	return false;
}

bool UMetaEditorLibrary::JsonHasTypedField(const FMetaEditorJsonObject& JsonObject, const FString& FieldName, EMetaEditorJsonType Type)
{
	if (JsonObject.Object.IsValid())
	{
		if (JsonObject.Object->HasField(FieldName))
		{
			return JsonObject.Object->GetField<EJson::None>(FieldName)->Type == (EJson)Type;
		}
	}
	return false;
}

const FMetaEditorJsonObject& UMetaEditorLibrary::JsonRemoveField(const FMetaEditorJsonObject& JsonObject, const FString& FieldName)
{
	if (JsonObject.Object.IsValid())
	{
		JsonObject.Object->RemoveField(FieldName);
	}
	return JsonObject;
}

FMetaEditorJsonValue UMetaEditorLibrary::Conv_JsonObjectToJsonValue(const FMetaEditorJsonObject& JsonObject, const FString& FieldName)
{
	FMetaEditorJsonValue Value;
	if (JsonObject.Object.IsValid())
	{
		Value.Value = JsonObject.Object->GetField<EJson::None>(FieldName);
	}
	return Value;
}

FString UMetaEditorLibrary::Conv_JsonObjectToString(const FMetaEditorJsonObject& JsonObject)
{
	FString Result;
	if (JsonObject.Object.IsValid())
	{
		TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Result, 0);
		FJsonSerializer::Serialize(JsonObject.Object.ToSharedRef(), JsonWriter);
	}
	return Result;
}

FString UMetaEditorLibrary::Conv_JsonObjectToPrettyString(const FMetaEditorJsonObject& JsonObject)
{
	FString Result;
	if (JsonObject.Object.IsValid())
	{
		TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&Result, 0);
		FJsonSerializer::Serialize(JsonObject.Object.ToSharedRef(), JsonWriter);
	}
	return Result;
}

FMetaEditorJsonObject UMetaEditorLibrary::Conv_StringToJsonObject(const FString& JsonString)
{
	FMetaEditorJsonObject Object;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
	FJsonSerializer::Deserialize(Reader, Object.Object);
	return Object;
}

const FMetaEditorJsonObject& UMetaEditorLibrary::JsonMakeField(const FMetaEditorJsonObject& JsonObject, const FString& FieldName, const FMetaEditorJsonValue& JsonValue)
{
	if (JsonObject.Object.IsValid() && JsonValue.Value.IsValid())
	{
		JsonObject.Object->SetField(FieldName, JsonValue.Value);
	}
	return JsonObject;
}

FMetaEditorJsonValue UMetaEditorLibrary::JsonMakeString(const FString& StringValue)
{
	FMetaEditorJsonValue Value;
	Value.Value = MakeShareable(new FJsonValueString(StringValue));
	return Value;
}

FMetaEditorJsonValue UMetaEditorLibrary::JsonMakeInt(int IntValue)
{
	FMetaEditorJsonValue Value;
	Value.Value = MakeShareable(new FJsonValueNumber(IntValue));
	return Value;
}

FMetaEditorJsonValue UMetaEditorLibrary::JsonMakeFloat(float FloatValue)
{
	FMetaEditorJsonValue Value;
	Value.Value = MakeShareable(new FJsonValueNumber(FloatValue));
	return Value;
}

FMetaEditorJsonValue UMetaEditorLibrary::JsonMakeBool(bool BoolValue)
{
	FMetaEditorJsonValue Value;
	Value.Value = MakeShareable(new FJsonValueBoolean(BoolValue));
	return Value;
}

FMetaEditorJsonValue UMetaEditorLibrary::JsonMakeArray(const TArray<FMetaEditorJsonValue>& ArrayValue)
{
	FMetaEditorJsonValue Value;
	TArray<FJsonValuePtr> Array;
	for (const FMetaEditorJsonValue& V : ArrayValue)
	{
		if (V.Value.IsValid())
		{
			Array.Add(V.Value);
		}
	}
	Value.Value = MakeShareable(new FJsonValueArray(Array));
	return Value;
}

FMetaEditorJsonValue UMetaEditorLibrary::JsonMakeObject(const FMetaEditorJsonObject& ObjectValue)
{
	FMetaEditorJsonValue Value;
	Value.Value = MakeShareable(new FJsonValueObject(ObjectValue.Object));
	return Value;
}

FMetaEditorJsonValue UMetaEditorLibrary::JsonMakeNull()
{
	FMetaEditorJsonValue Value;
	Value.Value = MakeShareable(new FJsonValueNull());
	return Value;
}

EMetaEditorJsonType UMetaEditorLibrary::JsonType(const FMetaEditorJsonValue& JsonValue)
{
	if (JsonValue.Value.IsValid())
	{
		return (EMetaEditorJsonType)JsonValue.Value->Type;
	}
	return EMetaEditorJsonType::None;
}

bool UMetaEditorLibrary::JsonIsNull(const FMetaEditorJsonValue& JsonValue)
{
	if (JsonValue.Value.IsValid())
	{
		return JsonValue.Value->IsNull();
	}
	return true;
}

bool UMetaEditorLibrary::EquaEqual_JsonValue(const FMetaEditorJsonValue& A, const FMetaEditorJsonValue& B)
{
	if (A.Value.IsValid() != B.Value.IsValid())
	{
		return false;
	}

	if (A.Value.IsValid() && B.Value.IsValid())
	{
		if (!FJsonValue::CompareEqual(*A.Value, *B.Value))
		{
			return false;
		}
	}

	return true;
}

bool UMetaEditorLibrary::NotEqual_JsonValue(const FMetaEditorJsonValue& A, const FMetaEditorJsonValue& B)
{
	if (A.Value.IsValid() != B.Value.IsValid())
	{
		return true;
	}

	if (A.Value.IsValid() && B.Value.IsValid())
	{
		if (!FJsonValue::CompareEqual(*A.Value, *B.Value))
		{
			return true;
		}
	}

	return false;
}

FString UMetaEditorLibrary::Conv_JsonValueToString(const FMetaEditorJsonValue& JsonValue)
{	
	if (JsonValue.Value.IsValid())
	{
		return JsonValue.Value->AsString();
	}
	FString Empty;
	return Empty;
}

int UMetaEditorLibrary::Conv_JsonValueToInteger(const FMetaEditorJsonValue& JsonValue)
{
	if (JsonValue.Value.IsValid())
	{
		int Result = 0;
		JsonValue.Value->TryGetNumber(Result);
		return Result;
	}
	return 0;
}

float UMetaEditorLibrary::Conv_JsonValueToFloat(const FMetaEditorJsonValue& JsonValue)
{
	if (JsonValue.Value.IsValid())
	{
		return JsonValue.Value->AsNumber();
	}
	return 0.0f;
}

bool UMetaEditorLibrary::Conv_JsonValueToBool(const FMetaEditorJsonValue& JsonValue)
{
	if (JsonValue.Value.IsValid())
	{
		return JsonValue.Value->AsBool();
	}
	return false;
}

TArray<FMetaEditorJsonValue> UMetaEditorLibrary::Conv_JsonValueToArray(const FMetaEditorJsonValue& JsonValue)
{
	TArray<FMetaEditorJsonValue> Result;

	if (JsonValue.Value.IsValid())
	{
		if (JsonValue.Value->Type == EJson::Array)
		{
			for (const auto& Val : JsonValue.Value->AsArray())
			{
				FMetaEditorJsonValue Tmp;
				Tmp.Value = Val;
				Result.Add(Tmp);
			}
		}
	}

	return Result;
}

FMetaEditorJsonObject UMetaEditorLibrary::Conv_JsonValueToObject(const FMetaEditorJsonValue& JsonValue)
{
	FMetaEditorJsonObject Object;
	if (JsonValue.Value.IsValid())
	{
		Object.Object = JsonValue.Value->AsObject();
	}
	return Object;
}