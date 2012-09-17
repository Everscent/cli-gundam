#include "StdAfx.h"
#include "ConfigFile.h"

using namespace RX78_2;

/**
 * コンフィグファイル
 */
ConfigFile::ConfigFile(System::String ^fileName)
{
	this->fileName = fileName;

	this->xmlDoc = gcnew XmlDocument();
	if (System::IO::File::Exists(this->fileName))
	{
		this->xmlDoc->Load(this->fileName);
	}
	else
	{
		this->xmlDoc->AppendChild(this->xmlDoc->CreateXmlDeclaration("1.0", "UTF-8", nullptr));
		XmlElement^ xmlEle = this->xmlDoc->CreateElement("RX78-2");
		this->xmlDoc->AppendChild(xmlEle);
	}
}
// ----------------------------------------------------------------------------------------------------

XmlElement^ ConfigFile::GetRootElement()
{
	return this->xmlDoc->DocumentElement;
}
// ----------------------------------------------------------------------------------------------------

XmlElement^ ConfigFile::GetElement(System::Xml::XmlElement ^parent, System::String ^name)
{
	for each (XmlElement^ ele in parent->ChildNodes)
	{
		if (ele->Name->Equals(name))
		{
			return ele;
		}
	}
	return nullptr;
}
// ----------------------------------------------------------------------------------------------------

XmlElement^ ConfigFile::GetElement(System::Xml::XmlElement ^parent, System::String ^name, System::String ^attrName, System::String ^attrValue)
{
	for each (XmlElement^ ele in parent->ChildNodes)
	{
		if (ele->Name->Equals(name) && ele->GetAttribute(attrName)->Equals(attrValue))
		{
			return ele;
		}
	}
	return nullptr;
}
// ----------------------------------------------------------------------------------------------------

String^ ConfigFile::GetValue(System::Xml::XmlElement ^parent, System::String ^name, System::String ^defValue)
{
	XmlElement^ ele = this->GetElement(parent, name);
	if (ele != nullptr && ele->FirstChild != nullptr)
	{
		return ele->FirstChild->Value;
	}
	return defValue;
}
// ----------------------------------------------------------------------------------------------------

String^ ConfigFile::GetValue(System::Xml::XmlElement ^parent, System::String ^name, System::String ^attrName, System::String ^attrValue, System::String ^defValue)
{
	XmlElement^ ele = this->GetElement(parent, name, attrName, attrValue);
	if (ele != nullptr && ele->FirstChild != nullptr)
	{
		return ele->FirstChild->Value;
	}
	return defValue;
}
// ----------------------------------------------------------------------------------------------------

void ConfigFile::SetValue(System::Xml::XmlElement ^parent, System::String ^name, System::String ^value)
{
	XmlElement^ ele = this->GetElement(parent, name);
	if (ele == nullptr)
	{
		ele = this->xmlDoc->CreateElement(name);
		ele->AppendChild(this->xmlDoc->CreateTextNode(value));
		parent->AppendChild(ele);
	}
	else if (ele->FirstChild == nullptr)
	{
		ele->AppendChild(this->xmlDoc->CreateTextNode(value));
	}
	else
	{
		ele->FirstChild->Value = value;
	}
}
// ----------------------------------------------------------------------------------------------------

void ConfigFile::SetValue(System::Xml::XmlElement ^parent, System::String ^name, System::String ^attrName, System::String ^attrValue, System::String ^value)
{
	XmlElement^ ele = this->GetElement(parent, name, attrName, attrValue);
	if (ele == nullptr)
	{
		ele = this->xmlDoc->CreateElement(name);
		ele->SetAttribute(attrName, attrValue);
		ele->AppendChild(this->xmlDoc->CreateTextNode(value));
		parent->AppendChild(ele);
	}
	else if (ele->FirstChild == nullptr)
	{
		ele->AppendChild(this->xmlDoc->CreateTextNode(value));
	}
	else
	{
		ele->FirstChild->Value = value;
	}
}
// ----------------------------------------------------------------------------------------------------

XmlElement^ ConfigFile::GetWindowElement(System::String ^name)
{
	XmlElement^ root = this->GetRootElement();
	XmlElement^ ele = this->GetElement(root, "Window", "Name", name);
	if (ele == nullptr)
	{
		ele = this->xmlDoc->CreateElement("Window");
		ele->SetAttribute("Name", name);
		root->AppendChild(ele);
	}
	return ele;
}
// ----------------------------------------------------------------------------------------------------

