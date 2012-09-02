#pragma once

namespace RX78_2
{
	namespace DirectX
	{
		using namespace System;
		using namespace System::Windows::Forms;
		using namespace System::Drawing;
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

		/**
		 * �R���X�g���N�^
		 */
		public:
			DirectX3D();

		/**
		 * ���\�b�h
		 */
		private:
			bool CreateDevice();
			void CreateFont();
			void SetCamera();
			void DrawCore();

		public:
			/// ������
			bool Initialize(Control^ canvas);
			/// �`��
			void Draw();
			/// �J��
			void Release();
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
