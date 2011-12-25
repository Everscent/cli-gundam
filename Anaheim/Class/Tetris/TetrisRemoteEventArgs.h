#pragma once

namespace Anaheim
{
	namespace Tetris
	{
		namespace Model
		{
			ref class TetrisField;
			ref class TetrisMino;
		}

		using namespace System;
		using namespace Model;

		/**
		 * テトリスリモートイベントArgs
		 */
		public ref class TetrisRemoteEventArgs : public EventArgs
		{
		/**
		 * フィールド
		 */
		private:
			TetrisField^ field;
			TetrisMino^ mino;

		/**
		 * コンストラクタ
		 */
		public:
			TetrisRemoteEventArgs(TetrisField^ field, TetrisMino^ mino);

		/**
		 * プロパティ
		 */
		public:
			/// フィールド
			property TetrisField^ Field
			{
				TetrisField^ get() { return this->field; }
			}
			/// ミノ
			property TetrisMino^ Mino
			{
				TetrisMino^ get() { return this->mino; }
			}
		};
		// ----------------------------------------------------------------------------------------------------

		/**
		 * テトリスリモートイベント デリゲート
		 */
		public delegate void TetrisRemoteEventHandler(Object^ sender, TetrisRemoteEventArgs^ e);
		// ----------------------------------------------------------------------------------------------------
	}
}
