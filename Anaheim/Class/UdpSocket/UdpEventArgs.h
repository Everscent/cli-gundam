#pragma once

namespace Anaheim
{
	namespace UdpSocket
	{
		using namespace System;
		using namespace System::Net;
		using namespace System::Net::Sockets;
		using namespace System::Text;

		/**
		 * UDPイベントArgs
		 */
		public ref class UdpEventArgs : public EventArgs
		{
		/**
		 * フィールド
		 */
		private:
			IPEndPoint^ remoteEndPoint;
			array<Byte>^ bytes;
			String^ message;

		/**
		 * コンストラクタ
		 */
		public:
			UdpEventArgs(IPEndPoint^ remoteEndPoint, array<Byte>^ bytes, Encoding^ encoding);

		/**
		 * プロパティ
		 */
		public:
			/// リモートIP/ポート
			property IPEndPoint^ RemoteEndPoint
			{
				IPEndPoint^ get() { return this->remoteEndPoint; }
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
		 * UDPイベント デリゲート
		 */
		public delegate void UdpEventHandler(Object^ sender, UdpEventArgs^ e);
		// ----------------------------------------------------------------------------------------------------
	}
}
