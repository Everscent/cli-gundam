#pragma once

namespace Anaheim
{
	using namespace System;

	/**
	 * INIファイル
	 */
	public ref class IniFile
	{
	/**
	 * フィールド
	 */
	private:
		String^ fileName;

	/**
	 * コンストラクタ
	 */
	public:
		IniFile(String^ fileName);

	/**
	 * メソッド
	 */
	public:
		/// String読み込み
		String^ GetString(String^ section, String^ key, String^ defValue);
		/// String書き込み
		bool SetString(String^ section, String^ key, String^ value);
		/// bool読み込み
		bool GetBoolean(String^ section, String^ key, bool defValue);
		/// bool書き込み
		bool SetBoolean(String^ section, String^ key, bool value);
		/// int読み込み
		int GetInteger(String^ section, String^ key, int defValue);
		/// int書き込み
		bool SetInteger(String^ section, String^ key, int value);
	};
	// ----------------------------------------------------------------------------------------------------
}
