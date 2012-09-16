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
		 * 床
		 */
		ref class Floor : public IDrawable
		{
		/**
		 * フィールド
		 */
		private:
			literal int TILE_COUNT = 5;

			Material material1;
			Material material2;
			VertexBuffer^ vertex1;
			VertexBuffer^ vertex2;

		/**
		 * コンストラクタ
		 */
		public:
			Floor(Device^ device, float size, Color color1, Color color2);

		/**
		 * メソッド
		 */
		public:
			/// 描画
			virtual void Draw(Device^ device);
			/// 影描画
			virtual void DrawShadow(Device^ device, Vector3 lightingLocation, Plane plane);

		/**
		 * プロパティ
		 */
		public:
			/// 平面情報（影描画用）
			property Plane PlaneInfomation
			{
				Plane get() { return Plane(0.0f, 1.0f, 0.0f, 0.0f); }
			}
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
