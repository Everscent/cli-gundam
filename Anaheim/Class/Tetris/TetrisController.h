#pragma once

#include "TetrisScoreEventArgs.h"

namespace Anaheim
{
	namespace Tetris
	{
		using namespace System;
		using namespace System::Windows::Forms;

		ref class TetrisModel;
		ref class TetrisView;
		ref class TetrisRemoteController;

		/**
		 * テトリスController
		 */
		public ref class TetrisController
		{
		/**
		 * フィールド
		 */
		private:
			TetrisModel^ model;
			TetrisView^ view;
			TetrisRemoteController^ remote;
			Timer^ timer;

		/**
		 * コンストラクタ
		 */
		public:
			TetrisController(TetrisModel^ model, TetrisView^ view, Control^ mainCanvas, array<Control^>^ nextCanvases);

		/**
		 * メソッド
		 */
		private:
			void TimerTick(System::Object^  sender, System::EventArgs^  e);
			void CanvasPaint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e);
			void ModelGameOver(System::Object^  sender, Anaheim::Tetris::TetrisScoreEventArgs^  e);
			void RemoteSend();

		public:
			/// クリア
			void Clear();
			/// 初期化
			void Initialize();
			/// スタート
			bool Start();
			/// ストップ
			bool Stop();
			/// キー押下
			bool ProcessDialogKey(System::Windows::Forms::Keys keyData);
			/// リモートスタート
			bool StartRemote();
			/// リモートストップ
			bool StopRemote();

		/**
		 * プロパティ
		 */
		public:
			/// 実行中判定
			property bool IsRunning
			{
				bool get() { return this->timer->Enabled; }
			}

		/**
		 * イベント
		 */
		protected:
			virtual void OnGameOver(TetrisScoreEventArgs^ e);

		public:
			/// ゲームオーバーイベント
			event TetrisScoreEventHandler^ GameOver;
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
