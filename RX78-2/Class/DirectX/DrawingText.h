#pragma once

#include "IDrawable.h"

namespace RX78_2
{
	namespace DirectX
	{
		using namespace System;
		using namespace System::Drawing;
		using namespace Microsoft::DirectX;
		using namespace Microsoft::DirectX::Direct3D;

		/**
		 * 描画テキスト
		 */
		ref class DrawingText
		{
		/**
		 * フィールド
		 */
		private:
			Microsoft::DirectX::Direct3D::Font^ font;

		/**
		 * コンストラクタ
		 */
		public:
			DrawingText(Device^ device, int height, String^ fontName);

		/**
		 * メソッド
		 */
		public:
			/// 書き込み
			void Write(String^ string, int lineIndex, Color color);
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
