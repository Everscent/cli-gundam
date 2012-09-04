#pragma once

namespace RX78_2
{
	namespace DirectX
	{
		using namespace System;
		using namespace System::Windows::Forms;
		using namespace System::Drawing;
		using namespace System::ComponentModel;
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
			array<bool>^ keys;
			float lensPosTheta;
			float lensPosPhi;

			BackgroundWorker^ backWorker;

		/**
		 * コンストラクタ
		 */
		public:
			DirectX3D();

		/**
		 * メソッド
		 */
		private:
			void CreateInputEvent(Control^ keyOwner);
			bool CreateDevice();
			void CreateFont();
			void CreateSquarePolygon();
			void SetCamera();
			void DoLoopProcess();
			void Draw();
			void DrawSquarePolygon();
			void BackWorkerDoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
			void ControlKeyDown(Object^ sender, KeyEventArgs^ e);
			void ControlKeyUp(Object^ sender, KeyEventArgs^ e);

		public:
			/// 初期化
			bool Initialize(Control^ canvas, Control^ keyOwner);
			/// 開放
			void Release();
			/// スタート
			bool Start();
			/// ストップ
			bool Stop();
		};
		// ----------------------------------------------------------------------------------------------------
	}
}
