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


#include "BFSquirrelK2_SquirrelStreamRand.h"
#include "BFSquirrelK2Utility.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "GraphEditorSettings.h"
#include "K2Node_CallFunction.h"
#include "KismetCompiler.h"

#include "BFSquirrel/Squirrel/BFSquirrelStream.h"



void UBFSquirrelK2_SquirrelStreamRand::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec,  UEdGraphSchema_K2::PN_Execute);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec,  UEdGraphSchema_K2::PN_Then);
	
	UEnum* SqrlEnum = StaticEnum<ESquirrelRandType>();
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Byte, SqrlEnum, SqrlK2::Priv::FunctionInputSquirrelRandomType)->DefaultValue = SqrlEnum->GetNameStringByIndex((int32)LastEnumType);
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Struct, FSquirrelStream::StaticStruct(), SqrlK2::Priv::FunctionInputSquirrelStream)->PinType.bIsReference = true;
	auto* ReversePin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Boolean, SqrlK2::Priv::FunctionInputReverseFlag);
	ReversePin->DefaultValue = bLastReverse ? TEXT("true") : TEXT("false");
	ReversePin->PinToolTip = TEXT("If true the streams index will decrement instead of increment, this allows you to go forward and back through the noise random numbers and get the same value, requires the same random type as before and after to be accurate.");

	// All have friendly names and are hidden depending on the type
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, SqrlK2::Priv::FunctionInputParamA)->bHidden = true;
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, SqrlK2::Priv::FunctionInputParamB)->bHidden = true;
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, SqrlK2::Priv::FunctionInputParamC)->bHidden = true;
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, SqrlK2::Priv::FunctionInputParamD)->bHidden = true;
	
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Wildcard, SqrlK2::Priv::FunctionOutputParam)->PinFriendlyName = SqrlK2::Priv::RandResultPinName;

	UpdateOutputPinType();
}


void UBFSquirrelK2_SquirrelStreamRand::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);
	
	bool bResult = true;
	auto* CallFunction = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	
	CallFunction->SetFromFunction(UBFSquirrelNoiseBPFL::StaticClass()->FindFunctionByName(SqrlK2::Priv::FunctionNameSquirrelStreamRand));
	CallFunction->AllocateDefaultPins();
	
	auto* EnumPin = FindPin(SqrlK2::Priv::FunctionInputSquirrelRandomType);
	auto* ReversePin = FindPin(SqrlK2::Priv::FunctionInputReverseFlag);
	auto* StreamPin = FindPin(SqrlK2::Priv::FunctionInputSquirrelStream);
	auto* ParamAPin = FindPin(SqrlK2::Priv::FunctionInputParamA);
	auto* ParamBPin = FindPin(SqrlK2::Priv::FunctionInputParamB);
	auto* ParamCPin = FindPin(SqrlK2::Priv::FunctionInputParamC);
	auto* ParamDPin = FindPin(SqrlK2::Priv::FunctionInputParamD);
	auto* ResultPin = FindPin(SqrlK2::Priv::FunctionOutputParam);
	
	
	auto* CallFunctionInputPin = CallFunction->FindPin(SqrlK2::Priv::FunctionInputSquirrelRandomType);
	auto* CallFunctionReversePin = CallFunction->FindPin(SqrlK2::Priv::FunctionInputReverseFlag);
	auto* CallFunctionStreamPin = CallFunction->FindPin(SqrlK2::Priv::FunctionInputSquirrelStream);
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
	bResult &= CompilerContext.MovePinLinksToIntermediate(*ReversePin, *CallFunctionReversePin).CanSafeConnect();
	bResult &= CompilerContext.MovePinLinksToIntermediate(*StreamPin, *CallFunctionStreamPin).CanSafeConnect();
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

void UBFSquirrelK2_SquirrelStreamRand::ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins)
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
FText UBFSquirrelK2_SquirrelStreamRand::GetTooltipText() const
{
	if(auto* Pin = FindPin(SqrlK2::Priv::FunctionInputSquirrelRandomType))
		return SqrlK2::Priv::GetSquirrelRandTypeDescription((ESquirrelRandType)StaticEnum<ESquirrelRandType>()->GetValueByNameString(Pin->DefaultValue));
	return FText::GetEmpty();
}


FText UBFSquirrelK2_SquirrelStreamRand::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return SqrlK2::Priv::SquirrelStreamRandNodeTitle;
}


void UBFSquirrelK2_SquirrelStreamRand::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	Super::GetMenuActions(ActionRegistrar);
	UClass* Action = GetClass();
	if (ActionRegistrar.IsOpenForRegistration(Action))
	{
		UBlueprintNodeSpawner* Spawner = UBlueprintNodeSpawner::Create(GetClass());
		ActionRegistrar.AddBlueprintAction(Action, Spawner);
	}
}

