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

#include "BFSquirrel/Squirrel/squirrelnoise5.h"
#include "BFSquirrelStream.generated.h"


/** Each squirrel stream has their own unique seed and index and has the ability to go back and forwards between random values, the only thing of caution
 * worth noting is when going between different random function calls, like a `NextInt()` and `NextFVector()` call, the int would advance the index by one where as the FVector advances us by 3.
 * So now if we wanted to return to the original int's index it would need to be decremented by 3 not 1 which means calling `PreviousVector()` before `PreviousInt()`.
 * Basically if you want forward and back behaviour probably stick to using it for one thing. If you blueprint this is represented via a bool bReverse Flag on the node. */
USTRUCT(BlueprintType)
struct FSquirrelStream
{
	GENERATED_BODY()
	
	/** I am very deliberately post and pre increment/decrementing, for example:
	 * X = 2;
	 * A = X++ = 2 (since post increment returns the original value, X has now been updated to 3 though)
	 * B = --X = 2 (since pre returns the new value straight away)
	 */
public:
	/** Random Seed for each stream unless explicit */
	FSquirrelStream() { Seed = Sqrl::RandInt(); InitialSeed = Seed; }
	FSquirrelStream(int32 InitSeed, int32 InitIndex) : Index(InitIndex), Seed(InitSeed) {}
	
	void Reset() { Index = 0; Seed = InitialSeed; }
	void SetSeed(int32 NewSeed) { Seed = NewSeed; }
	void SetIndex(int32 NewIndex) { Index = NewIndex; }
	int32 GetSeed() const { return Seed; }
	int32 GetIndex() const { return Index; }

	int32 RandInt1DIndex(int32 X) { return Sqrl::Priv::Get1dNoiseInt(X, static_cast<uint32>(Seed)); }
	int32 RandInt2DIndex(int32 X, int32 Y) { return Sqrl::Priv::Get2dNoiseInt(X, Y, static_cast<uint32>(Seed)); }
	int32 RandInt3DIndex(int32 X, int32 Y, int32 Z) { return Sqrl::Priv::Get3dNoiseInt(X, Y, Z, static_cast<uint32>(Seed)); }
	int32 RandInt4DIndex(int32 X, int32 Y, int32 Z, int32 W) { return Sqrl::Priv::Get4dNoiseInt(X, Y, Z, W, static_cast<uint32>(Seed)); }

	uint32 RandUint1DIndex(int32 X) { return Sqrl::Priv::Get1dNoiseUint(X, static_cast<uint32>(Seed)); }
	uint32 RandUint2DIndex(int32 X, int32 Y) { return Sqrl::Priv::Get2dNoiseUint(X, Y, static_cast<uint32>(Seed)); }
	uint32 RandUint3DIndex(int32 X, int32 Y, int32 Z) { return Sqrl::Priv::Get3dNoiseUint(X, Y, Z, static_cast<uint32>(Seed)); }
	uint32 RandUint4DIndex(int32 X, int32 Y, int32 Z, int32 W) { return Sqrl::Priv::Get4dNoiseUint(X, Y, Z, W, static_cast<uint32>(Seed)); }
	

	bool NextBool() { return (Sqrl::Priv::Get1dNoiseInt(Index++, static_cast<uint32>(Seed)) % 2) == 0; }
	bool PreviousBool() { return( Sqrl::Priv::Get1dNoiseInt(--Index, static_cast<uint32>(Seed)) % 2) ==0; }
	int32 NextInt() { return Sqrl::Priv::Get1dNoiseInt(Index++, static_cast<uint32>(Seed)); }
	int32 PreviousInt() { return Sqrl::Priv::Get1dNoiseInt(--Index, static_cast<uint32>(Seed)); }
	unsigned int NextUint() { return Sqrl::Priv::Get1dNoiseUint(Index++, static_cast<uint32>(Seed)); }
	unsigned int PreviousUint() { return Sqrl::Priv::Get1dNoiseUint(--Index, static_cast<uint32>(Seed)); }
	float NextFloat() { return Sqrl::Priv::Get1dNoiseZeroToOne(Index++, static_cast<uint32>(Seed)); }
	float PreviousFloat() { return Sqrl::Priv::Get1dNoiseZeroToOne(--Index, static_cast<uint32>(Seed)); }
	double NextDouble() { return static_cast<double>(Sqrl::Priv::Get1dNoiseZeroToOne(Index++, static_cast<uint32>(Seed))); }
	double PreviousDouble() { return static_cast<double>(Sqrl::Priv::Get1dNoiseZeroToOne(--Index, static_cast<uint32>(Seed))); }
	FVector NextVector() { return FVector{NextFloat(), NextFloat(), NextFloat()}.GetSafeNormal(); }
	FVector PreviousVector() { return FVector{PreviousFloat(), PreviousFloat(), PreviousFloat()}.GetSafeNormal(); }
	FVector2D NextVector2D() { return FVector2D{NextFloat(), NextFloat()}.GetSafeNormal(); }
	FVector2D PreviousVector2D() { return FVector2D{PreviousFloat(), PreviousFloat()}.GetSafeNormal(); }
	FRotator NextRotation() { return FRotator{NextFloat() * 360.f, NextFloat() * 360.f, NextFloat() * 360.f}; }
	FRotator PreviousRotation() { return FRotator{PreviousFloat() * 360.f, PreviousFloat() * 360.f, PreviousFloat() * 360.f}; }
	FIntPoint NextIntPoint() { return FIntPoint{NextInt(), NextInt()}; }
	FIntPoint PreviousIntPoint() { return FIntPoint{PreviousInt(), PreviousInt()}; }
	FColor NextColor(bool bSolidAlpha = true);
	FColor PreviousColor(bool bSolidAlpha = true);

