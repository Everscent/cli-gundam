#pragma once

#include "TetrisScoreEventArgs.h"
#include "TetrisKey.h"

namespace Anaheim
{
	namespace Tetris
	{
		using namespace System;
		using namespace System::Windows::Forms;

		ref class TetrisModel;
		ref class TetrisView;
		ref class TetrisRemoting;
		ref class TetrisSound;

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
			TetrisKey^ key;
			TetrisRemoting^ remoting;
			TetrisSound^ sound;
			Timer^ timer;
			bool isPause;

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
			void ModelFieldChanged(System::Object^  sender, System::EventArgs^  e);
			void ModelGameOver(System::Object^  sender, Anaheim::Tetris::TetrisScoreEventArgs^  e);
			void RemoteSend();
			void SetSoundON(bool isON);

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
			/// 音楽ON設定
			property bool SoundON
			{
				void set(bool value) { this->SetSoundON(value); }
			}
			/// 下移動キー設定
			property PublicTetrisKey^ Key
			{
				PublicTetrisKey^ get() { return this->key; }
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
