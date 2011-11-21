#pragma once

namespace Anaheim
{
	namespace Tetris
	{
		using namespace System;
		using namespace System::Windows::Forms;
		using namespace System::Collections::Generic;

		ref class TetrisDrawing;
		ref class TetrisField;
		ref class TetrisMino;

		/**
		 * テトリスView
		 */
		ref class TetrisView
		{
		/**
		 * フィールド
		 */
		private:
			array<TetrisDrawing^>^ drawings;
			TetrisField^ field;
			List<TetrisMino^>^ minos;

		/**
		 * コンストラクタ
		 */
		public:
			TetrisView(Control^ mainCanvas, array<Control^>^ nextCanvases, TetrisField^ field, List<TetrisMino^>^ minos);

		/**
		 * メソッド
		 */
		public:
			/// クリア
			void Clear();
			/// 描画（全描画）
			bool Draw();
			/// 描画（指定）
			bool Draw(Control^ canvas);
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
