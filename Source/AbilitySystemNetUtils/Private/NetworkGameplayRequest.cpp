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

#include "NetworkGameplayRequest.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(NetworkGameplayRequest)

void FNetworkGameplayRequestInfo::SetTimestamp(const float InTime)
{
	Timestamp = InTime;
	Flags |= static_cast<uint8>(ENetRequestFlags::Timestamp);
}

void FNetworkGameplayRequestInfo::SetEstimateRTT(const float InRTT)
{
	EstimateRTT = InRTT;
	Flags |= static_cast<uint8>(ENetRequestFlags::EstimateRTT);
}

void FNetworkGameplayRequestInfo::SetReconciliationId(const int32 InId)
{
	ReconciliationId = InId;
	Flags |= static_cast<uint8>(ENetRequestFlags::ReconciliationId);
}

bool FNetworkGameplayRequestInfo::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
	if (Flags & static_cast<int32>(ENetRequestFlags::Timestamp))
	{
		Ar << Timestamp;
	}
	if (Flags & static_cast<int32>(ENetRequestFlags::EstimateRTT))
	{
		Ar << EstimateRTT;
	}
	if (Flags & static_cast<int32>(ENetRequestFlags::ReconciliationId))
	{
		Ar << ReconciliationId;
	}
	
	bOutSuccess = true;
	return true;
}
