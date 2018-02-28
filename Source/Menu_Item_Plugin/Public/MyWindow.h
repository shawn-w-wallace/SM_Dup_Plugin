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
	TOptional<float> GetXValueCopies() const;
	TOptional<float> GetXValueSpacing() const;
	TOptional<float> GetYValueCopies() const;
	TOptional<float> GetYValueSpacing() const;
	TOptional<float> GetZValueCopies() const;
	TOptional<float> GetZValueSpacing() const;
	void SetXValueCopies(float XCopies);
	void SetXValueSpacing(float XSpacing);
	void SetYValueCopies(float YCopies);
	void SetYValueSpacing(float YSpacing);
	void SetZValueCopies(float ZCopies);
	void SetZValueSpacing(float ASpacing);
	UWorld* MyWorld();
	FText GetActorName() const;
	bool IsActorSelected(AStaticMeshActor* SelectedActor);
	void SelectedActor(AStaticMeshActor* SelectedActor);
	TSharedRef<SWidget> DisplayActorList();

private:

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);
	TSharedPtr<SComboButton> ActorDropdown;
	float MyXValueSpacing = 0.0;
	float MyXValueCopies = 1.0;
	float MyYValueSpacing = 0.0;
	float MyYValueCopies = 1.0;
	float MyZValueSpacing = 0.0;
	float MyZValueCopies = 1.0;
	AStaticMeshActor* MyActor = NULL;

	FActorSpawnParameters SpawnParams;
	AStaticMeshActor* MyActorCopy;
	float MyActorCopyX;
	float MyActorCopyY;
	float MyActorCopyZ;
	FVector Origin;
	FVector GroundOrigin;
	FVector GroundExtends;
	int32 CopiesX = 0;
	float SpacingX = 0.f;
	int32 CopiesY = 0;
	float SpacingY = 0.f;
	int32 CopiesZ = 0;
	float SpacingZ = 0.f;
	int CopyCount = 0;
	FString StringCopyCount;
	FString MyActorName;
	FString NewName;
	bool XChecked;
	bool YChecked;
	bool ZChecked;

};
