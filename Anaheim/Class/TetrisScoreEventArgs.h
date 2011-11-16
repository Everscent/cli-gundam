#pragma once

#include "TetrisScore.h"

namespace Anaheim
{
	namespace Tetris
	{
		using namespace System;

		/**
		 * テトリス得点イベントArgs
		 */
		public ref class TetrisScoreEventArgs : public EventArgs
		{
		/**
		 * フィールド
		 */
		private:
			PublicTetrisScore^ score;

		/**
		 * コンストラクタ
		 */
		public:
			TetrisScoreEventArgs(PublicTetrisScore^ score);

		/**
		 * プロパティ
		 */
		public:
			/// スコア
			property PublicTetrisScore^ Score
			{
				PublicTetrisScore^ get() { return this->score; }
			}
		};
		// ----------------------------------------------------------------------------------------------------

		/**
		 * テトリス得点イベント デリゲート
		 */
		public delegate void TetrisScoreEventHandler(Object^ sender, TetrisScoreEventArgs^ e);
		// ----------------------------------------------------------------------------------------------------
	}
}
