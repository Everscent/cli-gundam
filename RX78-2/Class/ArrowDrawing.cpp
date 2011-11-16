#include "StdAfx.h"
#include "ArrowDrawing.h"

using namespace RX78_2;
using namespace RX78_2::Arrow;

/**
 * Arrow•`‰æ
 */
ArrowDrawing::ArrowDrawing(System::Windows::Forms::Control ^canvas)
{
	this->canvas = canvas;
	Rectangle rect = System::Windows::Forms::Screen::PrimaryScreen->Bounds;
	this->bitmap = gcnew Bitmap(rect.Width, rect.Height);
	this->graphics = nullptr;
}
// ----------------------------------------------------------------------------------------------------

void ArrowDrawing::BeginDraw()
{
	this->graphics = System::Drawing::Graphics::FromImage(this->bitmap);

	SolidBrush^ brush = gcnew SolidBrush(this->canvas->BackColor);
	this->graphics->FillRectangle(brush, 0, 0, this->canvas->Width, this->canvas->Height);
}
// ----------------------------------------------------------------------------------------------------

void ArrowDrawing::Draw(RX78_2::Arrow::Insect ^insect)
{
	if (this->graphics == nullptr) return;

	Color color = insect->Color;
	Pen^ pen = gcnew Pen(color, 2);

	array<PointF>^ bodies = insect->GetBodyPoints();
	this->graphics->DrawPolygon(pen, bodies);

	array<PointF>^ legs = insect->GetLegPoints();
	int count = 0;
	for each (PointF leg in legs)
	{
		this->graphics->DrawLine(pen, bodies[count], leg);
		this->graphics->DrawEllipse(pen, leg.X - 1, leg.Y - 1, 2.0, 2.0);
		count++;
	}

	array<PointF>^ arrow = insect->GetArrowPoints();
	this->graphics->DrawLine(pen, arrow[0], arrow[1]);
	this->graphics->DrawLine(pen, arrow[1], arrow[2]);
	this->graphics->DrawLine(pen, arrow[1], arrow[3]);
}
// ----------------------------------------------------------------------------------------------------

void ArrowDrawing::EndDraw()
{
	Graphics^ gr = this->canvas->CreateGraphics();
	gr->DrawImage(this->bitmap, 0, 0);

	this->graphics = nullptr;
}
// ----------------------------------------------------------------------------------------------------
