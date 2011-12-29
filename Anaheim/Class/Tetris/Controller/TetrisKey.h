#pragma once

namespace Anaheim
{
	namespace Tetris
	{
		namespace Model
		{
			ref class TetrisModel;
		}

		namespace Controller
		{
			using namespace System;
			using namespace System::Windows::Forms;
			using namespace Model;

			/**
			 * テトリスキー（公開用）
			 */
			public ref class PublicTetrisKey abstract
			{
			/**
			 * コンストラクタ
			 */
			public:
				PublicTetrisKey();

			/**
			 * メソッド
			 */
			public:
				/// 登録済みキーか判定
				virtual bool IsRegisteredKey(Keys key) abstract;
				/// 実行
				virtual bool Execute(Keys key) abstract;

			/**
			 * プロパティ
			 */
			public:
				/// 下移動キー設定
				property array<Keys>^ MoveDownKeys
				{
					virtual void set(array<Keys>^ value) abstract;
				}
				/// 左移動キー設定
				property array<Keys>^ MoveLeftKeys
				{
					virtual void set(array<Keys>^ value) abstract;
				}
				/// 右移動キー設定
				property array<Keys>^ MoveRightKeys
				{
					virtual void set(array<Keys>^ value) abstract;
				}
				/// 左回転キー設定
				property array<Keys>^ RotateLeftKeys
				{
					virtual void set(array<Keys>^ value) abstract;
				}
				/// 右回転キー設定
				property array<Keys>^ RotateRightKeys
				{
					virtual void set(array<Keys>^ value) abstract;
				}
				/// ハードドロップキー設定
				property array<Keys>^ HardDropKeys
				{
					virtual void set(array<Keys>^ value) abstract;
				}
			};
			// ----------------------------------------------------------------------------------------------------

			/**
			 * テトリスキー
			 */
			ref class TetrisKey : public PublicTetrisKey
			{
			/**
			 * enum class
			 */
			private:
				enum class ActionType
				{
					MoveDown,
					MoveLeft,
					MoveRight,
					RotateLeft,
					RotateRight,
					HardDrop,
					Max
				};

			/**
			 * フィールド
			 */
			private:
				array<array<Keys>^>^ keysArray;
				TetrisModel^ model;
				Timer^ timer;

			/**
			 * コンストラクタ
			 */
			public:
				TetrisKey(TetrisModel^ model, Timer^ timer);

			/**
			 * メソッド
			 */
			private:
				bool ExecuteCore(ActionType type);

			public:
				/// 登録済みキーか判定
				virtual bool IsRegisteredKey(Keys key) override;
				/// 実行
				virtual bool Execute(Keys key) override;

			/**
			 * プロパティ
			 */
			public:
				/// 下移動キー設定
				property array<Keys>^ MoveDownKeys
				{
					virtual void set(array<Keys>^ value) override { this->keysArray[static_cast<int>(ActionType::MoveDown)] = value; }
				}
				/// 左移動キー設定
				property array<Keys>^ MoveLeftKeys
				{
					virtual void set(array<Keys>^ value) override { this->keysArray[static_cast<int>(ActionType::MoveLeft)] = value; }
				}
				/// 右移動キー設定
				property array<Keys>^ MoveRightKeys
				{
					virtual void set(array<Keys>^ value) override { this->keysArray[static_cast<int>(ActionType::MoveRight)] = value; }
				}
				/// 左回転キー設定
				property array<Keys>^ RotateLeftKeys
				{
					virtual void set(array<Keys>^ value) override { this->keysArray[static_cast<int>(ActionType::RotateLeft)] = value; }
				}
				/// 右回転キー設定
				property array<Keys>^ RotateRightKeys
				{
					virtual void set(array<Keys>^ value) override { this->keysArray[static_cast<int>(ActionType::RotateRight)] = value; }
				}
				/// ハードドロップキー設定
				property array<Keys>^ HardDropKeys
				{
					virtual void set(array<Keys>^ value) override { this->keysArray[static_cast<int>(ActionType::HardDrop)] = value; }
				}
			};
			// ----------------------------------------------------------------------------------------------------
		}
	}
}
