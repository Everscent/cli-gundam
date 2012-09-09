#pragma once

namespace RX78_2
{
	namespace DirectX
	{
		using namespace System;
		using namespace System::IO;
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
			IndexBuffer^ index;
			Texture^ texture;
			Material material;
			Mesh^ mesh;
			VertexBuffer^ xyzLineVertex;
			Vector3 trans;
			Vector3 scale;
			array<ExtendedMaterial>^ materials;
			array<Texture^>^ textures;
			array<bool>^ keys;
			float lensPosRadius;
			float lensPosTheta;
			float lensPosPhi;
			float rotate;
			Point oldMousePoint;
			BackgroundWorker^ backWorker;

			static initonly array<short>^ vertexIndices;

		/**
		 * コンストラクタ
		 */
		public:
			DirectX3D();
			static DirectX3D();

		/**
		 * メソッド
		 */
		private:
			void CreateInputEvent(Control^ keyOwner, Control^ mouseOwner);
			bool CreateDevice();
			void CreateFont();
			void CreateSquarePolygon();
			void CreateCubePolygon();
			bool CreateMesh(String^ xfileName);
			void CreateXYZLine();
			void SetCamera();
			void SetLight();
			void MoveLight();
			void InputKey();
			void DoLoopProcess();
			void Draw();
			void DrawSquarePolygon();
			void DrawCubePolygon();
			void DrawMesh();
			void DrawXYZLine();
			void DrawText();
			void BackWorkerDoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
			void ControlKeyDown(Object^ sender, KeyEventArgs^ e);
			void ControlKeyUp(Object^ sender, KeyEventArgs^ e);
			void ControlMouseMove(Object^ sender, MouseEventArgs^ e);

		public:
			/// 初期化
			bool Initialize(Control^ canvas, Control^ keyOwner, Control^ mouseOwner);
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
