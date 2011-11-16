#pragma once

#include "TetrisField.h"
#include "TetrisMino.h"
#include "TetrisDrawAPI.h"

namespace Anaheim
{
	namespace Tetris
	{
		using namespace System;
		using namespace System::Drawing;
		using namespace System::Windows::Forms;
		using namespace System::Collections::Generic;

		/**
		 * テトリス描画
		 */
		ref class TetrisDrawing abstract
		{
		/**
		 * フィールド
		 */
		protected:
			Control^ canvas;
			ITetrisDrawAPI^ api;

		/**
		 * コンストラクタ
		 */
		public:
			TetrisDrawing(Control^ canvas, ITetrisDrawAPI^ api);

		/**
		 * メソッド
		 */
		protected:
			/// ブロックサイズ取得
			virtual SizeF GetBlockSize() abstract;
			/// 描画
			virtual void DrawCore(TetrisMino^ mino) abstract;

			PointF GetBlockLocation(Point point, SizeF blockSize);
			void DrawBlock(PointF location, SizeF size, Color color);

		public:
			///　描画
			void Draw(TetrisMino^ mino);
			/// クリア
			void Clear();
			/// キャンバスコントロールの一致判定
			bool IsMyCanvas(Control^ canvas);
		};
		// ----------------------------------------------------------------------------------------------------

		/**
		 * メイン描画
		 */
		ref class MainTetrisDrawing : public TetrisDrawing
		{
		/**
		 * フィールド
		 */
		private:
			TetrisField^ field;

		/**
		 * コンストラクタ
		 */
		public:
			MainTetrisDrawing(Control^ canvas, ITetrisDrawAPI^ api, TetrisField^ field);

		/**
		 * メソッド
		 */
		private:
			void DrawMino(TetrisMino^ mino);

		protected:
			/// ブロックサイズ取得
			virtual SizeF GetBlockSize() override;
			///　描画
			virtual void DrawCore(TetrisMino^ mino) override;
		};
		// ----------------------------------------------------------------------------------------------------

		/**
		 * ネクスト描画
		 */
		ref class NextTetrisDrawing : public TetrisDrawing
		{
		/**
		 * コンストラクタ
		 */
		public:
			NextTetrisDrawing(Control^ canvas, ITetrisDrawAPI^ api);

		/**
		 * メソッド
		 */
		protected:
			/// ブロックサイズ取得
			virtual SizeF GetBlockSize() override;
			///　描画
			virtual void DrawCore(TetrisMino^ mino) override;
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
