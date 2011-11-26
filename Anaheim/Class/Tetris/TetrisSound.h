#pragma once

namespace Anaheim
{
	ref class SoundPlayer;

	namespace Tetris
	{
		using namespace System;
		using namespace System::IO;

		/**
		 * �e�g���X���y
		 */
		ref class TetrisSound
		{
		/**
		 * �t�B�[���h
		 */
		private:
			bool isON;
			SoundPlayer^ player;

		/**
		 * �R���X�g���N�^
		 */
		public:
			TetrisSound();

		/**
		 * ���\�b�h
		 */
		private:
			void SetSoundON(bool isON);

		public:
			/// �Đ�
			bool PlayMainSound();
			/// ��~
			bool StopMainSound();
			/// �Q�[���I�[�o�[��
			bool PlayGameOverSound();

		/**
		 * �v���p�e�B
		 */
		public:
			property bool ON
			{
				void set(bool value) { this->SetSoundON(value); }
			}
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
