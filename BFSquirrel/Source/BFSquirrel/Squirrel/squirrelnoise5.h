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

//-----------------------------------------------------------------------------------------------
// Modified version of the original SquirrelNoise5 code by Squirrel Eiserloh <http://eiserloh.net/noise/SquirrelNoise5.hpp>
//


/*
 * Squirrel Noise 5 Helper namespace, See Sqrl::Helpers::TDistributionMetricTracker<int/float> for a utility struct to track the distribution of values.
 * 
 * All Functions besides Index based ones advance the global index each time which means we have the option to reverse the order of the random values generated,
 * this is useful if you want to replay the same randomness in reverse order or have now changed the global index and want to go back to the previous state you are aware of.
 * Although keep in mind this is a global seed and index, if you really need consistent behaviour consider using a FSquirrelStream instead.
 * */
namespace Sqrl
{
	// Returns a psuedo-random signed integer based on the 1D index, benefits of index based is deterministic and order-independent as long as the global seed is the same(UBFSquirrelDeveloperSettings::GlobalNoiseSeed).
	int32		RandInt1DIndex( int32 X );
	// Returns a psuedo-random signed integer based on the 2D index, benefits of index based is deterministic and order-independent as long as the global seed is the same(UBFSquirrelDeveloperSettings::GlobalNoiseSeed).
	int32		RandInt2DIndex( int32 X, int32 Y );
	// Returns a psuedo-random signed integer based on the 3D index, benefits of index based is deterministic and order-independent as long as the global seed is the same(UBFSquirrelDeveloperSettings::GlobalNoiseSeed).
	int32		RandInt3DIndex( int32 X, int32 Y, int32 Z );
	// Returns a psuedo-random signed integer based on the 4D index, benefits of index based is deterministic and order-independent as long as the global seed is the same(UBFSquirrelDeveloperSettings::GlobalNoiseSeed).
	int32		RandInt4DIndex( int32 X, int32 Y, int32 Z, int32 T );
	
	// Returns a psuedo-random unsigned integer based on the 1D index, benefits of index based is deterministic and order-independent as long as the global seed is the same(UBFSquirrelDeveloperSettings::GlobalNoiseSeed).
	uint32		RandUInt1DIndex( int32 X );
	// Returns a psuedo-random unsigned integer based on the 2D index, benefits of index based is deterministic and order-independent as long as the global seed is the same(UBFSquirrelDeveloperSettings::GlobalNoiseSeed).
	uint32		RandUInt2DIndex( int32 X, int32 Y );
	// Returns a psuedo-random unsigned integer based on the 3D index, benefits of index based is deterministic and order-independent as long as the global seed is the same(UBFSquirrelDeveloperSettings::GlobalNoiseSeed).
	uint32		RandUInt3DIndex( int32 X, int32 Y, int32 Z );
	// Returns a psuedo-random unsigned integer based on the 4D index, benefits of index based is deterministic and order-independent as long as the global seed is the same(UBFSquirrelDeveloperSettings::GlobalNoiseSeed).
	uint32		RandUInt4DIndex( int32 X, int32 Y, int32 Z, int32 T );

	
	// Returns a random signed integer from MIN_INT to MAX_INT
	int32		RandInt(bool bReverse = false);
	// Returns a random unsigned integer from 0 to MAX_UINT
	uint32		RandUint(bool bReverse = false);
	// Returns a random boolean value
	bool		RandBool(bool bReverse = false);
	// Returns a random float value in the range [0, 1]
	float		RandFloat(bool bReverse = false);
	// Returns a random double value in the range [0, 1]
	double		RandDouble(bool bReverse = false);
	// Returns a random unit vector
	FVector		RandVector(bool bReverse = false);
	// Returns a random unit vector2D
	FVector2D	RandVector2D(bool bReverse = false);
	// Returns a random rotator with values in the range [0, 360]
	FRotator	RandRotation(bool bReverse = false);
	// Returns a random int point struct
	FIntPoint	RandIntPoint(bool bReverse = false);
	// Returns a random color struct
	FColor		RandColor(bool bSolidAlpha, bool bReverse = false);

