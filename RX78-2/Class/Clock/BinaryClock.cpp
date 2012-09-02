#include "StdAfx.h"
#include "BinaryClock.h"

using namespace RX78_2::Clock;

/**
 * バイナリクロック
 */
BinaryClock::BinaryClock(cli::array<System::Windows::Forms::Control ^,2> ^sec, cli::array<System::Windows::Forms::Control ^,2> ^min, cli::array<System::Windows::Forms::Control ^,2> ^hour)
{
	this->panelsSec = sec;
	this->panelsMin = min;
	this->panelsHour = hour;

	this->onColor = Color::MediumBlue;
	this->offColor = Color::Snow;
}
// ----------------------------------------------------------------------------------------------------

String^ BinaryClock::Display()
{
	DateTime now = DateTime::Now;

	array<String^>^ sec = { Convert::ToString(now.Second % 10, 2), Convert::ToString(now.Second / 10, 2) };
	array<String^>^ min = { Convert::ToString(now.Minute % 10, 2), Convert::ToString(now.Minute / 10, 2) };
	array<String^>^ hour = { Convert::ToString(now.Hour % 10, 2), Convert::ToString(now.Hour / 10, 2) };

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (this->panelsSec[i, j] != nullptr)
			{
				if (j < sec[i]->Length)
				{
					if (sec[i]->Substring(sec[i]->Length - j - 1, 1)->Equals("1"))
					{
						this->panelsSec[i, j]->BackColor = this->onColor;
					}
					else
					{
						this->panelsSec[i, j]->BackColor = this->offColor;
					}
				}
				else
				{
					this->panelsSec[i, j]->BackColor = this->offColor;
				}
			}
			if (this->panelsMin[i, j] != nullptr)
			{
				if (j < min[i]->Length)
				{
					if (min[i]->Substring(min[i]->Length - j - 1, 1)->Equals("1"))
					{
						this->panelsMin[i, j]->BackColor = this->onColor;
					}
					else
					{
						this->panelsMin[i, j]->BackColor = this->offColor;
					}
				}
				else
				{
					this->panelsMin[i, j]->BackColor = this->offColor;
				}
			}
			if (this->panelsHour[i, j] != nullptr)
			{
				if (j < hour[i]->Length)
				{
					if (hour[i]->Substring(hour[i]->Length - j - 1, 1)->Equals("1"))
					{
						this->panelsHour[i, j]->BackColor = this->onColor;
					}
					else
					{
						this->panelsHour[i, j]->BackColor = this->offColor;
					}
				}
				else
				{
					this->panelsHour[i, j]->BackColor = this->offColor;
				}
			}
		}
	}

	return now.ToLongTimeString();
}
// ----------------------------------------------------------------------------------------------------

TimeSpan BinaryClock::GetTimerSpan()
{
	return this->endTime.Subtract(DateTime::Now.AddSeconds(-1.0));
}
// ----------------------------------------------------------------------------------------------------
