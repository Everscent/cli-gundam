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
	this->index = nullptr;
	this->texture = nullptr;
	this->scale = Vector3(1.0f, 1.0f, 1.0f);
	this->material = Material();
	this->mesh = nullptr;
	this->xyzLineVertex = nullptr;
	this->trans = Vector3(0.0f, 1.5f, 0.0f);
	this->materials = nullptr;
	this->textures = nullptr;
	this->keys = gcnew array<bool>(256);
	this->lensPosRadius = 20.0f;
	this->lensPosTheta = 270.0f;
	this->lensPosPhi = 0.0f;
	this->rotate = 0.0f;
	this->oldMousePoint = Point::Empty;
	this->backWorker = gcnew BackgroundWorker();
	this->backWorker->WorkerSupportsCancellation = true;
	this->backWorker->DoWork += gcnew DoWorkEventHandler(this, &DirectX3D::BackWorkerDoWork);
}
// ----------------------------------------------------------------------------------------------------

static DirectX3D::DirectX3D()
{
	DirectX3D::vertexIndices = gcnew array<short> { 2, 0, 1, 1, 3, 2, 4, 0, 2, 2, 6, 4, 5, 1, 0, 0, 4, 5, 7, 3, 1, 1, 5, 7, 6, 2, 3, 3, 7, 6, 4, 6, 7, 7, 5, 4 };
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::CreateInputEvent(System::Windows::Forms::Control ^keyOwner, System::Windows::Forms::Control ^mouseOwner)
{
	keyOwner->KeyDown += gcnew KeyEventHandler(this, &DirectX3D::ControlKeyDown);
	keyOwner->KeyUp += gcnew KeyEventHandler(this, &DirectX3D::ControlKeyUp);
	mouseOwner->MouseMove += gcnew MouseEventHandler(this, &DirectX3D::ControlMouseMove);
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

	fd.Height = 12;
	fd.FaceName = "ＭＳ ゴシック";

	this->font = gcnew Microsoft::DirectX::Direct3D::Font(this->device, fd);
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::CreateSquarePolygon()
{
	this->vertex = gcnew VertexBuffer(
		CustomVertex::PositionColored::typeid, 4, this->device, Usage::None, CustomVertex::PositionColored::Format, Pool::Managed);
	
	array<CustomVertex::PositionColored>^ vertices = gcnew array<CustomVertex::PositionColored>(4);
	vertices[0] = CustomVertex::PositionColored(-4.0f, 4.0f, 0.0f, Color::Red.ToArgb());
	vertices[1] = CustomVertex::PositionColored(4.0f, 4.0f, 0.0f, Color::Blue.ToArgb());
	vertices[2] = CustomVertex::PositionColored(-4.0f, -4.0f, 0.0f, Color::Green.ToArgb());
	vertices[3] = CustomVertex::PositionColored(4.0f, -4.0f, 0.0f, Color::Yellow.ToArgb());

	GraphicsStream^ stream = this->vertex->Lock(0, 0, LockFlags::None);
	stream->Write(vertices);
	this->vertex->Unlock();
	delete stream;
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::CreateCubePolygon()
{
	this->vertex = gcnew VertexBuffer(
		CustomVertex::PositionNormal::typeid, 8, this->device, Usage::None, CustomVertex::PositionNormal::Format, Pool::Managed);

	array<CustomVertex::PositionNormal>^ vertices = gcnew array<CustomVertex::PositionNormal>(8);
	vertices[0] = CustomVertex::PositionNormal(Vector3(-2.0f, 2.0f, 2.0f), Vector3::Normalize(Vector3(-1.0f, 1.0f, 1.0f)));
	vertices[1] = CustomVertex::PositionNormal(Vector3(2.0f, 2.0f, 2.0f), Vector3::Normalize(Vector3(1.0f, 1.0f, 1.0f)));
	vertices[2] = CustomVertex::PositionNormal(Vector3(-2.0f, 2.0f, -2.0f), Vector3::Normalize(Vector3(-1.0f, 1.0f, -1.0f)));
	vertices[3] = CustomVertex::PositionNormal(Vector3(2.0f, 2.0f, -2.0f), Vector3::Normalize(Vector3(1.0f, 1.0f, -1.0f)));
	vertices[4] = CustomVertex::PositionNormal(Vector3(-2.0f, -2.0f, 2.0f), Vector3::Normalize(Vector3(-1.0f, -1.0f, 1.0f)));
	vertices[5] = CustomVertex::PositionNormal(Vector3(2.0f, -2.0f, 2.0f), Vector3::Normalize(Vector3(1.0f, -1.0f, 1.0f)));
	vertices[6] = CustomVertex::PositionNormal(Vector3(-2.0f, -2.0f, -2.0f), Vector3::Normalize(Vector3(-1.0f, -1.0f, -1.0f)));
	vertices[7] = CustomVertex::PositionNormal(Vector3(2.0f, -2.0f, -2.0f), Vector3::Normalize(Vector3(1.0f, -1.0f, -1.0f)));

	GraphicsStream^ stream = this->vertex->Lock(0, 0, LockFlags::None);
	stream->Write(vertices);
	this->vertex->Unlock();

	this->index = gcnew IndexBuffer(this->device, 12 * 3 * 2, Usage::WriteOnly, Pool::Managed, true);

	stream = this->index->Lock(0, 0, LockFlags::None);
	stream->Write(vertexIndices);
	this->index->Unlock();
	delete stream;
}
// ----------------------------------------------------------------------------------------------------

bool DirectX3D::CreateMesh(System::String ^xfileName)
{
	System::Reflection::Assembly^ assembly = System::Reflection::Assembly::GetExecutingAssembly();
	System::Resources::ResourceManager^ resources = gcnew System::Resources::ResourceManager("RX78_2.RX78_2", assembly);
	array<Byte>^ bytes = safe_cast<array<Byte>^>(resources->GetObject(xfileName));
	MemoryStream^ stream = gcnew MemoryStream(bytes);
	this->mesh = Mesh::FromStream(stream, MeshFlags::Managed, this->device, this->materials);


	if ((this->mesh->VertexFormat & VertexFormats::Normal) == VertexFormats::None)
	{
		Mesh^ temp = this->mesh->Clone(this->mesh->Options.Value, this->mesh->VertexFormat | VertexFormats::Normal, this->device);
		temp->ComputeNormals();
		delete this->mesh;
		this->mesh = temp;
	}

	if (1 <= this->materials->Length)
	{
		this->textures = gcnew array<Texture^>(this->materials->Length);

		for (int i = 0; i < this->materials->Length; i++)
		{
			this->textures[i] = nullptr;

			if ((this->materials[i].TextureFilename != nullptr) && (1 <= this->materials[i].TextureFilename->Length))
			{
				try
				{
					String^ resourceName = System::IO::Path::GetFileNameWithoutExtension(this->materials[i].TextureFilename);
					Bitmap^ bitmap = safe_cast<Bitmap^>(resources->GetObject(resourceName));
					ImageConverter^ imgconv = gcnew ImageConverter();
					array<Byte>^ bytes = safe_cast<array<Byte>^>(imgconv->ConvertTo(bitmap, array<Byte>::typeid));
					MemoryStream^ stream = gcnew MemoryStream(bytes);
					this->textures[i] = TextureLoader::FromStream(this->device, stream);
				}
				catch (DirectXException^)
				{
					return false;
				}
			}
		}
	}

	return true;
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::CreateXYZLine()
{
	this->xyzLineVertex = gcnew VertexBuffer(
		CustomVertex::PositionColored::typeid, 6, this->device, Usage::None, CustomVertex::PositionColored::Format, Pool::Managed);

	const float length = 20.0f;
	array<CustomVertex::PositionColored>^ vertices = gcnew array<CustomVertex::PositionColored>(6);
	vertices[0] = CustomVertex::PositionColored(0.0f, 0.0f, 0.0f, Color::Red.ToArgb());
	vertices[1] = CustomVertex::PositionColored(length, 0.0f, 0.0f, Color::Red.ToArgb());
	vertices[2] = CustomVertex::PositionColored(0.0f, 0.0f, 0.0f, Color::Green.ToArgb());
	vertices[3] = CustomVertex::PositionColored(0.0f, length, 0.0f, Color::Green.ToArgb());
	vertices[4] = CustomVertex::PositionColored(0.0f, 0.0f, 0.0f, Color::Blue.ToArgb());
	vertices[5] = CustomVertex::PositionColored(0.0f, 0.0f, length, Color::Blue.ToArgb());

	GraphicsStream^ stream = this->xyzLineVertex->Lock(0, 0, LockFlags::None);
	stream->Write(vertices);
	this->xyzLineVertex->Unlock();
	delete stream;
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::SetCamera()
{
	// レンズの位置を三次元極座標で変換
	float radius = this->lensPosRadius;
	float theta = Geometry::DegreeToRadian(this->lensPosTheta);
	float phi = Geometry::DegreeToRadian(this->lensPosPhi);
	Vector3 lensPosition = Vector3(static_cast<float>(radius * Math::Cos(theta) * Math::Cos(phi)),
		static_cast<float>(radius * Math::Sin(phi)), static_cast<float>(radius * Math::Sin(theta) * Math::Cos(phi)));

	// ビュー変換行列を左手座標系ビュー行列で設定する
	this->device->Transform->View = Matrix::LookAtLH(lensPosition, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));

	// 射影変換を設定
	this->device->Transform->Projection = Matrix::PerspectiveFovLH(Geometry::DegreeToRadian(60.0f),
		static_cast<float>(this->device->Viewport.Width) / static_cast<float>(this->device->Viewport.Height), 1.0f, 100.0f);
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::SetLight()
{
	this->device->Lights[0]->Type = LightType::Directional;
	this->device->Lights[0]->Direction = Vector3(1.0f, -5.0f, 2.0f);
	this->device->Lights[0]->Diffuse = Color::White;
	this->device->Lights[0]->Ambient = Color::FromArgb(255, 128, 128, 128);
	this->device->Lights[0]->Enabled = true;
	this->device->Lights[0]->Update();
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::MoveLight()
{
	Matrix matrix = Matrix::RotationY(Environment::TickCount / 1000.0f);
	this->device->Lights[0]->Direction = Vector3::TransformCoordinate(Vector3::Normalize(Vector3(1.0f, -5.0f, 2.0f)), matrix);
	this->device->Lights[0]->Update();
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::InputKey()
{
	if (this->keys[static_cast<int>(Keys::Left)])
	{
		this->rotate -= 5.0f;
	}
	if (this->keys[static_cast<int>(Keys::Right)])
	{
		this->rotate += 5.0f;
	}
	if (this->keys[static_cast<int>(Keys::Up)])
	{
		this->trans += Vector3::TransformCoordinate(Vector3(0.0f, 0.0f, -0.3f), Matrix::RotationY(Geometry::DegreeToRadian(this->rotate)));
	}
	if (this->keys[static_cast<int>(Keys::Down)])
	{
		this->trans -= Vector3::TransformCoordinate(Vector3(0.0f, 0.0f, -0.3f), Matrix::RotationY(Geometry::DegreeToRadian(this->rotate)));
	}
	if (this->keys[static_cast<int>(Keys::Z)])
	{
		this->scale.X /= 1.01f;
		this->scale.Y /= 1.01f;
		this->scale.Z /= 1.01f;
	}
	if (this->keys[static_cast<int>(Keys::A)])
	{
		this->scale *= 1.01f;
	}
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::DoLoopProcess()
{
	this->InputKey();
	this->SetCamera();

	this->MoveLight();

	this->device->Clear(ClearFlags::Target | ClearFlags::ZBuffer, Color::DarkBlue, 1.0f, 0);

	this->device->BeginScene();
	this->Draw();
	this->device->EndScene();

	this->device->Present();
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::Draw()
{
	this->DrawMesh();
	this->DrawText();
	this->DrawXYZLine();
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::DrawSquarePolygon()
{
	this->device->SetStreamSource(0, this->vertex, 0);
	this->device->VertexFormat = CustomVertex::PositionColored::Format;
	this->device->DrawPrimitives(PrimitiveType::TriangleStrip, 0, 2);
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::DrawCubePolygon()
{
	this->device->Material = this->material;
	this->device->SetStreamSource(0, this->vertex, 0);
	this->device->VertexFormat = CustomVertex::PositionNormal::Format;
	this->device->Indices = this->index;
	this->device->DrawIndexedPrimitives(PrimitiveType::TriangleList, 0, 0, 8, 0, 12);
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::DrawMesh()
{
	// モデル座標変換用マトリックスを初期化
	Matrix modelTransform = Matrix::Identity;
	// 最初に拡大縮小
	modelTransform *= Matrix::Scaling(this->scale);
	// 回転
	modelTransform *= Matrix::RotationY(Geometry::DegreeToRadian(this->rotate));
	// 最後に移動
	modelTransform *= Matrix::Translation(this->trans);

	this->device->SetTransform(TransformType::World, modelTransform);

	for (int i = 0; i < this->materials->Length; i++)
	{
		this->device->SetTexture(0, this->textures[i]);
		this->device->Material = this->materials[i].Material3D;
		this->mesh->DrawSubset(i);
	}
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::DrawXYZLine()
{
	this->device->RenderState->Lighting = false;

	this->device->SetTransform(TransformType::World, Matrix::Identity);

	this->device->SetStreamSource(0, this->xyzLineVertex, 0);
	this->device->VertexFormat = CustomVertex::PositionColored::Format;
	this->device->DrawPrimitives(PrimitiveType::LineList, 0, 3);

	this->device->RenderState->Lighting = true;
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::DrawText()
{
	this->font->DrawText(nullptr, "[←→]回転 [↑↓]移動 [ZA]拡大縮小", 0, 0, Color::White);
	this->font->DrawText(nullptr, "θ：" + this->lensPosTheta, 0, 12, Color::White);
	this->font->DrawText(nullptr, "φ：" + this->lensPosPhi, 0, 24, Color::White);
	this->font->DrawText(nullptr, "移動：" + this->trans.X + ", " + this->trans.Y + ", " + this->trans.Z, 0, 36, Color::White);
	this->font->DrawText(nullptr, "回転：" + this->rotate, 0, 48, Color::White);
	this->font->DrawText(nullptr, "拡大：" + this->scale.X, 0, 60, Color::White);
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::BackWorkerDoWork(System::Object ^sender, System::ComponentModel::DoWorkEventArgs ^e)
{
	while (true)
	{
		if (this->backWorker->CancellationPending)
		{
			e->Cancel = true;
			return;
		}

		this->DoLoopProcess();

		System::Threading::Thread::Sleep(10);
	}
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::ControlKeyDown(System::Object ^sender, System::Windows::Forms::KeyEventArgs ^e)
{
	if (static_cast<int>(e->KeyCode) < this->keys->Length)
	{
		this->keys[static_cast<int>(e->KeyCode)] = true;
	}
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::ControlKeyUp(System::Object ^sender, System::Windows::Forms::KeyEventArgs ^e)
{
	if (static_cast<int>(e->KeyCode) < this->keys->Length)
	{
		this->keys[static_cast<int>(e->KeyCode)] = false;
	}
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::ControlMouseMove(System::Object ^sender, System::Windows::Forms::MouseEventArgs ^e)
{
	if (e->Button == MouseButtons::Left)
	{
		this->lensPosTheta -= e->Location.X - this->oldMousePoint.X;
		this->lensPosPhi += e->Location.Y - this->oldMousePoint.Y;

		if (90.0f <= this->lensPosPhi)
		{
			this->lensPosPhi = 89.9999f;
		}
		else if (this->lensPosPhi <= -90.0f)
		{
			this->lensPosPhi = -89.9999f;
		}
	}

	this->oldMousePoint = e->Location;
}
// ----------------------------------------------------------------------------------------------------

bool DirectX3D::Initialize(System::Windows::Forms::Control ^canvas, System::Windows::Forms::Control ^keyOwner, System::Windows::Forms::Control ^mouseOwner)
{
	this->canvas = canvas;

	this->CreateInputEvent(keyOwner, mouseOwner);

	if (!this->CreateDevice())
	{
		return false;
	}
	
	if (!this->CreateMesh(L"DeruderuXFile"))
	{
		return false;
	}

	this->CreateFont();

	this->CreateXYZLine();

	this->SetLight();

	this->device->RenderState->NormalizeNormals = true;

	return true;
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::Release()
{
	if (this->xyzLineVertex != nullptr)
	{
		delete this->xyzLineVertex;
	}

	if (this->texture != nullptr)
	{
		for each (Texture^ texture in this->textures)
		{
			if (texture != nullptr)
			{
				delete texture;
			}
		}
	}

	if (this->mesh != nullptr)
	{
		delete this->mesh;
	}

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

	if (this->index != nullptr)
	{
		delete this->index;
		this->index = nullptr;
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

bool DirectX3D::Start()
{
	if (this->device == nullptr || this->backWorker->IsBusy) return false;

	this->backWorker->RunWorkerAsync();
	return true;
}
// ----------------------------------------------------------------------------------------------------

bool DirectX3D::Stop()
{
	if (!this->backWorker->IsBusy) return false;

	this->backWorker->CancelAsync();
	return true;
}
// ----------------------------------------------------------------------------------------------------
