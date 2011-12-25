#pragma once

#include "TetrisRemoteEventArgs.h"

namespace Anaheim
{
	namespace Tetris
	{
		namespace Model
		{
			ref class TetrisMino;
			ref class TetrisRemoting;
		}

		namespace View
		{
			ref class MainTetrisDrawing;
		}

		using namespace System;
		using namespace System::Windows::Forms;
		using namespace Model;
		using namespace View;

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
			TetrisRemoting^ remoting;
			MainTetrisDrawing^ drawing;
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
			bool Draw();

		public:
			/// リモートスタート
			bool StartRemote();
			/// リモートストップ
			bool StopRemote();
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
