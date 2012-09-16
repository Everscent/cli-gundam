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
		 * XYZ線
		 */
		ref class XYZLine : public IDrawable
		{
		/**
		 * フィールド
		 */
		private:
			VertexBuffer^ vertex;

		/**
		 * コンストラクタ
		 */
		public:
			XYZLine(Device^ device, float length);

		/**
		 * メソッド
		 */
		public:
			/// 描画
			virtual void Draw(Device^ device);
			/// 影描画
			virtual void DrawShadow(Device^ device, Vector3 lightingLocation, Plane plane);
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
