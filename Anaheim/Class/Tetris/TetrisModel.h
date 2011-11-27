#pragma once

#include "TetrisScoreEventArgs.h"

namespace Anaheim
{
	namespace Tetris
	{
		using namespace System;
		using namespace System::Collections::Generic;

		ref class TetrisField;
		ref class TetrisMino;
		ref class TetrisScore;
		ref class PublicTetrisScore;

		/**
		 * テトリスModel
		 */
		ref class TetrisModel
		{
		/**
		 * フィールド
		 */
		private:
			TetrisField^ field;
			List<TetrisMino^>^ minos;
			TetrisScore^ score;
			int nextCount;

		/**
		 * コンストラクタ
		 */
		public:
			TetrisModel(TetrisField^ field, List<TetrisMino^>^ minos, TetrisScore^ score, int nextCount);

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

		/**
		 * プロパティ
		 */
		public:
			/// フィールド
			property TetrisField^ Field
			{
				TetrisField^ get() { return this->field; }
			}
			/// 今落ちているミノ
			property TetrisMino^ CurrentMino
			{
				TetrisMino^ get() { return ((this->minos == nullptr || this->minos->Count == 0) ? nullptr : this->minos[0]); }
			}
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
			virtual void OnChangedField(EventArgs^ e);
			virtual void OnChangedScore(TetrisScoreEventArgs^ e);
			virtual void OnGameOver(TetrisScoreEventArgs^ e);

		public:
			/// ターンエンドイベント
			event EventHandler^ TurnEnd;
			/// フィールド更新イベント
			event EventHandler^ ChangedField;
			/// スコア更新イベント
			event TetrisScoreEventHandler^ ChangedScore;
			/// ゲームオーバーイベント
			event TetrisScoreEventHandler^ GameOver;
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
