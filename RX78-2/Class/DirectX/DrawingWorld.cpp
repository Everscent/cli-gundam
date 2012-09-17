#include "StdAfx.h"
#include "DrawingWorld.h"
#include "Lighting.h"
#include "Camera.h"
#include "DrawingText.h"
#include "XYZLine.h"
#include "Floor.h"
#include "RandomMovingCube.h"
#include "Deruderu.h"

using namespace RX78_2::DirectX;

/**
 * •`‰æ¢ŠE
 */
DrawingWorld::DrawingWorld(System::Windows::Forms::Control ^canvas, System::Windows::Forms::Control ^keyOwner, System::Windows::Forms::Control ^mouseOwner)
{
	this->canvas = canvas;
	this->device = nullptr;
	this->backWorker = gcnew BackgroundWorker();
	this->backWorker->WorkerSupportsCancellation = true;
	this->backWorker->DoWork += gcnew DoWorkEventHandler(this, &DrawingWorld::BackWorkerDoWork);
	keyOwner->KeyDown += gcnew KeyEventHandler(this, &DrawingWorld::ControlKeyDown);
	keyOwner->KeyUp += gcnew KeyEventHandler(this, &DrawingWorld::ControlKeyUp);
	mouseOwner->MouseMove += gcnew MouseEventHandler(this, &DrawingWorld::ControlMouseMove);
	mouseOwner->MouseWheel += gcnew MouseEventHandler(this, &DrawingWorld::ControlMouseWheel);

	this->movingItems = gcnew List<IMovable^>;
	this->drawingItems = gcnew List<IDrawable^>;

	this->lighting = nullptr;
	this->camera = nullptr;
	this->floor = nullptr;
	this->deruderu = nullptr;
	this->text = nullptr;
}
// ----------------------------------------------------------------------------------------------------

