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

#include "Abilities/AbilityNetUtilsTargetTypes.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AbilityNetUtilsTargetTypes)


bool FNetworkedAbilityTargetData_OriginInfo::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
	bool bReplicationInfoSuccess = true;
	bool bOriginSuccess = true;

	ReplicationInfo.NetSerialize(Ar, Map, bReplicationInfoSuccess);

	if (!bReplicationInfoSuccess || Ar.IsError())
	{
		bOutSuccess = false;
		return false;
	}

	OriginLocation.NetSerialize(Ar, Map, bOriginSuccess);

	if (!bOriginSuccess || Ar.IsError())
	{
		bOutSuccess = false;
		return false;
	}

	bOutSuccess = true;
	return true;
}

bool FNetworkedAbilityTargetData_TargetLocationInfo::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
	bool bReplicationInfoSuccess = true;
	bool bTargetSuccess = true;

	ReplicationInfo.NetSerialize(Ar, Map, bReplicationInfoSuccess);

	if (!bReplicationInfoSuccess || Ar.IsError())
	{
		bOutSuccess = false;
		return false;
	}

	TargetLocation.NetSerialize(Ar, Map, bTargetSuccess);

	if (!bTargetSuccess || Ar.IsError())
	{
		bOutSuccess = false;
		return false;
	}

	bOutSuccess = true;
	return true;
}

bool FNetworkedAbilityTargetData_LocationInfo::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
	bool bReplicationInfoSuccess = true;
	bool bOriginSuccess = true;
	bool bTargetSuccess = true;

	ReplicationInfo.NetSerialize(Ar, Map, bReplicationInfoSuccess);

	if (!bReplicationInfoSuccess || Ar.IsError())
	{
		bOutSuccess = false;
		return false;
	}

	OriginLocation.NetSerialize(Ar, Map, bOriginSuccess);

	if (!bOriginSuccess || Ar.IsError())
	{
		bOutSuccess = false;
		return false;
	}

	TargetLocation.NetSerialize(Ar, Map, bTargetSuccess);

	if (!bTargetSuccess || Ar.IsError())
	{
		bOutSuccess = false;
		return false;
	}

	bOutSuccess = true;
	return true;
}
