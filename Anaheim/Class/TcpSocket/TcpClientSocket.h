#pragma once

#include "TcpEventArgs.h"

namespace Anaheim
{
	namespace TcpSocket
	{
		using namespace System;
		using namespace System::Net;
		using namespace System::Net::Sockets;
		using namespace System::Collections::Generic;
		using namespace System::ComponentModel;
		using namespace System::Text;

		/**
		 * TCPクライアント
		 */
		public ref class TcpClientSocket
		{
		/**
		 * フィールド
		 */
		private:
			TcpClient^ client;
			BackgroundWorker^ receiveWorker;
			Encoding^ encoding;

		/**
		 * コンストラクタ
		 */
		public:
			TcpClientSocket();
			TcpClientSocket(TcpClient^ client);

		/**
		 * メソッド
		 */
		private:
			void ReceiveWorkerDoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
			void ReceiveWorkerProgressChanged(System::Object^ sender, System::ComponentModel::ProgressChangedEventArgs^ e);

		public:
			/// 接続
			bool Connect(IPEndPoint^ endPoint);
			/// 切断
			bool DisConnect();
			/// データ送信
			bool SendData(array<Byte>^ bytes);
			/// メッセージ送信
			bool SendMessage(String^ message);

		/**
		 * プロパティ
		 */
		public:
			/// リモートIP/ポート
			property IPEndPoint^ RemoteEndPoint
			{
				IPEndPoint^ get() { return dynamic_cast<IPEndPoint^>(this->client->Client->RemoteEndPoint); }
			}
			/// ローカルIP/ポート
			property IPEndPoint^ LocalEndPoint
			{
				IPEndPoint^ get() { return dynamic_cast<IPEndPoint^>(this->client->Client->LocalEndPoint); }
			}
			/// 接続状態
			property bool Connected
			{
				bool get() { return this->client->Connected; }
			}
			/// エンコード
			property System::Text::Encoding^ Encoding
			{
				System::Text::Encoding^ get() { return this->encoding; }
				void set(System::Text::Encoding^ value) { this->encoding = value; }
			}

		/**
		 * イベント
		 */
		protected:
			virtual void OnReceived(TcpEventArgs^ e);
			virtual void OnDisConnected(TcpEventArgs^ e);

		public:
			/// 受信イベント
			event TcpEventHandler^ Received;
			/// 切断イベント
			event TcpEventHandler^ DisConnected;
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
