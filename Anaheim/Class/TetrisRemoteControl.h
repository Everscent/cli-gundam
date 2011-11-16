#pragma once

#include "TetrisField.h"
#include "TetrisMino.h"
#include "TetrisRemoteEventArgs.h"
#include "UdpClientSocket.h"

namespace Anaheim
{
	namespace Tetris
	{
		using namespace System;
		using namespace Anaheim::UdpSocket;

		/**
		 * �e�g���X�����[�g����
		 */
		ref class TetrisRemoteControl
		{
		/**
		 * �t�B�[���h
		 */
		private:
			UdpClientSocket^ udpSocket;
			bool isBusy;

		/**
		 * �R���X�g���N�^
		 */
		public:
			TetrisRemoteControl();

		/**
		 * ���\�b�h
		 */
		private:
			void UdpClientSocketReceived(System::Object^ sender, UdpEventArgs^ e);
			TetrisMino^ CreateMino(array<Byte>^ bytes, TetrisField^ field);

		public:
			/// �X�^�[�g
			bool Start(IPEndPoint^ endPoint);
			/// �X�g�b�v
			bool Stop();
			/// �f�[�^���M
			bool Send(TetrisField^ field, TetrisMino^ mino, IPEndPoint^ endPoint);

		/**
		 * �C�x���g
		 */
		protected:
			virtual void OnReceived(TetrisRemoteEventArgs^ e);

		public:
			/// ��M�C�x���g
			event TetrisRemoteEventHandler^ Received;
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
