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
#include "NetworkGameplayRequest.generated.h"

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class ENetRequestFlags : uint8
{
	None = 0 UMETA(Hidden),
	Timestamp = 1 << 0,
	EstimateRTT = 1 << 1,
	ReconciliationId = 1 << 2,
};

/**
 * Packages the core request timing/replication info.
 */
USTRUCT(BlueprintType)
struct FNetworkGameplayRequestInfo
{
	GENERATED_BODY()
	
	FNetworkGameplayRequestInfo() : Timestamp(0.f), EstimateRTT(0.f), ReconciliationId(0), Flags(0)
	{
	}
	
	FNetworkGameplayRequestInfo(const float InTime, const float InRTT, const int32 InId) : Flags(0)
	{
		Timestamp = InTime;
		EstimateRTT = InRTT;
		ReconciliationId = InId;
		Flags |= static_cast<uint8>(ENetRequestFlags::Timestamp);
		Flags |= static_cast<uint8>(ENetRequestFlags::EstimateRTT);
		Flags |= static_cast<uint8>(ENetRequestFlags::ReconciliationId);
	}

	UPROPERTY(BlueprintReadWrite, Category = "Targeting|Replication")
	float Timestamp;
	
	UPROPERTY(BlueprintReadWrite, Category = "Targeting|Replication")
	float EstimateRTT;
	
	UPROPERTY(BlueprintReadWrite, Category = "Targeting|Replication")
	float ReconciliationId;
	
	UPROPERTY(BlueprintReadWrite, Category = "Targeting|Replication", meta = (Bitmask, BitmaskEnum = "ENetRequestFlags", ExposeOnSpawn = true))
	int32 Flags;
	
	bool CheckFlag(ENetRequestFlags InFlag) const
	{
		return Flags & static_cast<int32>(InFlag);
	}
	
	void SetTimestamp(const float InTime);
	
	void SetEstimateRTT(const float InRTT);
	
	void SetReconciliationId(const int32 InId);
	
	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
};

template <>
struct TStructOpsTypeTraits<FNetworkGameplayRequestInfo> : public TStructOpsTypeTraitsBase2<FNetworkGameplayRequestInfo>
{
	enum
	{
		WithNetSerializer = true
	};
};
