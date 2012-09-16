#include "StdAfx.h"
#include "Camera.h"

using namespace RX78_2::DirectX;

/**
 * カメラ
 */
Camera::Camera(float radius)
{
	this->radius = radius;
	this->locationTheta = 300.0f;
	this->locationPhi = 30.0f;
	this->targetY = 2.0f;
	this->oldMouseLocation = Point::Empty;
}
// ----------------------------------------------------------------------------------------------------

void Camera::InputMouseMove(System::Drawing::Point mouseLocation, System::Windows::Forms::MouseButtons button)
{
	if (button == MouseButtons::Left)
	{
		this->locationTheta -= mouseLocation.X - this->oldMouseLocation.X;
		this->locationPhi += mouseLocation.Y - this->oldMouseLocation.Y;
		
		if (90.0f <= this->locationPhi)
		{
			this->locationPhi = 89.9999f;
		}
		else if (this->locationPhi <= -90.0f)
		{
			this->locationPhi = -89.9999f;
		}
	}
	this->oldMouseLocation = mouseLocation;
}
// ----------------------------------------------------------------------------------------------------

void Camera::InputMouseWheel(int delta)
{
	this->radius -= delta / 480.0f;
	if (this->radius < 4.0f)
	{
		this->radius = 4.0f;
	}
}
// ----------------------------------------------------------------------------------------------------

void Camera::Move(Microsoft::DirectX::Direct3D::Device ^device)
{
	// レンズの位置を三次元極座標で変換
	float theta = Geometry::DegreeToRadian(this->locationTheta);
	float phi = Geometry::DegreeToRadian(this->locationPhi);
	Vector3 lensPosition = Vector3(static_cast<float>(this->radius * Math::Cos(theta) * Math::Cos(phi)),
		static_cast<float>(this->radius * Math::Sin(phi)), static_cast<float>(this->radius * Math::Sin(theta) * Math::Cos(phi)));

	// ビュー変換行列を左手座標系ビュー行列で設定する
	device->Transform->View = Matrix::LookAtLH(lensPosition, Vector3(0.0f, targetY, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
}
// ----------------------------------------------------------------------------------------------------
