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



#include "BFSquirrelK2_SquirrelRand.h"
#include "BFSquirrelK2Utility.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "GraphEditorSettings.h"
#include "K2Node_CallFunction.h"
#include "BFSquirrel/BFSquirrelCore.h"
#include "KismetCompiler.h"



void UBFSquirrelK2_SquirrelRand::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec,  UEdGraphSchema_K2::PN_Execute);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec,  UEdGraphSchema_K2::PN_Then);
	
	UEnum* SqrlEnum = StaticEnum<ESquirrelRandType>();
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Byte, SqrlEnum, SqrlK2::Priv::FunctionInputSquirrelRandomType)->DefaultValue = SqrlEnum->GetNameStringByIndex((int32)LastEnumType);
	
	// All have friendly names and are hidden depending on the type
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, SqrlK2::Priv::FunctionInputParamA)->bHidden = true;
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, SqrlK2::Priv::FunctionInputParamB)->bHidden = true;
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, SqrlK2::Priv::FunctionInputParamC)->bHidden = true;
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, SqrlK2::Priv::FunctionInputParamD)->bHidden = true;
	
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Wildcard, SqrlK2::Priv::FunctionOutputParam)->PinFriendlyName = SqrlK2::Priv::RandResultPinName;

	UpdateOutputPinType();
}

void UBFSquirrelK2_SquirrelRand::ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins)
{
	Super::ReallocatePinsDuringReconstruction(OldPins);
	for(auto* OldPin : OldPins)
	{
		for(auto* Pin : Pins)
		{
			if(Pin->PinName == OldPin->PinName)
			{
				Pin->PinType = OldPin->PinType;
				Pin->DefaultValue = OldPin->DefaultValue;
				break;
			}
		}
	}
}

void UBFSquirrelK2_SquirrelRand::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);
	
	bool bResult = true;
	auto* CallFunction = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	
	CallFunction->SetFromFunction(UBFSquirrelNoiseBPFL::StaticClass()->FindFunctionByName(SqrlK2::Priv::FunctionNameSquirrelRand));
	CallFunction->AllocateDefaultPins();
	
	auto* EnumPin =	  FindPin(SqrlK2::Priv::FunctionInputSquirrelRandomType);
	auto* ParamAPin = FindPin(SqrlK2::Priv::FunctionInputParamA);
	auto* ParamBPin = FindPin(SqrlK2::Priv::FunctionInputParamB);
	auto* ParamCPin = FindPin(SqrlK2::Priv::FunctionInputParamC);
	auto* ParamDPin = FindPin(SqrlK2::Priv::FunctionInputParamD);
	auto* ResultPin = FindPin(SqrlK2::Priv::FunctionOutputParam);
	
	
	auto* CallFunctionInputPin  = CallFunction->FindPin(SqrlK2::Priv::FunctionInputSquirrelRandomType);
	auto* CallFunctionParamAPin = CallFunction->FindPin(SqrlK2::Priv::FunctionInputParamA);
	auto* CallFunctionParamBPin = CallFunction->FindPin(SqrlK2::Priv::FunctionInputParamB);
	auto* CallFunctionParamCPin = CallFunction->FindPin(SqrlK2::Priv::FunctionInputParamC);
	auto* CallFunctionParamDPin = CallFunction->FindPin(SqrlK2::Priv::FunctionInputParamD);
	auto* CallFunctionOutputPin = CallFunction->FindPin(SqrlK2::Priv::FunctionOutputParam);


	// Update the wild card type to match
	CallFunctionParamAPin->PinType = ParamAPin->PinType;
	CallFunctionParamBPin->PinType = ParamBPin->PinType;
	CallFunctionParamCPin->PinType = ParamCPin->PinType;
	CallFunctionParamDPin->PinType = ParamDPin->PinType;
	CallFunctionOutputPin->PinType = ResultPin->PinType;


	// Connect everything and done!
	bResult &= CompilerContext.MovePinLinksToIntermediate(*GetExecPin(), *CallFunction->GetExecPin()).CanSafeConnect();

	bResult &= CompilerContext.MovePinLinksToIntermediate(*EnumPin, *CallFunctionInputPin).CanSafeConnect();
	bResult &= CompilerContext.MovePinLinksToIntermediate(*ParamAPin, *CallFunctionParamAPin).CanSafeConnect();
	bResult &= CompilerContext.MovePinLinksToIntermediate(*ParamBPin, *CallFunctionParamBPin).CanSafeConnect();
	bResult &= CompilerContext.MovePinLinksToIntermediate(*ParamCPin, *CallFunctionParamCPin).CanSafeConnect();
	bResult &= CompilerContext.MovePinLinksToIntermediate(*ParamDPin, *CallFunctionParamDPin).CanSafeConnect();
	bResult &= CompilerContext.MovePinLinksToIntermediate(*ResultPin, *CallFunctionOutputPin).CanSafeConnect();
	
	bResult &= CompilerContext.MovePinLinksToIntermediate(*GetThenPin(), *CallFunction->GetThenPin()).CanSafeConnect();

	if(!bResult)
		CompilerContext.MessageLog.Error(TEXT("Failed to connect pins in %s"), this);
	
	BreakAllNodeLinks();
}


