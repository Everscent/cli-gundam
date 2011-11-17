#include "StdAfx.h"
#include "ReportEditor.h"

using namespace RX78_2;
using namespace RX78_2::Report;

/**
 * レポート編集クラス
 */
ReportEditor::ReportEditor(RX78_2::Report::ReportBook ^report)
{
	this->report = report;
	this->commands = gcnew List<ReportCommand^>;
	this->currentIndex = -1;
}
// ----------------------------------------------------------------------------------------------------

bool ReportEditor::AddCommand(RX78_2::Report::ReportCommand ^command)
{
	if (command->Execute())
	{
		if (this->currentIndex != this->commands->Count - 1)
		{
			this->commands->RemoveRange(this->currentIndex + 1, this->commands->Count - (this->currentIndex + 1));
		}
		this->commands->Add(command);
		this->currentIndex++;

		ReportEventArgs^ e = command->GetEventArgs();
		e->IsUndo = false;
		this->OnEndAction(e);

		return true;
	}
	return false;

}
// ----------------------------------------------------------------------------------------------------

bool ReportEditor::Edit(System::String ^section, System::Drawing::Point point, System::String ^value)
{
	ReportList^ list = this->report->Select(section);
	ReportItem^ item = list->Items[point.Y];

	if (item->Count <= point.X) return false;
	if (item->GetValue(point.X)->Equals(value)) return false;

	return this->AddCommand(gcnew ReportEdit(list, point, value));
}
// ----------------------------------------------------------------------------------------------------

bool ReportEditor::Insert(System::String ^section, System::Drawing::Point point, System::String ^value)
{
	ReportList^ list = this->report->Select(section);
	ReportItem^ item = list->Items[point.Y];

	if (item->Count < point.X) return false;

	return this->AddCommand(gcnew ReportInsert(list, point, value));
}
// ----------------------------------------------------------------------------------------------------

bool ReportEditor::Remove(System::String ^section, System::Drawing::Point point)
{
	ReportList^ list = this->report->Select(section);
	ReportItem^ item = list->Items[point.Y];

	if (item->Count <= point.X) return false;

	return this->AddCommand(gcnew ReportRemove(list, point));
}
// ----------------------------------------------------------------------------------------------------

bool ReportEditor::InsertStep(System::String ^section, int index, RX78_2::Report::ReportItem ^item)
{
	ReportList^ list = this->report->Select(section);
	if (list->Items->Count < index) return false;

	return this->AddCommand(gcnew ReportInsertStep(list, index, item));
}
// ----------------------------------------------------------------------------------------------------

bool ReportEditor::RemoveStep(System::String ^section, int index)
{
	ReportList^ list = this->report->Select(section);
	if (list->Items->Count <= index) return false;

	return this->AddCommand(gcnew ReportRemoveStep(list, index));
}
// ----------------------------------------------------------------------------------------------------

bool ReportEditor::CanUndo()
{
	return (-1 < this->currentIndex) ? true : false;
}
// ----------------------------------------------------------------------------------------------------

bool ReportEditor::CanRedo()
{
	return (this->currentIndex < this->commands->Count - 1) ? true : false;
}
// ----------------------------------------------------------------------------------------------------

bool ReportEditor::Undo()
{
	if (!this->CanUndo()) return false;

	ReportCommand^ command = this->commands[this->currentIndex];
	if (command->Undo())
	{
		this->currentIndex--;

		ReportEventArgs^ e = command->GetEventArgs();
		e->IsUndo = true;
		this->OnEndAction(e);

		return true;
	}
	return false;
}
// ----------------------------------------------------------------------------------------------------

bool ReportEditor::Redo()
{
	if (!this->CanRedo()) return false;

	ReportCommand^ command = this->commands[this->currentIndex + 1];
	if (command->Execute())
	{
		this->currentIndex++;

		ReportEventArgs^ e = command->GetEventArgs();
		e->IsUndo = false;
		this->OnEndAction(e);

		return true;
	}
	return false;
}
// ----------------------------------------------------------------------------------------------------

void ReportEditor::Clear()
{
	this->commands->Clear();
	this->currentIndex = -1;
}
// ----------------------------------------------------------------------------------------------------

void ReportEditor::OnEndAction(RX78_2::Report::ReportEventArgs ^e)
{
	this->EndAction(this, e);
}
// ----------------------------------------------------------------------------------------------------