XmlElement^ ConfigFile::GetReportElement()
{
	XmlElement^ root = this->GetRootElement();
	XmlElement^ ele = this->GetElement(root, "Report");
	if (ele == nullptr)
	{
		ele = this->xmlDoc->CreateElement("Report");
		root->AppendChild(ele);
	}
	return ele;
}
// ----------------------------------------------------------------------------------------------------

XmlElement^ ConfigFile::GetTcpServerElement()
{
	XmlElement^ root = this->GetRootElement();
	XmlElement^ ele = this->GetElement(root, "TCPServer");
	if (ele == nullptr)
	{
		ele = this->xmlDoc->CreateElement("TCPServer");
		root->AppendChild(ele);
	}
	return ele;
}
// ----------------------------------------------------------------------------------------------------

XmlElement^ ConfigFile::GetFtpClientElement()
{
	XmlElement^ root = this->GetRootElement();
	XmlElement^ ele = this->GetElement(root, "FTPClient");
	if (ele == nullptr)
	{
		ele = this->xmlDoc->CreateElement("FTPClient");
		root->AppendChild(ele);
	}
	return ele;
}
// ----------------------------------------------------------------------------------------------------

XmlElement^ ConfigFile::GetPicturePuzzleElement()
{
	XmlElement^ root = this->GetRootElement();
	XmlElement^ ele = this->GetElement(root, "PicturePuzzle");
	if (ele == nullptr)
	{
		ele = this->xmlDoc->CreateElement("PicturePuzzle");
		root->AppendChild(ele);
	}
	return ele;
}
// ----------------------------------------------------------------------------------------------------

XmlElement^ ConfigFile::GetBinaryClockElement()
{
	XmlElement^ root = this->GetRootElement();
	XmlElement^ ele = this->GetElement(root, "BinaryClock");
	if (ele == nullptr)
	{
		ele = this->xmlDoc->CreateElement("BinaryClock");
		root->AppendChild(ele);
	}
	return ele;
}
// ----------------------------------------------------------------------------------------------------

XmlElement^ ConfigFile::GetTetrisElement()
{
	XmlElement^ root = this->GetRootElement();
	XmlElement^ ele = this->GetElement(root, "TETRiS");
	if (ele == nullptr)
	{
		ele = this->xmlDoc->CreateElement("TETRiS");
		root->AppendChild(ele);
	}
	return ele;
}
// ----------------------------------------------------------------------------------------------------

XmlElement^ ConfigFile::GetDirectXElement()
{
	XmlElement^ root = this->GetRootElement();
	XmlElement^ ele = this->GetElement(root, "DirectX");
	if (ele == nullptr)
	{
		ele = this->xmlDoc->CreateElement("DirectX");
		root->AppendChild(ele);
	}
	return ele;
}
// ----------------------------------------------------------------------------------------------------

void ConfigFile::Save()
{
	this->xmlDoc->Save(this->fileName);
}
// ----------------------------------------------------------------------------------------------------

void ConfigFile::LoadFormSizeAndLocation(System::Windows::Forms::Form ^form)
{
	XmlElement^ ele = this->GetWindowElement(form->Name);

	String^ maximized = this->GetValue(ele, "Maximized", false.ToString());
	String^ width = this->GetValue(ele, "Width", "700");
	String^ height = this->GetValue(ele, "Height", "700");
	String^ left = this->GetValue(ele, "Left", "0");
	String^ top = this->GetValue(ele, "Top", "0");

	form->Size = Size(int::Parse(width), int::Parse(height));
	form->Location = Point(int::Parse(left), int::Parse(top));

	if (maximized->Equals(true.ToString()))
	{
		form->WindowState = FormWindowState::Maximized;
	}
}
// ----------------------------------------------------------------------------------------------------

void ConfigFile::SaveFormSizeAndLocation(System::Windows::Forms::Form ^form)
{
	XmlElement^ ele = this->GetWindowElement(form->Name);

	String^ maximized = (form->WindowState == FormWindowState::Maximized) ? true.ToString() : false.ToString();
	this->SetValue(ele, "Maximized", maximized);

	if (form->WindowState == FormWindowState::Normal)
	{
		this->SetValue(ele, "Width", form->Width.ToString());
		this->SetValue(ele, "Height", form->Height.ToString());
		this->SetValue(ele, "Left", form->Left.ToString());
		this->SetValue(ele, "Top", form->Top.ToString());
	}
}
// ----------------------------------------------------------------------------------------------------