	int32		RandIntInRange( int32 Min, int32 Max, bool bReverse = false );
	uint32		RandUintInRange( uint32 Min, uint32 Max, bool bReverse = false );
	float		RandFloatInRange( float Min, float Max, bool bReverse = false );
	double		RandDoubleInRange( double Min, double Max, bool bReverse = false );
	FVector 	RandVectorInRange(const FVector& Min, const FVector& Max, bool bReverse = false);
	/** Returns a random unit vector, uniformly distributed, within the specified cone
 	* ConeHalfAngleRadians is the half-angle of cone, in **radians**.  Returns a normalized vector. */
	FVector		RandVectorInCone(const FVector& Direction, float ConeHalfAngleRadians, bool bReverse = false);
	FVector 	RandVectorInBox(const FBox& Box, bool bReverse = false);
	FVector2D	RandVector2DInRange(const FVector2D& Min, const FVector2D& Max, bool bReverse = false);
	FRotator	RandRotationInRange(const FRotator& Min, const FRotator& Max, bool bReverse = false);
	FIntPoint	RandIntPointInRange( FIntPoint Min, FIntPoint Max, bool bReverse = false );
	FColor		RandColorInRange( const FColor& Min, const FColor& Max, bool bReverse = false );
}







#include "BFSquirrel/DeveloperSettings/BFSquirrelDeveloperSettings.h"


/////////////////////////////////////////////////////////////////////////////////////////////////
// SquirrelNoise5 - Squirrel's Raw Noise utilities (version 5)
//
// This code is made available under the Creative Commons attribution 3.0 license (CC-BY-3.0 US):
//	Attribution in source code comments (even closed-source/commercial code) is sufficient.
//	License summary and text available at: https://creativecommons.org/licenses/by/3.0/us/
//
// These noise functions were written by Squirrel Eiserloh as a cheap and simple substitute for
//	the [sometimes awful] bit-noise sample code functions commonly found on the web, many of which
//	are hugely biased or terribly patterned, e.g. having bits which are on (or off) 75% or even
//	100% of the time (or are excessively overkill/slow for our needs, such as MD5 or SHA).
//
// Note: This is work in progress; not all functions have been tested.  Use at your own risk.
//	Please report any bugs, issues, or bothersome cases to SquirrelEiserloh at gmail.com.
//
// The following functions are all based on a simple bit-noise hash function which returns an
//	unsigned integer containing 32 reasonably-well-scrambled bits, based on a given (signed)
//	integer input parameter (position/index) and [optional] seed.  Kind of like looking up a
//	value in an infinitely large [non-existent] table of previously rolled random numbers.
//
// These functions are deterministic and random-access / order-independent (i.e. state-free),
//	so they are particularly well-suited for use in smoothed/fractal/simplex/Perlin noise
//	functions and out-of-order (or or-demand) procedural content generation (i.e. that mountain
//	village is the same whether you generated it first or last, ahead of time or just now).
//
// The N-dimensional variations simply hash their multidimensional coordinates down to a single
//	32-bit index and then proceed as usual, so while results are not unique they should
//	(hopefully) not seem locally predictable or repetitive.
//
/////////////////////////////////////////////////////////////////////////////////////////////////



namespace Sqrl::Priv
{
	template<typename T> concept CIs_FP = std::floating_point<T>;
	template<typename T> concept CIs_Int = std::integral<T>;
	BFSQUIRREL_API extern int GlobalNoiseIndex;

	
	
	//-----------------------------------------------------------------------------------------------
	// Raw pseudorandom noise functions (random-access / deterministic).  Basis of all other noise.
	//
	constexpr int Get1dNoiseInt( int index, unsigned int seed=0 );
	constexpr int Get2dNoiseInt( int indexX, int indexY, unsigned int seed=0 );
	constexpr int Get3dNoiseInt( int indexX, int indexY, int indexZ, unsigned int seed=0 );
	constexpr int Get4dNoiseInt( int indexX, int indexY, int indexZ, int indexT, unsigned int seed=0 );
	
	constexpr unsigned int Get1dNoiseUint( int index, unsigned int seed=0 );
	constexpr unsigned int Get2dNoiseUint( int indexX, int indexY, unsigned int seed=0 );
	constexpr unsigned int Get3dNoiseUint( int indexX, int indexY, int indexZ, unsigned int seed=0 );
	constexpr unsigned int Get4dNoiseUint( int indexX, int indexY, int indexZ, int indexT, unsigned int seed=0 );

	//-----------------------------------------------------------------------------------------------
	// Same functions, mapped to floats in [0,1] for convenience.
	//
	constexpr float Get1dNoiseZeroToOne( int index, unsigned int seed=0 );
	constexpr float Get2dNoiseZeroToOne( int indexX, int indexY, unsigned int seed=0 );
	constexpr float Get3dNoiseZeroToOne( int indexX, int indexY, int indexZ, unsigned int seed=0 );
	constexpr float Get4dNoiseZeroToOne( int indexX, int indexY, int indexZ, int indexT, unsigned int seed=0 );