FText UBFSquirrelK2_SquirrelRand::GetTooltipText() const
{
	if(auto* Pin = FindPin(SqrlK2::Priv::FunctionInputSquirrelRandomType))
	{
		FString CurrentType =  Pin->DefaultValue;
		return SqrlK2::Priv::GetSquirrelRandTypeDescription((ESquirrelRandType)StaticEnum<ESquirrelRandType>()->GetValueByNameString(CurrentType));
	}
	return FText::GetEmpty();
}


FText UBFSquirrelK2_SquirrelRand::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return SqrlK2::Priv::SquirrelRandNodeTitle;
}


void UBFSquirrelK2_SquirrelRand::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	Super::GetMenuActions(ActionRegistrar);
	UClass* Action = GetClass();
	if (ActionRegistrar.IsOpenForRegistration(Action))
	{
		UBlueprintNodeSpawner* Spawner = UBlueprintNodeSpawner::Create(GetClass());
		ActionRegistrar.AddBlueprintAction(Action, Spawner);
	}
}

void UBFSquirrelK2_SquirrelRand::NotifyPinConnectionListChanged(UEdGraphPin* Pin)
{
	Super::NotifyPinConnectionListChanged(Pin);
	UpdateOutputPinType();
}

void UBFSquirrelK2_SquirrelRand::PostReconstructNode()
{
	Super::PostReconstructNode();
	UpdateOutputPinType();
}

void UBFSquirrelK2_SquirrelRand::PinDefaultValueChanged(UEdGraphPin* Pin)
{
	Super::PinDefaultValueChanged(Pin);
	UpdateOutputPinType();
}


FSlateIcon UBFSquirrelK2_SquirrelRand::GetIconAndTint(FLinearColor& OutColor) const
{
	OutColor = GetDefault<UGraphEditorSettings>()->FunctionCallNodeTitleColor;
	return {FAppStyle::GetAppStyleSetName(), "Kismet.AllClasses.FunctionIcon"};
}


