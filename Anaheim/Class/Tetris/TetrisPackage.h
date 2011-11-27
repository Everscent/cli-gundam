#pragma once

#include "TetrisScoreEventArgs.h"

namespace Anaheim
{
	namespace Tetris
	{
		using namespace System;
		using namespace System::Windows::Forms;
		using namespace System::Collections::Generic;

		ref class TetrisController;
		ref class TetrisModel;
		ref class TetrisView;

		/**
		 * �e�g���X�p�b�P�[�W
		 */
		public ref class TetrisPackage
		{
		/**
		 * �t�B�[���h
		 */
		private:
			TetrisController^ controller;
			TetrisModel^ model;
			TetrisView^ view;

		/**
		 * �R���X�g���N�^
		 */
		public:
			TetrisPackage(Control^ mainCanvas, array<Control^>^ nextCanvases);

		/**
		 * ���\�b�h
		 */
		private:
			void ModelTurnEnd(System::Object^  sender, System::EventArgs^  e);
			void ModelScoreChanged(System::Object^  sender, Anaheim::Tetris::TetrisScoreEventArgs^  e);
			void ModelGameOver(System::Object^  sender, Anaheim::Tetris::TetrisScoreEventArgs^  e);
			void ControllerGameOver(System::Object^  sender, Anaheim::Tetris::TetrisScoreEventArgs^  e);

		/**
		 * �v���p�e�B
		 */
		public:
			/// �R���g���[��
			property TetrisController^ Controller
			{
				TetrisController^ get() { return this->controller; }
			}

		/**
		 * �C�x���g
		 */
		protected:
			virtual void OnTurnEnd(EventArgs^ e);
			virtual void OnScoreChanged(TetrisScoreEventArgs^ e);
			virtual void OnGameOver(TetrisScoreEventArgs^ e);

		public:
			/// �^�[���G���h�C�x���g
			event EventHandler^ TurnEnd;
			/// �X�R�A�X�V�C�x���g
			event TetrisScoreEventHandler^ ScoreChanged;
			/// �Q�[���I�[�o�[�C�x���g
			event TetrisScoreEventHandler^ GameOver;
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