	//-----------------------------------------------------------------------------------------------
	// Same functions, mapped to floats in [-1,1] for convenience.
	//
	constexpr float Get1dNoiseNegOneToOne( int index, unsigned int seed=0 );
	constexpr float Get2dNoiseNegOneToOne( int indexX, int indexY, unsigned int seed=0 );
	constexpr float Get3dNoiseNegOneToOne( int indexX, int indexY, int indexZ, unsigned int seed=0 );
	constexpr float Get4dNoiseNegOneToOne( int indexX, int indexY, int indexZ, int indexT, unsigned int seed=0 );
}



// Implementation of functions
namespace Sqrl
{
	inline [[nodiscard]] int32 RandInt1DIndex( int32 X) { return Priv::Get1dNoiseInt( X, UBFSquirrelDeveloperSettings::Get().GlobalNoiseSeed ); }
	inline [[nodiscard]] int32 RandInt2DIndex( int32 X, int32 Y) { return Priv::Get2dNoiseInt( X, Y, UBFSquirrelDeveloperSettings::Get().GlobalNoiseSeed ); }
	inline [[nodiscard]] int32 RandInt3DIndex( int32 X, int32 Y, int32 Z) { return Priv::Get3dNoiseInt( X, Y, Z, UBFSquirrelDeveloperSettings::Get().GlobalNoiseSeed ); }
	inline [[nodiscard]] int32 RandInt4DIndex( int32 X, int32 Y, int32 Z, int32 T) { return Priv::Get4dNoiseInt( X, Y, Z, T, UBFSquirrelDeveloperSettings::Get().GlobalNoiseSeed ); }

	inline [[nodiscard]] uint32 RandUInt1DIndex( int32 X) { return Priv::Get1dNoiseUint( X, UBFSquirrelDeveloperSettings::Get().GlobalNoiseSeed ); }
	inline [[nodiscard]] uint32 RandUInt2DIndex( int32 X, int32 Y) { return Priv::Get2dNoiseUint( X, Y, UBFSquirrelDeveloperSettings::Get().GlobalNoiseSeed ); }
	inline [[nodiscard]] uint32 RandUInt3DIndex( int32 X, int32 Y, int32 Z) { return Priv::Get3dNoiseUint( X, Y, Z, UBFSquirrelDeveloperSettings::Get().GlobalNoiseSeed ); }
	inline [[nodiscard]] uint32 RandUInt4DIndex( int32 X, int32 Y, int32 Z, int32 T) { return Priv::Get4dNoiseUint( X, Y, Z, T, UBFSquirrelDeveloperSettings::Get().GlobalNoiseSeed ); }

	inline [[nodiscard]] int32			RandInt(bool bReverse)		{ return Priv::Get1dNoiseInt(bReverse ? Priv::GlobalNoiseIndex++ : --Priv::GlobalNoiseIndex, UBFSquirrelDeveloperSettings::Get().GlobalNoiseSeed); }
	inline [[nodiscard]] uint32			RandUint(bool bReverse)		{ return Priv::Get1dNoiseUint(bReverse ? Priv::GlobalNoiseIndex++ : --Priv::GlobalNoiseIndex, UBFSquirrelDeveloperSettings::Get().GlobalNoiseSeed); }
	inline [[nodiscard]] bool			RandBool(bool bReverse)		{ return (RandInt(bReverse) % 2) == 0; }
	inline [[nodiscard]] float			RandFloat(bool bReverse)	{ return Priv::Get1dNoiseZeroToOne(bReverse ? Priv::GlobalNoiseIndex++ : --Priv::GlobalNoiseIndex, UBFSquirrelDeveloperSettings::Get().GlobalNoiseSeed); }
	inline [[nodiscard]] double			RandDouble(bool bReverse)	{ return static_cast<double>(Priv::Get1dNoiseZeroToOne(bReverse ? Priv::GlobalNoiseIndex++ : --Priv::GlobalNoiseIndex, UBFSquirrelDeveloperSettings::Get().GlobalNoiseSeed)); }
	inline [[nodiscard]] FVector		RandVector(bool bReverse)	{ return FVector{RandFloatInRange(-1, 1, bReverse), RandFloatInRange(-1, 1, bReverse), RandFloatInRange(-1, 1, bReverse)}.GetSafeNormal(); };
	inline [[nodiscard]] FVector2D		RandVector2D(bool bReverse)	{ return FVector2D{ RandFloatInRange(-1, 1, bReverse), RandFloatInRange(-1, 1, bReverse) }.GetSafeNormal(); }
	inline [[nodiscard]] FRotator		RandRotation(bool bReverse)	{ return { RandFloatInRange(0, 360.f, bReverse), RandFloatInRange(0, 360.f, bReverse), RandFloatInRange(0, 360.f, bReverse) }; }
	inline [[nodiscard]] FIntPoint		RandIntPoint(bool bReverse)	{ return { RandInt(bReverse), RandInt(bReverse) }; }

