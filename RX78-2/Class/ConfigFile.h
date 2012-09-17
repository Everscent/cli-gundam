#pragma once

namespace RX78_2
{
	using namespace System;
	using namespace System::Xml;
	using namespace System::Drawing;
	using namespace System::Windows::Forms;
	using namespace System::Net;
	using namespace System::Text;

	/**
	 * コンフィグファイル
	 */
	public ref class ConfigFile
	{
	/**
	 * フィールド
	 */
	private:
		XmlDocument^ xmlDoc;
		String^ fileName;

	/**
	 * コンストラクタ
	 */
	public:
		ConfigFile(String^ fileName);

	/**
	 * メソッド
	 */
	private:
		XmlElement^ GetRootElement();
		XmlElement^ GetElement(XmlElement^ parent, String^ name);
		XmlElement^ GetElement(XmlElement^ parent, String^ name, String^ attrName, String^ attrValue);

		String^ GetValue(XmlElement^ parent, String^ name, String^ defValue);
		String^ GetValue(XmlElement^ parent, String^ name, String^ attrName, String^ attrValue, String^ defValue);
		void SetValue(XmlElement^ parent, String^ name, String^ value);
		void SetValue(XmlElement^ parent, String^ name, String^ attrName, String^ attrValue, String^ value);

		XmlElement^ GetWindowElement(String^ name);
		XmlElement^ GetReportElement();
		XmlElement^ GetTcpServerElement();
		XmlElement^ GetFtpClientElement();
		XmlElement^ GetPicturePuzzleElement();
		XmlElement^ GetBinaryClockElement();
		XmlElement^ GetTetrisElement();
		XmlElement^ GetDirectXElement();

	public:
		/// 保存
		void Save();


		/// ウィンドウ設定

		/// 位置，サイズ読み込み
		void LoadFormSizeAndLocation(Form^ form);
		/// 位置，サイズ保存
		void SaveFormSizeAndLocation(Form^ form);


		/// レポート編集

		/// ファイル名読み込み
		String^ GetReportFileName();
		/// ファイル名保存
		void SetReportFileName(String^ fileName);


		/// TCPサーバ

		/// IPアドレス，ポート読み込み
		IPEndPoint^ GetTcpIPEndPoint();
		/// IPアドレス，ポート保存
		void SetTcpIPEndPoint(IPEndPoint^ endPoint);
		/// エンコード読み込み
		Encoding^ GetTcpEncoding();
		/// エンコード保存
		void SetTcpEncoding(Encoding^ encoding);


		/// FTPクライアント

		/// リモートパス読み込み
		String^ GetFtpRemotePath();
		/// リモートパス保存
		void SetFtpRemotePath(String^ path);
		/// ローカルパス読み込み
		String^ GetFtpLocalPath();
		/// ローカルパス保存
		void SetFtpLocalPath(String^ path);
		/// FTPサーバIPアドレス読み込み
		IPAddress^ GetFtpAddress();
		/// FTPサーバIPアドレス保存
		void SetFtpAddress(IPAddress^ address);
		/// ユーザ名読み込み
		String^ GetFtpUserName();
		/// ユーザ名保存
		void SetFtpUserName(String^ user);
		/// パスワード読み込み
		String^ GetFtpPassword();
		/// パスワード保存
		void SetFtpPassword(String^ password);


		/// 写真パズル

		/// ファイルパス読み込み
		String^ GetPicturePath();
		/// ファイルパス保存
		void SetPicturePath(String^ path);


		/// バイナリクロック

		/// タイマー時刻読み込み
		String^ GetTimerDateTime();
		/// タイマー時刻保存
		void SetTimerDateTime(String^ time);
		/// タイマー時間読み込み
		String^ GetTimetTimeSpan();
		/// タイマー時間保存
		void SetTimerTimeSpan(String^ span);
		/// 時刻 or 時間読み込み
		bool GetTimerIsSpan();
		/// 時刻 or 時間保存
		void SetTimerIsSpan(bool isSpan);


		/// テトリス

		/// ランキング読み込み
		int GetTetrisScore(int ranking);
		/// ランキング保存
		void SetTetrisScore(int score);
		/// サウンドON読み込み
		bool GetTetrisSoundON();
		/// サウンドON保存
		void SetTetrisSoundON(bool isON);
		/// リモート有効読み込み
		bool GetTetrisRemoteEnabled();
		/// リモート有効保存
		void SetTetrisRemoteEnabled(bool enabled);


		/// DirectX

		/// XYZ軸表示ON読み込み
		bool GetDirectXXYZAxisON();
		/// XYZ軸表示ON保存
		void SetDirectXXYZAxisON(bool isON);
	};
	// ----------------------------------------------------------------------------------------------------
}
