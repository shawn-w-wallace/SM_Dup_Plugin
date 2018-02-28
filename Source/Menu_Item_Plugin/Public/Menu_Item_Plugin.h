// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MyWindow.h"
#include <memory>
#include "ModuleManager.h"

class FMenuBuilder;

TUniquePtr<MyWindow> WindowPtr(new MyWindow);

class FMenu_Item_PluginModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:

	void AddMenuExtension(FMenuBuilder& Builder);
	void DisplayWindow();

};