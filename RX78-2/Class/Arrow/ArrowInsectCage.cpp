#include "StdAfx.h"
#include "ArrowInsectCage.h"

using namespace RX78_2;
using namespace RX78_2::Arrow;

/**
 * Arrow’
 */
ArrowInsectCage::ArrowInsectCage(System::Windows::Forms::Control ^canvas, int count)
{
	this->canvas = canvas;
	this->random = gcnew Random();
	this->insects = gcnew array<Insect^>(count);
	for each (Insect^% insect in this->insects)
	{
		insect = CreateInsect();
	}

	this->drawing = gcnew ArrowDrawing(this->canvas);
}
// ----------------------------------------------------------------------------------------------------

Insect^ ArrowInsectCage::CreateInsect()
{
	int num = random->Next(0, 20);

	if (num % 20 == 0)
	{
		return gcnew CharInsect(this->canvas, this->random);
	}
	else
	{
		return gcnew Insect(this->canvas, this->random);
	}
}
// ----------------------------------------------------------------------------------------------------

void ArrowInsectCage::Move()
{
	for each (Insect^ insect in this->insects)
	{
		insect->Move();
	}
}
// ----------------------------------------------------------------------------------------------------

void ArrowInsectCage::Draw()
{
	this->drawing->BeginDraw();

	for each (Insect^ insect in this->insects)
	{
		this->drawing->Draw(insect);
	}

	this->drawing->EndDraw();
}
// ----------------------------------------------------------------------------------------------------

void ArrowInsectCage::Reset()
{
	for each (Insect^% insect in this->insects)
	{
		insect = CreateInsect();
	}
}
// ----------------------------------------------------------------------------------------------------
