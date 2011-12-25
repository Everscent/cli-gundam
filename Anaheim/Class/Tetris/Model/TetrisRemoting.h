#pragma once

#include "TetrisRemoteEventArgs.h"
#include "UdpEventArgs.h"

namespace Anaheim
{
	namespace UdpSocket
	{
		ref class UdpClientSocket;
	}

	namespace Tetris
	{
		namespace Model
		{
			using namespace System;
			using namespace System::Net;
			using namespace Model;
			using namespace Anaheim::UdpSocket;

			ref class TetrisField;
			ref class TetrisMino;
			
			/**
			 * テトリスリモート操作
			 */
			ref class TetrisRemoting
			{
			/**
			 * フィールド
			 */
			private:
				UdpClientSocket^ udpSocket;
				bool isRunning;

			/**
			 * コンストラクタ
			 */
			public:
				TetrisRemoting();

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
}
