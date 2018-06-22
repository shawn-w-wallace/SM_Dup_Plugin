#include "MyWindow.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Input/SNumericEntryBox.h"
#include "Widgets/Input/SComboButton.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "LevelEditor.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
#include "EngineGlobals.h"

//Tab Reference
static const FName Menu_Item_PluginTabName("Menu_Item_Plugin");

//required to use LOCTEXT() macro for creating text
#define LOCTEXT_NAMESPACE "Menu_Item_PluginModule"

MyWindow::MyWindow()
{

}

//Registers tab as a nomad tab (dockable window)
void MyWindow::RegisterTab()
{
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(Menu_Item_PluginTabName, FOnSpawnTab::CreateRaw(this, &MyWindow::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FESW_PluginTabTitle", "My Dockable Window"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

//loads window
void MyWindow::SpawnTab()
{
	FGlobalTabmanager::Get()->InvokeTab(Menu_Item_PluginTabName);
}

//unregisters tab
void MyWindow::UnregisterTab()
{
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(Menu_Item_PluginTabName);
}

//defines text parameters for the created window
TSharedRef<SDockTab> MyWindow::OnSpawnPluginTab(const FSpawnTabArgs & SpawnTabArgs)
{
	FText WindowMessage = LOCTEXT("WindowMessage", "My Actor Duplicator");
	FText AxisMessage = LOCTEXT("AxisMessage", "Axis");
	FText CopiesMessage = LOCTEXT("CopiesMessage", "Copies");
	FText SpacingMessage = LOCTEXT("SpacingMessage", "Spacing");
	FText ButtonLabel = LOCTEXT("ButtonLabel", "Duplicate!");
	FText ComboBoxLabel = LOCTEXT("ComboBoxLabel", "Actor:");
	FText CheckBoxXLabel = LOCTEXT("CheckBoxXLabel", "x");
	FText CheckBoxYLabel = LOCTEXT("CheckBoxYLabel", "y");
	FText CheckBoxZLabel = LOCTEXT("CheckBoxZLabel", "z");
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			//Window Root
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			[
				//Title
				SNew(SVerticalBox)
				+ SVerticalBox::Slot().HAlign(HAlign_Left).VAlign(VAlign_Top)
				[
					SNew(STextBlock).Text(WindowMessage)
				]
				//Horizontal Textrun (vertical run)
				+ SVerticalBox::Slot()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					[
						SNew(STextBlock).Text(CopiesMessage)
					]
					+ SHorizontalBox::Slot()
					[
						SNew(STextBlock).Text(AxisMessage)
					]
					+ SHorizontalBox::Slot()
					[
						SNew(STextBlock).Text(SpacingMessage)
					]
				]
				//Horizontal interactables (vertical run)
				+ SVerticalBox::Slot().VAlign(VAlign_Top)
				[
					SNew(SHorizontalBox)
					//Number field
					+ SHorizontalBox::Slot().Padding(10, 0)

					+ SHorizontalBox::Slot()
					[
						//On click changes state of check box to the previous state via Toggle(function)
						SNew(SCheckBox).OnCheckStateChanged_Raw(this, &MyWindow::ToggleXCheckBox).Content()[SNew(STextBlock).Text(CheckBoxXLabel)]
					]
					//Number field
					+ SHorizontalBox::Slot().Padding(10, 0)
					[
						//float numeric text field, calls functions to get user input and save it to field
						SNew(SNumericEntryBox<float>)
						.Value_Raw(this, &MyWindow::GetXValueSpacing)
						.OnValueChanged_Raw(this, &MyWindow::SetXValueSpacing)
					]
				]
				//Horizontal interactables (vertical run)
				+ SVerticalBox::Slot().VAlign(VAlign_Top)
				[
					SNew(SHorizontalBox)
					//Number field
					+ SHorizontalBox::Slot().Padding(10, 0)
					[
						//float numeric text field, calls functions to get user input and save it to field
						SNew(SNumericEntryBox<float>)
						.Value_Raw(this, &MyWindow::GetValueCopies)
						.OnValueChanged_Raw(this, &MyWindow::SetValueCopies)
					]
					//CheckBox
					+ SHorizontalBox::Slot()
					[
						//On click changes state of check box to the previous state via Toggle(function)
						SNew(SCheckBox).OnCheckStateChanged_Raw(this, &MyWindow::ToggleYCheckBox).Content()[SNew(STextBlock).Text(CheckBoxYLabel)]
					]
					//Number field
					+ SHorizontalBox::Slot().Padding(10, 0)
					[
						//float numeric text field, calls functions to get user input and save it to field
						SNew(SNumericEntryBox<float>)
						.Value_Raw(this, &MyWindow::GetYValueSpacing)
						.OnValueChanged_Raw(this, &MyWindow::SetYValueSpacing)
					]
				]
				//Horizontal interactables (vertical run)
				+ SVerticalBox::Slot().VAlign(VAlign_Top)
				[
					SNew(SHorizontalBox)
					//Number field
					+ SHorizontalBox::Slot().Padding(10,0)

					//CheckBox
					+ SHorizontalBox::Slot()
					[
						//On click changes state of check box to the previous state via Toggle(function)
						SNew(SCheckBox).OnCheckStateChanged_Raw(this, &MyWindow::ToggleZCheckBox).Content()[SNew(STextBlock).Text(CheckBoxZLabel)]
					]
					//Number field
					+ SHorizontalBox::Slot().Padding(10, 0)
					[
						//float numeric text field, calls functions to get user input and save it to field
						SNew(SNumericEntryBox<float>)
						.Value_Raw(this, &MyWindow::GetZValueSpacing)
						.OnValueChanged_Raw(this, &MyWindow::SetZValueSpacing)
					]
				]
				//Horizontal interactables (vertical run)
				+ SVerticalBox::Slot().VAlign(VAlign_Top)
				[
					SNew(SHorizontalBox)
					//Dropdown Box
					+ SHorizontalBox::Slot().Padding(10, 0)
					[
						SAssignNew(ActorDropdown, SComboButton).ButtonContent()[SNew(STextBlock).Text_Raw(this, &MyWindow::GetActorName)]
						.OnGetMenuContent_Raw(this, &MyWindow::DisplayActorList)
					]
					//Button
					+ SHorizontalBox::Slot().Padding(10, 0)
					[
						//When clicked executes ToggleButton
						SNew(SButton).Text(ButtonLabel).OnClicked_Raw(this, &MyWindow::ToggleButton)
					]
				]
			]
		];
}

//Duplicate button output (function)
FReply MyWindow::ToggleButton()
{
	if (XChecked == true)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Value entered: %f for copies along the X axis"), MyXValueCopies);
		UE_LOG(LogTemp, Warning, TEXT("Value entered: %f for spacing along the X axis"), MyXValueSpacing);
	}

	if (YChecked == true)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Value entered: %f for copies along the Y axis"), MyYValueCopies);
		UE_LOG(LogTemp, Warning, TEXT("Value entered: %f for spacing along the Y axis"), MyYValueSpacing);
	}

	if (ZChecked == true)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Value entered: %f for copies along the Z axis"), MyZValueCopies);
		UE_LOG(LogTemp, Warning, TEXT("Value entered: %f for spacing along the Z axis"), MyZValueSpacing);
	}

	//what happens when no static mesh actor is selected
	if (MyActor == NULL)
		return FReply::Handled();

	Copies = MyValueCopies;
	SpacingX = MyXValueSpacing;
	SpacingY = MyYValueSpacing;
	SpacingZ = MyZValueSpacing;

	//loop for copying static mesh, X field Copies
	for (int32 i = 0; i < Copies; i++)
	{
		if (XChecked == true || YChecked == true || ZChecked == true)
		{
			//retrieves mesh, increments copycount each iteration of loop, assigns name to new mesh
			MyActor->GetActorBounds(false, GroundOrigin, GroundExtends);
			CopyCount++;
			StringCopyCount = FString::FromInt(CopyCount);
			MyActorName = MyActor->GetFName().ToString();
			NewName = MyActorName + "_" + StringCopyCount;

			//gets mesh by name, copies mesh, and assignes pointer for transform
			SpawnParams.Name = FName(*NewName);
			SpawnParams.Template = MyActor;
			MyActorCopy = MyWorld()->SpawnActorAbsolute<AStaticMeshActor>(MyActor->GetClass(), MyActor->GetTransform(), SpawnParams);

			//transforms the position of the static mesh relative to the position of the previous mesh
			if (XChecked == true)
				MyActorCopyX = ((i + 1) * GroundExtends.X * 2) + MyActorCopy->GetActorLocation().X + (SpacingX * (i + 1));
			else
				MyActorCopyX = GroundOrigin.X;

			if (YChecked == true)
				MyActorCopyY = ((i + 1) * GroundExtends.Y * 2) + MyActorCopy->GetActorLocation().Y + (SpacingY * (i + 1));
			else
				MyActorCopyY = GroundOrigin.Y;

			if (ZChecked == true)
				MyActorCopyZ = ((i + 1) * GroundExtends.Z * 2) + MyActorCopy->GetActorLocation().Z + (SpacingZ * (i + 1));
			else
				MyActorCopyZ = MyActor->GetActorLocation().Z;

			//moves mesh to new location
			MyActorCopy->SetActorLocation(FVector(MyActorCopyX, MyActorCopyY, MyActorCopyZ));
		}
	}



	return FReply::Handled();
}

