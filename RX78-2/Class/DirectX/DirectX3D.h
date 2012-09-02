#pragma once

namespace RX78_2
{
	namespace DirectX
	{
		using namespace System;
		using namespace System::Windows::Forms;
		using namespace System::Drawing;
		using namespace Microsoft::DirectX;
		using namespace Microsoft::DirectX::Direct3D;

		/**
		 * DirectX3D
		 */
		ref class DirectX3D
		{
		/**
		 * フィールド
		 */
		private:
			Control^ canvas;
			Device^ device;
			Microsoft::DirectX::Direct3D::Font^ font;
			VertexBuffer^ vertex;
			Texture^ texture;

		/**
		 * コンストラクタ
		 */
		public:
			DirectX3D();

		/**
		 * メソッド
		 */
		private:
			bool CreateDevice();
			void CreateFont();
			void SetCamera();
			void DrawCore();

		public:
			/// 初期化
			bool Initialize(Control^ canvas);
			/// 描画
			void Draw();
			/// 開放
			void Release();
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
