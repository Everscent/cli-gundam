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
			bool isBusy;

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
