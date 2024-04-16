// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonCommand.h"

FButtonCommand::FButtonCommand()
	: TCommands("ButtonCommand", FText::FromString("Button Commands"), NAME_None, FEditorStyle::GetStyleSetName())
{
	LoadMeshCommand = MakeShareable(new FUICommandList());
}

FButtonCommand::~FButtonCommand()
{
	if (LoadMeshCommand.IsValid())
		LoadMeshCommand.Reset();
}

void FButtonCommand::RegisterCommands()
{
#define LOCTEXT_NAMESPACE ""
	UI_COMMAND(LoadMeshID, "LoadMesh", "Load Mesh Data", EUserInterfaceActionType::Button, FInputChord());
#undef LOCTEXT_NAMESPACE

	LoadMeshCommand->MapAction(LoadMeshID, FExecuteAction::CreateRaw(this, &FButtonCommand::OnClicked));
}

void FButtonCommand::OnClicked()
{
	UE_LOG(LogTemp, Error, TEXT("Load Mesh Button is Clicked"));
}
