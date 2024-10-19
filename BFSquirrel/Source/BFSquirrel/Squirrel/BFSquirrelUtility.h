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

#include "BFSquirrelUtility.generated.h"


/** Updating the below enum also means updating all K2 nodes that use it, not a super fun task
 * but its already all there, its a simple copy pasta and rename in most cases for k2 node switches using this
 */


/** Defines a random type to use. */
UENUM(BlueprintType)
enum class ESquirrelRandType : uint8
{
	Int=0,
	Bool,
	Float,
	Vector,
	Vector2D,
	Rotation,
	IntPoint,
	Color,

	IntInRange,
	FloatInRange,
	VectorInRange,
	VectorInCone,
	VectorInBox,
	Vector2DInRange,
	RotationInRange,
	IntPointInRange,
	ColorInRange,

	From1DIndex,
	From2DIndex,
	From3DIndex,
	From4DIndex,

	LAST UMETA(Hidden)
};






