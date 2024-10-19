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

#include "CoreMinimal.h"
#include "BFSquirrelK2Utility.h"
#include "K2Node.h"
#include "BFSquirrelK2_SquirrelStreamRand.generated.h"


struct FSquirrelStream;

UCLASS()
class BFSQUIRREL_K2_API UBFSquirrelK2_SquirrelStreamRand : public UK2Node
{
	GENERATED_BODY()
public:
	virtual void AllocateDefaultPins() override;  
	virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;  
	virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;  
	virtual FText GetTooltipText() const override;  
	virtual bool IsNodePure() const override {return false;}
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;  
	virtual FText GetMenuCategory() const override { return SqrlK2::Priv::SquirrelCategory; }

	virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;  
	virtual void PostReconstructNode() override;
	virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;
	
	virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;

private:
	void UpdateOutputPinType();

private:
	UPROPERTY()
	ESquirrelRandType LastEnumType = ESquirrelRandType::Int;
	UPROPERTY()
	bool bLastReverse = false;
	UPROPERTY()
	bool bSolidAlpha = false;
};