void UBFSquirrelK2_SquirrelRand::UpdateOutputPinType()
{
    auto* RandEnumPin =	FindPin(SqrlK2::Priv::FunctionInputSquirrelRandomType);
    auto* ParamAPin = 	FindPin(SqrlK2::Priv::FunctionInputParamA);
    auto* ParamBPin = 	FindPin(SqrlK2::Priv::FunctionInputParamB);
    auto* ParamCPin = 	FindPin(SqrlK2::Priv::FunctionInputParamC);
    auto* ParamDPin = 	FindPin(SqrlK2::Priv::FunctionInputParamD);
    auto* ResultPin = 	FindPin(SqrlK2::Priv::FunctionOutputParam);
    
    if(ResultPin && RandEnumPin &&
    	ParamAPin && ParamBPin && ParamCPin && ParamDPin)
    {
        ESquirrelRandType RandType = (ESquirrelRandType)StaticEnum<ESquirrelRandType>()->GetValueByNameString(RandEnumPin->DefaultValue);
		bool bDirty = LastEnumType != RandType || ResultPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Wildcard;

    	LastEnumType = RandType;
    	bSolidAlpha = ParamAPin->DefaultValue == TEXT("true");

    	// Force updates if we have a wildcard type
    	if(!bDirty)
    		return;
    	
    	// When changing pin types this should break any existing connections for all dynamic pins
    	GetSchema()->RecombinePin(ParamAPin);
    	GetSchema()->RecombinePin(ParamBPin);
    	GetSchema()->RecombinePin(ParamCPin);
    	GetSchema()->RecombinePin(ParamDPin);
    	
    	ParamAPin->BreakAllPinLinks();
    	ParamBPin->BreakAllPinLinks();
    	ParamCPin->BreakAllPinLinks();
    	ParamDPin->BreakAllPinLinks();
    	
    	ResultPin->BreakAllPinLinks();
    	
        switch (RandType)
        {
            // Basic rand types dont use extra pins
            case ESquirrelRandType::Int:
            {
	            SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0");
	            SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
	            SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
	            SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
	            SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
                break;
            }
            case ESquirrelRandType::Bool:
            {
				SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Boolean, NAME_None, nullptr, "False");
            	SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
                break;
            }
            case ESquirrelRandType::Float:
            {
            	SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Real, UEdGraphSchema_K2::PC_Float, nullptr, "0");
				SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
                break;
            }
            case ESquirrelRandType::Vector:
            {
            	SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FVector>::Get());
            	SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
                break;
            }
            case ESquirrelRandType::Vector2D:
            {
            	SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FVector2D>::Get());
            	SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
                break;
            }
            case ESquirrelRandType::Rotation:
            {
            	SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FRotator>::Get());
            	SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
                break;
            }
            case ESquirrelRandType::IntPoint:
            {
				SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FIntPoint>::Get());
				SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
				SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
				SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
				SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
                break;
            }
            case ESquirrelRandType::Color:
            {
				SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FColor>::Get());
            	SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Boolean, NAME_None, nullptr, bSolidAlpha ? "true" : "false");
				SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
				SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
				SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	ParamAPin->PinFriendlyName = SqrlK2::Priv::SolidAlphaPinName;
                break;
            }

        	
        	// These range rands show the pins needed
            case ESquirrelRandType::IntInRange:
            {
            	SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0");
            	if(bDirty)
            	{
            		SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", false);
            		SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", false);
            		SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            		SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);

            		ParamAPin->PinFriendlyName = SqrlK2::Priv::MinPinName;
	                ParamBPin->PinFriendlyName = SqrlK2::Priv::MaxPinName;
            	}
				break;
            }
            case ESquirrelRandType::FloatInRange:
            {
				SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Real, UEdGraphSchema_K2::PC_Float, nullptr, "0");
            	if(bDirty)
            	{
            		SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Real, UEdGraphSchema_K2::PC_Float, nullptr, "0", false);
            		SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Real, UEdGraphSchema_K2::PC_Float, nullptr, "0", false);
            		SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            		SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            		
            		ParamAPin->PinFriendlyName = SqrlK2::Priv::MinPinName;
            		ParamBPin->PinFriendlyName = SqrlK2::Priv::MaxPinName;
            	}
				break;
            }
            case ESquirrelRandType::VectorInRange:
            {
            	SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FVector>::Get());
            	if(bDirty)
            	{
            		SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FVector>::Get());
            		SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FVector>::Get());
            		SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            		SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            		
            		ParamAPin->PinFriendlyName = SqrlK2::Priv::MinPinName;
            		ParamBPin->PinFriendlyName = SqrlK2::Priv::MaxPinName;
            	}
				break;
            }
            case ESquirrelRandType::VectorInCone:
            {
				SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FVector>::Get());
            	if(bDirty)
            	{
            		SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FVector>::Get());
            		SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Real, UEdGraphSchema_K2::PC_Float, nullptr, "0");
            		SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            		SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            		
            		ParamAPin->PinFriendlyName = SqrlK2::Priv::DirPinName;
            		ParamBPin->PinFriendlyName = SqrlK2::Priv::HalfAnglePinName;
            	}
				break;
            }
			case ESquirrelRandType::VectorInBox:
            {
            	SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FVector>::Get());
            	if(bDirty)
            	{
            		SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FVector>::Get());
            		SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FVector>::Get());
            		SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            		SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	
            		ParamAPin->PinFriendlyName = SqrlK2::Priv::MinPinName;
            		ParamBPin->PinFriendlyName = SqrlK2::Priv::MaxPinName;
            	}
            	break;
            }
            case ESquirrelRandType::Vector2DInRange:
            {
				SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FVector2D>::Get());
            	if(bDirty)
            	{
            		SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FVector2D>::Get());
            		SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FVector2D>::Get());
            		SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            		SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            		
            		ParamAPin->PinFriendlyName = SqrlK2::Priv::MinPinName;
            		ParamBPin->PinFriendlyName = SqrlK2::Priv::MaxPinName;
            	}
				break;
            }
            case ESquirrelRandType::RotationInRange:
            {
            	SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FRotator>::Get());
            	if(bDirty)
            	{
            		SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FRotator>::Get());
            		SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FRotator>::Get());
            		SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            		SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            		
            		ParamAPin->PinFriendlyName = SqrlK2::Priv::MinPinName;
            		ParamBPin->PinFriendlyName = SqrlK2::Priv::MaxPinName;
            	}
				break;
            }
            case ESquirrelRandType::IntPointInRange:
            {
            	SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FIntPoint>::Get());
            	if(bDirty)
            	{
            		SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FIntPoint>::Get());
            		SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FIntPoint>::Get());
            		SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            		SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            		
            		ParamAPin->PinFriendlyName = SqrlK2::Priv::MinPinName;
            		ParamBPin->PinFriendlyName = SqrlK2::Priv::MaxPinName;
            	}
				break;
            }
            case ESquirrelRandType::ColorInRange:
            {
            	SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FColor>::Get());
            	if(bDirty)
            	{
            		SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FColor>::Get());
            		SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FColor>::Get());
            		SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            		SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            		ParamAPin->PinFriendlyName = SqrlK2::Priv::MinPinName;
            		ParamBPin->PinFriendlyName = SqrlK2::Priv::MaxPinName;
            	}
				break;
            }
			case ESquirrelRandType::From1DIndex:
            {
            	SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0");
            	if(bDirty)
            	{
            		SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", false);
            		SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            		SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            		SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            		ParamAPin->PinFriendlyName = SqrlK2::Priv::XIndexPinName;
            	}
            	break;
            }
        	case ESquirrelRandType::From2DIndex:
			{
            	SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0");
				if(bDirty)
				{
					SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", false);
					SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", false);
					SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
					SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
					ParamAPin->PinFriendlyName = SqrlK2::Priv::XIndexPinName;
					ParamBPin->PinFriendlyName = SqrlK2::Priv::YIndexPinName;
				}
				break;
			}
        	case ESquirrelRandType::From3DIndex:
            {
            	SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0");
	            if(bDirty)
	            {
	            	SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", false);
	            	SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", false);
	            	SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", false);
	            	SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
	            	ParamAPin->PinFriendlyName = SqrlK2::Priv::XIndexPinName;
	            	ParamBPin->PinFriendlyName = SqrlK2::Priv::YIndexPinName;
	            	ParamCPin->PinFriendlyName = SqrlK2::Priv::ZIndexPinName;
	            }
	            break;
            }
			case ESquirrelRandType::From4DIndex:
            {
            	SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0");
            	if(bDirty)
            	{
            		SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", false);
            		SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", false);
            		SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", false);
            		SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", false);
            		ParamAPin->PinFriendlyName = SqrlK2::Priv::XIndexPinName;
            		ParamBPin->PinFriendlyName = SqrlK2::Priv::YIndexPinName;
            		ParamCPin->PinFriendlyName = SqrlK2::Priv::ZIndexPinName;
            		ParamDPin->PinFriendlyName = SqrlK2::Priv::WIndexPinName;
            	}
            	break;
            }
        }
	    GetGraph()->NotifyGraphChanged();
    }
}



