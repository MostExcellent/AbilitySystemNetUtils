/*
MIT License

Copyright (c) 2025 David Glover

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include "CoreMinimal.h"
#include "NetworkGameplayRequest.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "AbilityNetUtilsTargetTypes.generated.h"


/**
 * Target data with additional virtual functions to support network prediction patterns
 * Server should ideally be the authority for RTT. However, you might want to allow for a suggested adjustment
 * This does not support serialization on its own, inherit from this.
 * Timestamps are expected in seconds, although it may not matter with your own code.
 */
USTRUCT()
struct FNetworkedAbilityTargetData : public FGameplayAbilityTargetData
{
	GENERATED_BODY()
	
	virtual bool HasTimestamp() const { return false; }
	virtual bool HasEstimateRTT() const { return false; }
	virtual bool HasReconciliationId() const { return false; }

	virtual float GetTimestamp() const { return 0.f; }
	virtual float GetEstimateRTT() const { return 0.f; }
	virtual int32 GetReconciliationId() const { return 0; }
	
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return StaticStruct();
	}
	
	virtual FString ToString() const override
	{
		return TEXT("FNetworkedAbilityTargetData");
	}

	// Derived structs must implement NetSerialize and related type traits themselves
};

/**
 * Timestamped target data with only an origin location
 */
USTRUCT(BlueprintType)
struct FNetworkedAbilityTargetData_OriginInfo : public FNetworkedAbilityTargetData
{
	GENERATED_BODY()

	/** Struct with timestamp, local RTT estimate, and integer reconciliation ID **/
	UPROPERTY(BlueprintReadWrite, Category = Targeting, meta = (ExposeOnSpawn = true))
	FNetworkGameplayRequestInfo ReplicationInfo;

	/** Generic location data for the origin */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Targeting)
	FGameplayAbilityTargetingLocationInfo OriginLocation;

	virtual bool HasTimestamp() const override { return ReplicationInfo.CheckFlag(ENetRequestFlags::Timestamp); }
	virtual float GetTimestamp() const override { return ReplicationInfo.Timestamp; }

	virtual bool HasEstimateRTT() const override { return ReplicationInfo.CheckFlag(ENetRequestFlags::EstimateRTT); }
	virtual float GetEstimateRTT() const override { return ReplicationInfo.EstimateRTT; }

	virtual bool HasReconciliationId() const override { return ReplicationInfo.CheckFlag(ENetRequestFlags::ReconciliationId); }
	virtual int32 GetReconciliationId() const override { return ReplicationInfo.ReconciliationId; }

	virtual bool HasOrigin() const override { return true; }
	virtual FTransform GetOrigin() const override { return OriginLocation.GetTargetingTransform(); }

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FNetworkedAbilityTargetData_OriginInfo::StaticStruct();
	}

	virtual FString ToString() const override
	{
		return TEXT("FNetworkedAbilityTargetData_OriginInfo");
	}

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
};

template <>
struct TStructOpsTypeTraits<FNetworkedAbilityTargetData_OriginInfo> : TStructOpsTypeTraitsBase2<FNetworkedAbilityTargetData_OriginInfo>
{
	enum
	{
		WithNetSerializer = true
	};
};

/**
 * Timestamped target data with only a target location
 */
USTRUCT(BlueprintType)
struct FNetworkedAbilityTargetData_TargetLocationInfo : public FNetworkedAbilityTargetData
{
	GENERATED_BODY()

	/** Struct with timestamp, local RTT estimate, and integer reconciliation ID **/
	UPROPERTY(BlueprintReadWrite, Category = Targeting, meta = (ExposeOnSpawn = true))
	FNetworkGameplayRequestInfo ReplicationInfo;

	/** Generic location data for target */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Targeting)
	FGameplayAbilityTargetingLocationInfo TargetLocation;

	virtual bool HasTimestamp() const override { return ReplicationInfo.CheckFlag(ENetRequestFlags::Timestamp); }
	virtual float GetTimestamp() const override { return ReplicationInfo.Timestamp; }

	virtual bool HasEstimateRTT() const override { return ReplicationInfo.CheckFlag(ENetRequestFlags::EstimateRTT); }
	virtual float GetEstimateRTT() const override { return ReplicationInfo.EstimateRTT; }

	virtual bool HasReconciliationId() const override { return ReplicationInfo.CheckFlag(ENetRequestFlags::ReconciliationId); }
	virtual int32 GetReconciliationId() const override { return ReplicationInfo.ReconciliationId; }

	virtual bool HasEndPoint() const override { return true; }
	virtual FVector GetEndPoint() const override { return TargetLocation.GetTargetingTransform().GetLocation(); }
	virtual FTransform GetEndPointTransform() const override { return TargetLocation.GetTargetingTransform(); }

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FNetworkedAbilityTargetData_TargetLocationInfo::StaticStruct();
	}

	virtual FString ToString() const override
	{
		return TEXT("FNetworkedAbilityTargetData_TargetLocationInfo");
	}

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
};

template <>
struct TStructOpsTypeTraits<FNetworkedAbilityTargetData_TargetLocationInfo> : TStructOpsTypeTraitsBase2<FNetworkedAbilityTargetData_TargetLocationInfo>
{
	enum
	{
		WithNetSerializer = true
	};
};

/**
 * Timestamped target data with an origin and target location
 */
USTRUCT(BlueprintType)
struct FNetworkedAbilityTargetData_LocationInfo : public FNetworkedAbilityTargetData
{
	GENERATED_BODY()

	/** Struct with timestamp, local RTT estimate, and integer reconciliation ID **/
	UPROPERTY(BlueprintReadWrite, Category = Targeting, meta = (ExposeOnSpawn = true))
	FNetworkGameplayRequestInfo ReplicationInfo;

	/** Generic location data for the origin */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Targeting)
	FGameplayAbilityTargetingLocationInfo OriginLocation;

	/** Generic location data for target */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Targeting)
	FGameplayAbilityTargetingLocationInfo TargetLocation;

	virtual bool HasTimestamp() const override { return ReplicationInfo.CheckFlag(ENetRequestFlags::Timestamp); }
	virtual float GetTimestamp() const override { return ReplicationInfo.Timestamp; }

	virtual bool HasEstimateRTT() const override { return ReplicationInfo.CheckFlag(ENetRequestFlags::EstimateRTT); }
	virtual float GetEstimateRTT() const override { return ReplicationInfo.EstimateRTT; }

	virtual bool HasReconciliationId() const override { return ReplicationInfo.CheckFlag(ENetRequestFlags::ReconciliationId); }
	virtual int32 GetReconciliationId() const override { return ReplicationInfo.ReconciliationId; }

	virtual bool HasOrigin() const override { return true; }
	virtual FTransform GetOrigin() const override { return OriginLocation.GetTargetingTransform(); }

	virtual bool HasEndPoint() const override { return true; }
	virtual FVector GetEndPoint() const override { return TargetLocation.GetTargetingTransform().GetLocation(); }
	virtual FTransform GetEndPointTransform() const override { return TargetLocation.GetTargetingTransform(); }

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FNetworkedAbilityTargetData_LocationInfo::StaticStruct();
	}

	virtual FString ToString() const override
	{
		return TEXT("FNetworkedAbilityTargetData_LocationInfo");
	}

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
};

template <>
struct TStructOpsTypeTraits<FNetworkedAbilityTargetData_LocationInfo> : TStructOpsTypeTraitsBase2<FNetworkedAbilityTargetData_LocationInfo>
{
	enum
	{
		WithNetSerializer = true
	};
};
