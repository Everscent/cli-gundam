#pragma once

namespace RX78_2
{
	namespace DirectX
	{
		using namespace Microsoft::DirectX;
		using namespace Microsoft::DirectX::Direct3D;

		/**
		 * 移動可能
		 */
		interface class IMovable
		{
		/**
		 * メソッド
		 */
		public:
			/// 移動
			virtual void Move(Device^ device) abstract;
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
