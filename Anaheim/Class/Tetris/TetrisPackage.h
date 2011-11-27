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
			void ModelScoreChanged(System::Object^  sender, Anaheim::Tetris::TetrisScoreEventArgs^  e);
			void ModelGameOver(System::Object^  sender, Anaheim::Tetris::TetrisScoreEventArgs^  e);
			void ControllerGameOver(System::Object^  sender, Anaheim::Tetris::TetrisScoreEventArgs^  e);

		/**
		 * プロパティ
		 */
		public:
			/// コントローラ
			property TetrisController^ Controller
			{
				TetrisController^ get() { return this->controller; }
			}

		/**
		 * イベント
		 */
		protected:
			virtual void OnTurnEnd(EventArgs^ e);
			virtual void OnScoreChanged(TetrisScoreEventArgs^ e);
			virtual void OnGameOver(TetrisScoreEventArgs^ e);

		public:
			/// ターンエンドイベント
			event EventHandler^ TurnEnd;
			/// スコア更新イベント
			event TetrisScoreEventHandler^ ScoreChanged;
			/// ゲームオーバーイベント
			event TetrisScoreEventHandler^ GameOver;
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
