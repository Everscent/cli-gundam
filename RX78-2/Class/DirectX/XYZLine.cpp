#include "StdAfx.h"
#include "XYZLine.h"

using namespace RX78_2::DirectX;

/**
 * XYZü
 */
XYZLine::XYZLine(Microsoft::DirectX::Direct3D::Device ^device, float length)
{
	this->vertex = gcnew VertexBuffer(
		CustomVertex::PositionColored::typeid, 6, device, Usage::None, CustomVertex::PositionColored::Format, Pool::Managed);

	array<CustomVertex::PositionColored>^ vertices = gcnew array<CustomVertex::PositionColored>(6);
	vertices[0] = CustomVertex::PositionColored(0.0f, 0.f, 0.0f, Color::Red.ToArgb());
	vertices[1] = CustomVertex::PositionColored(length, 0.0f, 0.0f, Color::Red.ToArgb());
	vertices[2] = CustomVertex::PositionColored(0.0f, 0.0f, 0.0f, Color::Green.ToArgb());
	vertices[3] = CustomVertex::PositionColored(0.0f, length, 0.0f, Color::Green.ToArgb());
	vertices[4] = CustomVertex::PositionColored(0.0f, 0.0f, 0.0f, Color::Blue.ToArgb());
	vertices[5] = CustomVertex::PositionColored(0.0f, 0.0f, length, Color::Blue.ToArgb());

	GraphicsStream^ stream = this->vertex->Lock(0, 0, LockFlags::None);
	stream->Write(vertices);
	this->vertex->Unlock();
	delete stream;
}
// ----------------------------------------------------------------------------------------------------

void XYZLine::Draw(Device ^device)
{
#ifdef _DEBUG
	device->RenderState->Lighting = false;

	device->SetTransform(TransformType::World, Matrix::Identity);
	device->SetStreamSource(0, this->vertex, 0);
	device->VertexFormat = CustomVertex::PositionColored::Format;
	device->DrawPrimitives(PrimitiveType::LineList, 0, 3);

	device->RenderState->Lighting = true;
#endif
}
// ----------------------------------------------------------------------------------------------------

void XYZLine::DrawShadow(Microsoft::DirectX::Direct3D::Device ^device, Microsoft::DirectX::Vector3 lightingLocation, Microsoft::DirectX::Plane plane)
{
	// ‰e‚È‚µ
}
// ----------------------------------------------------------------------------------------------------
