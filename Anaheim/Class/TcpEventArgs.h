#pragma once

namespace Anaheim
{
	namespace TcpSocket
	{
		using namespace System;
		using namespace System::Net;
		using namespace System::Net::Sockets;

		/**
		 * TCPイベントArgs
		 */
		public ref class TcpEventArgs : public EventArgs
		{
		/**
		 * フィールド
		 */
		private:
			IPEndPoint^ remoteEndPoint;
			IPEndPoint^ localEndPoint;
			String^ message;

		/**
		 * コンストラクタ
		 */
		public:
			TcpEventArgs(IPEndPoint^ remoteEndPoint, IPEndPoint^ localEndPoint, String^ message);

		/**
		 * プロパティ
		 */
		public:
			/// リモートIP/ポート
			property IPEndPoint^ RemoteEndPoint
			{
				IPEndPoint^ get() { return this->remoteEndPoint; }
			}
			/// ローカルIP/ポート
			property IPEndPoint^ LocalEndPoint
			{
				IPEndPoint^ get() { return this->localEndPoint; }
			}
			/// メッセージ
			property String^ Message
			{
				String^ get() { return this->message; }
			}
		};
		// ----------------------------------------------------------------------------------------------------

		/**
		 * TCPイベント デリゲート
		 */
		public delegate void TcpEventHandler(Object^ sender, TcpEventArgs^ e);
		// ----------------------------------------------------------------------------------------------------
	}
}
