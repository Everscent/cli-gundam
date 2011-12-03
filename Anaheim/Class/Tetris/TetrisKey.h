#pragma once

namespace Anaheim
{
	namespace Tetris
	{
		using namespace System;
		using namespace System::Windows::Forms;

		ref class TetrisModel;

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
			bool ExecuteKeyActionCore(ActionType type);

		public:
			/// 登録済みキー判定
			bool IsRegisteredKey(Keys key);
			/// キーアクション実行
			bool ExecuteKeyAction(Keys key);

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
