#include "StdAfx.h"
#include "ReportCommand.h"

using namespace RX78_2;
using namespace RX78_2::Report;

/**
 * レポート編集コマンド（抽象クラス）
 */
ReportCommand::ReportCommand(ReportList ^report)
{
	this->report = report;
}
// ----------------------------------------------------------------------------------------------------

ReportEventArgs^ ReportCommand::GetEventArgs()
{
	ReportEventArgs^ args = gcnew ReportEventArgs();
	args->Section = this->report->Section;
	return args;
}
// ----------------------------------------------------------------------------------------------------

/**
 * レポート編集コマンド（編集）
 */
ReportEdit::ReportEdit(ReportList ^report, System::Drawing::Point point, System::String ^value)
	: ReportCommand(report)
{
	this->point = point;
	this->newValue = value;
	ReportItem^ item = this->report->Items[this->point.Y];
	this->oldValue = item->GetValue(this->point.X);
}
// ----------------------------------------------------------------------------------------------------

bool ReportEdit::Execute()
{
	ReportItem^ item = this->report->Items[this->point.Y];
	return item->SetValue(this->point.X, this->newValue);
}
// ----------------------------------------------------------------------------------------------------

bool ReportEdit::Undo()
{
	ReportItem^ item = this->report->Items[this->point.Y];
	return item->SetValue(this->point.X, this->oldValue);
}
// ----------------------------------------------------------------------------------------------------

ReportEventArgs^ ReportEdit::GetEventArgs()
{
	ReportEventArgs^ args = ReportCommand::GetEventArgs();
	args->IsEdit = true;
	args->Point = this->point;
	args->OldValue = this->oldValue;
	args->NewValue = this->newValue;
	return args;
}
// ----------------------------------------------------------------------------------------------------

/**
 * レポート編集コマンド（挿入）
 */
ReportInsert::ReportInsert(ReportList ^report, System::Drawing::Point point, System::String ^value)
	: ReportCommand(report)
{
	this->point = point;
	this->value = value;
}
// ----------------------------------------------------------------------------------------------------

bool ReportInsert::Execute()
{
	ReportItem^ item = this->report->Items[this->point.Y];
	if (this->point.X == item->Count)
	{
		item->Add(this->value);
		return true;
	}
	else if (this->point.X < item->Count)
	{
		return item->Insert(this->point.X ,this->value);
	}
	return false;
}
// ----------------------------------------------------------------------------------------------------

bool ReportInsert::Undo()
{
	ReportItem^ item = this->report->Items[this->point.Y];
	return item->RemoveAt(this->point.X);
}
// ----------------------------------------------------------------------------------------------------

ReportEventArgs^ ReportInsert::GetEventArgs()
{
	ReportEventArgs^ args = ReportCommand::GetEventArgs();
	args->Point = this->point;
	return args;
}
// ----------------------------------------------------------------------------------------------------

/**
 * レポート編集コマンド（削除）
 */
ReportRemove::ReportRemove(RX78_2::Report::ReportList ^report, System::Drawing::Point point)
	: ReportCommand(report)
{
	this->point = point;
	ReportItem^ item = this->report->Items[this->point.Y];
	this->value = item->GetValue(this->point.X);
}
// ----------------------------------------------------------------------------------------------------

bool ReportRemove::Execute()
{
	ReportItem^ item = this->report->Items[this->point.Y];
	return item->RemoveAt(this->point.X);
}
// ----------------------------------------------------------------------------------------------------

bool ReportRemove::Undo()
{
	ReportItem^ item = this->report->Items[this->point.Y];
	if (this->point.X == item->Count)
	{
		item->Add(this->value);
		return true;
	}
	else if (this->point.X < item->Count)
	{
		return item->Insert(this->point.X ,this->value);
	}
	return false;
}
// ----------------------------------------------------------------------------------------------------

ReportEventArgs^ ReportRemove::GetEventArgs()
{
	ReportEventArgs^ args = ReportCommand::GetEventArgs();
	args->Point = this->point;
	return args;
}
// ----------------------------------------------------------------------------------------------------

/**
 * レポート編集コマンド（ステップ挿入）
 */
ReportInsertStep::ReportInsertStep(RX78_2::Report::ReportList ^report, int index, RX78_2::Report::ReportItem ^item)
	: ReportCommand(report)
{
	this->index = index;
	this->item = item;
}
// ----------------------------------------------------------------------------------------------------

bool ReportInsertStep::Execute()
{
	if (this->index == this->report->Items->Count)
	{
		this->report->Add(this->item);
		return true;
	}
	else if (this->index < this->report->Items->Count)
	{
		return this->report->Insert(this->index, this->item);
	}
	return false;
}
// ----------------------------------------------------------------------------------------------------

bool ReportInsertStep::Undo()
{
	return this->report->Remove(this->item);
}
// ----------------------------------------------------------------------------------------------------

ReportEventArgs^ ReportInsertStep::GetEventArgs()
{
	ReportEventArgs^ args = ReportCommand::GetEventArgs();
	args->Point = Point(-1, this->index);
	return args;
}
// ----------------------------------------------------------------------------------------------------

/**
 * レポート編集コマンド（ステップ削除）
 */
ReportRemoveStep::ReportRemoveStep(RX78_2::Report::ReportList ^report, int index)
	: ReportCommand(report)
{
	this->index = index;
	this->item = this->report->Items[index];
}
// ----------------------------------------------------------------------------------------------------

bool ReportRemoveStep::Execute()
{
	return this->report->Remove(this->item);	
}
// ----------------------------------------------------------------------------------------------------

bool ReportRemoveStep::Undo()
{
	if (this->index == this->report->Items->Count)
	{
		this->report->Add(this->item);
		return true;
	}
	else if (this->index < this->report->Items->Count)
	{
		return this->report->Insert(this->index, this->item);
	}
	return false;
}
// ----------------------------------------------------------------------------------------------------

ReportEventArgs^ ReportRemoveStep::GetEventArgs()
{
	ReportEventArgs^ args = ReportCommand::GetEventArgs();
	args->Point = Point(-1, this->index);
	return args;
}
// ----------------------------------------------------------------------------------------------------
