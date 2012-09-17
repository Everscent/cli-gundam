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
		ref class XYZAxis : public IDrawable
		{
		/**
		 * �t�B�[���h
		 */
		private:
			VertexBuffer^ vertex;
			bool enabled;

		/**
		 * �R���X�g���N�^
		 */
		public:
			XYZAxis(Device^ device, float length);

		/**
		 * ���\�b�h
		 */
		public:
			/// �`��
			virtual void Draw(Device^ device);
			/// �e�`��
			virtual void DrawShadow(Device^ device, Vector3 lightingLocation, Plane plane);

		/**
		 * �v���p�e�B
		 */
		public:
			/// �L��/����
			property bool Enabled
			{
				void set(bool value) { this->enabled = value; }
			}
		};
		// ----------------------------------------------------------------------------------------------------
	}
}