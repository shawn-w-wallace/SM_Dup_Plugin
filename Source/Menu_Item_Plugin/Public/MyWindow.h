#pragma once
#include "CoreMinimal.h"
#include "EngineUtils.h"

class MyWindow
{

public:

	MyWindow();

	void RegisterTab();
	void SpawnTab();
	void UnregisterTab();
	FReply MyWindow::ToggleButton();
	void ToggleXCheckBox(ECheckBoxState NewXState);
	void ToggleYCheckBox(ECheckBoxState NewYState);
	void ToggleZCheckBox(ECheckBoxState NewZState);
	TOptional<float> GetXValueSpacing() const;
	TOptional<float> GetYValueSpacing() const;
	TOptional<float> GetZValueSpacing() const;
	TOptional<float> GetValueCopies() const;
	void SetXValueSpacing(float XSpacing);
	void SetYValueSpacing(float YSpacing);
	void SetZValueSpacing(float ZSpacing);
	void SetValueCopies(float Copies);
	UWorld* MyWorld();
	FText GetActorName() const;
	bool IsActorSelected(AStaticMeshActor* SelectedActor);
	void SelectedActor(AStaticMeshActor* SelectedActor);
	TSharedRef<SWidget> DisplayActorList();

private:

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);
	TSharedPtr<SComboButton> ActorDropdown;
	float MyXValueSpacing = 0.0;
	float MyYValueSpacing = 0.0;
	float MyZValueSpacing = 0.0;
	float MyValueCopies = 1.0;
	AStaticMeshActor* MyActor = NULL;

	FActorSpawnParameters SpawnParams;
	AStaticMeshActor* MyActorCopy;
	float MyActorCopyX;
	float MyActorCopyY;
	float MyActorCopyZ;
	FVector Origin;
	FVector GroundOrigin;
	FVector GroundExtends;
	float SpacingX = 0.f;
	float SpacingY = 0.f;
	float SpacingZ = 0.f;
	int32 Copies = 0;
	int CopyCount = 0;
	FString StringCopyCount;
	FString MyActorName;
	FString NewName;
	bool XChecked;
	bool YChecked;
	bool ZChecked;

};

};
