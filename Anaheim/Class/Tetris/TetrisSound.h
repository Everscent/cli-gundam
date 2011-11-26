#pragma once

namespace Anaheim
{
	ref class SoundPlayer;

	namespace Tetris
	{
		using namespace System;
		using namespace System::IO;

		/**
		 * テトリス音楽
		 */
		ref class TetrisSound
		{
		/**
		 * フィールド
		 */
		private:
			bool isON;
			SoundPlayer^ player;

		/**
		 * コンストラクタ
		 */
		public:
			TetrisSound();

		/**
		 * メソッド
		 */
		private:
			void SetSoundON(bool isON);

		public:
			/// 再生
			bool PlayMainSound();
			/// 停止
			bool StopMainSound();
			/// ゲームオーバー音
			bool PlayGameOverSound();

		/**
		 * プロパティ
		 */
		public:
			property bool ON
			{
				void set(bool value) { this->SetSoundON(value); }
			}
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
