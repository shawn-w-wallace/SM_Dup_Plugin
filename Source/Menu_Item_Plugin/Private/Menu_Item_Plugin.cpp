// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Menu_Item_Plugin.h"
#include "LevelEditor.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

#define LOCTEXT_NAMESPACE "FMenu_Item_PluginModule"

void FMenu_Item_PluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
	MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, NULL, FMenuExtensionDelegate::CreateRaw(this, &FMenu_Item_PluginModule::AddMenuExtension));

	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	
	//ptr calls function when plugin is loaded
	WindowPtr->RegisterTab();
}

void FMenu_Item_PluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	//ptr calls function when plugin is unloaded
	WindowPtr->UnregisterTab();
}

void FMenu_Item_PluginModule::AddMenuExtension(FMenuBuilder& Builder)
{
	FText label = LOCTEXT("Label", "Static Mesh Duplicator");
	FText tooltip = LOCTEXT("Tooltip", "This menu item displays the Static Mesh Duplicator Window!");
	Builder.AddMenuEntry(label, tooltip, FSlateIcon(), FUIAction(FExecuteAction::CreateRaw(this, &FMenu_Item_PluginModule::DisplayWindow)));
}

void FMenu_Item_PluginModule::DisplayWindow()
{
	WindowPtr->SpawnTab();
}
#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMenu_Item_PluginModule, Menu_Item_Plugin)