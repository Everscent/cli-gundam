#pragma once

#include "TcpEventArgs.h"

namespace Anaheim
{
	namespace TcpSocket
	{
		using namespace System;
		using namespace System::Net;
		using namespace System::Net::Sockets;

		/**
		 * 接続時受け渡しパラメータ
		 */
		private ref class TcpAcceptWorkerArgs
		{
		/**
		 * フィールド
		 */
		private:
			TcpEventArgs^ tcpArgs;
			TcpClient^ client;

		/**
		 * コンストラクタ
		 */
		public:
			TcpAcceptWorkerArgs(TcpEventArgs^ tcpArgs, TcpClient^ client);

		/**
		 * プロパティ
		 */
		public:
			/// イベント用パラメータ
			property TcpEventArgs^ TcpArgs
			{
				TcpEventArgs^ get() { return this->tcpArgs; }
			}
			/// TCPクライアント
			property TcpClient^ Client
			{
				TcpClient^ get() { return this->client; }
			}
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