void UBFSquirrelK2_SquirrelStreamRand::NotifyPinConnectionListChanged(UEdGraphPin* Pin)
{
	Super::NotifyPinConnectionListChanged(Pin);
	UpdateOutputPinType();
}

void UBFSquirrelK2_SquirrelStreamRand::PostReconstructNode()
{
	Super::PostReconstructNode();
	UpdateOutputPinType();
}

void UBFSquirrelK2_SquirrelStreamRand::PinDefaultValueChanged(UEdGraphPin* Pin)
{
	Super::PinDefaultValueChanged(Pin);
	UpdateOutputPinType();
}


FSlateIcon UBFSquirrelK2_SquirrelStreamRand::GetIconAndTint(FLinearColor& OutColor) const
{
	OutColor = GetDefault<UGraphEditorSettings>()->FunctionCallNodeTitleColor;
	return {FAppStyle::GetAppStyleSetName(), "Kismet.AllClasses.FunctionIcon"};
}


void UBFSquirrelK2_SquirrelStreamRand::UpdateOutputPinType()
{
    auto* RandEnumPin =		FindPin(SqrlK2::Priv::FunctionInputSquirrelRandomType);
    auto* InputStreamPin = 	FindPin(SqrlK2::Priv::FunctionInputSquirrelStream);
    auto* ReversePin = 		FindPin(SqrlK2::Priv::FunctionInputReverseFlag);
    auto* ParamAPin = 		FindPin(SqrlK2::Priv::FunctionInputParamA);
    auto* ParamBPin = 		FindPin(SqrlK2::Priv::FunctionInputParamB);
    auto* ParamCPin = 		FindPin(SqrlK2::Priv::FunctionInputParamC);
    auto* ParamDPin = 		FindPin(SqrlK2::Priv::FunctionInputParamD);
    auto* ResultPin = 		FindPin(SqrlK2::Priv::FunctionOutputParam);
    
    if(ResultPin && RandEnumPin && InputStreamPin &&
    	ParamAPin && ParamBPin && ParamCPin && ParamDPin)
    {
        ESquirrelRandType RandType = (ESquirrelRandType)StaticEnum<ESquirrelRandType>()->GetValueByNameString(RandEnumPin->DefaultValue);
		bool bDirty = LastEnumType != RandType || ResultPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Wildcard;

    	bSolidAlpha = ParamAPin->DefaultValue == TEXT("true");
		LastEnumType = RandType;
    	bLastReverse = ReversePin->DefaultValue == TEXT("true");

    	if(InputStreamPin->LinkedTo.Num() == 1)
    	{
			InputStreamPin->PinType = InputStreamPin->LinkedTo[0]->PinType;
    		InputStreamPin->PinType.bIsReference = true;
    	}
	    else
	    {
		    InputStreamPin->PinType.PinCategory = UEdGraphSchema_K2::PC_Struct;
	    	InputStreamPin->PinType.PinSubCategoryObject = FSquirrelStream::StaticStruct();
	    	InputStreamPin->PinType.PinSubCategory = NAME_None;
	    }
    	
    	// If we didn't dirty the dynamic pins by changing the enum type, we can skip this
    	if(!bDirty)
    		return;

    	// Easier to set it here since it should always be on besides for index based noise, so let it turn it off if it needs to
    	ReversePin->bHidden = false; 

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
            // These basic rands hide the pins not needed
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
            	SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", false);
            	SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", false);
            	SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);

            	ParamAPin->PinFriendlyName = SqrlK2::Priv::MinPinName;
                ParamBPin->PinFriendlyName = SqrlK2::Priv::MaxPinName;
				break;
            }
            case ESquirrelRandType::FloatInRange:
            {
				SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Real, UEdGraphSchema_K2::PC_Float, nullptr, "0");
            	SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Real, UEdGraphSchema_K2::PC_Float, nullptr, "0", false);
            	SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Real, UEdGraphSchema_K2::PC_Float, nullptr, "0", false);
            	SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	
            	ParamAPin->PinFriendlyName = SqrlK2::Priv::MinPinName;
            	ParamBPin->PinFriendlyName = SqrlK2::Priv::MaxPinName;
				break;
            }
            case ESquirrelRandType::VectorInRange:
            {
            	SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FVector>::Get());
            	SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FVector>::Get());
            	SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FVector>::Get());
            	SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	
            	ParamAPin->PinFriendlyName = SqrlK2::Priv::MinPinName;
            	ParamBPin->PinFriendlyName = SqrlK2::Priv::MaxPinName;
				break;
            }
            case ESquirrelRandType::VectorInCone:
            {
				SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FVector>::Get());
            	SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FVector>::Get());
            	SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Real, UEdGraphSchema_K2::PC_Float, nullptr, "0");
            	SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	
            	ParamAPin->PinFriendlyName = SqrlK2::Priv::DirPinName;
            	ParamBPin->PinFriendlyName = SqrlK2::Priv::HalfAnglePinName;
				break;
            }
			case ESquirrelRandType::VectorInBox:
            {
            	SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FVector>::Get());
            	SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FVector>::Get());
            	SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FVector>::Get());
            	SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
        
            	ParamAPin->PinFriendlyName = SqrlK2::Priv::MinPinName;
            	ParamBPin->PinFriendlyName = SqrlK2::Priv::MaxPinName;
            	break;
            }
            case ESquirrelRandType::Vector2DInRange:
            {
				SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FVector2D>::Get());
            	SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FVector2D>::Get());
            	SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FVector2D>::Get());
            	SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	
            	ParamAPin->PinFriendlyName = SqrlK2::Priv::MinPinName;
            	ParamBPin->PinFriendlyName = SqrlK2::Priv::MaxPinName;
				break;
            }
            case ESquirrelRandType::RotationInRange:
            {
            	SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FRotator>::Get());
            	SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FRotator>::Get());
            	SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FRotator>::Get());
            	SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	
            	ParamAPin->PinFriendlyName = SqrlK2::Priv::MinPinName;
            	ParamBPin->PinFriendlyName = SqrlK2::Priv::MaxPinName;
				break;
            }
            case ESquirrelRandType::IntPointInRange:
            {
				SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FIntPoint>::Get());
            	SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FIntPoint>::Get());
            	SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FIntPoint>::Get());
            	SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	
            	ParamAPin->PinFriendlyName = SqrlK2::Priv::MinPinName;
            	ParamBPin->PinFriendlyName = SqrlK2::Priv::MaxPinName;
				break;
            }
            case ESquirrelRandType::ColorInRange:
            {
            	SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FColor>::Get());
            	SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FColor>::Get());
            	SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Struct, NAME_None, TBaseStructure<FColor>::Get());
            	SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	ParamAPin->PinFriendlyName = SqrlK2::Priv::MinPinName;
            	ParamBPin->PinFriendlyName = SqrlK2::Priv::MaxPinName;
            	break;
            }
			case ESquirrelRandType::From1DIndex:
            {
            	SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0");
            	ReversePin->bHidden = true; // Cant reverse when we are the one supplying the index
            	SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", false);
            	SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
            	ParamAPin->PinFriendlyName = SqrlK2::Priv::XIndexPinName;
            	break;
            }
        	case ESquirrelRandType::From2DIndex:
			{
            	SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0");
            	ReversePin->bHidden = true; // Cant reverse when we are the one supplying the index
				SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", false);
				SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", false);
				SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
				SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
				ParamAPin->PinFriendlyName = SqrlK2::Priv::XIndexPinName;
				ParamBPin->PinFriendlyName = SqrlK2::Priv::YIndexPinName;
				break;
			}
        	case ESquirrelRandType::From3DIndex:
            {
            	SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0");
            	ReversePin->bHidden = true; // Cant reverse when we are the one supplying the index
	            SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", false);
	            SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", false);
	            SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", false);
	            SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", true);
	            ParamAPin->PinFriendlyName = SqrlK2::Priv::XIndexPinName;
	            ParamBPin->PinFriendlyName = SqrlK2::Priv::YIndexPinName;
	            ParamCPin->PinFriendlyName = SqrlK2::Priv::ZIndexPinName;
	            break;
            }
			case ESquirrelRandType::From4DIndex:
            {
            	SqrlK2::Priv::SetPinValues(ResultPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0");
            	ReversePin->bHidden = true; // Cant reverse when we are the one supplying the index
            	SqrlK2::Priv::SetPinValues(ParamAPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", false);
            	SqrlK2::Priv::SetPinValues(ParamBPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", false);
            	SqrlK2::Priv::SetPinValues(ParamCPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", false);
            	SqrlK2::Priv::SetPinValues(ParamDPin, UEdGraphSchema_K2::PC_Int, NAME_None, nullptr, "0", false);
            	ParamAPin->PinFriendlyName = SqrlK2::Priv::XIndexPinName;
            	ParamBPin->PinFriendlyName = SqrlK2::Priv::YIndexPinName;
            	ParamCPin->PinFriendlyName = SqrlK2::Priv::ZIndexPinName;
            	ParamDPin->PinFriendlyName = SqrlK2::Priv::WIndexPinName;
            	break;
            }
        }
	    GetGraph()->NotifyGraphChanged();
    }
}

