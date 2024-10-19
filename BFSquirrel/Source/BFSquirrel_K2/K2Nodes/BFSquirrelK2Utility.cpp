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

#include "BFSquirrelK2Utility.h"




#define LOCTEXT_NAMESPACE "BFSquirrelK2"

namespace SqrlK2::Priv
{
    void SetPinValues(UEdGraphPin* Pin, FName PinCategory, FName PinSubCategory, UObject* PinSubCategoryObject, FString DefaultValue, bool bHidden)
    {
        Pin->PinType.PinCategory = PinCategory;
        Pin->PinType.PinSubCategory = PinSubCategory;
        Pin->PinType.PinSubCategoryObject = PinSubCategoryObject;
        Pin->DefaultValue = DefaultValue;
        Pin->bHidden = bHidden;
    }

    
    FText GetSquirrelRandTypeDescription(ESquirrelRandType RandType)
    {
        switch (RandType)
        {
            case ESquirrelRandType::Int:
                return LOCTEXT("BFSquirrelK2_SquirrelRand_Desc_Int", "Returns a random signed integer.");
            
            case ESquirrelRandType::Bool:
                return LOCTEXT("BFSquirrelK2_SquirrelRand_Desc_Bool", "Returns a random boolean.");
            
            case ESquirrelRandType::Float:
                return LOCTEXT("BFSquirrelK2_SquirrelRand_Desc_Float", "Returns a random float from the range of [0, 1].");
            
            case ESquirrelRandType::Vector:
                return LOCTEXT("BFSquirrelK2_SquirrelRand_Desc_Vector", "Returns a random unit vector.");
            
            case ESquirrelRandType::Vector2D:
                return LOCTEXT("BFSquirrelK2_SquirrelRand_Desc_Vector2D", "Returns a random 2D unit vector.");
            
            case ESquirrelRandType::Rotation:
                return LOCTEXT("BFSquirrelK2_SquirrelRand_Desc_Rotation", "Returns a random rotation in the range of [0, 360].");
            
            case ESquirrelRandType::IntPoint:
                return LOCTEXT("BFSquirrelK2_SquirrelRand_Desc_IntPoint", "Returns a random int point vector.");
            
            case ESquirrelRandType::Color:
                return LOCTEXT("BFSquirrelK2_SquirrelRand_Desc_Color", "Returns a random color.");
            
            case ESquirrelRandType::IntInRange:
                return LOCTEXT("BFSquirrelK2_SquirrelRand_Desc_IntInRange", "Returns a random integer within the given range.");
            
            case ESquirrelRandType::FloatInRange:
                return LOCTEXT("BFSquirrelK2_SquirrelRand_Desc_FloatInRange", "Returns a random float within the given range.");
            
            case ESquirrelRandType::VectorInRange:
                return LOCTEXT("BFSquirrelK2_SquirrelRand_Desc_VectorInRange", "Returns a random vector within the given range.");
            
            case ESquirrelRandType::VectorInCone:
                return LOCTEXT("BFSquirrelK2_SquirrelRand_Desc_VectorInCone", "Returns a random unit vector, uniformly distributed, within the specified cone. ConeHalfAngleRad is the half-angle of cone, in radians. Returns a normalized vector.");
            
            case ESquirrelRandType::VectorInBox:
                return LOCTEXT("BFSquirrelK2_SquirrelRand_Desc_VectorInBox", "Returns a random vector within the specified box's Min and Max extent.");
            
            case ESquirrelRandType::Vector2DInRange:
                return LOCTEXT("BFSquirrelK2_SquirrelRand_Desc_Vector2DInRange", "Returns a random 2D vector within the given range.");
            
            case ESquirrelRandType::RotationInRange:
                return LOCTEXT("BFSquirrelK2_SquirrelRand_Desc_RotationInRange", "Returns a random rotation within the specified range.");
            
            case ESquirrelRandType::IntPointInRange:
                return LOCTEXT("BFSquirrelK2_SquirrelRand_Desc_IntPointInRange", "Returns a random int point vector within the given range.");
            
            case ESquirrelRandType::ColorInRange:
                return LOCTEXT("BFSquirrelK2_SquirrelRand_Desc_ColorInRange", "Returns a random color within the given range.");

            case ESquirrelRandType::From1DIndex:
                return LOCTEXT("BFSquirrelK2_SquirrelRand_Desc_Int1DIndex", "Returns a psuedo-random integer based on the 1D index, benefits of index based is deterministic and order-independent as long as the global seed is the same(UBFSquirrelDeveloperSettings::GlobalNoiseSeed).");
            
            case ESquirrelRandType::From2DIndex:
                return LOCTEXT("BFSquirrelK2_SquirrelRand_Desc_Int2DIndex", "Returns a psuedo-random integer based on the 2D index, benefits of index based is deterministic and order-independent as long as the global seed is the same(UBFSquirrelDeveloperSettings::GlobalNoiseSeed).");
            
            case ESquirrelRandType::From3DIndex:
                return LOCTEXT("BFSquirrelK2_SquirrelRand_Desc_Int3DIndex", "Returns a psuedo-random integer based on the 3D index, benefits of index based is deterministic and order-independent as long as the global seed is the same(UBFSquirrelDeveloperSettings::GlobalNoiseSeed).");

            case ESquirrelRandType::From4DIndex:
                return LOCTEXT("BFSquirrelK2_SquirrelRand_Desc_Int4DIndex", "Returns a psuedo-random integer based on the 4D index, benefits of index based is deterministic and order-independent as long as the global seed is the same(UBFSquirrelDeveloperSettings::GlobalNoiseSeed).");
        }
        return FText::GetEmpty();
    }
}

#undef LOCTEXT_NAMESPACE

