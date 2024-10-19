// Copyright © Jack Holland.
//
// DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
// Version 2, December 2004
// 
// Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>
// 
// Everyone is permitted to copy and distribute verbatim or modified
// copies of this license document, and changing it is allowed as long
// as the name is changed.
// 
// DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "BFSquirrel/Squirrel/BFSquirrelStream.h"
#include "BFSquirrel/Squirrel/squirrelnoise5.h"
#include "BFSquirrel/Squirrel/BFSquirrelUtility.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BFSquirrelNoiseBPFL.generated.h"


UCLASS()
class BFSQUIRREL_API UBFSquirrelNoiseBPFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Sets the global noise seed stored within the UBFSquirrelDeveloperSettings class.
	UFUNCTION(BlueprintCallable, Category="Squirrel", meta=(Keywords="noise, rand, random, rng"))
	static void SquirrelRandSetGlobalSeed(int32 Seed) {Sqrl::SetGlobalRandNoiseIndex(static_cast<uint32>(Seed));}

	// Sets the global noise index.
	UFUNCTION(BlueprintCallable, Category="Squirrel", meta=(Keywords="noise, rand, random, rng"))
	static void SquirrelRandSetGlobalIndex(int32 Index) {Sqrl::SetGlobalRandNoiseIndex(Index);}

	// Gets the current global noise seed and index used for squirrelnoise.
	UFUNCTION(BlueprintCallable, BlueprintPure=true, Category="Squirrel", meta=(Keywords="noise, rand, random, rng"))
	static void SquirrelRandGetGlobalSeedAndIndex(int32& Seed, int32& Index) { Seed = Sqrl::GetGlobalRandNoiseSeed(); Index =  Sqrl::GetGlobalRandNoiseIndex(); }

	// Sets the streams noise seed stored within the UBFSquirrelDeveloperSettings class.
	UFUNCTION(BlueprintCallable, Category="Squirrel", meta=(Keywords="noise, rand, random, rng"))
	static void SquirrelStreamSetSeed(UPARAM(ref)FSquirrelStream& SquirrelStream, int32 Seed) {SquirrelStream.SetSeed(Seed);}

	// Sets the streams noise index.
	UFUNCTION(BlueprintCallable, Category="Squirrel", meta=(Keywords="noise, rand, random, rng"))
	static void SquirrelStreamSetIndex(UPARAM(ref)FSquirrelStream& SquirrelStream, int32 Index) { SquirrelStream.SetIndex(Index);}
	
	// Resets the streams noise seed and index to their initial values.
	UFUNCTION(BlueprintCallable, Category="Squirrel", meta=(Keywords="noise, rand, random, rng"))
	static void SquirrelStreamReset(UPARAM(ref)FSquirrelStream& SquirrelStream) { SquirrelStream.Reset();}

	// Gets the streams global noise seed and index used for squirrelnoise.
	UFUNCTION(BlueprintCallable, BlueprintPure=true, Category="Squirrel", meta=(Keywords="noise, rand, random, rng"))
	static void SquirrelStreamGetSeedAndIndex(UPARAM(ref)FSquirrelStream& SquirrelStream, int32& Seed, int32& Index) { Seed = SquirrelStream.GetSeed(); Index = SquirrelStream.GetIndex(); }
	

private:
	// Private helpers
	UFUNCTION(BlueprintCallable,  CustomThunk, meta=(CustomStructureParam="ParamA,ParamB,ParamC,ParamD,Result", BlueprintInternalUseOnly = "true"))
	static void InternalSquirrelRandK2(ESquirrelRandType RandomType,int ParamA, int ParamB, int ParamC, int ParamD, int& Result) { check(0); }
	UFUNCTION(BlueprintCallable,  CustomThunk, meta=(CustomStructureParam="ParamA,ParamB,ParamC,ParamD,Result", BlueprintInternalUseOnly = "true"))
	static void InternalSquirrelStreamRandK2(ESquirrelRandType RandomType, bool bReverse, UPARAM(ref)FSquirrelStream& Stream, int ParamA, int ParamB, int ParamC, int ParamD, int& Result) { check(0); }

	DECLARE_FUNCTION(execInternalSquirrelRandK2);
	DECLARE_FUNCTION(execInternalSquirrelStreamRandK2);
	
};
































