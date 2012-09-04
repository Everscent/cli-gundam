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
	this->keys = gcnew array<bool>(256);
	this->lensPosTheta = 270.0f;
	this->lensPosPhi = 0.0f;
	this->backWorker = gcnew BackgroundWorker();
	this->backWorker->WorkerSupportsCancellation = true;
	this->backWorker->DoWork += gcnew DoWorkEventHandler(this, &DirectX3D::BackWorkerDoWork);
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::CreateInputEvent(System::Windows::Forms::Control ^keyOwner)
{
	keyOwner->KeyDown += gcnew KeyEventHandler(this, &DirectX3D::ControlKeyDown);
	keyOwner->KeyUp += gcnew KeyEventHandler(this, &DirectX3D::ControlKeyUp);
}
// ----------------------------------------------------------------------------------------------------

bool DirectX3D::CreateDevice()
{
	PresentParameters^ param = gcnew PresentParameters();
	// true �E�B���h�E���[�h, false �t���X�N���[��
	param->Windowed = true;
	// �X���b�v���ʁD�Ƃ肠����Discard���w��D
	param->SwapEffect = SwapEffect::Discard;
	// �[�x�X�e���V���o�b�t�@�D3D�ł͑O��֌W������̂Œʏ�true�D
	param->EnableAutoDepthStencil = true;
	// �����[�x�X�e���V�� �T�[�t�F�C�X�̃t�H�[�}�b�g�D
	param->AutoDepthStencilFormat = DepthFormat::D16;

	try
	{
		// �n�[�h�E�F�A�ɂ�钸�_����
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
	fd.FaceName = "�l�r �S�V�b�N";

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

void DirectX3D::SetCamera()
{
	// �r���[�ϊ��s���ݒ�
	this->device->Transform->View = Matrix::LookAtLH(Vector3(0.0f, 0.0f, -10.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));

	// �ˉe�ϊ���ݒ�
	this->device->Transform->Projection = Matrix::PerspectiveFovLH(Geometry::DegreeToRadian(60.0f),
		static_cast<float>(this->device->Viewport.Width) / static_cast<float>(this->device->Viewport.Height), 1.0f, 100.0f);
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::DoLoopProcess()
{
	if (this->keys[static_cast<int>(Keys::Left)])
	{
		this->lensPosTheta -= 3.0f;
	}
	if (this->keys[static_cast<int>(Keys::Right)])
	{
		this->lensPosTheta += 3.0f;
	}
	if (this->keys[static_cast<int>(Keys::Up)])
	{
		this->lensPosPhi += 3.0f;
	}
	if (this->keys[static_cast<int>(Keys::Down)])
	{
		this->lensPosPhi -= 3.0f;
	}

	// �ӂɊւ��Ă͐���������
	if (this->lensPosPhi >= 90.0f)
	{
		this->lensPosPhi = 89.9999f;
	}
	else if (this->lensPosPhi <= -90.0f)
	{
		this->lensPosPhi = -89.9999f;
	}

	// �����Y�̈ʒu���O�����ɍ��W�ŕϊ�
	float radius = 10.0f;
	float theta = Geometry::DegreeToRadian(this->lensPosTheta);
	float phi = Geometry::DegreeToRadian(this->lensPosPhi);
	Vector3 lensPosition = Vector3(static_cast<float>(radius * Math::Cos(theta) * Math::Cos(phi)),
		static_cast<float>(radius * Math::Sin(phi)), static_cast<float>(radius * Math::Sin(theta) * Math::Cos(phi)));

	// �r���[�ϊ��s���������W�n�r���[�s��Őݒ肷��
	this->device->Transform->View = Matrix::LookAtLH(lensPosition, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));

	this->device->Clear(ClearFlags::Target | ClearFlags::ZBuffer, Color::DarkBlue, 1.0f, 0);

	this->device->BeginScene();
	this->Draw();
	this->device->EndScene();

	this->device->Present();
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::Draw()
{
	this->DrawSquarePolygon();

	this->font->DrawText(nullptr, "[����]�J�����̏㉺��]  [����]�J�����̍��E��]", 0, 0, Color::White);
	this->font->DrawText(nullptr, "�ƁF" + this->lensPosTheta, 0, 12, Color::White);
	this->font->DrawText(nullptr, "�ӁF" + this->lensPosPhi, 0, 24, Color::White);
}
// ----------------------------------------------------------------------------------------------------

void DirectX3D::DrawSquarePolygon()
{
	this->device->SetStreamSource(0, this->vertex, 0);
	this->device->VertexFormat = CustomVertex::PositionColored::Format;
	this->device->DrawPrimitives(PrimitiveType::TriangleStrip, 0, 2);
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

bool DirectX3D::Initialize(System::Windows::Forms::Control ^canvas, System::Windows::Forms::Control ^keyOwner)
{
	this->canvas = canvas;

	this->CreateInputEvent(keyOwner);

	if (!this->CreateDevice())
	{
		return false;
	}
	this->CreateFont();

	this->CreateSquarePolygon();

	// �J�����̐ݒ�
	this->SetCamera();

	// ���C�g�𖳌�
	this->device->RenderState->Lighting = false;

	// �J�����O�𖳌��ɂ��ă|���S���̗����`�悷��
	this->device->RenderState->CullMode = Cull::None;


	return true;
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
