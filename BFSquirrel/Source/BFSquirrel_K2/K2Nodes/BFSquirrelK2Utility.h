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

#include "BFSquirrel/BFSquirrelCore.h"




#define LOCTEXT_NAMESPACE "BFSquirrelK2"

namespace SqrlK2::Priv
{
	// Node titles
	const FText SquirrelRandNodeTitle = LOCTEXT("BFSquirrelK2_SquirrelRand_SquirrelRand", "Squirrel Rand");
	const FText SquirrelStreamRandNodeTitle = LOCTEXT("BFSquirrelK2_SquirrelRand_SquirrelStreamRand", "Squirrel Stream Rand");

	const FText SquirrelCategory = LOCTEXT("BFSquirrelK2_SquirrelRand_SquirrelStreamCategory", "Squirrel");
	
	
	// Friendly names for the dynamic pins
	const FText SolidAlphaPinName = LOCTEXT("BFSquirrelK2_SquirrelRand_SolidAlpha", "Solid Alpha");
	const FText MinPinName = LOCTEXT("BFSquirrelK2_SquirrelRand_Min", "Min");
	const FText MaxPinName = LOCTEXT("BFSquirrelK2_SquirrelRand_Max", "Max");
	const FText DirPinName = LOCTEXT("BFSquirrelK2_SquirrelRand_Direction", "Direction");
	const FText HalfAnglePinName = LOCTEXT("BFSquirrelK2_SquirrelRand_ConeHalfAngleRadians", "Cone Half Angle Radians");
	const FText XIndexPinName = LOCTEXT("BFSquirrelK2_SquirrelRand_XIndex", "X Index");
	const FText YIndexPinName = LOCTEXT("BFSquirrelK2_SquirrelRand_YIndex", "Y Index");
	const FText ZIndexPinName = LOCTEXT("BFSquirrelK2_SquirrelRand_ZIndex", "Z Index");
	const FText WIndexPinName = LOCTEXT("BFSquirrelK2_SquirrelRand_WIndex", "W Index");
	const FText RandResultPinName = LOCTEXT("BFSquirrelK2_SquirrelRand_Result", "Rand Result");

	// Shared pin and K2 node names
	const FName FunctionNameSquirrelRand = {"InternalSquirrelRandK2"};
	const FName FunctionNameSquirrelStreamRand = {"InternalSquirrelStreamRandK2"};

	const FName FunctionInputSquirrelRandomType = {"RandomType"};
	const FName FunctionInputSquirrelStream = {"Stream"};
	const FName FunctionInputReverseFlag = {"bReverse"};
	const FName FunctionInputParamA = {"ParamA"};
	const FName FunctionInputParamB = {"ParamB"};
	const FName FunctionInputParamC = {"ParamC"};
	const FName FunctionInputParamD = {"ParamD"};
	const FName FunctionOutputParam = {"Result"};


	extern FText GetSquirrelRandTypeDescription(ESquirrelRandType RandType);
	extern void SetPinValues(UEdGraphPin* Pin, FName PinCategory, FName PinSubCategory, UObject* PinSubCategoryObject, FString DefaultValue = "", bool bHidden = false);
}

#undef LOCTEXT_NAMESPACE