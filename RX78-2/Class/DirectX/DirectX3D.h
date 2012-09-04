#pragma once

namespace RX78_2
{
	namespace DirectX
	{
		using namespace System;
		using namespace System::Windows::Forms;
		using namespace System::Drawing;
		using namespace System::ComponentModel;
		using namespace Microsoft::DirectX;
		using namespace Microsoft::DirectX::Direct3D;

		/**
		 * DirectX3D
		 */
		ref class DirectX3D
		{
		/**
		 * �t�B�[���h
		 */
		private:
			Control^ canvas;
			Device^ device;
			Microsoft::DirectX::Direct3D::Font^ font;
			VertexBuffer^ vertex;
			Texture^ texture;
			array<bool>^ keys;
			float lensPosTheta;
			float lensPosPhi;

			BackgroundWorker^ backWorker;

		/**
		 * �R���X�g���N�^
		 */
		public:
			DirectX3D();

		/**
		 * ���\�b�h
		 */
		private:
			void CreateInputEvent(Control^ keyOwner);
			bool CreateDevice();
			void CreateFont();
			void CreateSquarePolygon();
			void SetCamera();
			void DoLoopProcess();
			void Draw();
			void DrawSquarePolygon();
			void BackWorkerDoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
			void ControlKeyDown(Object^ sender, KeyEventArgs^ e);
			void ControlKeyUp(Object^ sender, KeyEventArgs^ e);

		public:
			/// ������
			bool Initialize(Control^ canvas, Control^ keyOwner);
			/// �J��
			void Release();
			/// �X�^�[�g
			bool Start();
			/// �X�g�b�v
			bool Stop();
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
