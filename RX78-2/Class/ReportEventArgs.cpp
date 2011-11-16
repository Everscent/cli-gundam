#include "StdAfx.h"
#include "ReportEventArgs.h"

using namespace RX78_2;
using namespace RX78_2::Report;

/**
 * レポート編集イベントパラメータ
 */
ReportEventArgs::ReportEventArgs()
{
	this->IsUndo = true;
	this->Section = String::Empty;
	this->IsEdit = false;
	this->OldValue = nullptr;
	this->NewValue = nullptr;
}
// ----------------------------------------------------------------------------------------------------
