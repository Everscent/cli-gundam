#pragma once

#include "TetrisRemoteControl.h"
#include "TetrisDrawing.h"
#include "TetrisField.h"
#include "TetrisMino.h"

namespace Anaheim
{
	namespace Tetris
	{
		using namespace System;
		using namespace System::Windows::Forms;

		/**
		 * �e�g���X�����[�g
		 */
		public ref class TetrisRemoteManager
		{
		/**
		 * �t�B�[���h
		 */
		private:
			Control^ canvas;
			TetrisRemoteControl^ remote;
			TetrisDrawing^ drawing;
			TetrisMino^ mino;

		/**
		 * �R���X�g���N�^
		 */
		public:
			TetrisRemoteManager(Control^ canvas);

		/**
		 * ���\�b�h
		 */
		private:
			void RemoteReceived(System::Object^ sender, TetrisRemoteEventArgs^ e);

		public:
			/// �����[�g�X�^�[�g
			bool StartRemote();
			/// �����[�g�X�g�b�v
			bool StopRemote();
			/// �`��
			bool Draw();
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