	inline [[nodiscard]] FColor	RandColor(bool bSolidAlpha, bool bReverse)
	{
		// Ensure the index stays in sync with the other functions
		uint8 Alpha = 255;
		if(bSolidAlpha)
			bReverse ? --Priv::GlobalNoiseIndex : ++Priv::GlobalNoiseIndex; 
		else
			Alpha = static_cast<uint8>(RandUintInRange(0, 255, bReverse));
		
		return FColor{static_cast<uint8>(RandUintInRange(0, 255, bReverse)), 
		static_cast<uint8>(RandUintInRange(0, 255, bReverse)), 
		static_cast<uint8>(RandUintInRange(0, 255, bReverse)), Alpha};
	} 

	inline [[nodiscard]] int32 RandIntInRange( int32 Min, int32 Max, bool bReverse )
	{
		if(Min > Max)
			std::swap(Min, Max);
		
		// For signed ints I need to ensure the modulo operation is adjusted to handle negative numbers correctly.
		int32 Range = (Max - Min) + 1;
		int32 NextVal = Priv::Get1dNoiseInt(bReverse ? Priv::GlobalNoiseIndex++ : --Priv::GlobalNoiseIndex, UBFSquirrelDeveloperSettings::Get().GlobalNoiseSeed);
		int32 ModVal = ((NextVal % Range) + Range) % Range; // Adjusted modulo operation
		return Min + ModVal;
	}

	inline [[nodiscard]] uint32 RandUintInRange( uint32 Min, uint32 Max, bool bReverse )
	{
		if(Min > Max)
			std::swap(Min, Max);
	    
		uint32 Range = (Max - Min) + 1; // Inclusive range
	    
		// if 0 and uint32MAX then will cause overflow so just return the next uint
		if (Range == 0)
			return Priv::Get1dNoiseUint(bReverse ? Priv::GlobalNoiseIndex++ : --Priv::GlobalNoiseIndex, UBFSquirrelDeveloperSettings::Get().GlobalNoiseSeed);
	    
		return Min + (Priv::Get1dNoiseUint(bReverse ? Priv::GlobalNoiseIndex++ : --Priv::GlobalNoiseIndex, UBFSquirrelDeveloperSettings::Get().GlobalNoiseSeed) % Range);
	}

	inline [[nodiscard]] float RandFloatInRange( float Min, float Max, bool bReverse )
	{
		if(Min > Max)
			std::swap(Min, Max);
		return Min + RandFloat(bReverse) * (Max - Min);
	}

	inline [[nodiscard]] double RandDoubleInRange( double Min, double Max, bool bReverse )
	{
		if(Min > Max)
			std::swap(Min, Max);
		return Min + RandDouble(bReverse) * (Max - Min);
	}

	
	inline [[nodiscard]] FVector RandVectorInRange(const FVector& Min, const FVector& Max, bool bReverse)
	{
		return {	RandFloatInRange(Min.X < Max.X ? Min.X : Max.X, Max.X > Min.X ? Max.X : Min.X, bReverse),
					RandFloatInRange(Min.Y < Max.Y ? Min.Y : Max.Y, Max.Y > Min.Y ? Max.Y : Min.Y, bReverse),
					RandFloatInRange(Min.Z < Max.Z ? Min.Z : Max.Z, Max.Z > Min.Z ? Max.Z : Min.Z, bReverse) };
	}

	inline [[nodiscard]] FVector RandVectorInCone(const FVector& Dir, float ConeHalfAngleRad, bool bReverse)
	{
		// yoinked directly from Unreals VRandCone
		if (ConeHalfAngleRad > 0.f)
		{
			float RandU = RandFloat(bReverse);
			float RandV = RandFloat(bReverse);

			// Get spherical coords that have an even distribution over the unit sphere
			// Method described at http://mathworld.wolfram.com/SpherePointPicking.html	
			float Theta = 2.f * UE_PI * RandU;
			float Phi = FMath::Acos((2.f * RandV) - 1.f);

			// restrict phi to [0, ConeHalfAngleRad]
			// this gives an even distribution of points on the surface of the cone
			// centered at the origin, pointing upward (z), with the desired angle
			Phi = FMath::Fmod(Phi, ConeHalfAngleRad);

			// get axes we need to rotate around
			FMatrix DirMat = FRotationMatrix(Dir.Rotation());
			// note the axis translation, since we want the variation to be around X
			FVector DirZ = DirMat.GetUnitAxis( EAxis::X );		
			FVector DirY = DirMat.GetUnitAxis( EAxis::Y );

			FVector Result = Dir.RotateAngleAxis(Phi * 180.f / UE_PI, DirY);
			Result = Result.RotateAngleAxis(Theta * 180.f / UE_PI, DirZ);

			// ensure it's a unit vector (might not have been passed in that way)
			return Result.GetSafeNormal();
		}
		
		return Dir.GetSafeNormal();
	}

