#pragma once

namespace Anaheim
{
	namespace Tetris
	{
		namespace Model
		{
			ref class PublicTetrisScore;
		}

		using namespace System;
		using namespace Model;

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
