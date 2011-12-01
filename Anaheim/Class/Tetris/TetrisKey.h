#pragma once

namespace Anaheim
{
	namespace Tetris
	{
		using namespace System;
		using namespace System::Windows::Forms;

		ref class TetrisModel;

		/**
		 * �e�g���X�L�[
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
		 * �t�B�[���h
		 */
		private:
			array<array<Keys>^>^ keysArray;
			TetrisModel^ model;
			Timer^ timer;

		/**
		 * �R���X�g���N�^
		 */
		public:
			TetrisKey(TetrisModel^ model, Timer^ timer);

		/**
		 * ���\�b�h
		 */
		private:
			bool ExecuteKeyActionCore(ActionType type);

		public:
			/// �o�^�ς݃L�[����
			bool IsRegisteredKey(Keys key);
			/// �L�[�A�N�V�������s
			bool ExecuteKeyAction(Keys key);

		/**
		 * �v���p�e�B
		 */
		public:
			/// ���ړ��L�[�ݒ�
			property array<Keys>^ MoveDownKeys
			{
				void set(array<Keys>^ value) { this->keysArray[static_cast<int>(ActionType::MoveDown)] = value; }
			}
			/// ���ړ��L�[�ݒ�
			property array<Keys>^ MoveLeftKeys
			{
				void set(array<Keys>^ value) { this->keysArray[static_cast<int>(ActionType::MoveLeft)] = value; }
			}
			/// �E�ړ��L�[�ݒ�
			property array<Keys>^ MoveRightKeys
			{
				void set(array<Keys>^ value) { this->keysArray[static_cast<int>(ActionType::MoveRight)] = value; }
			}
			/// ����]�L�[�ݒ�
			property array<Keys>^ RotateLeftKeys
			{
				void set(array<Keys>^ value) { this->keysArray[static_cast<int>(ActionType::RotateLeft)] = value; }
			}
			/// �E��]�L�[�ݒ�
			property array<Keys>^ RotateRightKeys
			{
				void set(array<Keys>^ value) { this->keysArray[static_cast<int>(ActionType::RotateRight)] = value; }
			}
			/// �n�[�h�h���b�v�L�[�ݒ�
			property array<Keys>^ HardDropKeys
			{
				void set(array<Keys>^ value) { this->keysArray[static_cast<int>(ActionType::HardDrop)] = value; }
			}
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
