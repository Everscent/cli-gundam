#pragma once

#include "IDrawable.h"

namespace RX78_2
{
	namespace DirectX
	{
		using namespace System;
		using namespace System::Drawing;
		using namespace Microsoft::DirectX;
		using namespace Microsoft::DirectX::Direct3D;

		/**
		 * XYZ��
		 */
		ref class XYZLine : public IDrawable
		{
		/**
		 * �t�B�[���h
		 */
		private:
			VertexBuffer^ vertex;

		/**
		 * �R���X�g���N�^
		 */
		public:
			XYZLine(Device^ device, float length);

		/**
		 * ���\�b�h
		 */
		public:
			/// �`��
			virtual void Draw(Device^ device);
			/// �e�`��
			virtual void DrawShadow(Device^ device, Vector3 lightingLocation, Plane plane);
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
