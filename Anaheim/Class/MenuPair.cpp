#include "StdAfx.h"
#include "MenuPair.h"

using namespace Anaheim;

/**
 * メニューバー，ツールバー，コンテキストメニューの関連付け
 */
MenuPair::MenuPair(System::Windows::Forms::ToolStripMenuItem ^mainMenu, System::Windows::Forms::ToolStripMenuItem ^contextMenu, System::Windows::Forms::ToolStripButton ^toolButton)
{
	this->mainMenu = mainMenu;
	this->contextMenu = contextMenu;
	this->toolButton = toolButton;
}
// ----------------------------------------------------------------------------------------------------

bool MenuPair::ExecuteMainMenu()
{
	if (this->mainMenu == nullptr) return false;

	this->mainMenu->PerformClick();
	return true;
}
// ----------------------------------------------------------------------------------------------------

bool MenuPair::ChangeEnabled(bool enabled)
{
	if (this->contextMenu != nullptr)
	{
		this->contextMenu->Enabled = enabled;
	}
	if (this->toolButton != nullptr)
	{
		this->toolButton->Enabled = enabled;
	}
	return (this->contextMenu == nullptr && this->toolButton == nullptr) ? false : true;
}
// ----------------------------------------------------------------------------------------------------

/**
 * メニュー関連付けリスト
 */
MenuPairList::MenuPairList()
{
	this->items = gcnew List<MenuPair^>;
}
// ----------------------------------------------------------------------------------------------------

void MenuPairList::SetPair(System::Windows::Forms::ToolStripMenuItem ^mainMenu, System::Windows::Forms::ToolStripMenuItem ^contextMenu)
{
	this->items->Add(gcnew MenuPair(mainMenu, contextMenu, nullptr));
}
// ----------------------------------------------------------------------------------------------------

void MenuPairList::SetPair(System::Windows::Forms::ToolStripMenuItem ^mainMenu, System::Windows::Forms::ToolStripButton ^toolButton)
{
	this->items->Add(gcnew MenuPair(mainMenu, nullptr, toolButton));
}
// ----------------------------------------------------------------------------------------------------

void MenuPairList::SetPair(System::Windows::Forms::ToolStripMenuItem ^mainMenu, System::Windows::Forms::ToolStripMenuItem ^contextMenu, System::Windows::Forms::ToolStripButton ^toolButton)
{
	this->items->Add(gcnew MenuPair(mainMenu, contextMenu, toolButton));
}
// ----------------------------------------------------------------------------------------------------

bool MenuPairList::ExecuteContext(System::Object ^contextMenu)
{
	ToolStripMenuItem^ context = dynamic_cast<ToolStripMenuItem^>(contextMenu);
	if (context == nullptr) return false;

	for each (MenuPair^ item in this->items)
	{
		if (item->ContextMenue == context)
		{
			return item->ExecuteMainMenu();
		}
	}

	return false;
}
// ----------------------------------------------------------------------------------------------------

bool MenuPairList::ExecuteToolButtont(System::Object ^toolButton)
{
	ToolStripButton^ tool = dynamic_cast<ToolStripButton^>(toolButton);
	if (tool == nullptr) return false;

	for each (MenuPair^ item in this->items)
	{
		if (item->ToolButton == tool)
		{
			return item->ExecuteMainMenu();
		}
	}

	return false;
}
// ----------------------------------------------------------------------------------------------------

bool MenuPairList::UpdateEnabled(System::Object ^mainMenu)
{
	ToolStripMenuItem^ main = dynamic_cast<ToolStripMenuItem^>(mainMenu);
	if (main == nullptr) return false;

	for each (MenuPair^ item in this->items)
	{
		if (item->MainMenu == main)
		{
			return item->ChangeEnabled(main->Enabled);
		}
	}

	return false;
}
// ----------------------------------------------------------------------------------------------------