#pragma once

#include "TetrisRemoteEventArgs.h"

namespace Anaheim
{
	namespace Tetris
	{
		using namespace System;
		using namespace System::Windows::Forms;

		ref class TetrisRemoteController;
		ref class TetrisDrawing;
		ref class TetrisMino;

		/**
		 * テトリスリモート
		 */
		public ref class TetrisRemotePackage
		{
		/**
		 * フィールド
		 */
		private:
			Control^ canvas;
			TetrisRemoteController^ remote;
			TetrisDrawing^ drawing;
			TetrisMino^ mino;

		/**
		 * コンストラクタ
		 */
		public:
			TetrisRemotePackage(Control^ canvas);

		/**
		 * メソッド
		 */
		private:
			void RemoteReceived(System::Object^ sender, TetrisRemoteEventArgs^ e);
			void CanvasPaint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e);
			void CanvasResize(System::Object^  sender, System::EventArgs^  e);

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
