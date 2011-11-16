#pragma once

namespace Anaheim
{
	using namespace System;
	using namespace System::Net;
	using namespace System::Net::Sockets;

	/**
	 *	FTPクライアント
	 */
	public ref class FtpClient
	{
	/**
	 * フィールド
	 */
	private:
		IPAddress^ ipAddress;
		NetworkCredential^ credential;	///< ユーザ名，パスワード

	public:
		/// 匿名ユーザ名
		literal String^ ANONYMITY_STRING = "anonymous";

	/**
	 * コンストラクタ
	 */
	public:
		FtpClient();

	/**
	 * メソッド
	 */
	private:
		String^ GetRootUri();
		array<String^>^ GetDirectoryAndFileArray(String^ path, bool isDirectory);

	public:
		/// 接続
		bool Connect(IPAddress^ ip, String^ user, String^ pass);
		/// 接続（匿名）
		bool Connect(IPAddress^ ip, String^ pass);
		/// 切断
		bool DisConnect();
		/// ダウンロード
		bool Download(String^ remotePath, String^ localPath);
		/// アップロード
		bool Upload(String^ remotePath, String^ localPath);
		/// ディレクトリ一覧取得
		array<String^>^ GetDirectory(String^ path);
		/// ファイル名一覧取得
		array<String^>^ GetFileName(String^ path);
		/// ファイルサイズ取得
		int GetFileSize(String^ path);
		/// ファイルスタンプ取得
		DateTime GetFileDateTime(String^ path);

	/**
	 * プロパティ
	 */
	public:
		/// ルートURI
		property String^ RootURI
		{
			String^ get() { return this->GetRootUri(); }
		}
	};
	// ----------------------------------------------------------------------------------------------------
}
