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
	this->font = nullptr;
	this->vertex = nullptr;
	this->texture = nullptr;
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

	return true;
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::CreateFont()
{
	FontDescription fd = FontDescription();

	fd.Height = 24;
	fd.FaceName = "ＭＳ ゴシック";

	this->font = gcnew Microsoft::DirectX::Direct3D::Font(this->device, fd);
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::SetCamera()
{
	// ビュー変換行列を設定
	this->device->Transform->View = Matrix::LookAtLH(Vector3(0.0f, 0.0f, -10.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));

	// 射影変換を設定
	this->device->Transform->Projection = Matrix::PerspectiveFovLH(Geometry::DegreeToRadian(60.0f),
		static_cast<float>(this->device->Viewport.Width) / static_cast<float>(this->device->Viewport.Height), 1.0f, 100.0f);
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::DrawCore()
{
	this->device->SetTexture(0, this->texture);
	this->device->SetStreamSource(0, this->vertex, 0);
	this->device->VertexFormat = CustomVertex::PositionTextured::Format;
	this->device->DrawPrimitives(PrimitiveType::TriangleStrip, 0, 2);

	this->font->DrawText(nullptr, "DirectX", 0, 0, Color::White);
}
// ----------------------------------------------------------------------------------------------------

bool DirectX3D::Initialize(System::Windows::Forms::Control ^canvas)
{
	this->canvas = canvas;

	if (!this->CreateDevice())
	{
		return false;
	}
	this->CreateFont();
	this->SetCamera();

	// 四角形ポリゴンを表示するための頂点バッファを作成
	this->vertex = gcnew VertexBuffer(
		CustomVertex::PositionTextured::typeid, 4, this->device, Usage::None, CustomVertex::PositionTextured::Format, Pool::Managed);
	
	array<CustomVertex::PositionTextured>^ vertices = gcnew array<CustomVertex::PositionTextured>(4);
	vertices[0] = CustomVertex::PositionTextured(-4.0f, 4.0f, 0.0f, 0.0f, 0.0f);
	vertices[1] = CustomVertex::PositionTextured(4.0f, 4.0f, 0.0f, 1.0f, 0.0f);
	vertices[2] = CustomVertex::PositionTextured(-4.0f, -4.0f, 0.0f, 0.0f, 1.0f);
	vertices[3] = CustomVertex::PositionTextured(4.0f, -4.0f, 0.0f, 1.0f, 1.0f);

	GraphicsStream^ stream = this->vertex->Lock(0, 0, LockFlags::None);
	stream->Write(vertices);
	this->vertex->Unlock();
	delete stream;

	// テクスチャー作成
	this->texture = TextureLoader::FromFile(this->device, "..\\sample_data\\SampleImage.jpg");

	// ライトを無効
	this->device->RenderState->Lighting = false;

	return true;
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::Draw()
{
	if (this->device == nullptr) return;

	this->device->Clear(ClearFlags::Target | ClearFlags::ZBuffer, Color::DarkBlue, 1.0f, 0);

	this->device->BeginScene();
	this->DrawCore();
	this->device->EndScene();

	this->device->Present();
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::Release()
{
	if (this->texture != nullptr)
	{
		delete this->texture;
		this->texture = nullptr;
	}

	if (this->vertex != nullptr)
	{
		delete this->vertex;
		this->vertex = nullptr;
	}

	if (this->font != nullptr)
	{
		delete this->font;
		this->font = nullptr;
	}

	if (this->device != nullptr)
	{
		delete this->device;
		this->device = nullptr;
	}
}
// ----------------------------------------------------------------------------------------------------
