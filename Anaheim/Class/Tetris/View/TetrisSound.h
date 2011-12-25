#pragma once

namespace Anaheim
{
	ref class WavPlayerDX;

	namespace Tetris
	{
		namespace View
		{
			using namespace System;
			using namespace System::IO;
			using namespace System::Windows::Forms;

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
				WavPlayerDX^ bgmPlayer;
				WavPlayerDX^ gameoverPlayer;
				WavPlayerDX^ removePlayer;
				WavPlayerDX^ enddownPlayer;

			/**
			 * コンストラクタ
			 */
			public:
				TetrisSound(Control^ owner);

			/**
			 * メソッド
			 */
			private:
				void SetSoundON(bool isON);

			public:
				/// BGM再生
				bool PlayBGM();
				/// BGM一時停止
				void PauseBGM();
				/// BGM停止
				void StopBGM();
				/// ゲームオーバー音
				bool PlayGameOverSound();
				/// 削除音
				bool PlayRemoveSound();
				/// 下移動終了音
				bool PlayEndDownSound();

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
}