String^ ConfigFile::GetReportFileName()
{
	XmlElement^ ele = this->GetReportElement();
	return this->GetValue(ele, "Path", String::Empty);
}
// ----------------------------------------------------------------------------------------------------

void ConfigFile::SetReportFileName(System::String ^fileName)
{
	XmlElement^ ele = this->GetReportElement();
	this->SetValue(ele, "Path", fileName);
}
// ----------------------------------------------------------------------------------------------------

IPEndPoint^ ConfigFile::GetTcpIPEndPoint()
{
	XmlElement^ ele = this->GetTcpServerElement();
	String^ ip = this->GetValue(ele, "IPAddress", "127.0.0.1");
	String^ port = this->GetValue(ele, "Port", "50000");
	return gcnew IPEndPoint(IPAddress::Parse(ip), int::Parse(port));
}
// ----------------------------------------------------------------------------------------------------

void ConfigFile::SetTcpIPEndPoint(System::Net::IPEndPoint ^endPoint)
{
	XmlElement^ ele = this->GetTcpServerElement();
	this->SetValue(ele, "IPAddress", endPoint->Address->ToString());
	this->SetValue(ele, "Port", endPoint->Port.ToString());
}
// ----------------------------------------------------------------------------------------------------

Encoding^ ConfigFile::GetTcpEncoding()
{
	XmlElement^ ele = this->GetTcpServerElement();
	String^ enc = this->GetValue(ele, "Encoding", System::Text::Encoding::ASCII->ToString());
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

void ConfigFile::SetTcpEncoding(System::Text::Encoding ^encoding)
{
	XmlElement^ ele = this->GetTcpServerElement();
	this->SetValue(ele, "Encoding", encoding->ToString());
}
// ----------------------------------------------------------------------------------------------------

String^ ConfigFile::GetFtpRemotePath()
{
	XmlElement^ ele = this->GetFtpClientElement();
	return this->GetValue(ele, "RemotePath", String::Empty);
}
// ----------------------------------------------------------------------------------------------------

void ConfigFile::SetFtpRemotePath(System::String ^path)
{
	XmlElement^ ele = this->GetFtpClientElement();
	this->SetValue(ele, "RemotePath", path);
}
// ----------------------------------------------------------------------------------------------------

String^ ConfigFile::GetFtpLocalPath()
{
	XmlElement^ ele = this->GetFtpClientElement();
	return this->GetValue(ele, "LocalPath", String::Empty);
}
// ----------------------------------------------------------------------------------------------------

void ConfigFile::SetFtpLocalPath(System::String ^path)
{
	XmlElement^ ele = this->GetFtpClientElement();
	this->SetValue(ele, "LocalPath", path);
}
// ----------------------------------------------------------------------------------------------------

IPAddress^ ConfigFile::GetFtpAddress()
{
	XmlElement^ ele = this->GetFtpClientElement();
	String^ ip = this->GetValue(ele, "IPAddress", String::Empty);
	if (ip->Equals(String::Empty))
	{
		return nullptr;
	}
	else
	{
		return IPAddress::Parse(ip);
	}
}
// ----------------------------------------------------------------------------------------------------

void ConfigFile::SetFtpAddress(System::Net::IPAddress ^address)
{
	XmlElement^ ele = this->GetFtpClientElement();
	this->SetValue(ele, "IPAddress", address->ToString());
}
// ----------------------------------------------------------------------------------------------------

String^ ConfigFile::GetFtpUserName()
{
	XmlElement^ ele = this->GetFtpClientElement();
	return this->GetValue(ele, "UserName", String::Empty);
}
// ----------------------------------------------------------------------------------------------------

void ConfigFile::SetFtpUserName(System::String ^user)
{
	XmlElement^ ele = this->GetFtpClientElement();
	this->SetValue(ele, "UserName", user);
}
// ----------------------------------------------------------------------------------------------------

String^ ConfigFile::GetFtpPassword()
{
	XmlElement^ ele = this->GetFtpClientElement();
	return this->GetValue(ele, "Password", String::Empty);
}
// ----------------------------------------------------------------------------------------------------

void ConfigFile::SetFtpPassword(System::String ^password)
{
	XmlElement^ ele = this->GetFtpClientElement();
	this->SetValue(ele, "Password", password);
}
// ----------------------------------------------------------------------------------------------------

String^ ConfigFile::GetPicturePath()
{
	XmlElement^ ele = this->GetPicturePuzzleElement();
	return this->GetValue(ele, "Path", String::Empty);
}
// ----------------------------------------------------------------------------------------------------

void ConfigFile::SetPicturePath(System::String ^path)
{
	XmlElement^ ele = this->GetPicturePuzzleElement();
	this->SetValue(ele, "Path", path);
}
// ----------------------------------------------------------------------------------------------------

String^ ConfigFile::GetTimerDateTime()
{
	XmlElement^ ele = this->GetBinaryClockElement();
	return this->GetValue(ele, "DateTime", String::Empty);
}
// ----------------------------------------------------------------------------------------------------

void ConfigFile::SetTimerDateTime(System::String ^time)
{
	XmlElement^ ele = this->GetBinaryClockElement();
	this->SetValue(ele, "DateTime", time->ToString());
}
// ----------------------------------------------------------------------------------------------------

String^ ConfigFile::GetTimetTimeSpan()
{
	XmlElement^ ele = this->GetBinaryClockElement();
	return this->GetValue(ele, "TimeSpan", String::Empty);
}
// ----------------------------------------------------------------------------------------------------

void ConfigFile::SetTimerTimeSpan(System::String ^span)
{
	XmlElement^ ele = this->GetBinaryClockElement();
	this->SetValue(ele, "TimeSpan", span->ToString());
}
// ----------------------------------------------------------------------------------------------------

bool ConfigFile::GetTimerIsSpan()
{
	XmlElement^ ele = this->GetBinaryClockElement();
	return bool::Parse(this->GetValue(ele, "IsSpan", false.ToString()));
}
// ----------------------------------------------------------------------------------------------------

void ConfigFile::SetTimerIsSpan(bool isSpan)
{
	XmlElement^ ele = this->GetBinaryClockElement();
	this->SetValue(ele, "IsSpan", isSpan.ToString());
}
// ----------------------------------------------------------------------------------------------------

int ConfigFile::GetTetrisScore(int ranking)
{
	XmlElement^ ele = this->GetTetrisElement();
	return int::Parse(this->GetValue(ele, "Score", "RANKING", ranking.ToString(), (0).ToString()));
}
// ----------------------------------------------------------------------------------------------------

void ConfigFile::SetTetrisScore(int score)
{
	XmlElement^ ele = this->GetTetrisElement();
	const int max = 3;
	array<int>^ scoreArray = { this->GetTetrisScore(1), this->GetTetrisScore(2), this->GetTetrisScore(3), score };
	Array::Sort(scoreArray);
	for (int i = 0; i < max; i++)
	{
		this->SetValue(ele, "Score", "RANKING", (i + 1).ToString(), scoreArray[max - i].ToString());
	}
}
// ----------------------------------------------------------------------------------------------------

bool ConfigFile::GetTetrisSoundON()
{
	XmlElement^ ele = this->GetTetrisElement();
	return bool::Parse(this->GetValue(ele, "SoundON", false.ToString()));
}
// ----------------------------------------------------------------------------------------------------

void ConfigFile::SetTetrisSoundON(bool isON)
{
	XmlElement^ ele = this->GetTetrisElement();
	this->SetValue(ele, "SoundON", isON.ToString());
}
// ----------------------------------------------------------------------------------------------------

bool ConfigFile::GetTetrisRemoteEnabled()
{
	XmlElement^ ele = this->GetTetrisElement();
	return bool::Parse(this->GetValue(ele, "RemoteEnabled", false.ToString()));
}
// ----------------------------------------------------------------------------------------------------

void ConfigFile::SetTetrisRemoteEnabled(bool enabled)
{
	XmlElement^ ele = this->GetTetrisElement();
	this->SetValue(ele, "RemoteEnabled", enabled.ToString());
}
// ----------------------------------------------------------------------------------------------------

bool ConfigFile::GetDirectXXYZAxisON()
{
	XmlElement^ ele = this->GetDirectXElement();
	return bool::Parse(this->GetValue(ele, "XYZAxisON", false.ToString()));
}
// ----------------------------------------------------------------------------------------------------

void ConfigFile::SetDirectXXYZAxisON(bool isON)
{
	XmlElement^ ele = this->GetDirectXElement();
	this->SetValue(ele, "XYZAxisON", isON.ToString());
}
// ----------------------------------------------------------------------------------------------------
