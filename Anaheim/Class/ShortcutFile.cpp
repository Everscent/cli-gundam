#include "StdAfx.h"
#include "ShortcutFile.h"

using namespace Anaheim;

/**
 * ショートカットファイル
 */
ShortcutFile::ShortcutFile(System::String ^fileName, System::String ^linkPath)
{
	this->fileName = fileName;
	this->linkPath = linkPath;
	this->argument = String::Empty;
	this->workDirectory = String::Empty;
	this->comment = String::Empty;
}
// ----------------------------------------------------------------------------------------------------

void ShortcutFile::Save()
{
	IWshRuntimeLibrary::WshShellClass^ shell = gcnew IWshRuntimeLibrary::WshShellClass();
	IWshRuntimeLibrary::IWshShortcut^ shortcut = dynamic_cast<IWshRuntimeLibrary::IWshShortcut^>(shell->CreateShortcut(this->fileName));
	
	shortcut->TargetPath = this->linkPath;
	shortcut->Arguments = this->argument;
	shortcut->WorkingDirectory = this->workDirectory;
	shortcut->Description = this->comment;

	shortcut->Save();

	System::Runtime::InteropServices::Marshal::ReleaseComObject(shortcut);
}
// ----------------------------------------------------------------------------------------------------
