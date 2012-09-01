#pragma once

#include "UdpEventArgs.h"

namespace Anaheim
{
	namespace UdpSocket
	{
		using namespace System;
		using namespace System::Net;
		using namespace System::Net::Sockets;
		using namespace System::ComponentModel;
		using namespace System::Text;

		/**
		 * UDPクライアント
		 */
		public ref class UdpClientSocket
		{
		/**
		 * フィールド
		 */
		private:
			UdpClient^ client;
			BackgroundWorker^ receiveWorker;
			Encoding^ encoding;
			bool connected;

		/**
		 * コンストラクタ
		 */
		public:
			UdpClientSocket();

		/**
		 * メソッド
		 */
		private:
			void ReceiveWorkerDoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
			void ReceiveWorkerProgressChanged(System::Object^ sender, System::ComponentModel::ProgressChangedEventArgs^ e);

		public:
			/// スタート
			bool Start(IPEndPoint^ endPoint);
			/// ストップ
			bool Stop();
			/// データ送信
			bool SendData(array<Byte>^ bytes, IPEndPoint^ endPoint);
			/// メッセージ送信
			bool SendMessage(String^ message, IPEndPoint^ endPoint);

		/**
		 * プロパティ
		 */
		public:
			/// ローカルIP/ポート
			property IPEndPoint^ LocalEndPoint
			{
				IPEndPoint^ get() { return (this->connected) ? dynamic_cast<IPEndPoint^>(this->client->Client->LocalEndPoint) : nullptr; }
			}
			/// 接続状態
			property bool Connected
			{
				bool get() { return this->connected; }
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
			virtual void OnReceived(UdpEventArgs^ e);

		public:
			/// 受信イベント
			event UdpEventHandler^ Received;
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
