#pragma once

namespace Anaheim
{
	namespace UdpSocket
	{
		using namespace System;
		using namespace System::Net;
		using namespace System::Net::Sockets;

		/**
		 * UDP�C�x���gArgs
		 */
		public ref class UdpEventArgs : public EventArgs
		{
		/**
		 * �t�B�[���h
		 */
		private:
			IPEndPoint^ remoteEndPoint;
			array<Byte>^ bytes;

		/**
		 * �R���X�g���N�^
		 */
		public:
			UdpEventArgs(IPEndPoint^ remoteEndPoint, array<Byte>^ bytes);

		/**
		 * �v���p�e�B
		 */
		public:
			/// �����[�gIP/�|�[�g
			property IPEndPoint^ RemoteEndPoint
			{
				IPEndPoint^ get() { return this->remoteEndPoint; }
			}
			/// ��M�f�[�^
			property array<Byte>^ Bytes
			{
				array<Byte>^ get() { return this->bytes; }
			}
		};
		// ----------------------------------------------------------------------------------------------------

		/**
		 * UDP�C�x���g �f���Q�[�g
		 */
		public delegate void UdpEventHandler(Object^ sender, UdpEventArgs^ e);
		// ----------------------------------------------------------------------------------------------------
	}
}
