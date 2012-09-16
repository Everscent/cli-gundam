#pragma once

namespace RX78_2
{
	namespace DirectX
	{
		using namespace Microsoft::DirectX;
		using namespace Microsoft::DirectX::Direct3D;

		/**
		 * •`‰æ‰Â”\
		 */
		interface class IDrawable
		{
		/**
		 * ƒƒ\ƒbƒh
		 */
		public:
			/// •`‰æ
			virtual void Draw(Device^ device) abstract;
			/// ‰e•`‰æ
			virtual void DrawShadow(Device^ device, Vector3 lightingLocation, Plane plane) abstract;
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
