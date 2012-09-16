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
		 * 照明
		 */
		ref class Lighting : public IMovable, IDrawable
		{
		/**
		 * フィールド
		 */
		private:
			initonly float distance;
			initonly int index;
			Mesh^ mesh;
			Material material;
			Vector3 location;

		/**
		 * コンストラクタ
		 */
		public:
			Lighting(Device^ device, float distance, int index, Color color);

		/**
		 * メソッド
		 */
		public:
			/// 移動
			virtual void Move(Device^ device);
			/// 描画
			virtual void Draw(Device^ device);
			/// 影描画
			virtual void DrawShadow(Device^ device, Vector3 lightingLocation, Plane plane);

		/**
		 * プロパティ
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
