#include "StdAfx.h"
#include "IniFile.h"
#include <windows.h>
#include <vcclr.h>

using namespace Anaheim;

IniFile::IniFile(System::String ^fileName)
{
	this->fileName = fileName;
}
// ----------------------------------------------------------------------------------------------------

String^ IniFile::GetString(System::String ^section, System::String ^key, System::String ^defValue)
{
	if (!System::IO::File::Exists(this->fileName))
	{
		return defValue;
	}

	LPCTSTR lpAppName;				// セクション名
	LPCTSTR lpKeyName;				// キー名
	LPCTSTR lpDefault;				// キー名が見つからない場合のデフォルトの文字列
	LPTSTR  lpReturnedString;		// (戻り値)文字列を受け取るバッファ
	DWORD   nSize;					// (戻り値)文字列を受け取るサイズ
	LPCTSTR lpFileName;				// INIファイル名

	const int buffSize = 1024;

	// System::String^ → wchar_t*
	pin_ptr<const wchar_t> wBuff = ::PtrToStringChars(section);
	lpAppName = wBuff;

	wBuff = ::PtrToStringChars(key);
	lpKeyName = wBuff;

	wBuff = ::PtrToStringChars(defValue);
	lpDefault = wBuff;

	lpReturnedString = new wchar_t[buffSize + 1];
	memset(lpReturnedString, 0, sizeof(lpReturnedString));

	nSize = sizeof(wchar_t) * buffSize;

	wBuff = ::PtrToStringChars(this->fileName);
	lpFileName = wBuff;

	DWORD returnSize = ::GetPrivateProfileString(lpAppName, lpKeyName, lpDefault, lpReturnedString, nSize, lpFileName);

	String^ result = String::Empty;
	if (0 < returnSize)
	{
		//　wchar_t* → System::String^
		result = gcnew String(lpReturnedString);
	}

	delete [] lpReturnedString;

	return result;
}
// ----------------------------------------------------------------------------------------------------

bool IniFile::SetString(System::String ^section, System::String ^key, System::String ^value)
{
	bool result = false;

	LPCTSTR lpAppName;		// セクション名
	LPCTSTR lpKeyName;		// キー名
	LPCTSTR lpString;		// キーの値になる文字列
	LPCTSTR lpFileName;		// INIファイル名

	pin_ptr<const wchar_t> wBuff = ::PtrToStringChars(section);
	lpAppName = wBuff;

	wBuff = ::PtrToStringChars(key);
	lpKeyName = wBuff;

	wBuff = ::PtrToStringChars(value);
	lpString = wBuff;

	wBuff = ::PtrToStringChars(this->fileName);
	lpFileName = wBuff;

	BOOL answer = ::WritePrivateProfileString(lpAppName, lpKeyName, lpString, lpFileName);

	if (answer == 0)
	{
		return false;
	}

	return true;
}
// ----------------------------------------------------------------------------------------------------

bool IniFile::GetBoolean(System::String ^section, System::String ^key, bool defValue)
{
	String^ value = this->GetString(section, key, defValue.ToString());
	return bool::Parse(value);
}
// ----------------------------------------------------------------------------------------------------

bool IniFile::SetBoolean(System::String ^section, System::String ^key, bool value)
{
	return this->SetString(section, key, value.ToString());
}
// ----------------------------------------------------------------------------------------------------

int IniFile::GetInteger(System::String ^section, System::String ^key, int defValue)
{
	String^ value = this->GetString(section, key, defValue.ToString());
	return int::Parse(value);
}
// ----------------------------------------------------------------------------------------------------

bool IniFile::SetInteger(System::String ^section, System::String ^key, int value)
{
	return this->SetString(section, key, value.ToString());
}
// ----------------------------------------------------------------------------------------------------
