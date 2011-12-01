#pragma once

#include "TetrisScoreEventArgs.h"
#include "TetrisKey.h"

namespace Anaheim
{
	namespace Tetris
	{
		using namespace System;
		using namespace System::Windows::Forms;

		ref class TetrisModel;
		ref class TetrisView;
		ref class TetrisRemoting;
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
			TetrisKey^ key;
			TetrisRemoting^ remoting;
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
			void ModelFieldChanged(System::Object^  sender, System::EventArgs^  e);
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
			/// ���yON�ݒ�
			property bool SoundON
			{
				void set(bool value) { this->SetSoundON(value); }
			}
			/// ���ړ��L�[�ݒ�
			property array<Keys>^ MoveDownKeys
			{
				void set(array<Keys>^ value) { this->key->MoveDownKeys = value; }
			}
			/// ���ړ��L�[�ݒ�
			property array<Keys>^ MoveLeftKeys
			{
				void set(array<Keys>^ value) { this->key->MoveLeftKeys = value; }
			}
			/// �E�ړ��L�[�ݒ�
			property array<Keys>^ MoveRightKeys
			{
				void set(array<Keys>^ value) { this->key->MoveRightKeys = value; }
			}
			/// ����]�L�[�ݒ�
			property array<Keys>^ RotateLeftKeys
			{
				void set(array<Keys>^ value) { this->key->RotateLeftKeys = value; }
			}
			/// �E��]�L�[�ݒ�
			property array<Keys>^ RotateRightKeys
			{
				void set(array<Keys>^ value) { this->key->RotateRightKeys = value; }
			}
			/// �n�[�h�h���b�v�L�[�ݒ�
			property array<Keys>^ HardDropKeys
			{
				void set(array<Keys>^ value) { this->key->HardDropKeys = value; }
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
