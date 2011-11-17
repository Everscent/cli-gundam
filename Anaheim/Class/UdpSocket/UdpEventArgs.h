#pragma once

namespace Anaheim
{
	namespace UdpSocket
	{
		using namespace System;
		using namespace System::Net;
		using namespace System::Net::Sockets;

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

		/**
		 * コンストラクタ
		 */
		public:
			UdpEventArgs(IPEndPoint^ remoteEndPoint, array<Byte>^ bytes);

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
		};
		// ----------------------------------------------------------------------------------------------------

		/**
		 * UDPイベント デリゲート
		 */
		public delegate void UdpEventHandler(Object^ sender, UdpEventArgs^ e);
		// ----------------------------------------------------------------------------------------------------
	}
}
