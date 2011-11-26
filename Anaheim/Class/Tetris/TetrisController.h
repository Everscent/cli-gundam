#pragma once

#include "TetrisScoreEventArgs.h"

namespace Anaheim
{
	namespace Tetris
	{
		using namespace System;
		using namespace System::Windows::Forms;

		ref class TetrisModel;
		ref class TetrisView;
		ref class TetrisRemoteController;
		ref class TetrisSound;

		/**
		 * �e�g���XController
		 */
		public ref class TetrisController
		{
		/**
		 * �t�B�[���h
		 */
		private:
			TetrisModel^ model;
			TetrisView^ view;
			TetrisRemoteController^ remote;
			TetrisSound^ sound;
			Timer^ timer;
			bool isPause;

		/**
		 * �R���X�g���N�^
		 */
		public:
			TetrisController(TetrisModel^ model, TetrisView^ view, Control^ mainCanvas, array<Control^>^ nextCanvases);

		/**
		 * ���\�b�h
		 */
		private:
			void TimerTick(System::Object^  sender, System::EventArgs^  e);
			void CanvasPaint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e);
			void ModelGameOver(System::Object^  sender, Anaheim::Tetris::TetrisScoreEventArgs^  e);
			void RemoteSend();
			void SetSoundON(bool isON);

		public:
			/// �N���A
			void Clear();
			/// ������
			void Initialize();
			/// �X�^�[�g
			bool Start();
			/// �X�g�b�v
			bool Stop();
			/// �L�[����
			bool ProcessDialogKey(System::Windows::Forms::Keys keyData);
			/// �����[�g�X�^�[�g
			bool StartRemote();
			/// �����[�g�X�g�b�v
			bool StopRemote();

		/**
		 * �v���p�e�B
		 */
		public:
			/// ���s������
			property bool IsRunning
			{
				bool get() { return this->timer->Enabled; }
			}
			/// ���yON
			property bool SoundON
			{
				void set(bool value) { this->SetSoundON(value); }
			}

		/**
		 * �C�x���g
		 */
		protected:
			virtual void OnGameOver(TetrisScoreEventArgs^ e);

		public:
			/// �Q�[���I�[�o�[�C�x���g
			event TetrisScoreEventHandler^ GameOver;
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