	inline FVector RandVectorInBox(const FBox& Box, bool bReverse)
	{
		return {	RandFloatInRange(Box.Min.X, Box.Max.X, bReverse),
					RandFloatInRange(Box.Min.Y, Box.Max.Y, bReverse),
					RandFloatInRange(Box.Min.Z, Box.Max.Z, bReverse) };
	}

	inline [[nodiscard]] FVector2D RandVector2DInRange(const FVector2D& Min, const FVector2D& Max, bool bReverse)
	{
		return {	RandFloatInRange(Min.X, Max.X, bReverse),
					RandFloatInRange(Min.Y, Max.Y, bReverse) };
	}

	inline [[nodiscard]] FRotator RandRotationInRange(const FRotator& Min, const FRotator& Max, bool bReverse)
	{
		return { RandFloatInRange(Min.Pitch, Max.Pitch, bReverse), RandFloatInRange(Min.Yaw, Max.Yaw, bReverse), RandFloatInRange(Min.Roll, Max.Roll, bReverse) };
	}
	
	inline [[nodiscard]] FIntPoint RandIntPointInRange( FIntPoint Min, FIntPoint Max, bool bReverse )
	{
		return {	RandIntInRange(Min.X < Max.X ? Min.X : Max.X, Max.X > Min.X ? Max.X : Min.X, bReverse),
					RandIntInRange(Min.Y < Max.Y ? Min.Y : Max.Y, Max.Y > Min.Y ? Max.Y : Min.Y, bReverse) };
	}

	inline [[nodiscard]] FColor RandColorInRange( const FColor& Min, const FColor& Max, bool bReverse )
	{
		return FColor{	static_cast<uint8>(RandUintInRange(Min.R, Max.R, bReverse)),
						static_cast<uint8>(RandUintInRange(Min.G, Max.G, bReverse)),
						static_cast<uint8>(RandUintInRange(Min.B, Max.B, bReverse)),
						static_cast<uint8>(RandUintInRange(Min.A, Max.A, bReverse))};
	}


		
	namespace Helpers
	{
		/* Helps with debugging distribution of values, to use:
		 * 1) Create an instance of TDistributionMetricTracker with the type you want to track like so:
		 *		- Sqrl::Helpers::TDistributionMetricTracker<int> Tracker;
		 *		
		 *	2) During gameplay call Tracker.Add(Value) to add a value to the distribution, doesn't matter if its already been added it will just increment the count.
		 *
		 *	3) When you want to log the distribution call Tracker.Log() to log the distribution to the output log.
		 */
	    template<typename T>
	    struct TDistributionMetricTracker
	    {
	        TMap<T, int32> Distribution;

	        T Add(T Value)
	        {
	            if (Distribution.Contains(Value))
	                Distribution[Value]++;
	            else
	                Distribution.Add(Value, 1);
        		return Value;
	        }

