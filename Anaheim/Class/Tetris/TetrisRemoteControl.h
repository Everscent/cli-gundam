#pragma once

#include "TetrisField.h"
#include "TetrisMino.h"
#include "TetrisRemoteEventArgs.h"
#include "UdpClientSocket.h"

namespace Anaheim
{
	namespace Tetris
	{
		using namespace System;
		using namespace Anaheim::UdpSocket;

		/**
		 * テトリスリモート操作
		 */
		ref class TetrisRemoteControl
		{
		/**
		 * フィールド
		 */
		private:
			UdpClientSocket^ udpSocket;
			bool isBusy;

		/**
		 * コンストラクタ
		 */
		public:
			TetrisRemoteControl();

		/**
		 * メソッド
		 */
		private:
			void UdpClientSocketReceived(System::Object^ sender, UdpEventArgs^ e);
			TetrisMino^ CreateMino(array<Byte>^ bytes, TetrisField^ field);

		public:
			/// スタート
			bool Start(IPEndPoint^ endPoint);
			/// ストップ
			bool Stop();
			/// データ送信
			bool Send(TetrisField^ field, TetrisMino^ mino, IPEndPoint^ endPoint);

		/**
		 * イベント
		 */
		protected:
			virtual void OnReceived(TetrisRemoteEventArgs^ e);

		public:
			/// 受信イベント
			event TetrisRemoteEventHandler^ Received;
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
