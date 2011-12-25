#include "StdAfx.h"
#include "TetrisDrawAPI.h"

using namespace Anaheim;
using namespace Anaheim::Tetris::View;

/**
 * ƒeƒgƒŠƒX•`‰æAPI
 */
GraphicsTetrisDrawAPI::GraphicsTetrisDrawAPI(Control ^canvas)
{
	this->canvas = canvas;
	this->canvas->Resize += gcnew System::EventHandler(this, &GraphicsTetrisDrawAPI::CanvasResize);
	this->bitmap = gcnew Bitmap(canvas->Width, canvas->Height);
	this->graphics = nullptr;
}
// ----------------------------------------------------------------------------------------------------

void GraphicsTetrisDrawAPI::CanvasResize(System::Object ^sender, System::EventArgs ^e)
{
	if (canvas->Width == 0 || canvas->Height == 0) return;

	delete this->bitmap;
	this->bitmap = gcnew Bitmap(canvas->Width, canvas->Height);
}
// ----------------------------------------------------------------------------------------------------

void GraphicsTetrisDrawAPI::Clear(System::Drawing::Graphics ^graphics)
{
	SolidBrush^ brush = gcnew SolidBrush(this->canvas->BackColor);
	graphics->FillRectangle(brush, 0, 0, this->canvas->Width, this->canvas->Height);
}
// ----------------------------------------------------------------------------------------------------

void GraphicsTetrisDrawAPI::BeginDraw()
{
	this->graphics = System::Drawing::Graphics::FromImage(this->bitmap);
	this->Clear(this->graphics);
}
// ----------------------------------------------------------------------------------------------------

void GraphicsTetrisDrawAPI::DrawLine(System::Drawing::Color color, float width, System::Drawing::PointF point1, System::Drawing::PointF point2)
{
	if (this->graphics == nullptr) return;

	Pen^ pen = gcnew Pen(color, width);
	this->graphics->DrawLine(pen, point1, point2);
}
// ----------------------------------------------------------------------------------------------------

void GraphicsTetrisDrawAPI::DrawRectangle(System::Drawing::Color color, float width, System::Drawing::PointF point, System::Drawing::SizeF size)
{
	if (this->graphics == nullptr) return;

	Pen^ pen = gcnew Pen(color, width);
	this->graphics->DrawRectangle(pen, point.X, point.Y, size.Width, size.Height);
}
// ----------------------------------------------------------------------------------------------------

void GraphicsTetrisDrawAPI::FillRectangle(System::Drawing::Color color, System::Drawing::PointF point, System::Drawing::SizeF size)
{
	if (this->graphics == nullptr) return;

	SolidBrush^ brush = gcnew SolidBrush(color);
	this->graphics->FillRectangle(brush, point.X , point.Y, size.Width, size.Height);
}
// ----------------------------------------------------------------------------------------------------

void GraphicsTetrisDrawAPI::FillRectangleGradation(System::Drawing::Color color1, System::Drawing::Color color2, System::Drawing::PointF point, System::Drawing::SizeF size)
{
	if (this->graphics == nullptr) return;

	LinearGradientBrush^ gbrush = gcnew LinearGradientBrush(point, PointF(point.X + size.Width, point.Y + size.Width), color1, color2);
	this->graphics->FillRectangle(gbrush, point.X , point.Y, size.Width, size.Height);
}
// ----------------------------------------------------------------------------------------------------

void GraphicsTetrisDrawAPI::EndDraw()
{
	Graphics^ gr = this->canvas->CreateGraphics();
	gr->DrawImage(this->bitmap, 0, 0);

	this->graphics = nullptr;
}
// ----------------------------------------------------------------------------------------------------

void GraphicsTetrisDrawAPI::Clear()
{
	Graphics^ graphics = this->canvas->CreateGraphics();
	this->Clear(graphics);
}
// ----------------------------------------------------------------------------------------------------
