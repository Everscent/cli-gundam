#include "StdAfx.h"
#include "Deruderu.h"

using namespace RX78_2::DirectX;

/**
 * ƒ‰ƒ“ƒ_ƒ€ˆÚ“®ƒLƒ…[ƒu
 */
Deruderu::Deruderu(Microsoft::DirectX::Direct3D::Device ^device)
{
	this->shadowMaterial.Diffuse = Color::FromArgb(128, 0, 0, 0);
	this->shadowMaterial.Ambient = Color::FromArgb(128, 0, 0, 0);
	this->initHeight = 2.0f;

	this->mesh = nullptr;
	this->materials = nullptr;
	this->textures = nullptr;

	this->scale = Vector3(0.5f, 0.5f, 0.5f);
	this->location = Vector3::Empty;
	this->rotate = 0.0f;
	this->heightAngle = 0.0f;
	this->keys = gcnew List<Keys>;
}
// ----------------------------------------------------------------------------------------------------

bool Deruderu::Initialize(Microsoft::DirectX::Direct3D::Device ^device)
{
	System::Reflection::Assembly^ assembly = System::Reflection::Assembly::GetExecutingAssembly();
	System::Resources::ResourceManager^ resources = gcnew System::Resources::ResourceManager("RX78_2.RX78_2", assembly);
	array<Byte>^ bytes = safe_cast<array<Byte>^>(resources->GetObject("DeruderuXFile"));
	MemoryStream^ stream = gcnew MemoryStream(bytes);
	this->mesh = Mesh::FromStream(stream, MeshFlags::Managed, device, this->materials);

	if ((this->mesh->VertexFormat & VertexFormats::Normal) == VertexFormats::None)
	{
		Mesh^ temp = this->mesh->Clone(this->mesh->Options.Value, this->mesh->VertexFormat | VertexFormats::Normal, device);
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
					this->textures[i] = TextureLoader::FromStream(device, stream);
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

void Deruderu::InputKeyDown(System::Windows::Forms::Keys key)
{
	if (this->keys->IndexOf(key) == -1)
	{
		this->keys->Add(key);
	}
}
// ----------------------------------------------------------------------------------------------------

void Deruderu::InputKeyUp(System::Windows::Forms::Keys key)
{
	if (this->keys->IndexOf(key) != -1)
	{
		this->keys->Remove(key);
	}
}
// ----------------------------------------------------------------------------------------------------

void Deruderu::Move(Device ^device)
{
	if (this->keys->IndexOf(Keys::Down) != -1)
	{
		this->location -= Vector3::TransformCoordinate(Vector3(0.0f, 0.0f, -0.1f), Matrix::RotationY(Geometry::DegreeToRadian(this->rotate)));
	}
	if (this->keys->IndexOf(Keys::Up) != -1)
	{
		this->location += Vector3::TransformCoordinate(Vector3(0.0f, 0.0f, -0.1f), Matrix::RotationY(Geometry::DegreeToRadian(this->rotate)));
	}
	if (this->keys->IndexOf(Keys::Left) != -1)
	{
		this->rotate -= 1.0f;
	}
	if (this->keys->IndexOf(Keys::Right) != -1)
	{
		this->rotate += 1.0f;
	}

	this->heightAngle += 3.0f;
	if (360.0f <= this->heightAngle)
	{
		this->heightAngle -= 360.0f;
	}
	this->location.Y = this->initHeight + static_cast<float>(System::Math::Sin(Geometry::DegreeToRadian(this->heightAngle)) / 2.0f);
}
// ----------------------------------------------------------------------------------------------------

void Deruderu::Draw(Device ^device)
{
	Matrix matrix = Matrix::Identity;
	// Å‰‚ÉŠg‘åk¬
	matrix *= Matrix::Scaling(this->scale);
	// ‰ñ“]
	matrix *= Matrix::RotationY(Geometry::DegreeToRadian(this->rotate));
	// ÅŒã‚ÉˆÚ“®
	matrix *= Matrix::Translation(this->location);

	device->SetTransform(TransformType::World, matrix);

	for (int i = 0; i < this->materials->Length; i++)
	{
		device->SetTexture(0, this->textures[i]);
		device->Material = this->materials[i].Material3D;
		this->mesh->DrawSubset(i);
	}
}
// ----------------------------------------------------------------------------------------------------

void Deruderu::DrawShadow(Microsoft::DirectX::Direct3D::Device ^device, Microsoft::DirectX::Vector3 lightingLocation, Microsoft::DirectX::Plane plane)
{
	Matrix matrix = Matrix::Identity;
	matrix *= Matrix::Scaling(this->scale);
	matrix *= Matrix::RotationY(Geometry::DegreeToRadian(this->rotate));
	matrix *= Matrix::Translation(this->location);
	Matrix shadowMtrix = Matrix::Identity;
	Vector4 lightingLocationV4 = Vector4(lightingLocation.X - this->location.X, lightingLocation.Y - this->location.Y, lightingLocation.Z - this->location.Z, 0);
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

	for (int i = 1; i < this->materials->Length; i++)
	{
		this->mesh->DrawSubset(i);
	}

	device->RenderState->AlphaBlendEnable = false;
	device->RenderState->StencilEnable = false;
}
// ----------------------------------------------------------------------------------------------------
