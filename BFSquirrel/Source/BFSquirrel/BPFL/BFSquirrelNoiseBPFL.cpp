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


#include "BFSquirrelNoiseBPFL.h"



DEFINE_FUNCTION(UBFSquirrelNoiseBPFL::execInternalSquirrelStreamRandK2)
{
	Stack.MostRecentProperty = nullptr;
	Stack.MostRecentPropertyAddress = nullptr;
	
	P_GET_ENUM(ESquirrelRandType, RandType);
	P_GET_UBOOL(bReverse);
	P_GET_STRUCT_REF(FSquirrelStream, SquirrelStream);

	// Our largest supported member is a vector but just in-case we have a larger one in the future we will use this as the buffer size
	static constexpr SIZE_T BufferSize =	std::max(sizeof(int32),
											std::max(sizeof(float),
											std::max(sizeof(FVector),
											std::max(sizeof(FVector2D),
											std::max(sizeof(FRotator),
											std::max(sizeof(FIntPoint),
													 sizeof(FColor)))))));
	
	uint8* ParamABuffer = (uint8*)FMemory_Alloca(BufferSize);
	uint8* ParamBBuffer = (uint8*)FMemory_Alloca(BufferSize);
	uint8* ParamCBuffer = (uint8*)FMemory_Alloca(BufferSize);
	uint8* ParamDBuffer = (uint8*)FMemory_Alloca(BufferSize);
	
	switch(RandType)
	{
		// we use no params at all here, they just exist to step through the stack
		case ESquirrelRandType::Int:		Stack.StepCompiledIn<FIntProperty>(ParamABuffer); Stack.StepCompiledIn<FIntProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::Bool:		Stack.StepCompiledIn<FIntProperty>(ParamABuffer); Stack.StepCompiledIn<FIntProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::Float:		Stack.StepCompiledIn<FIntProperty>(ParamABuffer); Stack.StepCompiledIn<FIntProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::Vector:		Stack.StepCompiledIn<FIntProperty>(ParamABuffer); Stack.StepCompiledIn<FIntProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::Vector2D: 	Stack.StepCompiledIn<FIntProperty>(ParamABuffer); Stack.StepCompiledIn<FIntProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::Rotation: 	Stack.StepCompiledIn<FIntProperty>(ParamABuffer); Stack.StepCompiledIn<FIntProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::IntPoint: 	Stack.StepCompiledIn<FIntProperty>(ParamABuffer); Stack.StepCompiledIn<FIntProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::Color:		Stack.StepCompiledIn<FBoolProperty>(ParamABuffer); Stack.StepCompiledIn<FIntProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;

		// First two params are used throughout here
		case ESquirrelRandType::IntInRange:			Stack.StepCompiledIn<FIntProperty>(ParamABuffer);		Stack.StepCompiledIn<FIntProperty>(ParamBBuffer);	 Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::FloatInRange:		Stack.StepCompiledIn<FFloatProperty>(ParamABuffer);		Stack.StepCompiledIn<FFloatProperty>(ParamBBuffer);  Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::VectorInRange:		Stack.StepCompiledIn<FStructProperty>(ParamABuffer); 	Stack.StepCompiledIn<FStructProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::VectorInCone:		Stack.StepCompiledIn<FStructProperty>(ParamABuffer); 	Stack.StepCompiledIn<FFloatProperty>(ParamBBuffer);	 Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::VectorInBox:		Stack.StepCompiledIn<FStructProperty>(ParamABuffer); 	Stack.StepCompiledIn<FStructProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::Vector2DInRange: 	Stack.StepCompiledIn<FStructProperty>(ParamABuffer); 	Stack.StepCompiledIn<FStructProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::RotationInRange: 	Stack.StepCompiledIn<FStructProperty>(ParamABuffer); 	Stack.StepCompiledIn<FStructProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::IntPointInRange:	Stack.StepCompiledIn<FStructProperty>(ParamABuffer); 	Stack.StepCompiledIn<FStructProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::ColorInRange:		Stack.StepCompiledIn<FStructProperty>(ParamABuffer);	Stack.StepCompiledIn<FStructProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;

		// All four params can be seen used here
		case ESquirrelRandType::From1DIndex:		Stack.StepCompiledIn<FIntProperty>(ParamABuffer); Stack.StepCompiledIn<FIntProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::From2DIndex:		Stack.StepCompiledIn<FIntProperty>(ParamABuffer); Stack.StepCompiledIn<FIntProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::From3DIndex:		Stack.StepCompiledIn<FIntProperty>(ParamABuffer); Stack.StepCompiledIn<FIntProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::From4DIndex:		Stack.StepCompiledIn<FIntProperty>(ParamABuffer); Stack.StepCompiledIn<FIntProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
	}

	// Get the output param as a void ptr and cast to the correct type
	P_GET_PROPERTY_REF(FIntProperty, ResultRef);
	void* ResultPtr = Stack.MostRecentPropertyAddress;
	
	P_FINISH;

	P_NATIVE_BEGIN;

	// Now we have the values and stepped through the stack we can assign the correct output
	switch(RandType)
	{
		case ESquirrelRandType::Int:		*(int32*)ResultPtr		= bReverse ? SquirrelStream.PreviousInt() : SquirrelStream.NextInt(); break;
		case ESquirrelRandType::Bool:		*(bool*)ResultPtr		= bReverse ? SquirrelStream.PreviousBool() : SquirrelStream.NextBool(); break;
		case ESquirrelRandType::Float:		*(float*)ResultPtr		= bReverse ? SquirrelStream.PreviousFloat() : SquirrelStream.NextFloat(); break;
		case ESquirrelRandType::Vector: 	*(FVector*)ResultPtr	= bReverse ? SquirrelStream.PreviousVector() : SquirrelStream.NextVector(); break;
		case ESquirrelRandType::Vector2D: 	*(FVector2D*)ResultPtr	= bReverse ? SquirrelStream.PreviousVector2D() : SquirrelStream.NextVector2D(); break;
		case ESquirrelRandType::Rotation: 	*(FRotator*)ResultPtr	= bReverse ? SquirrelStream.PreviousRotation() : SquirrelStream.NextRotation(); break;
		case ESquirrelRandType::IntPoint: 	*(FIntPoint*)ResultPtr	= bReverse ? SquirrelStream.PreviousIntPoint() : SquirrelStream.NextIntPoint(); break;
		case ESquirrelRandType::Color:		*(FColor*)ResultPtr		= bReverse ? SquirrelStream.PreviousColor(*(bool*)ParamABuffer) : SquirrelStream.NextColor(*(bool*)ParamABuffer); break;

		// Use whatever range we ended up with
		case ESquirrelRandType::IntInRange:			*(int32*)ResultPtr		= bReverse ? SquirrelStream.PreviousIntInRange(*(int32*)ParamABuffer, *(int32*)ParamBBuffer) :
																						 SquirrelStream.NextIntInRange(*(int32*)ParamABuffer, *(int32*)ParamBBuffer); break;
		
		case ESquirrelRandType::FloatInRange:		*(float*)ResultPtr		= bReverse ? SquirrelStream.PreviousFloatInRange(*(float*)ParamABuffer, *(float*)ParamBBuffer) :
																						 SquirrelStream.NextFloatInRange(*(float*)ParamABuffer, *(float*)ParamBBuffer); break;
		
		case ESquirrelRandType::VectorInRange:		*(FVector*)ResultPtr	= bReverse ? SquirrelStream.PreviousVectorInRange(*(FVector*)ParamABuffer, *(FVector*)ParamBBuffer) :
																					 	 SquirrelStream.NextVectorInRange(*(FVector*)ParamABuffer, *(FVector*)ParamBBuffer); break;
		
		case ESquirrelRandType::VectorInCone:		*(FVector*)ResultPtr	= bReverse ? SquirrelStream.PreviousVectorInCone(*(FVector*)ParamABuffer, *(float*)ParamBBuffer) :
																						 SquirrelStream.NextVectorInCone(*(FVector*)ParamABuffer, *(float*)ParamBBuffer); break;
																					
		case ESquirrelRandType::VectorInBox:		*(FVector*)ResultPtr	= bReverse ? SquirrelStream.PreviousVectorInBox(FBox{*(FVector*)ParamABuffer, *(FVector*)ParamBBuffer}) :
																						 SquirrelStream.NextVectorInBox(FBox{*(FVector*)ParamABuffer, *(FVector*)ParamBBuffer}); break;
		
		case ESquirrelRandType::Vector2DInRange: 	*(FVector2D*)ResultPtr	= bReverse ? SquirrelStream.PreviousVector2DInRange(*(FVector2D*)ParamABuffer, *(FVector2D*)ParamBBuffer) :
																						 SquirrelStream.NextVector2DInRange(*(FVector2D*)ParamABuffer, *(FVector2D*)ParamBBuffer); break;			
		
		case ESquirrelRandType::RotationInRange: 	*(FRotator*)ResultPtr	= bReverse ? SquirrelStream.PreviousRotationInRange(*(FRotator*)ParamABuffer, *(FRotator*)ParamBBuffer) :
																						 SquirrelStream.NextRotationInRange(*(FRotator*)ParamABuffer, *(FRotator*)ParamBBuffer); break;

		case ESquirrelRandType::IntPointInRange: 	*(FIntPoint*)ResultPtr	= bReverse ? SquirrelStream.PreviousIntPointInRange(*(FIntPoint*)ParamABuffer, *(FIntPoint*)ParamBBuffer) :
																						 SquirrelStream.NextIntPointInRange(*(FIntPoint*)ParamABuffer, *(FIntPoint*)ParamBBuffer); break;

		case ESquirrelRandType::ColorInRange:		*(FColor*)ResultPtr		= bReverse ? SquirrelStream.PreviousColorInRange(*(FColor*)ParamABuffer, *(FColor*)ParamBBuffer) :
																							SquirrelStream.NextColorInRange(*(FColor*)ParamABuffer, *(FColor*)ParamBBuffer); break;
		
		case ESquirrelRandType::From1DIndex:		*(int32*)ResultPtr		= SquirrelStream.RandInt1DIndex(*(int32*)ParamABuffer); break;
		case ESquirrelRandType::From2DIndex:		*(int32*)ResultPtr		= SquirrelStream.RandInt2DIndex(*(int32*)ParamABuffer, *(int32*)ParamBBuffer); break;
		case ESquirrelRandType::From3DIndex:		*(int32*)ResultPtr		= SquirrelStream.RandInt3DIndex(*(int32*)ParamABuffer, *(int32*)ParamBBuffer, *(int32*)ParamCBuffer); break;
		case ESquirrelRandType::From4DIndex:		*(int32*)ResultPtr		= SquirrelStream.RandInt4DIndex(*(int32*)ParamABuffer, *(int32*)ParamBBuffer, *(int32*)ParamCBuffer, *(int32*)ParamDBuffer); break;
	}

	P_NATIVE_END;
}



