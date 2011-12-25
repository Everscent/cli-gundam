#pragma once

namespace Anaheim
{
	namespace Tetris
	{
		namespace Model
		{
			ref class TetrisField;
		}

		using namespace System;
		using namespace Model;

		/**
		 * テトリスフィールドイベントArgs
		 */
		ref class TetrisFieldEventArgs
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
			TetrisFieldEventArgs(TetrisField^ field);

		/**
		 * プロパティ
		 */
		public:
			/// フィールド
			property TetrisField^ Field
			{
				TetrisField^ get() { return this->field; }
			}
		};
		// ----------------------------------------------------------------------------------------------------

		/**
		 * テトリスリモートイベント デリゲート
		 */
		delegate void TetrisFieldEventHandler(Object^ sender, TetrisFieldEventArgs^ e);
		// ----------------------------------------------------------------------------------------------------
	}
}
