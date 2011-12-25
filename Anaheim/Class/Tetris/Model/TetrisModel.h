#pragma once

#include "TetrisFieldEventArgs.h"
#include "TetrisScoreEventArgs.h"
#include "TetrisScore.h"

namespace Anaheim
{
	namespace Tetris
	{
		namespace Model
		{
			using namespace System;
			using namespace System::Collections::Generic;

			ref class TetrisField;
			ref class TetrisMino;
			ref class TetrisRemoting;

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
				TetrisRemoting^ remoting;
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
				bool RotateMoveCore(bool isSuccessful);
				void AddNextMinos();
				bool SetNewMino();
				bool EndDown();
				void SendRemote();

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
				/// ハードドロップ
				bool HardDrop();
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
					PublicTetrisScore^ get () { return this->score; }
				}

			/**
			 * イベント
			 */
			protected:
				virtual void OnMinoMoved(EventArgs^ e);
				virtual void OnFieldChanged(TetrisFieldEventArgs^ e);
				virtual void OnScoreChanged(TetrisScoreEventArgs^ e);
				virtual void OnTurnEnd(EventArgs^ e);
				virtual void OnGameOver(TetrisScoreEventArgs^ e);
				virtual void OnCleared(EventArgs^ e);

			public:
				/// ミノ移動
				event EventHandler^ MinoMoved;
				/// フィールド更新イベント
				event TetrisFieldEventHandler^ FieldChanged;
				/// ターンエンドイベント
				event EventHandler^ TurnEnd;
				/// スコア更新イベント
				event TetrisScoreEventHandler^ ScoreChanged;
				/// ゲームオーバーイベント
				event TetrisScoreEventHandler^ GameOver;
				/// クリアイベント
				event EventHandler^ Cleared;
			};
			// ----------------------------------------------------------------------------------------------------
		}
	}
}
