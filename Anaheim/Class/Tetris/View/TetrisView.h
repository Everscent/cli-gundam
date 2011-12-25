#pragma once

#include "TetrisSound.h"
#include "TetrisScoreEventArgs.h"
#include "TetrisFieldEventArgs.h"

namespace Anaheim
{
	namespace Tetris
	{
		namespace Model
		{
			ref class TetrisField;
			ref class TetrisMino;
			ref class TetrisModel;
		}

		namespace View
		{
			using namespace System;
			using namespace System::Windows::Forms;
			using namespace System::Collections::Generic;
			using namespace Model;

			ref class TetrisDrawing;

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
				TetrisSound^ sound;
				TetrisField^ field;
				List<TetrisMino^>^ minos;

			/**
			 * コンストラクタ
			 */
			public:
				TetrisView(Control^ mainCanvas, array<Control^>^ nextCanvases, TetrisModel^ model, TetrisField^ field, List<TetrisMino^>^ minos);

			/**
			 * メソッド
			 */
			private:
				void ModelMinoMoved(System::Object^  sender, System::EventArgs^  e);
				void ModelFieldChanged(System::Object^  sender, Anaheim::Tetris::TetrisFieldEventArgs^  e);
				void ModelTurnEnd(System::Object^  sender, System::EventArgs^  e);
				void ModelGameOver(System::Object^  sender, Anaheim::Tetris::TetrisScoreEventArgs^  e);
				void ModelCleared(System::Object^  sender, System::EventArgs^  e);

			public:
				/// クリア
				void Clear();
				/// 描画（全描画）
				bool Draw();
				/// 描画（指定）
				bool Draw(Control^ canvas);
				/// BGM再生
				bool PlayBGM();
				/// BGM一時停止
				void PauseBGM();
				/// BGM停止
				void StopBGM();

			/**
			 * プロパティ
			 */
			public:
				/// 音楽ON設定
				property bool SoundON
				{
					void set(bool value) { this->sound->ON = value; }
				}
			};
			// ----------------------------------------------------------------------------------------------------
		}
	}
}
