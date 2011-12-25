#pragma once

#include "TetrisController.h"
#include "TetrisScoreEventArgs.h"

namespace Anaheim
{
	namespace Tetris
	{
		namespace Model
		{
			ref class TetrisModel;
		}

		namespace View
		{
			ref class TetrisView;
		}

		using namespace System;
		using namespace System::Windows::Forms;
		using namespace System::Collections::Generic;
		using namespace Model;
		using namespace View;
		using namespace Controller;

		/**
		 * テトリスパッケージ
		 */
		public ref class TetrisPackage
		{
		/**
		 * フィールド
		 */
		private:
			TetrisModel^ model;
			TetrisView^ view;
			TetrisController^ controller;

		/**
		 * コンストラクタ
		 */
		public:
			TetrisPackage(Control^ mainCanvas, array<Control^>^ nextCanvases);

		/**
		 * メソッド
		 */
		private:
			void ModelScoreChanged(System::Object^  sender, Anaheim::Tetris::TetrisScoreEventArgs^  e);
			void ModelGameOver(System::Object^  sender, Anaheim::Tetris::TetrisScoreEventArgs^  e);
			void ControllerGameOver(System::Object^  sender, Anaheim::Tetris::TetrisScoreEventArgs^  e);

		/**
		 * プロパティ
		 */
		public:
			/// コントローラ
			property PublicTetrisController^ Controller
			{
				PublicTetrisController^ get() { return this->controller; }
			}

		/**
		 * イベント
		 */
		protected:
			virtual void OnScoreChanged(TetrisScoreEventArgs^ e);
			virtual void OnGameOver(TetrisScoreEventArgs^ e);

		public:
			/// スコア更新イベント
			event TetrisScoreEventHandler^ ScoreChanged;
			/// ゲームオーバーイベント
			event TetrisScoreEventHandler^ GameOver;
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
