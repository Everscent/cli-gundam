#pragma once

namespace Anaheim
{
	namespace Tetris
	{
		using namespace System;
		using namespace System::Windows::Forms;

		ref class TetrisModel;

		/**
		 * テトリスキー
		 */
		ref class TetrisKey
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
				void set(array<Keys>^ value) { this->keysArray[static_cast<int>(ActionType::MoveDown)] = value; }
			}
			/// 左移動キー設定
			property array<Keys>^ MoveLeftKeys
			{
				void set(array<Keys>^ value) { this->keysArray[static_cast<int>(ActionType::MoveLeft)] = value; }
			}
			/// 右移動キー設定
			property array<Keys>^ MoveRightKeys
			{
				void set(array<Keys>^ value) { this->keysArray[static_cast<int>(ActionType::MoveRight)] = value; }
			}
			/// 左回転キー設定
			property array<Keys>^ RotateLeftKeys
			{
				void set(array<Keys>^ value) { this->keysArray[static_cast<int>(ActionType::RotateLeft)] = value; }
			}
			/// 右回転キー設定
			property array<Keys>^ RotateRightKeys
			{
				void set(array<Keys>^ value) { this->keysArray[static_cast<int>(ActionType::RotateRight)] = value; }
			}
			/// ハードドロップキー設定
			property array<Keys>^ HardDropKeys
			{
				void set(array<Keys>^ value) { this->keysArray[static_cast<int>(ActionType::HardDrop)] = value; }
			}
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
