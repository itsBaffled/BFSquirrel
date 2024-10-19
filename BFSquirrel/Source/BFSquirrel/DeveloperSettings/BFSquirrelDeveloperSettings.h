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
#include "Engine/DeveloperSettings.h"
#include "BFSquirrelDeveloperSettings.generated.h"


UCLASS(config = Game, defaultconfig)
class BFSQUIRREL_API UBFSquirrelDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	virtual FName GetCategoryName() const override { return {"Squirrel"}; }
	static const UBFSquirrelDeveloperSettings& Get() { return *GetDefault<UBFSquirrelDeveloperSettings>(); }
	static UBFSquirrelDeveloperSettings& GetMutable() { return *GetMutableDefault<UBFSquirrelDeveloperSettings>(); }

	UPROPERTY(EditDefaultsOnly, config, Category = "Squirrel")
	uint32 GlobalNoiseSeed = 42;
};







