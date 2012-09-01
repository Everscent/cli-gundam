#pragma once

namespace MSM_07S
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
		literal String^ UDP_IP_SECTION    = "UDP_IP";			///< UDP IP関連 セクション名
		literal String^ LOCAL_IP_KEY      = "LOCAL_IP";			///< ローカルIPアドレス
		literal String^ LOCAL_PORT_KEY    = "LOCAL_PORT";		///< ローカルポートNo.
		literal String^ REMOTE_IP_KEY     = "REMOTE_IP";		///< リーモートIPアドレス
		literal String^ REMOTE_PORT_KEY   = "REMOTE_PORT";		///< リーモートポートNo.
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


		/// UDPクライアント

		/// ローカルIPアドレス，ポート読み込み
		IPEndPoint^ GetUdpLocalIPEndPoint();
		/// ローカルIPアドレス，ポート保存
		void SetUdpLocalIPEndPoint(IPEndPoint^ endPoint);
		/// リモートIPアドレス，ポート読み込み
		IPEndPoint^ GetUdpRemoteIPEndPoint();
		/// リモートIPアドレス，ポート保存
		void SetUdpRemoteIPEndPoint(IPEndPoint^ endPoint);
		/// エンコード読み込み
		Encoding^ GetUdpEncoding();
		/// エンコード保存
		void SetUdpEncoding(Encoding^ encoding);
	};
	// ----------------------------------------------------------------------------------------------------
}