	       void Log()
			{
			    if (Distribution.Num() == 0)
			    {
			        UE_LOG(LogTemp, Warning, TEXT("No data to log."));
			        return;
			    }

			    FString LogString = TEXT("Metrics for TDistributionMetricTracker of type\n");

			    if constexpr (TIsArithmetic<T>::Value)
			    {
			        float Sum = 0.0f;
			        float Mean = 0.0f;
			        float Variance = 0.0f;
			        float StandardDeviation = 0.0f;
			        T MinValue;
			        T MaxValue;
			        int32 TotalCount = 0;

			        auto It = Distribution.CreateConstIterator();
			        MinValue = It.Key();
			        MaxValue = It.Key();

			        // Compute the Sum, TotalCount, MinValue, MaxValue
			        for (const auto& Pair : Distribution)
			        {
			            T Value = Pair.Key;
			            int32 Count = Pair.Value;
			            TotalCount += Count;
			            Sum += static_cast<float>(Value) * Count;

			            if (Value < MinValue)
			                MinValue = Value;
			            if (Value > MaxValue)
			                MaxValue = Value;
			        }

			        Mean = Sum / TotalCount;

			        // Compute Variance
			        for (const auto& Pair : Distribution)
			        {
			            T Value = Pair.Key;
			            int32 Count = Pair.Value;
			            float Diff = static_cast<float>(Value) - Mean;
			            Variance += Diff * Diff * Count;
			        }

			        Variance /= TotalCount;
			        StandardDeviation = FMath::Sqrt(Variance);

			        LogString += FString::Format(TEXT("Unique Elem Count: {0}\nTotal values recorded: {1}\nSummation: {2}\nMean/Avg: {3}\nVariance: {4}\nStandard Deviation: {5}\nMin Value: {6}\nMax Value: {7}\nDistribution:\n"),
			            {Distribution.Num(), TotalCount, Sum, Mean, Variance, StandardDeviation, MinValue, MaxValue});

			        for (const auto& Pair : Distribution)
			        {
			            T Value = Pair.Key;
			            int32 Count = Pair.Value;
			            float Frequency = (static_cast<float>(Count) / TotalCount) * 100.0f;
			            LogString += FString::Format(TEXT("\t-Value: {0}, Count: {1}, Frequency: {2}%\n"), {static_cast<float>(Value), Count, Frequency});
			        }
			    }
			    else if constexpr (TIsSame<T, bool>::Value)
			    {
			        int32 TrueCount = Distribution.Contains(true) ? Distribution[true] : 0;
			        int32 FalseCount = Distribution.Contains(false) ? Distribution[false] : 0;
			        int32 TotalCount = TrueCount + FalseCount;
			        float TrueFrequency = (static_cast<float>(TrueCount) / TotalCount) * 100.0f;
			        float FalseFrequency = (static_cast<float>(FalseCount) / TotalCount) * 100.0f;

			        LogString += FString::Format(TEXT("Total Values Recorded: {0}\nTrue Count: {1}, Frequency: {2}%\nFalse Count: {3}, Frequency: {4}%\n"),
			            {TotalCount, TrueCount, TrueFrequency, FalseCount, FalseFrequency});
			    }
			    else
			    {
			        int32 TotalCount = 0;

			        for (const auto& Pair : Distribution)
			            TotalCount += Pair.Value;

			        LogString += FString::Format(TEXT("Unique Eleem Count: {0}\nTotal Values Recorded: {0}\nDistribution:\n"), {Distribution.Num(), TotalCount});

			        for (const auto& Pair : Distribution)
			        {
			            T Value = Pair.Key;
			            int32 Count = Pair.Value;
			            float Frequency = (static_cast<float>(Count) / TotalCount) * 100.0f;
			            LogString += FString::Format(TEXT("\t-Value: {0}, Count: {1}, Frequency: {2}%\n"), {Value, Count, Frequency});
			        }
			    }

			    UE_LOG(LogTemp, Warning, TEXT("%s"), *LogString);
			    Distribution.Empty();
			}
	    };
	}
	
	// Sets the global rand noise index, useful for replaying randomness.
	inline void SetGlobalRandNoiseIndex(int Index) {Priv::GlobalNoiseIndex = Index;}

	// Sets the global noise seed (which is sourced from UBFSquirrelDeveloperSettings).
	inline void SetGlobalRandNoiseSeed(unsigned int Seed) { UBFSquirrelDeveloperSettings::GetMutable().GlobalNoiseSeed = Seed; }

	inline int GetGlobalRandNoiseSeed() { return static_cast<int>(UBFSquirrelDeveloperSettings::Get().GlobalNoiseSeed); }
	inline int GetGlobalRandNoiseIndex() { return Priv::GlobalNoiseIndex; }
}