DEFINE_FUNCTION(UBFSquirrelNoiseBPFL::execInternalSquirrelRandK2)
{
	Stack.MostRecentProperty = nullptr;
	Stack.MostRecentPropertyAddress = nullptr;
	
	P_GET_ENUM(ESquirrelRandType, RandType);
	
	// Our largest supported member is a vector but just in-case we have a larger one in the future we will use this as the buffer size
	static constexpr SIZE_T BufferSize =	std::max(sizeof(int32),
											std::max(sizeof(float),
											std::max(sizeof(FVector),
											std::max(sizeof(FVector2D),
											std::max(sizeof(FRotator),
											std::max(sizeof(FIntPoint),
													 sizeof(FColor)))))));
	
	uint8* ParamABuffer = (uint8*)FMemory_Alloca(BufferSize);
	uint8* ParamBBuffer = (uint8*)FMemory_Alloca(BufferSize);
	uint8* ParamCBuffer = (uint8*)FMemory_Alloca(BufferSize);
	uint8* ParamDBuffer = (uint8*)FMemory_Alloca(BufferSize);
	
	switch(RandType)
	{
		// we use no params at all here, they just exist to step through the stack
		case ESquirrelRandType::Int:		Stack.StepCompiledIn<FIntProperty>(ParamABuffer); Stack.StepCompiledIn<FIntProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::Bool:		Stack.StepCompiledIn<FIntProperty>(ParamABuffer); Stack.StepCompiledIn<FIntProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::Float:		Stack.StepCompiledIn<FIntProperty>(ParamABuffer); Stack.StepCompiledIn<FIntProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::Vector:		Stack.StepCompiledIn<FIntProperty>(ParamABuffer); Stack.StepCompiledIn<FIntProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::Vector2D: 	Stack.StepCompiledIn<FIntProperty>(ParamABuffer); Stack.StepCompiledIn<FIntProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::Rotation: 	Stack.StepCompiledIn<FIntProperty>(ParamABuffer); Stack.StepCompiledIn<FIntProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::IntPoint: 	Stack.StepCompiledIn<FIntProperty>(ParamABuffer); Stack.StepCompiledIn<FIntProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::Color:		Stack.StepCompiledIn<FBoolProperty>(ParamABuffer); Stack.StepCompiledIn<FIntProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;

		// First two params are used throughout here
		case ESquirrelRandType::IntInRange:			Stack.StepCompiledIn<FIntProperty>(ParamABuffer);		Stack.StepCompiledIn<FIntProperty>(ParamBBuffer);	 Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::FloatInRange:		Stack.StepCompiledIn<FFloatProperty>(ParamABuffer);		Stack.StepCompiledIn<FFloatProperty>(ParamBBuffer);  Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::VectorInRange:		Stack.StepCompiledIn<FStructProperty>(ParamABuffer); 	Stack.StepCompiledIn<FStructProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::VectorInCone:		Stack.StepCompiledIn<FStructProperty>(ParamABuffer); 	Stack.StepCompiledIn<FFloatProperty>(ParamBBuffer);	 Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::VectorInBox:		Stack.StepCompiledIn<FStructProperty>(ParamABuffer); 	Stack.StepCompiledIn<FStructProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::Vector2DInRange: 	Stack.StepCompiledIn<FStructProperty>(ParamABuffer); 	Stack.StepCompiledIn<FStructProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::RotationInRange: 	Stack.StepCompiledIn<FStructProperty>(ParamABuffer); 	Stack.StepCompiledIn<FStructProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::IntPointInRange:	Stack.StepCompiledIn<FStructProperty>(ParamABuffer); 	Stack.StepCompiledIn<FStructProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::ColorInRange:		Stack.StepCompiledIn<FStructProperty>(ParamABuffer);	Stack.StepCompiledIn<FStructProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;

		// All four params can be seen used here
		case ESquirrelRandType::From1DIndex:		Stack.StepCompiledIn<FIntProperty>(ParamABuffer); Stack.StepCompiledIn<FIntProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::From2DIndex:		Stack.StepCompiledIn<FIntProperty>(ParamABuffer); Stack.StepCompiledIn<FIntProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::From3DIndex:		Stack.StepCompiledIn<FIntProperty>(ParamABuffer); Stack.StepCompiledIn<FIntProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
		case ESquirrelRandType::From4DIndex:		Stack.StepCompiledIn<FIntProperty>(ParamABuffer); Stack.StepCompiledIn<FIntProperty>(ParamBBuffer); Stack.StepCompiledIn<FIntProperty>(ParamCBuffer); Stack.StepCompiledIn<FIntProperty>(ParamDBuffer); break;
	}

	// Get the output param as a void ptr and cast to the correct type
	P_GET_PROPERTY_REF(FIntProperty, ResultRef);
	void* ResultPtr = Stack.MostRecentPropertyAddress;
	
	P_FINISH;

	P_NATIVE_BEGIN;

	bool bReverse = false; // Blueprint is always false due to VM and everything else causing our index to change so often its not even worth it, it is global after all. Only custom streams can reverse

	// Now we have the values and stepped through the stack we can assign the correct output
	switch(RandType)
	{
		case ESquirrelRandType::Int:		*(int32*)ResultPtr		= Sqrl::RandInt(bReverse); break;
		case ESquirrelRandType::Bool:		*(bool*)ResultPtr		= Sqrl::RandBool(bReverse); break;
		case ESquirrelRandType::Float:		*(float*)ResultPtr		= Sqrl::RandFloat(bReverse); break;
		case ESquirrelRandType::Vector: 	*(FVector*)ResultPtr	= Sqrl::RandVector(bReverse); break;
		case ESquirrelRandType::Vector2D: 	*(FVector2D*)ResultPtr	= Sqrl::RandVector2D(bReverse); break;
		case ESquirrelRandType::Rotation: 	*(FRotator*)ResultPtr	= Sqrl::RandRotation(bReverse); break;
		case ESquirrelRandType::IntPoint: 	*(FIntPoint*)ResultPtr	= Sqrl::RandIntPoint(bReverse); break;
		case ESquirrelRandType::Color:		*(FColor*)ResultPtr		= Sqrl::RandColor(*(bool*)ParamABuffer, bReverse); break;

		// Use whatever range we ended up with
		case ESquirrelRandType::IntInRange:			*(int32*)ResultPtr		= Sqrl::RandIntInRange(*(int32*)ParamABuffer, *(int32*)ParamBBuffer, bReverse); break;
		case ESquirrelRandType::FloatInRange:		*(float*)ResultPtr		= Sqrl::RandFloatInRange(*(float*)ParamABuffer, *(float*)ParamBBuffer, bReverse); break;
		case ESquirrelRandType::VectorInRange:		*(FVector*)ResultPtr	= Sqrl::RandVectorInRange(*(FVector*)ParamABuffer, *(FVector*)ParamBBuffer, bReverse); break;
		case ESquirrelRandType::VectorInCone:		*(FVector*)ResultPtr	= Sqrl::RandVectorInCone(*(FVector*)ParamABuffer, *(float*)ParamBBuffer, bReverse); break;
		case ESquirrelRandType::VectorInBox:		*(FVector*)ResultPtr	= Sqrl::RandVectorInBox(FBox{*(FVector*)ParamABuffer, *(FVector*)ParamBBuffer}, bReverse); break;
		case ESquirrelRandType::Vector2DInRange: 	*(FVector2D*)ResultPtr	= Sqrl::RandVector2DInRange(*(FVector2D*)ParamABuffer, *(FVector2D*)ParamBBuffer, bReverse); break;
		case ESquirrelRandType::RotationInRange: 	*(FRotator*)ResultPtr	= Sqrl::RandRotationInRange(*(FRotator*)ParamABuffer, *(FRotator*)ParamBBuffer, bReverse); break;
		case ESquirrelRandType::IntPointInRange: 	*(FIntPoint*)ResultPtr	= Sqrl::RandIntPointInRange(*(FIntPoint*)ParamABuffer, *(FIntPoint*)ParamBBuffer, bReverse); break;
		case ESquirrelRandType::ColorInRange:		*(FColor*)ResultPtr		= Sqrl::RandColorInRange(*(FColor*)ParamABuffer, *(FColor*)ParamBBuffer, bReverse); break;
		
		case ESquirrelRandType::From1DIndex:		*(int32*)ResultPtr		= Sqrl::RandInt1DIndex(*(int32*)ParamABuffer); break;
		case ESquirrelRandType::From2DIndex:		*(int32*)ResultPtr		= Sqrl::RandInt2DIndex(*(int32*)ParamABuffer, *(int32*)ParamBBuffer); break;
		case ESquirrelRandType::From3DIndex:		*(int32*)ResultPtr		= Sqrl::RandInt3DIndex(*(int32*)ParamABuffer, *(int32*)ParamBBuffer, *(int32*)ParamCBuffer); break;
		case ESquirrelRandType::From4DIndex:		*(int32*)ResultPtr		= Sqrl::RandInt4DIndex(*(int32*)ParamABuffer, *(int32*)ParamBBuffer, *(int32*)ParamCBuffer, *(int32*)ParamDBuffer); break;
	}

	P_NATIVE_END;
}