	int32 NextIntInRange(int32 Min, int32 Max);
	int32 PreviousIntInRange(int32 Min, int32 Max);
	uint32 NextUintInRange(uint32 Min, uint32 Max);
	uint32 PreviousUintInRange(uint32 Min, uint32 Max);
	float NextFloatInRange(float Min, float Max);
	float PreviousFloatInRange(float Min, float Max);
	double NextDoubleInRange(double Min, double Max);
	double PreviousDoubleInRange(double Min, double Max);
	FVector NextVectorInRange(const FVector& Min, const FVector& Max);
	FVector PreviousVectorInRange(const FVector& Min, const FVector& Max);
	FVector NextVectorInCone(const FVector& Direction, float ConeHalfAngleRad );
	FVector PreviousVectorInCone(const FVector& Direction, float ConeHalfAngleRad );
	FVector2D NextVector2DInRange(const FVector2D& Min, const FVector2D& Max);
	FVector2D PreviousVector2DInRange(const FVector2D& Min, const FVector2D& Max);
	FVector NextVectorInBox(const FBox& Box);
	FVector PreviousVectorInBox(const FBox& Box);
	FRotator NextRotationInRange(const FRotator& Min, const FRotator& Max);
	FRotator PreviousRotationInRange(const FRotator& Min, const FRotator& Max);
	FIntPoint NextIntPointInRange(const FIntPoint& Min, const FIntPoint& Max);
	FIntPoint PreviousIntPointInRange(const FIntPoint& Min, const FIntPoint& Max);
	FColor NextColorInRange(const FColor& Min, const FColor& Max);
	FColor PreviousColorInRange(const FColor& Min, const FColor& Max);
	
protected:
	int32 Index = 0;
	int32 Seed = 0;
	int32 InitialSeed = 0;
};



inline FColor FSquirrelStream::NextColor(bool bSolidAlpha)
{
	uint8 Alpha = 255;
	if(bSolidAlpha)
		++Index;  // Ensures we can Next and Previous even if we don't want to use the alpha value in one but do in the other
	else
		Alpha = static_cast<uint8>(NextUintInRange(0, 255));
	
	return {static_cast<uint8>(NextUintInRange(0, 255)), static_cast<uint8>(NextUintInRange(0, 255)), static_cast<uint8>(NextUintInRange(0, 255)), Alpha};
}

inline FColor FSquirrelStream::PreviousColor(bool bSolidAlpha)
{
	uint8 Alpha = 255;
	if(bSolidAlpha)
		--Index;  // Ensures we can Next and Previous even if we don't want to use the alpha value in one but do in the other
	else
		Alpha = static_cast<uint8>(PreviousUintInRange(0, 255));
	
	return {static_cast<uint8>(NextUintInRange(0, 255)), static_cast<uint8>(NextUintInRange(0, 255)), static_cast<uint8>(NextUintInRange(0, 255)), Alpha};
}

inline int32 FSquirrelStream::NextIntInRange(int32 Min, int32 Max)
{
	if(Min > Max)
		std::swap(Min, Max);
	
	// For signed ints I need to ensure the modulo operation is adjusted to handle negative numbers correctly.
	int32 Range = (Max - Min) + 1;
	int32 NextVal = NextInt();
	int32 ModVal = ((NextVal % Range) + Range) % Range; // Adjusted modulo operation
	return Min + ModVal;
}

