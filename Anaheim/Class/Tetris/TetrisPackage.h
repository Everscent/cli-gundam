#pragma once

#include "TetrisScoreEventArgs.h"

namespace Anaheim
{
	namespace Tetris
	{
		using namespace System;
		using namespace System::Windows::Forms;
		using namespace System::Collections::Generic;

		ref class TetrisController;
		ref class TetrisModel;
		ref class TetrisView;

		/**
		 * テトリスパッケージ
		 */
		public ref class TetrisPackage
		{
		/**
		 * フィールド
		 */
		private:
			TetrisController^ controller;
			TetrisModel^ model;
			TetrisView^ view;

		/**
		 * コンストラクタ
		 */
		public:
			TetrisPackage(Control^ mainCanvas, array<Control^>^ nextCanvases);

		/**
		 * メソッド
		 */
		private:
			void ModelTurnEnd(System::Object^  sender, System::EventArgs^  e);
			void ModelChangedScore(System::Object^  sender, Anaheim::Tetris::TetrisScoreEventArgs^  e);
			void ModelGameOver(System::Object^  sender, Anaheim::Tetris::TetrisScoreEventArgs^  e);
			void ControllerGameOver(System::Object^  sender, Anaheim::Tetris::TetrisScoreEventArgs^  e);

		/**
		 * プロパティ
		 */
		public:
			property TetrisController^ Controller
			{
				TetrisController^ get() { return this->controller; }
			}

		/**
		 * イベント
		 */
		protected:
			virtual void OnTurnEnd(EventArgs^ e);
			virtual void OnChangedScore(TetrisScoreEventArgs^ e);
			virtual void OnGameOver(TetrisScoreEventArgs^ e);

		public:
			/// ターンエンドイベント
			event EventHandler^ TurnEnd;
			/// スコア更新イベント
			event TetrisScoreEventHandler^ ChangedScore;
			/// ゲームオーバーイベント
			event TetrisScoreEventHandler^ GameOver;
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
