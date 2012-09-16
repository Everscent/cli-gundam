#include "StdAfx.h"
#include "Lighting.h"

using namespace RX78_2::DirectX;

/**
 * Æ–¾
 */
Lighting::Lighting(Microsoft::DirectX::Direct3D::Device ^device, float distance, int index, System::Drawing::Color color)
{
	this->distance = distance;
	this->index = index;
	this->mesh = Mesh::Sphere(device, 0.2f, 16, 16);
	this->material.Diffuse = color;
	this->material.Ambient = color;
	this->location = Vector3::Empty;

	device->RenderState->Lighting = true;
	device->Lights[index]->Type = LightType::Directional;
	device->Lights[index]->Diffuse = Color::White;
	device->Lights[index]->Ambient = Color::FromArgb(255, 192, 192, 192);
	device->Lights[index]->Enabled = true;
	device->Lights[index]->Update();
}
// ----------------------------------------------------------------------------------------------------

void Lighting::Move(Microsoft::DirectX::Direct3D::Device ^device)
{
	Matrix matrix = Matrix::RotationY(Environment::TickCount / 1000.0f);
	device->Lights[this->index]->Direction = Vector3::TransformCoordinate(Vector3::Normalize(Vector3(1.0f, -1.5f, 0.0f)), matrix);
	device->Lights[this->index]->Update();

	Vector3 directon = device->Lights[this->index]->Direction;
	this->location = Vector3(-directon.X * this->distance, -directon.Y * this->distance, -directon.Z * this->distance);
}
// ----------------------------------------------------------------------------------------------------

void Lighting::Draw(Microsoft::DirectX::Direct3D::Device ^device)
{
	device->Material = this->material;
	device->SetTransform(TransformType::World, Matrix::Translation(this->location));
	this->mesh->DrawSubset(0);
}
// ----------------------------------------------------------------------------------------------------

void Lighting::DrawShadow(Microsoft::DirectX::Direct3D::Device ^device, Microsoft::DirectX::Vector3 lightingLocation, Microsoft::DirectX::Plane plane)
{
	// ‰e‚È‚µ
}
// ----------------------------------------------------------------------------------------------------
