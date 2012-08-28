#pragma once

namespace Anaheim
{
	namespace TcpSocket
	{
		using namespace System;
		using namespace System::Net;
		using namespace System::Net::Sockets;
		using namespace System::Text;

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
			array<Byte>^ bytes;
			String^ message;

		/**
		 * コンストラクタ
		 */
		public:
			TcpEventArgs(IPEndPoint^ remoteEndPoint, IPEndPoint^ localEndPoint, array<Byte>^ bytes, Encoding^ encoding);

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
			/// 受信データ
			property array<Byte>^ Bytes
			{
				array<Byte>^ get() { return this->bytes; }
			}
			/// 受信メッセージ
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