//Changes state of X check box sets checked bool
void MyWindow::ToggleXCheckBox(ECheckBoxState NewXState)
{
	if (NewXState == ECheckBoxState::Checked)
	{
		UE_LOG(LogTemp, Warning, TEXT("Checked!"));
		XChecked = true;
	}
	else if (NewXState == ECheckBoxState::Unchecked)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unchecked!"));
		XChecked = false;
	}
}

//Changes state of Y check box sets checked bool
void MyWindow::ToggleYCheckBox(ECheckBoxState NewYState)
{
	if (NewYState == ECheckBoxState::Checked)
	{
		UE_LOG(LogTemp, Warning, TEXT("Checked!"));
		YChecked = true;
	}
	else if (NewYState == ECheckBoxState::Unchecked)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unchecked!"));
		YChecked = false;
	}
}

//Changes state of Z check box sets checked bool
void MyWindow::ToggleZCheckBox(ECheckBoxState NewZState)
{
	if (NewZState == ECheckBoxState::Checked)
	{
		UE_LOG(LogTemp, Warning, TEXT("Checked!"));
		ZChecked = true;
	}
	else if (NewZState == ECheckBoxState::Unchecked)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unchecked!"));
		ZChecked = false;
	}
}

//Gets user input from this text field
TOptional<float> MyWindow::GetValueCopies() const
{
	return MyValueCopies;
}

