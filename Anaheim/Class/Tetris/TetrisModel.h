#pragma once

#include "TetrisScoreEventArgs.h"

namespace Anaheim
{
	namespace Tetris
	{
		using namespace System;
		using namespace System::Collections::Generic;

		ref class TetrisField;
		ref class TetrisMino;
		ref class TetrisScore;
		ref class PublicTetrisScore;

		/**
		 * �e�g���XModel
		 */
		ref class TetrisModel
		{
		/**
		 * �t�B�[���h
		 */
		private:
			TetrisField^ field;
			List<TetrisMino^>^ minos;
			TetrisScore^ score;
			int nextCount;

		/**
		 * �R���X�g���N�^
		 */
		public:
			TetrisModel(TetrisField^ field, List<TetrisMino^>^ minos, TetrisScore^ score, int nextCount);

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
			/// �n�[�h�h���b�v
			bool HardDrop();

		/**
		 * �v���p�e�B
		 */
		public:
			/// �t�B�[���h
			property TetrisField^ Field
			{
				TetrisField^ get() { return this->field; }
			}
			/// �������Ă���~�m
			property TetrisMino^ CurrentMino
			{
				TetrisMino^ get() { return ((this->minos == nullptr || this->minos->Count == 0) ? nullptr : this->minos[0]); }
			}
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
			virtual void OnFieldChanged(EventArgs^ e);
			virtual void OnScoreChanged(TetrisScoreEventArgs^ e);
			virtual void OnGameOver(TetrisScoreEventArgs^ e);

		public:
			/// �^�[���G���h�C�x���g
			event EventHandler^ TurnEnd;
			/// �t�B�[���h�X�V�C�x���g
			event EventHandler^ FieldChanged;
			/// �X�R�A�X�V�C�x���g
			event TetrisScoreEventHandler^ ScoreChanged;
			/// �Q�[���I�[�o�[�C�x���g
			event TetrisScoreEventHandler^ GameOver;
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
