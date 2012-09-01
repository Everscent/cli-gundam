#include "StdAfx.h"
#include "ConfigFile.h"

using namespace MSM_07S;

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

	int width = this->iniFile->GetInteger(this->WINDOW_SECTION, this->WIDTH_SIZE_KEY, 500);
	int height = this->iniFile->GetInteger(this->WINDOW_SECTION, this->HEIGHT_SIZE_KEY, 500);
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

IPEndPoint^ ConfigFile::GetUdpLocalIPEndPoint()
{
	String^ ip = this->iniFile->GetString(this->UDP_IP_SECTION, this->LOCAL_IP_KEY, "127.0.0.1");
	int port = this->iniFile->GetInteger(this->UDP_IP_SECTION, this->LOCAL_PORT_KEY, 50100);
	return gcnew IPEndPoint(IPAddress::Parse(ip), port);
}
// ----------------------------------------------------------------------------------------------------

void ConfigFile::SetUdpLocalIPEndPoint(System::Net::IPEndPoint ^endPoint)
{
	this->iniFile->SetString(this->UDP_IP_SECTION, this->LOCAL_IP_KEY, endPoint->Address->ToString());
	this->iniFile->SetInteger(this->UDP_IP_SECTION, this->LOCAL_PORT_KEY, endPoint->Port);
}
// ----------------------------------------------------------------------------------------------------

IPEndPoint^ ConfigFile::GetUdpRemoteIPEndPoint()
{
	String^ ip = this->iniFile->GetString(this->UDP_IP_SECTION, this->REMOTE_IP_KEY, "127.0.0.1");
	int port = this->iniFile->GetInteger(this->UDP_IP_SECTION, this->REMOTE_PORT_KEY, 50200);
	return gcnew IPEndPoint(IPAddress::Parse(ip), port);
}
// ----------------------------------------------------------------------------------------------------

void ConfigFile::SetUdpRemoteIPEndPoint(System::Net::IPEndPoint ^endPoint)
{
	this->iniFile->SetString(this->UDP_IP_SECTION, this->REMOTE_IP_KEY, endPoint->Address->ToString());
	this->iniFile->SetInteger(this->UDP_IP_SECTION, this->REMOTE_PORT_KEY, endPoint->Port);
}
// ----------------------------------------------------------------------------------------------------

Encoding^ ConfigFile::GetUdpEncoding()
{
	String^ enc = this->iniFile->GetString(this->UDP_IP_SECTION, this->ENCODING_KEY, System::Text::Encoding::ASCII->ToString());
	if (enc->Equals(System::Text::Encoding::ASCII->ToString()))
	{
		return System::Text::Encoding::ASCII;
	}
	else if (enc->Equals(System::Text::Encoding::UTF8->ToString()))
	{
		return System::Text::Encoding::UTF8;
	}
	else
	{
		return System::Text::Encoding::Default;
	}
}
// ----------------------------------------------------------------------------------------------------

void ConfigFile::SetUdpEncoding(System::Text::Encoding ^encoding)
{
	this->iniFile->SetString(this->UDP_IP_SECTION, this->ENCODING_KEY, encoding->ToString());
}
// ----------------------------------------------------------------------------------------------------