namespace Sqrl::Priv
{
	/////////////////////////////////////////////////////////////////////////////////////////////////
	// Inline function definitions below
	/////////////////////////////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------------------------------
	// Fast hash of an int32 into a different (unrecognizable) uint32.
	//
	// Returns an unsigned integer containing 32 reasonably-well-scrambled bits, based on the hash
	//	of a given (signed) integer input parameter (position/index) and [optional] seed.  Kind of
	//	like looking up a value in an infinitely large table of previously generated random numbers.
	//
	// I call this particular approach SquirrelNoise5 (5th iteration of my 1D raw noise function).
	//
	// Many thanks to Peter Schmidt-Nielsen whose outstanding analysis helped identify a weakness
	//	in the SquirrelNoise3 code I originally used in my GDC 2017 talk, "Noise-based RNG".
	//	Version 5 avoids a noise repetition found in version 3 at extremely high position values
	//	caused by a lack of influence by some of the high input bits onto some of the low output bits.
	//
	// The revised SquirrelNoise5 function ensures all input bits affect all output bits, and to
	//	(for me) a statistically acceptable degree.  I believe the worst-case here is in the amount
	//	of influence input position bit #30 has on output noise bit #0 (49.99%, vs. 50% ideal).
	//
	constexpr unsigned int SquirrelNoise5( int positionX, unsigned int seed )
	{
		constexpr unsigned int SQ5_BIT_NOISE1 = 0xd2a80a3f;	// 11010010101010000000101000111111
		constexpr unsigned int SQ5_BIT_NOISE2 = 0xa884f197;	// 10101000100001001111000110010111
		constexpr unsigned int SQ5_BIT_NOISE3 = 0x6C736F4B; // 01101100011100110110111101001011
		constexpr unsigned int SQ5_BIT_NOISE4 = 0xB79F3ABB;	// 10110111100111110011101010111011
		constexpr unsigned int SQ5_BIT_NOISE5 = 0x1b56c4f5;	// 00011011010101101100010011110101

		unsigned int mangledBits = (unsigned int) positionX;
		mangledBits *= SQ5_BIT_NOISE1;
		mangledBits += seed;
		mangledBits ^= (mangledBits >> 9);
		mangledBits += SQ5_BIT_NOISE2;
		mangledBits ^= (mangledBits >> 11);
		mangledBits *= SQ5_BIT_NOISE3;
		mangledBits ^= (mangledBits >> 13);
		mangledBits += SQ5_BIT_NOISE4;
		mangledBits ^= (mangledBits >> 15);
		mangledBits *= SQ5_BIT_NOISE5;
		mangledBits ^= (mangledBits >> 17);
		return mangledBits;
	}

	
	//------------------------------------------------------------------------------------------------
	constexpr int SquirrelNoise5Signed( int positionX, unsigned int seed )
	{
		constexpr unsigned int SQ5_BIT_NOISE1 = 0xd2a80a3f;	// 11010010101010000000101000111111
		constexpr unsigned int SQ5_BIT_NOISE2 = 0xa884f197;	// 10101000100001001111000110010111
		constexpr unsigned int SQ5_BIT_NOISE3 = 0x6C736F4B; // 01101100011100110110111101001011
		constexpr unsigned int SQ5_BIT_NOISE4 = 0xB79F3ABB;	// 10110111100111110011101010111011
		constexpr unsigned int SQ5_BIT_NOISE5 = 0x1b56c4f5;	// 00011011010101101100010011110101

		unsigned int mangledBits = (unsigned int) positionX;
		mangledBits *= SQ5_BIT_NOISE1;
		mangledBits += seed;
		mangledBits ^= (mangledBits >> 9);
		mangledBits += SQ5_BIT_NOISE2;
		mangledBits ^= (mangledBits >> 11);
		mangledBits *= SQ5_BIT_NOISE3;
		mangledBits ^= (mangledBits >> 13);
		mangledBits += SQ5_BIT_NOISE4;
		mangledBits ^= (mangledBits >> 15);
		mangledBits *= SQ5_BIT_NOISE5;
		mangledBits ^= (mangledBits >> 17);
		return mangledBits;
	}



	//------------------------------------------------------------------------------------------------
	constexpr unsigned int Get1dNoiseUint( int positionX, unsigned int seed )
	{
		return SquirrelNoise5( positionX, seed );
	}


	//------------------------------------------------------------------------------------------------
	constexpr int Get1dNoiseInt( int positionX, unsigned int seed )
	{
		return SquirrelNoise5Signed( positionX, seed );
	}


	//-----------------------------------------------------------------------------------------------
	constexpr unsigned int Get2dNoiseUint( int indexX, int indexY, unsigned int seed )
	{
		constexpr int PRIME_NUMBER = 198491317; // Large prime number with non-boring bits
		return SquirrelNoise5( indexX + (PRIME_NUMBER * indexY), seed );
	}

	//-----------------------------------------------------------------------------------------------
	constexpr int Get2dNoiseInt( int indexX, int indexY, unsigned int seed )
	{
		constexpr int PRIME_NUMBER = 198491317; // Large prime number with non-boring bits
		return SquirrelNoise5Signed( indexX + (PRIME_NUMBER * indexY), seed );
	}

	//-----------------------------------------------------------------------------------------------
	constexpr unsigned int Get3dNoiseUint( int indexX, int indexY, int indexZ, unsigned int seed )
	{
		constexpr int PRIME1 = 198491317; // Large prime number with non-boring bits
		constexpr int PRIME2 = 6542989; // Large prime number with distinct and non-boring bits
		return SquirrelNoise5( indexX + (PRIME1 * indexY) + (PRIME2 * indexZ), seed );
	}

	//-----------------------------------------------------------------------------------------------
	constexpr int Get3dNoiseInt( int indexX, int indexY, int indexZ, unsigned int seed )
	{
		constexpr int PRIME1 = 198491317; // Large prime number with non-boring bits
		constexpr int PRIME2 = 6542989; // Large prime number with distinct and non-boring bits
		return SquirrelNoise5Signed( indexX + (PRIME1 * indexY) + (PRIME2 * indexZ), seed );
	}

