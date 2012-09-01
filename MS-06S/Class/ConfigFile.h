#pragma once

namespace MS_06S
{
	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Net;
	using namespace System::Drawing;
	using namespace System::Text;
	using namespace Anaheim;

	/**
	 * コンフィグファイル
	 */
	ref class ConfigFile
	{
	/**
	 * フィールド
	 */
	private:
		IniFile ^ iniFile;

		literal String^ WINDOW_SECTION    = "WINDOW";			///< Window関連 セクション名
		literal String^ TOP_LOCATION_KEY  = "WINDOW_TOP";		///< Window Top
		literal String^ LEFT_LOCATION_KEY = "WINDOW_LEFT";		///< Window Left
		literal String^ WIDTH_SIZE_KEY    = "WINDOW_WIDTH";		///< Window Width
		literal String^ HEIGHT_SIZE_KEY   = "WINDOW_HEIGHT";	///< Window Height
		literal String^ TCP_IP_SECTION    = "TCP_IP";			///< TCP IP関連 セクション名
		literal String^ IP_ADDRESS_KEY    = "IP_ADDRESS";		///< IPアドレス
		literal String^ PORT_NUMBER_KEY   = "PORT_NUMBER";		///< ポートNo.
		literal String^ ENCODING_KEY      = "ENCODING";			///< エンコード

	/**
	 * コストラクタ
	 */
	public:
		ConfigFile(String^ fileName);

	/**
	 * メソッド
	 */
	public:
		/// ウィンドウ設定

		/// 位置，サイズ読み込み
		void LoadFormSizeAndLocation(Form^ form);
		/// 位置，サイズ保存
		void SaveFormSizeAndLocation(Form^ form);


		/// TCPクライアント

		/// IPアドレス，ポート読み込み
		IPEndPoint^ GetTcpIPEndPoint();
		/// IPアドレス，ポート保存
		void SetTcpIPEndPoint(IPEndPoint^ endPoint);
		/// エンコード読み込み
		Encoding^ GetTcpEncoding();
		/// エンコード保存
		void SetTcpEncoding(Encoding^ encoding);
	};
	// ----------------------------------------------------------------------------------------------------
}
