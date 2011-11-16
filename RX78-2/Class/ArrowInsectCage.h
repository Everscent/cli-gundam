#pragma once

#include "Insect.h"
#include "ArrowDrawing.h"

namespace RX78_2
{
	namespace Arrow
	{
		using namespace System;
		using namespace System::Windows::Forms;

		/**
		 * Arrow虫
		 */
		ref class ArrowInsectCage
		{
		/**
		 * フィールド
		 */
		private:
			Control^ canvas;
			Random^ random;
			array<Insect^>^ insects;
			ArrowDrawing^ drawing;

		/**
		 * コンストラクタ
		 */
		public:
			ArrowInsectCage(Control^ canvas, int count);

		/**
		 * メソッド
		 */
		private:
			Insect^ CreateInsect();

		public:
			/// 移動
			void Move();
			/// 描画
			void Draw();
			/// 位置，角度リセット
			void Reset();
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
