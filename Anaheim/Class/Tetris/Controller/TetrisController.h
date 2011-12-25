#pragma once

#include "TetrisScoreEventArgs.h"
#include "TetrisFieldEventArgs.h"
#include "TetrisKey.h"

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

		namespace Controller
		{
			using namespace System;
			using namespace System::Windows::Forms;
			using namespace Model;
			using namespace View;

			/**
			 * テトリスController（公開用）
			 */
			public ref class PublicTetrisController abstract
			{
			/**
			 * コンストラクタ
			 */
			public:
				PublicTetrisController();

			/**
			 * メソッド
			 */
			public:
				/// クリア
				virtual void Clear() abstract;
				/// 初期化
				virtual void Initialize() abstract;
				/// スタート
				virtual bool Start() abstract;
				/// 一時停止
				virtual bool Pause() abstract;
				/// リモートスタート
				virtual bool StartRemote() abstract;
				/// リモートストップ
				virtual bool StopRemote() abstract;

			/**
			 * プロパティ
			 */
			public:
				/// 実行中か判定
				property bool IsRunning
				{
					virtual bool get() abstract;
				}
				/// キー
				property PublicTetrisKey^ Key
				{
					virtual PublicTetrisKey^ get() abstract;
				}
				/// 音楽ON設定
				property bool SoundON
				{
					virtual void set(bool value) abstract;
				}
			};
			// ----------------------------------------------------------------------------------------------------

			/**
			 * テトリスController
			 */
			ref class TetrisController : public PublicTetrisController
			{
			/**
			 * フィールド
			 */
			private:
				TetrisModel^ model;
				TetrisView^ view;
				TetrisKey^ key;
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
				void ModelFieldChanged(System::Object^  sender, Anaheim::Tetris::TetrisFieldEventArgs^  e);
				void ModelGameOver(System::Object^  sender, Anaheim::Tetris::TetrisScoreEventArgs^  e);
				void SetSoundON(bool isON);

			public:
				/// クリア
				virtual void Clear() override;
				/// 初期化
				virtual void Initialize() override;
				/// スタート
				virtual bool Start() override;
				/// 一時停止
				virtual bool Pause() override;
				/// リモートスタート
				virtual bool StartRemote() override;
				/// リモートストップ
				virtual bool StopRemote() override;

			/**
			 * プロパティ
			 */
			public:
				/// 実行中か判定
				property bool IsRunning
				{
					virtual bool get() override { return this->timer->Enabled; }
				}
				/// キー
				property PublicTetrisKey^ Key
				{
					virtual PublicTetrisKey^ get() override { return this->key; }
				}
				/// 音楽ON設定
				property bool SoundON
				{
					virtual void set(bool value) override { this->SetSoundON(value); }
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
}
