#pragma once

#include "TetrisRemoteEventArgs.h"

namespace Anaheim
{
	namespace Tetris
	{
		using namespace System;
		using namespace System::Windows::Forms;

		ref class TetrisRemoteController;
		ref class TetrisDrawing;
		ref class TetrisMino;

		/**
		 * �e�g���X�����[�g
		 */
		public ref class TetrisRemotePackage
		{
		/**
		 * �t�B�[���h
		 */
		private:
			Control^ canvas;
			TetrisRemoteController^ remote;
			TetrisDrawing^ drawing;
			TetrisMino^ mino;

		/**
		 * �R���X�g���N�^
		 */
		public:
			TetrisRemotePackage(Control^ canvas);

		/**
		 * ���\�b�h
		 */
		private:
			void RemoteReceived(System::Object^ sender, TetrisRemoteEventArgs^ e);
			void CanvasPaint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e);
			void CanvasResize(System::Object^  sender, System::EventArgs^  e);

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