//"saves" user input to this field
void MyWindow::SetValueCopies(float Copies)
{
	MyValueCopies = Copies;
}

//Gets user input from this text field
TOptional<float> MyWindow::GetXValueSpacing() const
{
	//sets text field to zero if a negative number is entered
	if (MyXValueSpacing < 0.0)
		return 0;
	else
		return MyXValueSpacing;
}

//"saves" user input to this field
void MyWindow::SetXValueSpacing(float XSpacing)
{
	//sets value of XSpacing as long as a negative number is not entered
	if (MyXValueSpacing >= 0.0)
		MyXValueSpacing = XSpacing;
}

//Gets user input from this text field
TOptional<float> MyWindow::GetYValueSpacing() const
{
	//sets text field to zero if a negative number is entered
	if (MyYValueSpacing < 0.0)
		return 0;
	else
		return MyYValueSpacing;
}

//"saves" user input to this field
void MyWindow::SetYValueSpacing(float YSpacing)
{
	//sets value of XSpacing as long as a negative number is not entered
	if (MyYValueSpacing >= 0.0)
		MyYValueSpacing = YSpacing;
}

//Gets user input from this text field
TOptional<float> MyWindow::GetZValueSpacing() const
{
	//sets text field to zero if a negative number is entered
	if (MyZValueSpacing < 0.0)
		return 0;
	else
		return MyZValueSpacing;
}

//"saves" user input to this field
void MyWindow::SetZValueSpacing(float ZSpacing)
{
	//sets value of XSpacing as long as a negative number is not entered
	if (MyZValueSpacing >= 0.0)
		MyZValueSpacing = ZSpacing;
}

//returns world type, either Play in Editor (PIE) or the level editor
UWorld* MyWindow::MyWorld()
{
	UWorld* World = NULL;

	const TIndirectArray<FWorldContext>& MyContexts = GEngine->GetWorldContexts();

	for (int32 i = 0; i < MyContexts.Num(); i++)
	{
		if (MyContexts[i].WorldType == EWorldType::PIE)
			return MyContexts[i].World();

		if (MyContexts[i].WorldType == EWorldType::Editor)
			World = MyContexts[i].World();
	}
	return World;
}

// if no actor is selected from drop down return text until actor is selected
FText MyWindow::GetActorName() const
{
	if (MyActor == NULL)
		return FText::FromString("No Actor Selected!");

	return FText::FromString(MyActor->GetName());
}

//takes retrieved world type and iterates through static mesh actors in world to populate drop down menu with static mesh actors
TSharedRef<SWidget> MyWindow::DisplayActorList()
{
	UWorld* World = MyWorld();
	FMenuBuilder menu(true, NULL);

	for (TActorIterator<AStaticMeshActor> It(World); It; ++It)
	{
		menu.AddMenuEntry(
			FText::FromString(It->GetName()),
			FText::FromString(It->GetName()),
			FSlateIcon(),
			FUIAction(
				FExecuteAction::CreateRaw(this, &MyWindow::SelectedActor, *It),
				FCanExecuteAction(),
				FIsActionChecked::CreateRaw(this, &MyWindow::IsActorSelected, *It)
			),
			NAME_None,
			EUserInterfaceActionType::ToggleButton
		);
	}
	return menu.MakeWidget();
}

//selected actor function called with menu item is selected from dropdown box
bool MyWindow::IsActorSelected(AStaticMeshActor* SelectedActor)
{
	return SelectedActor == MyActor;
}

//selected actor function called with menu item is selected from dropdown box
void MyWindow::SelectedActor(AStaticMeshActor* SelectedActor)
{
	MyActor = SelectedActor;
}
