#pragma once

#include "UdpEventArgs.h"

namespace Anaheim
{
	namespace UdpSocket
	{
		using namespace System;
		using namespace System::Net;
		using namespace System::Net::Sockets;
		using namespace System::ComponentModel;
		using namespace System::Text;

		/**
		 * UDP�N���C�A���g
		 */
		public ref class UdpClientSocket
		{
		/**
		 * �t�B�[���h
		 */
		private:
			UdpClient^ client;
			BackgroundWorker^ receiveWorker;
			bool isBusy;

		/**
		 * �R���X�g���N�^
		 */
		public:
			UdpClientSocket();

		/**
		 * ���\�b�h
		 */
		private:
			void ReceiveWorkerDoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
			void ReceiveWorkerProgressChanged(System::Object^ sender, System::ComponentModel::ProgressChangedEventArgs^ e);

		public:
			/// �X�^�[�g
			bool Start(IPEndPoint^ endPoint);
			/// �X�g�b�v
			bool Stop();
			/// �f�[�^���M
			bool SendData(array<Byte>^ bytes, IPEndPoint^ endPoint);

		/**
		 * �C�x���g
		 */
		protected:
			virtual void OnReceived(UdpEventArgs^ e);

		public:
			/// ��M�C�x���g
			event UdpEventHandler^ Received;
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
