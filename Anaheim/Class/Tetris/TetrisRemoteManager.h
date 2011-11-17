#pragma once

#include "TetrisRemoteControl.h"
#include "TetrisDrawing.h"
#include "TetrisField.h"
#include "TetrisMino.h"

namespace Anaheim
{
	namespace Tetris
	{
		using namespace System;
		using namespace System::Windows::Forms;

		/**
		 * テトリスリモート
		 */
		public ref class TetrisRemoteManager
		{
		/**
		 * フィールド
		 */
		private:
			Control^ canvas;
			TetrisRemoteControl^ remote;
			TetrisDrawing^ drawing;
			TetrisMino^ mino;

		/**
		 * コンストラクタ
		 */
		public:
			TetrisRemoteManager(Control^ canvas);

		/**
		 * メソッド
		 */
		private:
			void RemoteReceived(System::Object^ sender, TetrisRemoteEventArgs^ e);

		public:
			/// リモートスタート
			bool StartRemote();
			/// リモートストップ
			bool StopRemote();
			/// 描画
			bool Draw();
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
