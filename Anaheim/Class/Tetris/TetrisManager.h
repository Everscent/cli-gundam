#pragma once

#include "TetrisField.h"
#include "TetrisMino.h"
#include "TetrisDrawing.h"
#include "TetrisScore.h"
#include "TetrisScoreEventArgs.h"
#include "TetrisRemoteControl.h"

namespace Anaheim
{
	namespace Tetris
	{
		using namespace System;
		using namespace System::Windows::Forms;
		using namespace System::Collections::Generic;

		/**
		 * �e�g���X
		 */
		public ref class TetrisManager
		{
		/**
		 * �t�B�[���h
		 */
		private:
			TetrisField^ field;
			List<TetrisMino^>^ minos;
			array<TetrisDrawing^>^ drawings;
			TetrisScore^ score;
			TetrisRemoteControl^ remote;

		/**
		 * �R���X�g���N�^
		 */
		public:
			TetrisManager(Control^ mainCanvas, array<Control^>^ nextCanvases);

		/**
		 * ���\�b�h
		 */
		private:
			void AddNextMinos();
			bool SetNewMino();
			bool EndDown();

		public:
			/// �N���A
			void Clear();
			/// ������
			void Initialize();
			/// �`��i�S�`��j
			bool Draw();
			/// �`��i�w��j
			bool Draw(Control^ canvas);
			/// �E��]
			bool RotateRight();
			/// ����]
			bool RotateLeft();
			/// �E�ړ�
			bool MoveRight();
			/// ���ړ�
			bool MoveLeft();
			/// ���ړ�
			bool MoveDown();
			/// ���ړ��i�����㏈���j
			bool MoveDownAutomatic();
			/// �e���|�[�g
			bool Teleport();
			/// �����[�g�X�^�[�g
			bool StartRemote();
			/// �����[�g�X�g�b�v
			bool StopRemote();

		/**
		 * �v���p�e�B
		 */
		private:
			/// �������Ă���~�m
			property TetrisMino^ CurrentMino
			{
				TetrisMino^ get() { return ((this->minos == nullptr || this->minos->Count == 0) ? nullptr : this->minos[0]); }
			}

		public:
			/// �X�R�A
			property PublicTetrisScore^ Score
			{
				PublicTetrisScore^ get() { return this->score; }
			}

		/**
		 * �C�x���g
		 */
		protected:
			virtual void OnTurnEnd(EventArgs^ e);
			virtual void OnChangedScore(TetrisScoreEventArgs^ e);
			virtual void OnGameOver(EventArgs^ e);

		public:
			/// �^�[���G���h�C�x���g
			event EventHandler^ TurnEnd;
			/// �X�R�A�X�V�C�x���g
			event TetrisScoreEventHandler^ ChangedScore;
			/// �Q�[���I�[�o�[�C�x���g
			event EventHandler^ GameOver;
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
