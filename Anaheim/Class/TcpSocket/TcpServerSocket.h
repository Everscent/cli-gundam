#pragma once

#include "TcpEventArgs.h"
#include "TcpClientSocket.h"

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
		 * TCPサーバ
		 */
		public ref class TcpServerSocket
		{
		/**
		 * フィールド
		 */
		private:
			TcpListener^ server;
			List<TcpClientSocket^>^ clients;
			bool started;
			BackgroundWorker^ acceptWorker;
			Encoding^ encoding;

		/**
		 * コンストラクタ
		 */
		public:
			TcpServerSocket();

		/**
		 * メソッド
		 */
		private:
			void AcceptWorkerDoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
			void AcceptWorkerProgressChanged(System::Object^ sender, System::ComponentModel::ProgressChangedEventArgs^ e);

			void ReceivedClient(System::Object^ sender, TcpEventArgs^ e);
			void DisConnectedClient(System::Object^ sender, TcpEventArgs^ e);

			bool IsEnabledEndPoint(IPEndPoint^ endPoint);
			void SetEncoding(System::Text::Encoding^ encoding);

		public:
			/// 初期化
			bool Initialize(IPEndPoint^ endPoint);
			/// スタート
			bool Start();
			/// ストップ
			bool Stop();
			/// 切断
			bool DisConnect(IPEndPoint^ endPoint);
			/// メッセージ送信
			bool SendMessage(String^ message, IPEndPoint^ endPoint);

		/**
		 * プロパティ
		 */
		public:
			/// クライアントリスト
			property List<TcpClientSocket^>^ Clients
			{
				List<TcpClientSocket^>^ get() { return this->clients; }
			}
			/// 開始状態
			property bool Started
			{
				bool get() { return this->started; }
			}
			/// エンコーダ
			property System::Text::Encoding^ Encoding
			{
				System::Text::Encoding^ get() { return this->encoding; }
				void set(System::Text::Encoding^ value) { this->SetEncoding(value); }
			}

		/**
		 * イベント
		 */
		protected:
			virtual void OnConnected(TcpEventArgs^ e);
			virtual void OnDisConnected(TcpEventArgs^ e);
			virtual void OnReceived(TcpEventArgs^ e);

		public:
			/// 接続イベント
			event TcpEventHandler^ Connected;
			/// 切断イベント
			event TcpEventHandler^ DisConnected;
			/// 受信イベント
			event TcpEventHandler^ Received;
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
