#include "StdAfx.h"
#include "DirectX3D.h"

using namespace RX78_2::DirectX;

/**
 * DirectX3D
 */
DirectX3D::DirectX3D()
{
	this->canvas = nullptr;
	this->device = nullptr;
	this->vertex = nullptr;
}
// ----------------------------------------------------------------------------------------------------

DirectX3D::~DirectX3D()
{
	if (this->vertex != nullptr)
	{
		delete this->vertex;
	}

	if (this->device != nullptr)
	{
		delete this->device;
	}
}
// ----------------------------------------------------------------------------------------------------

bool DirectX3D::CreateDevice()
{
	PresentParameters^ param = gcnew PresentParameters();
	// true ウィンドウモード, false フルスクリーン
	param->Windowed = true;
	// スワップ効果．とりあえずDiscardを指定．
	param->SwapEffect = SwapEffect::Discard;
	// 深度ステンシルバッファ．3Dでは前後関係があるので通常true．
	param->EnableAutoDepthStencil = true;
	// 自動深度ステンシル サーフェイスのフォーマット．
	param->AutoDepthStencilFormat = DepthFormat::D16;

	try
	{
		// ハードウェアによる頂点処理
		this->device = gcnew Device(0, DeviceType::Hardware, this->canvas->Handle, CreateFlags::HardwareVertexProcessing, param);
	}
	catch (DirectXException^)
	{
		try
		{
			this->device = gcnew Device(0, DeviceType::Hardware, this->canvas->Handle, CreateFlags::SoftwareVertexProcessing, param);
		}
		catch (DirectXException^)
		{
			try
			{
				this->device = gcnew Device(0, DeviceType::Reference, this->canvas->Handle, CreateFlags::SoftwareVertexProcessing, param);
			}
			catch (DirectXException^)
			{
				return false;
			}
		}
	}

	// ビュー変換行列を設定
	this->device->Transform->View = Matrix::LookAtLH(Vector3(0.0f, 0.0f, -10.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));

	// 射影変換を設定
	this->device->Transform->Projection = Matrix::PerspectiveFovLH(Geometry::DegreeToRadian(60.0f),
		static_cast<float>(this->device->Viewport.Width) / static_cast<float>(this->device->Viewport.Height), 1.0f, 100.0f);

	return true;
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::DrawCore()
{
	this->device->SetStreamSource(0, this->vertex, 0);
	this->device->VertexFormat = CustomVertex::PositionColored::Format;
	this->device->DrawPrimitives(PrimitiveType::TriangleList, 0, 1);
}
// ----------------------------------------------------------------------------------------------------

bool DirectX3D::Initialize(System::Windows::Forms::Control ^canvas)
{
	this->canvas = canvas;

	if (!this->CreateDevice())
	{
		return false;
	}

	// 三角形ポリゴンを表示するための頂点バッファを作成
	this->vertex = gcnew VertexBuffer(CustomVertex::PositionColored::typeid, 3, this->device, Usage::None, CustomVertex::PositionColored::Format, Pool::Managed);
	
	array<CustomVertex::PositionColored>^ vertices = gcnew array<CustomVertex::PositionColored>(3);
	vertices[0] = CustomVertex::PositionColored(0.0f, 5.0f, 0.0f, Color::Red.ToArgb());
	vertices[1] = CustomVertex::PositionColored(4.0f, -3.0f, 0.0f, Color::Blue.ToArgb());
	vertices[2] = CustomVertex::PositionColored(-4.0f, -3.0f, 0.0f, Color::Green.ToArgb());

	GraphicsStream^ stream = this->vertex->Lock(0, 0, LockFlags::None);
	stream->Write(vertices);
	this->vertex->Unlock();
	delete stream;

	// ライトを無効
	this->device->RenderState->Lighting = false;

	return true;
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::Draw()
{
	this->device->Clear(ClearFlags::Target | ClearFlags::ZBuffer, Color::DarkBlue, 1.0f, 0);

	this->device->BeginScene();

	this->DrawCore();

	this->device->EndScene();

	this->device->Present();
}
// ----------------------------------------------------------------------------------------------------