bool DrawingWorld::CreateInstance()
{
	PresentParameters^ param = gcnew PresentParameters();
	param->Windowed = true;
	param->SwapEffect = SwapEffect::Discard;
	param->EnableAutoDepthStencil = true;
	param->AutoDepthStencilFormat = DepthFormat::D24S8;

	try
	{
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

	this->lighting = gcnew Lighting(this->device, 12.0f, 0, Color::Gold);
	this->camera = gcnew Camera(16.0f);
	this->floor = gcnew Floor(this->device, 10.0f, Color::DarkGreen, Color::DarkGray);
	this->deruderu = gcnew Deruderu(this->device);
	this->text = gcnew DrawingText(this->device, 12, "‚l‚r ƒSƒVƒbƒN");
	XYZLine^ xyzLine = gcnew XYZLine(this->device, 20.0f);

	this->movingItems->Add(this->lighting);
	this->movingItems->Add(this->camera);
	this->movingItems->Add(this->deruderu);

	this->drawingItems->Add(this->lighting);
	this->drawingItems->Add(xyzLine);
	this->drawingItems->Add(floor);
	this->drawingItems->Add(this->deruderu);

	Random^ random = gcnew Random();
	for (int i = 0; i < 10; i++)
	{
		RandomMovingCube^ cube = gcnew RandomMovingCube(this->device, Vector3(10.0f, 10.0f, 10.0f), 1.0f, random);
		this->movingItems->Add(cube);
		this->drawingItems->Add(cube);
	}

	if (!this->deruderu->Initialize(this->device)) return false;

	return true;
}
// ----------------------------------------------------------------------------------------------------

void DrawingWorld::DoLoopProcess()
{
	this->Move();

	this->device->Clear(ClearFlags::Target | ClearFlags::ZBuffer | ClearFlags::Stencil, Color::LightSteelBlue, 1.0f, 0xFFFFFFFF);

	this->device->BeginScene();
	this->Draw();
	this->device->EndScene();

	this->device->Present();
}
// ----------------------------------------------------------------------------------------------------

void DrawingWorld::Move()
{
	for each (IMovable^ item in this->movingItems)
	{
		item->Move(this->device);
	}
}
// ----------------------------------------------------------------------------------------------------

void DrawingWorld::Draw()
{
	for each (IDrawable^ item in this->drawingItems)
	{
		item->Draw(this->device);
		item->DrawShadow(this->device, this->lighting->Location, this->floor->PlaneInfomation);
	}

	int lineIndex = 0;
	this->text->Write("Camera setting", lineIndex++, Color::Crimson);
	this->text->Write("ƒÆF" + this->camera->Theta + "‹", lineIndex++, Color::Crimson);
	this->text->Write("ƒÓF" + this->camera->Phi + "‹", lineIndex++, Color::Crimson);
	this->text->Write("‚qF" + String::Format("{0:F2}", this->camera->Radius), lineIndex++, Color::Crimson);
	this->text->Write(String::Empty, lineIndex++, Color::Crimson);
	this->text->Write("Deruderu", lineIndex++, Color::Crimson);
	this->text->Write("[©¨]‰ñ“] [ª«]ˆÚ“®", lineIndex++, Color::Crimson);
	this->text->Write("ˆÊ’uF" + String::Format("{0:F4}", this->deruderu->Location.X) + ", " + 
		String::Format("{0:F4}", this->deruderu->Location.Y) + ", " + String::Format("{0:F4}", this->deruderu->Location.Z), lineIndex++, Color::Crimson);
	this->text->Write("‰ñ“]F" + this->deruderu->Rotate + "‹", lineIndex++, Color::Crimson);
}
// ----------------------------------------------------------------------------------------------------

void DrawingWorld::ControlKeyDown(System::Object ^sender, System::Windows::Forms::KeyEventArgs ^e)
{
	this->deruderu->InputKeyDown(e->KeyCode);
}
// ----------------------------------------------------------------------------------------------------

void DrawingWorld::ControlKeyUp(System::Object ^sender, System::Windows::Forms::KeyEventArgs ^e)
{
	this->deruderu->InputKeyUp(e->KeyCode);
}
// ----------------------------------------------------------------------------------------------------

void DrawingWorld::ControlMouseMove(System::Object ^sender, System::Windows::Forms::MouseEventArgs ^e)
{
	this->camera->InputMouseMove(e->Location, e->Button);
}
// ----------------------------------------------------------------------------------------------------

void DrawingWorld::ControlMouseWheel(System::Object ^sender, System::Windows::Forms::MouseEventArgs ^e)
{
	this->camera->InputMouseWheel(e->Delta);
}
// ----------------------------------------------------------------------------------------------------

void DrawingWorld::BackWorkerDoWork(System::Object ^sender, System::ComponentModel::DoWorkEventArgs ^e)
{
	while (true)
	{
		if (this->backWorker->CancellationPending)
		{
			e->Cancel = true;
			return;
		}

		this->DoLoopProcess();

		System::Threading::Thread::Sleep(1);
	}
}
// ----------------------------------------------------------------------------------------------------

bool DrawingWorld::Initialize()
{
	if (!this->CreateInstance()) return false;

	// ŽË‰e•ÏŠ·‚ðÝ’è
	this->device->Transform->Projection = Matrix::PerspectiveFovLH(Geometry::DegreeToRadian(60.0f),
		static_cast<float>(this->device->Viewport.Width) / static_cast<float>(this->device->Viewport.Height), 1.0f, 100.0f);

	// ƒJƒŠƒ“ƒO‚ð–³Œø‚É‚µ‚Äƒ|ƒŠƒSƒ“‚Ì— ‚à•`‰æ‚·‚é
	this->device->RenderState->CullMode = Cull::None;

	return true;
}
// ----------------------------------------------------------------------------------------------------

void DrawingWorld::Release()
{
	this->drawingItems->Clear();
	this->movingItems->Clear();

	delete this->text;
	delete this->deruderu;
	delete this->floor;
	delete this->camera;
	delete this->lighting;

	if (this->device != nullptr)
	{
		delete this->device;
		this->device = nullptr;
	}
}
// ----------------------------------------------------------------------------------------------------

bool DrawingWorld::Start()
{
	if (this->device == nullptr || this->backWorker->IsBusy) return false;

	this->backWorker->RunWorkerAsync();
	return true;
}
// ----------------------------------------------------------------------------------------------------

bool DrawingWorld::Stop()
{
	if (!this->backWorker->IsBusy) return false;

	this->backWorker->CancelAsync();
	return true;
}
// ----------------------------------------------------------------------------------------------------