inline int32 FSquirrelStream::PreviousIntInRange(int32 Min, int32 Max)
{
	if(Min > Max)
		std::swap(Min, Max);
	
	// For signed ints I need to ensure the modulo operation is adjusted to handle negative numbers correctly.
	int32 Range = (Max - Min) + 1;
	int32 PrevVal = PreviousInt();
	int32 ModVal = ((PrevVal % Range) + Range) % Range; // Adjusted modulo operation
	return Min + ModVal;
}

inline uint32 FSquirrelStream::NextUintInRange(uint32 Min, uint32 Max)
{
	if(Min > Max)
		std::swap(Min, Max);

	uint32 Range = (Max - Min) + 1; // Inclusive range

	// if 0 and uint32MAX then will cause overflow so just return the next uint
	if (Range == 0)
		return NextUint(); 

	return Min + (NextUint() % Range);
}

inline uint32 FSquirrelStream::PreviousUintInRange(uint32 Min, uint32 Max)
{
	if(Min > Max)
		std::swap(Min, Max);

	uint32 Range = (Max - Min) + 1; // Inclusive range

	// if 0 and uint32MAX then will cause overflow so just return the next uint
	if (Range == 0)
		return PreviousUint(); 

	return Min + (PreviousUint() % Range);
}

inline float FSquirrelStream::NextFloatInRange(float Min, float Max)
{
	if(Min > Max)
		std::swap(Min, Max);
	return Min + NextFloat() * (Max - Min);
}

inline float FSquirrelStream::PreviousFloatInRange(float Min, float Max)
{
	if(Min > Max)
		std::swap(Min, Max);
	return Min + PreviousFloat() * (Max - Min);
}

inline double FSquirrelStream::NextDoubleInRange(double Min, double Max)
{
	if(Min > Max)
		std::swap(Min, Max);
	return Min + NextDouble() * (Max - Min);
}

inline double FSquirrelStream::PreviousDoubleInRange(double Min, double Max)
{
	if(Min > Max)
		std::swap(Min, Max);
	return Min + PreviousDouble() * (Max - Min);
}

inline FVector FSquirrelStream::NextVectorInRange(const FVector& Min, const FVector& Max)
{
	return { NextFloatInRange(Min.X, Max.X), NextFloatInRange(Min.Y, Max.Y), NextFloatInRange(Min.Z, Max.Z) };
}

inline FVector FSquirrelStream::PreviousVectorInRange(const FVector& Min, const FVector& Max)
{
	return { PreviousFloatInRange(Min.X, Max.X), PreviousFloatInRange(Min.Y, Max.Y), PreviousFloatInRange(Min.Z, Max.Z) };
}

inline FVector FSquirrelStream::NextVectorInCone(const FVector& Direction, float ConeHalfAngleRad )
{
	// yoinked directly from Unreals VRandCone
	if (ConeHalfAngleRad > 0.f)
	{
		float RandU = NextFloat();
		float RandV = NextFloat();

		// Get spherical coords that have an even distribution over the unit sphere
		// Method described at http://mathworld.wolfram.com/SpherePointPicking.html	
		float Theta = 2.f * UE_PI * RandU;
		float Phi = FMath::Acos((2.f * RandV) - 1.f);

		// restrict phi to [0, ConeHalfAngleRad]
		// this gives an even distribution of points on the surface of the cone
		// centered at the origin, pointing upward (z), with the desired angle
		Phi = FMath::Fmod(Phi, ConeHalfAngleRad);

		// get axes we need to rotate around
		FMatrix DirMat = FRotationMatrix(Direction.Rotation());
		// note the axis translation, since we want the variation to be around X
		FVector DirZ = DirMat.GetUnitAxis( EAxis::X );		
		FVector DirY = DirMat.GetUnitAxis( EAxis::Y );

		FVector Result = Direction.RotateAngleAxis(Phi * 180.f / UE_PI, DirY);
		Result = Result.RotateAngleAxis(Theta * 180.f / UE_PI, DirZ);

		// ensure it's a unit vector (might not have been passed in that way)
		return Result.GetSafeNormal();
	}
	
	return Direction.GetSafeNormal();
}

