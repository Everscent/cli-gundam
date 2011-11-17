#include "StdAfx.h"
#include "ArrowUtility.h"

using namespace RX78_2;
using namespace RX78_2::Arrow;

/**
 * Arrowユーティリティ
 */
Point ArrowUtility::GetMousePoint(System::Windows::Forms::Control ^canvas)
{
	Point result = System::Windows::Forms::Cursor::Position;
	if (canvas != nullptr)
	{
		result = canvas->PointToClient(result);
	}
	return result;
}
// ----------------------------------------------------------------------------------------------------

double ArrowUtility::ConvertDegree(double degree)
{
	double result = degree;

	while (result < 0)
	{
		result += 360;
	}

	while (360 <= result)
	{
		result -= 360;
	}

	return result;
}
// ----------------------------------------------------------------------------------------------------

double ArrowUtility::GetAngle(System::Drawing::PointF point1, System::Drawing::PointF point2)
{
	PointF offset = PointF(point1.X - point2.X, point1.Y - point2.Y);
	double radian = System::Math::Atan2(offset.Y, offset.X);
	double degree = radian * 180.0 / System::Math::PI;
	return ArrowUtility::ConvertDegree(degree);
}
// ----------------------------------------------------------------------------------------------------

double ArrowUtility::GetHalfAngle(double degree1, double degree2)
{
	double degree = (degree1 + degree2) / 2;

	if (90 < System::Math::Abs(degree - degree1))
	{
		degree += 180;
	}

	return ArrowUtility::ConvertDegree(degree);
}
// ----------------------------------------------------------------------------------------------------

PointF ArrowUtility::RotatePoint(System::Drawing::PointF point, System::Drawing::PointF center, double degree)
{
	PointF offset = PointF(point.X - center.X, point.Y - center.Y);

	PointF temp;
	double radian = degree * System::Math::PI / 180.0;
	temp.X = static_cast<float>(offset.X * System::Math::Cos(radian) - offset.Y * System::Math::Sin(radian));
	temp.Y = static_cast<float>(offset.X * System::Math::Sin(radian) + offset.Y * System::Math::Cos(radian));

	return PointF(temp.X + center.X, temp.Y + center.Y);
}
// ----------------------------------------------------------------------------------------------------

PointF ArrowUtility::MovePoint(System::Drawing::PointF point, int distance, double degree)
{
	double radian = degree * System::Math::PI / 180.0;
	float distanceX = static_cast<float>(distance * System::Math::Cos(radian));
	float distanceY = static_cast<float>(distance * System::Math::Sin(radian));
	return PointF(point.X + distanceX, point.Y + distanceY);
}
// ----------------------------------------------------------------------------------------------------
