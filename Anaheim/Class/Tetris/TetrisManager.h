#pragma once

#include "TetrisField.h"
#include "TetrisMino.h"
#include "TetrisDrawing.h"
#include "TetrisScore.h"
#include "TetrisScoreEventArgs.h"
#include "TetrisRemoteControl.h"

namespace Anaheim
{
	namespace Tetris
	{
		using namespace System;
		using namespace System::Windows::Forms;
		using namespace System::Collections::Generic;

		/**
		 * テトリス
		 */
		public ref class TetrisManager
		{
		/**
		 * フィールド
		 */
		private:
			TetrisField^ field;
			List<TetrisMino^>^ minos;
			array<TetrisDrawing^>^ drawings;
			TetrisScore^ score;
			TetrisRemoteControl^ remote;

		/**
		 * コンストラクタ
		 */
		public:
			TetrisManager(Control^ mainCanvas, array<Control^>^ nextCanvases);

		/**
		 * メソッド
		 */
		private:
			void AddNextMinos();
			bool SetNewMino();
			bool EndDown();

		public:
			/// クリア
			void Clear();
			/// 初期化
			void Initialize();
			/// 描画（全描画）
			bool Draw();
			/// 描画（指定）
			bool Draw(Control^ canvas);
			/// 右回転
			bool RotateRight();
			/// 左回転
			bool RotateLeft();
			/// 右移動
			bool MoveRight();
			/// 左移動
			bool MoveLeft();
			/// 下移動
			bool MoveDown();
			/// 下移動（自動後処理）
			bool MoveDownAutomatic();
			/// テレポート
			bool Teleport();
			/// リモートスタート
			bool StartRemote();
			/// リモートストップ
			bool StopRemote();

		/**
		 * プロパティ
		 */
		private:
			/// 今落ちているミノ
			property TetrisMino^ CurrentMino
			{
				TetrisMino^ get() { return ((this->minos == nullptr || this->minos->Count == 0) ? nullptr : this->minos[0]); }
			}

		public:
			/// スコア
			property PublicTetrisScore^ Score
			{
				PublicTetrisScore^ get() { return this->score; }
			}

		/**
		 * イベント
		 */
		protected:
			virtual void OnTurnEnd(EventArgs^ e);
			virtual void OnChangedScore(TetrisScoreEventArgs^ e);
			virtual void OnGameOver(EventArgs^ e);

		public:
			/// ターンエンドイベント
			event EventHandler^ TurnEnd;
			/// スコア更新イベント
			event TetrisScoreEventHandler^ ChangedScore;
			/// ゲームオーバーイベント
			event EventHandler^ GameOver;
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
