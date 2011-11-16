#pragma once

#include "Insect.h"

namespace RX78_2
{
	namespace Arrow
	{
		using namespace System;
		using namespace System::Drawing;
		using namespace System::Windows::Forms;

		/**
		 * Arrow描画
		 */
		ref class ArrowDrawing
		{
		/**
		 * フィールド
		 */
		private:
			Control^ canvas;
			Bitmap^ bitmap;
			Graphics^ graphics;

		/**
		 * コンストラクタ
		 */
		public:
			ArrowDrawing(Control^ canvas);

		/**
		 * メソッド
		 */
		public:
			/// 描画開始
			void BeginDraw();
			/// 描画
			void Draw(Insect^ insect);
			/// 描画終了
			void EndDraw();
		};
		// ----------------------------------------------------------------------------------------------------
	}
}