inline FVector FSquirrelStream::PreviousVectorInCone(const FVector& Direction, float ConeHalfAngleRad )
{
	// yoinked directly from Unreals VRandCone
	if (ConeHalfAngleRad > 0.f)
	{
		float RandU = PreviousFloat();
		float RandV = PreviousFloat();

		// Get spherical coords that have an even distribution over the unit sphere
		// Method described at http://mathworld.wolfram.com/SpherePointPicking.html	
		float Theta = 2.f * UE_PI * RandU;
		float Phi = FMath::Acos((2.f * RandV) - 1.f);

		// restrict phi to [0, ConeHalfAngleRad]
		// this gives an even distribution of points on the surface of the cone
		// centered at the origin, pointing upward (z), with the desired angle
		Phi = FMath::Fmod(Phi, ConeHalfAngleRad);

		// get axes we need to rotate around
		FMatrix DirMat = FRotationMatrix(Direction.Rotation());
		// note the axis translation, since we want the variation to be around X
		FVector DirZ = DirMat.GetUnitAxis( EAxis::X );		
		FVector DirY = DirMat.GetUnitAxis( EAxis::Y );

		FVector Result = Direction.RotateAngleAxis(Phi * 180.f / UE_PI, DirY);
		Result = Result.RotateAngleAxis(Theta * 180.f / UE_PI, DirZ);

		// ensure it's a unit vector (might not have been passed in that way)
		return Result.GetSafeNormal();
	}
	
	return Direction.GetSafeNormal();
}


inline FVector2D FSquirrelStream::NextVector2DInRange(const FVector2D& Min, const FVector2D& Max)
{
	return { NextFloatInRange(Min.X, Max.X),
				NextFloatInRange(Min.Y, Max.Y) };
}

inline FVector2D FSquirrelStream::PreviousVector2DInRange(const FVector2D& Min, const FVector2D& Max)
{
	return {	PreviousFloatInRange(Min.X, Max.X),
				PreviousFloatInRange(Min.Y, Max.Y) };
}

inline FVector FSquirrelStream::NextVectorInBox(const FBox& Box)
{
	return {	NextFloatInRange(Box.Min.X, Box.Max.X),
				NextFloatInRange(Box.Min.Y, Box.Max.Y),
				NextFloatInRange(Box.Min.Z, Box.Max.Z)};
}

inline FVector FSquirrelStream::PreviousVectorInBox(const FBox& Box)
{
	return { PreviousFloatInRange(Box.Min.X, Box.Max.X),
				PreviousFloatInRange(Box.Min.Y, Box.Max.Y),
				PreviousFloatInRange(Box.Min.Z, Box.Max.Z)};
}

inline FRotator FSquirrelStream::NextRotationInRange(const FRotator& Min, const FRotator& Max)
{
	return { NextFloatInRange(Min.Pitch, Max.Pitch),
				NextFloatInRange(Min.Yaw, Max.Yaw),
				NextFloatInRange(Min.Roll, Max.Roll) };
}

inline FRotator FSquirrelStream::PreviousRotationInRange(const FRotator& Min, const FRotator& Max)
{
	return { PreviousFloatInRange(Min.Pitch, Max.Pitch),
				PreviousFloatInRange(Min.Yaw, Max.Yaw),
				PreviousFloatInRange(Min.Roll, Max.Roll) };
}

inline FIntPoint FSquirrelStream::NextIntPointInRange(const FIntPoint& Min, const FIntPoint& Max)
{
	return { NextIntInRange(Min.X, Max.X),
				NextIntInRange(Min.Y, Max.Y) };
}

inline FIntPoint FSquirrelStream::PreviousIntPointInRange(const FIntPoint& Min, const FIntPoint& Max)
{
	return { PreviousIntInRange(Min.X, Max.X),
				PreviousIntInRange(Min.Y, Max.Y) };
}

inline FColor FSquirrelStream::NextColorInRange(const FColor& Min, const FColor& Max)
{
	return {	static_cast<uint8>(NextUintInRange(Min.R, Max.R)),
				static_cast<uint8>(NextUintInRange(Min.G, Max.G)),
				static_cast<uint8>(NextUintInRange(Min.B, Max.B)),
				static_cast<uint8>(NextUintInRange(Min.A, Max.A)) };
}

inline FColor FSquirrelStream::PreviousColorInRange(const FColor& Min, const FColor& Max)
{
	return {	static_cast<uint8>(PreviousUintInRange(Min.R, Max.R)),
				static_cast<uint8>(PreviousUintInRange(Min.G, Max.G)),
				static_cast<uint8>(PreviousUintInRange(Min.B, Max.B)),
				static_cast<uint8>(PreviousUintInRange(Min.A, Max.A)) };
}























