#include "ToyPlugin.h"
#include "LevelEditor.h"
#include "Toolbar/ButtonCommand.h"

#define LOCTEXT_NAMESPACE "FToyPluginModule"

void FToyPluginModule::StartupModule()
{
	UE_LOG(LogTemp, Error, TEXT("Startup Toy Plugin"));

	FButtonCommand::Register();
	Extender = MakeShareable(new FExtender());

	FToolBarExtensionDelegate toolBarExtensionDelegate = FToolBarExtensionDelegate::CreateRaw(this, &FToyPluginModule::AddToolBar);

	Extender->AddToolBarExtension("Compile", EExtensionHook::Before, FButtonCommand::Get().LoadMeshCommand, toolBarExtensionDelegate);

	FLevelEditorModule& levelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	levelEditor.GetToolBarExtensibilityManager()->AddExtender(Extender);

	// Engine Content Resource Log
	//TArray<const FSlateBrush*> resources;
	//FEditorStyle::GetResources(resources);
	//
	//for (const auto& resource : resources)
	//	GLog->Log((TEXT("%s"), *resource->GetResourceName().ToString()));
}

void FToyPluginModule::ShutdownModule()
{
	UE_LOG(LogTemp, Error, TEXT("Shutdown Toy Plugin"));
}

void FToyPluginModule::AddToolBar(FToolBarBuilder& InBuilder)
{
	FSlateIcon icon = FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.SelectMode");

	InBuilder.AddToolBarButton
	(
		FButtonCommand::Get().LoadMeshID,
		"Test",
		FText::FromString("Load Mesh"),
		FText::FromString("Load Mesh Data"),
		icon
	);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FToyPluginModule, ToyPlugin)