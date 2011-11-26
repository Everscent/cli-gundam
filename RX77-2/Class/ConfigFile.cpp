#include "StdAfx.h"
#include "ConfigFile.h"

using namespace RX77_2;

/**
 * コンフィグファイル
 */
ConfigFile::ConfigFile(System::String ^fileName)
{
	this->iniFile = gcnew IniFile(fileName);
}
// ----------------------------------------------------------------------------------------------------

void ConfigFile::LoadFormSizeAndLocation(System::Windows::Forms::Form ^form)
{
	int left = this->iniFile->GetInteger(this->WINDOW_SECTION, this->LEFT_LOCATION_KEY, 0);
	int top = this->iniFile->GetInteger(this->WINDOW_SECTION, this->TOP_LOCATION_KEY, 0);
	form->Location = Point(left, top);

	int width = this->iniFile->GetInteger(this->WINDOW_SECTION, this->WIDTH_SIZE_KEY, 316);
	int height = this->iniFile->GetInteger(this->WINDOW_SECTION, this->HEIGHT_SIZE_KEY, 637);
	form->Size = Size(width, height);
}
// ----------------------------------------------------------------------------------------------------

void ConfigFile::SaveFormSizeAndLocation(System::Windows::Forms::Form ^form)
{
	this->iniFile->SetInteger(this->WINDOW_SECTION, this->LEFT_LOCATION_KEY, form->Left);
	this->iniFile->SetInteger(this->WINDOW_SECTION, this->TOP_LOCATION_KEY, form->Top);
	this->iniFile->SetInteger(this->WINDOW_SECTION, this->WIDTH_SIZE_KEY, form->Width);
	this->iniFile->SetInteger(this->WINDOW_SECTION, this->HEIGHT_SIZE_KEY, form->Height);
}
// ----------------------------------------------------------------------------------------------------
