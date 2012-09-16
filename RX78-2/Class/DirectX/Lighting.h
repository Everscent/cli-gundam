#pragma once

#include "IMovable.h"
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
		 * �Ɩ�
		 */
		ref class Lighting : public IMovable, IDrawable
		{
		/**
		 * �t�B�[���h
		 */
		private:
			initonly float distance;
			initonly int index;
			Mesh^ mesh;
			Material material;
			Vector3 location;

		/**
		 * �R���X�g���N�^
		 */
		public:
			Lighting(Device^ device, float distance, int index, Color color);

		/**
		 * ���\�b�h
		 */
		public:
			/// �ړ�
			virtual void Move(Device^ device);
			/// �`��
			virtual void Draw(Device^ device);
			/// �e�`��
			virtual void DrawShadow(Device^ device, Vector3 lightingLocation, Plane plane);

		/**
		 * �v���p�e�B
		 */
		public:
			property Vector3 Location
			{
				Vector3 get() { return this->location; }
			}
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
