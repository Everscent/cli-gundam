#include "StdAfx.h"
#include "RandomMovingCube.h"

using namespace RX78_2::DirectX;

/**
 * ランダム移動キューブ
 */
RandomMovingCube::RandomMovingCube(Microsoft::DirectX::Direct3D::Device ^device, Microsoft::DirectX::Vector3 range, float size, System::Random ^random)
{
	this->range = range;
	this->shadowMaterial.Diffuse = Color::FromArgb(128, 0, 0, 0);
	this->shadowMaterial.Ambient = Color::FromArgb(128, 0, 0, 0);
	this->size = size;

	this->mesh = Mesh::Box(device, size, size, size);

	this->random = random;
	double x = random->NextDouble() * range.X * 2 - range.X;
	double y = random->NextDouble() * range.Y + this->size / 2;
	double z = random->NextDouble() * range.Z * 2 - range.Z;
	this->location = Vector3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));

	this->Reset();
}
// ----------------------------------------------------------------------------------------------------

void RandomMovingCube::Reset()
{
	this->material.Diffuse = Color::FromArgb(255, this->random->Next(256), this->random->Next(256), this->random->Next(256));
	this->material.Ambient = this->material.Diffuse;

	double tx = this->random->NextDouble() * range.X * 2 - range.X;
	double ty = this->random->NextDouble() * range.Y + this->size / 2;
	double tz = this->random->NextDouble() * range.Z * 2 - range.Z;
	this->targetLocation = Vector3(static_cast<float>(tx), static_cast<float>(ty), static_cast<float>(tz));

	this->count = this->random->Next(100, 200);
	float sx = (this->targetLocation.X - this->location.X) / count;
	float sy = (this->targetLocation.Y - this->location.Y) / count;
	float sz = (this->targetLocation.Z - this->location.Z) / count;
	this->step = Vector3(sx, sy, sz);
}
// ----------------------------------------------------------------------------------------------------

void RandomMovingCube::Move(Device ^device)
{
	if (this->count <= 0)
	{
		this->Reset();
	}

	this->location.X += this->step.X;
	this->location.Y += this->step.Y;
	this->location.Z += this->step.Z;
	this->count--;
}
// ----------------------------------------------------------------------------------------------------

void RandomMovingCube::Draw(Device ^device)
{
	device->Material = this->material;
	device->SetTransform(TransformType::World, Matrix::Translation(this->location));
	this->mesh->DrawSubset(0);
}
// ----------------------------------------------------------------------------------------------------

void RandomMovingCube::DrawShadow(Microsoft::DirectX::Direct3D::Device ^device, Microsoft::DirectX::Vector3 lightingLocation, Microsoft::DirectX::Plane plane)
{
	Matrix matrix = Matrix::Identity;
	matrix *= Matrix::Translation(this->location);
	Matrix shadowMtrix = Matrix::Identity;
	Vector4 lightingLocationV4 = Vector4(lightingLocation.X, lightingLocation.Y, lightingLocation.Z, 0);
	shadowMtrix.Shadow(lightingLocationV4, plane);
	matrix *= shadowMtrix;

	device->Material = this->shadowMaterial;
	device->SetTransform(TransformType::World, matrix);

	device->RenderState->StencilEnable = true;
	device->RenderState->StencilFunction = Compare::Greater;
	device->RenderState->StencilPass = StencilOperation::Replace;
	device->RenderState->StencilFail = StencilOperation::Keep;
	device->RenderState->ReferenceStencil = 1;

	device->RenderState->AlphaBlendEnable = true;
	device->RenderState->SourceBlend = Blend::SourceAlpha;
	device->RenderState->DestinationBlend = Blend::InvSourceAlpha;

	this->mesh->DrawSubset(0);

	device->RenderState->AlphaBlendEnable = false;
	device->RenderState->StencilEnable = false;
}
// ----------------------------------------------------------------------------------------------------
