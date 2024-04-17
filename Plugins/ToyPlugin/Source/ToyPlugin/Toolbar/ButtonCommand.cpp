// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonCommand.h"

FButtonCommand::FButtonCommand()
	: TCommands("ButtonCommand", FText::FromString("Button Commands"), NAME_None, FEditorStyle::GetStyleSetName())
{
	Command = MakeShareable(new FUICommandList());
}

FButtonCommand::~FButtonCommand()
{
	if (Command.IsValid())
		Command.Reset();
}

void FButtonCommand::RegisterCommands()
{
#define LOCTEXT_NAMESPACE ""
	UI_COMMAND(LoadMeshID, "LoadMesh", "Load Mesh Data", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(OpenViewerID, "OpenViewer", "Open Asset Viewer", EUserInterfaceActionType::Button, FInputChord());
#undef LOCTEXT_NAMESPACE

	Command->MapAction(LoadMeshID, FExecuteAction::CreateRaw(this, &FButtonCommand::OnClicked_LoadMesh));
	Command->MapAction(OpenViewerID, FExecuteAction::CreateRaw(this, &FButtonCommand::OnClicked_OpenViewer));
}

void FButtonCommand::OnClicked_LoadMesh()
{
	UE_LOG(LogTemp, Error, TEXT("Load Mesh Button is Clicked"));
}

void FButtonCommand::OnClicked_OpenViewer()
{
	UE_LOG(LogTemp, Error, TEXT("Open Viewer Button is Clicked"));
}
