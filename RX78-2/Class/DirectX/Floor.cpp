#include "StdAfx.h"
#include "Floor.h"

using namespace RX78_2::DirectX;

/**
 * °
 */
Floor::Floor(Microsoft::DirectX::Direct3D::Device ^device, float size, System::Drawing::Color color1, System::Drawing::Color color2)
{
	this->material1.Diffuse = color1;
	this->material1.Ambient = color1;
	this->material2.Diffuse = color2;
	this->material2.Ambient = color2;

	array<CustomVertex::PositionNormal>^ vertices1 = gcnew array<CustomVertex::PositionNormal>(4 * (this->TILE_COUNT * 2) * (this->TILE_COUNT * 2) / 2);
	array<CustomVertex::PositionNormal>^ vertices2 = gcnew array<CustomVertex::PositionNormal>(4 * (this->TILE_COUNT * 2) * (this->TILE_COUNT * 2) / 2);
	const float length = size / this->TILE_COUNT;
	const Vector3 normal = Vector3(0.0f, 1.0f, 0.0f);

	int index1 = 0;
	int index2 = 0;
	for (int x = 0; x < this->TILE_COUNT * 2; x++)
	{
		for (int z = 0; z < this->TILE_COUNT * 2; z++)
		{
			if ((x % 2 == 0 && z % 2 == 0) || (x % 2 == 1 && z % 2 == 1))
			{
				vertices1[index1++] = CustomVertex::PositionNormal(Vector3(-size + length * x		, -0.01f, size - length * z), normal);
				vertices1[index1++] = CustomVertex::PositionNormal(Vector3(-size + length * (x + 1)	, -0.01f, size - length * z), normal);
				vertices1[index1++] = CustomVertex::PositionNormal(Vector3(-size + length * x		, -0.01f, size - length * (z + 1)), normal);
				vertices1[index1++] = CustomVertex::PositionNormal(Vector3(-size + length * (x + 1)	, -0.01f, size - length * (z + 1)), normal);
			}
			else
			{
				vertices2[index2++] = CustomVertex::PositionNormal(Vector3(-size + length * x		, -0.01f, size - length * z), normal);
				vertices2[index2++] = CustomVertex::PositionNormal(Vector3(-size + length * (x + 1)	, -0.01f, size - length * z), normal);
				vertices2[index2++] = CustomVertex::PositionNormal(Vector3(-size + length * x		, -0.01f, size - length * (z + 1)), normal);
				vertices2[index2++] = CustomVertex::PositionNormal(Vector3(-size + length * (x + 1)	, -0.01f, size - length * (z + 1)), normal);
			}
		}
	}

	this->vertex1 = gcnew VertexBuffer(
		CustomVertex::PositionNormal::typeid, vertices1->Length, device, Usage::None, CustomVertex::PositionColored::Format, Pool::Managed);
	this->vertex2 = gcnew VertexBuffer(
		CustomVertex::PositionNormal::typeid, vertices2->Length, device, Usage::None, CustomVertex::PositionColored::Format, Pool::Managed);

	GraphicsStream^ stream1 = this->vertex1->Lock(0, 0, LockFlags::None);
	stream1->Write(vertices1);
	this->vertex1->Unlock();
	delete stream1;

	GraphicsStream^ stream2 = this->vertex2->Lock(0, 0, LockFlags::None);
	stream2->Write(vertices2);
	this->vertex2->Unlock();
	delete stream2;
}
// ----------------------------------------------------------------------------------------------------

void Floor::Draw(Device ^device)
{
	device->RenderState->StencilEnable = true;
	device->RenderState->StencilFunction = Compare::Always;
	device->RenderState->StencilPass = StencilOperation::Replace;
	device->RenderState->ReferenceStencil = 0;

	device->SetTransform(TransformType::World, Matrix::Identity);
	device->VertexFormat = CustomVertex::PositionNormal::Format;

	const int loopMax = this->TILE_COUNT * 2 * this->TILE_COUNT * 2 / 2;
	device->SetStreamSource(0, this->vertex1, 0);
	device->Material = this->material1;
	for (int i = 0; i < loopMax; i++)
	{
		device->DrawPrimitives(PrimitiveType::TriangleStrip, 4 * i, 2);	
	}

	device->SetStreamSource(0, this->vertex2, 0);
	device->Material = this->material2;
	for (int i = 0; i < loopMax; i++)
	{
		device->DrawPrimitives(PrimitiveType::TriangleStrip, 4 * i, 2);	
	}

	device->RenderState->StencilEnable = false;
}
// ----------------------------------------------------------------------------------------------------

void Floor::DrawShadow(Microsoft::DirectX::Direct3D::Device ^device, Microsoft::DirectX::Vector3 lightingLocation, Microsoft::DirectX::Plane plane)
{
	// ‰e‚È‚µ
}
// ----------------------------------------------------------------------------------------------------
