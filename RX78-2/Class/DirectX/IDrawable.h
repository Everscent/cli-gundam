#pragma once

namespace RX78_2
{
	namespace DirectX
	{
		using namespace Microsoft::DirectX;
		using namespace Microsoft::DirectX::Direct3D;

		/**
		 * �`��\
		 */
		interface class IDrawable
		{
		/**
		 * ���\�b�h
		 */
		public:
			/// �`��
			virtual void Draw(Device^ device) abstract;
			/// �e�`��
			virtual void DrawShadow(Device^ device, Vector3 lightingLocation, Plane plane) abstract;
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
