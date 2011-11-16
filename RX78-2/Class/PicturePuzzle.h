#pragma once

#include "PuzzleBitmap.h"
#include "PuzzleDrag.h"

namespace RX78_2
{
	namespace Puzzle
	{
		using namespace System;
		using namespace System::Drawing;
		using namespace System::Windows::Forms;

		/**
		 * ピクチャーパズル
		 */
		ref class PicturePuzzle
		{
		/**
		 * フィールド
		 */
		private:
			PuzzleBitmap^ bitmap;
			PuzzleDrag^ drag;

			array<Control^>^ correctArray;		///< 正解場所
			array<Control^>^ realArray;			///< 実際の場所
			Point emptyPoint;					///< 空白場所

		/**
		 * コンストラクタ
		 */
		public:
			PicturePuzzle();

		/**
		 * メソッド
		 */
		private:
			Point IndexToPoint(int index);
			int PointToIndex(Point point);

		public:
			/// パズルコントロール設定
			void SetPuzzleControl(array<Control^, 2>^ puzzle);
			/// パズルシャッフル
			void Shuffle();
			/// パズルを移動可能箇所へ移動
			bool MovePuzzle(Control^ puzzle);
			/// 正解かどうか判定
			bool IsCorrect(Control^ puzzle);
			/// 正解ポイント取得
			Point GetCorrectPoint(Control^ puzzle);
			/// パズルの場所取得
			Point GetRialPoint(Control^ puzzle);
			/// 移動可能方向取得
			PuzzleDrag::Direction GetDirectionCanMove(Control^ puzzle);

		/**
		 * プロパティ
		 */
		public:
			/// ビットマップ
			property PuzzleBitmap^ Bitmap
			{
				PuzzleBitmap^ get() { return this->bitmap; }
			}
			/// ドラッグ操作
			property PuzzleDrag^ Drag
			{
				PuzzleDrag^ get() { return this->drag; }
			}
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
