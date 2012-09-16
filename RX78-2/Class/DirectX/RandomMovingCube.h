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
		 * �����_���ړ��L���[�u
		 */
		ref class RandomMovingCube : public IMovable, IDrawable
		{
		/**
		 * �t�B�[���h
		 */
		private:
			initonly Vector3 range;
			initonly Material shadowMaterial;

			Mesh^ mesh;
			Material material;
			Vector3 location;

			Vector3 targetLocation;
			Vector3 step;
			int count;

		/**
		 * �R���X�g���N�^
		 */
		public:
			RandomMovingCube(Device^ device, Vector3 range, float size);

		/**
		 * ���\�b�h
		 */
		private:
			void Reset();

		public:
			/// �ړ�
			virtual void Move(Device^ device);
			/// �`��
			virtual void Draw(Device^ device);
			/// �e�`��
			virtual void DrawShadow(Device^ device, Vector3 lightingLocation, Plane plane);
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