	//-----------------------------------------------------------------------------------------------
	constexpr unsigned int Get4dNoiseUint( int indexX, int indexY, int indexZ, int indexT, unsigned int seed )
	{
		constexpr int PRIME1 = 198491317; // Large prime number with non-boring bits
		constexpr int PRIME2 = 6542989; // Large prime number with distinct and non-boring bits
		constexpr int PRIME3 = 357239; // Large prime number with distinct and non-boring bits
		return SquirrelNoise5( indexX + (PRIME1 * indexY) + (PRIME2 * indexZ) + (PRIME3 * indexT), seed );
	}

	//-----------------------------------------------------------------------------------------------
	constexpr int Get4dNoiseInt( int indexX, int indexY, int indexZ, int indexT, unsigned int seed )
	{
		constexpr int PRIME1 = 198491317; // Large prime number with non-boring bits
		constexpr int PRIME2 = 6542989; // Large prime number with distinct and non-boring bits
		constexpr int PRIME3 = 357239; // Large prime number with distinct and non-boring bits
		return SquirrelNoise5Signed( indexX + (PRIME1 * indexY) + (PRIME2 * indexZ) + (PRIME3 * indexT), seed );
	}

	//-----------------------------------------------------------------------------------------------
	constexpr float Get1dNoiseZeroToOne( int index, unsigned int seed )
	{
		constexpr double ONE_OVER_MAX_UINT = (1.0 / (double) 0xFFFFFFFF);
		return (float)( ONE_OVER_MAX_UINT * (double) SquirrelNoise5( index, seed ) );
	}

	//-----------------------------------------------------------------------------------------------
	constexpr float Get2dNoiseZeroToOne( int indexX, int indexY, unsigned int seed )
	{
		constexpr double ONE_OVER_MAX_UINT = (1.0 / (double) 0xFFFFFFFF);
		return (float)( ONE_OVER_MAX_UINT * (double) Get2dNoiseUint( indexX, indexY, seed ) );
	}

	//-----------------------------------------------------------------------------------------------
	constexpr float Get3dNoiseZeroToOne( int indexX, int indexY, int indexZ, unsigned int seed )
	{
		constexpr double ONE_OVER_MAX_UINT = (1.0 / (double) 0xFFFFFFFF);
		return (float)( ONE_OVER_MAX_UINT * (double) Get3dNoiseUint( indexX, indexY, indexZ, seed ) );
	}

	//-----------------------------------------------------------------------------------------------
	constexpr float Get4dNoiseZeroToOne( int indexX, int indexY, int indexZ, int indexT, unsigned int seed )
	{
		constexpr double ONE_OVER_MAX_UINT = (1.0 / (double) 0xFFFFFFFF);
		return (float)( ONE_OVER_MAX_UINT * (double) Get4dNoiseUint( indexX, indexY, indexZ, indexT, seed ) );
	}


	//-----------------------------------------------------------------------------------------------
	constexpr float Get1dNoiseNegOneToOne( int index, unsigned int seed )
	{
		constexpr double ONE_OVER_MAX_INT = (1.0 / (double) 0x7FFFFFFF);
		return (float)( ONE_OVER_MAX_INT * (double) (int) SquirrelNoise5( index, seed ) );
	}


	//-----------------------------------------------------------------------------------------------
	constexpr float Get2dNoiseNegOneToOne( int indexX, int indexY, unsigned int seed )
	{
		constexpr double ONE_OVER_MAX_INT = (1.0 / (double) 0x7FFFFFFF);
		return (float)( ONE_OVER_MAX_INT * (double) (int) Get2dNoiseUint( indexX, indexY, seed ) );
	}


	//-----------------------------------------------------------------------------------------------
	constexpr float Get3dNoiseNegOneToOne( int indexX, int indexY, int indexZ, unsigned int seed )
	{
		constexpr double ONE_OVER_MAX_INT = (1.0 / (double) 0x7FFFFFFF);
		return (float)( ONE_OVER_MAX_INT * (double) (int) Get3dNoiseUint( indexX, indexY, indexZ, seed ) );
	}


	//-----------------------------------------------------------------------------------------------
	constexpr float Get4dNoiseNegOneToOne( int indexX, int indexY, int indexZ, int indexT, unsigned int seed )
	{
		constexpr double ONE_OVER_MAX_INT = (1.0 / (double) 0x7FFFFFFF);
		return (float)( ONE_OVER_MAX_INT * (double) (int) Get4dNoiseUint( indexX, indexY, indexZ, indexT, seed ) );
	}
}







