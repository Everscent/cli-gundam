#pragma once

#include "ConfigFile.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace RX78_2
{
	/// <summary>
	/// SetTimerForm の概要
	///
	/// 警告: このクラスの名前を変更する場合、このクラスが依存するすべての .resx ファイルに関連付けられた
	///          マネージ リソース コンパイラ ツールに対して 'Resource File Name' プロパティを
	///          変更する必要があります。この変更を行わないと、
	///          デザイナと、このフォームに関連付けられたローカライズ済みリソースとが、
	///          正しく相互に利用できなくなります。
	/// </summary>
	public ref class SetTimerForm : public System::Windows::Forms::Form
	{
	private: DateTime endTime;		///< 終了時間
	private: ConfigFile^ config;	///< コンフィグファイル

	private: System::Windows::Forms::RadioButton^  radioTime;
	private: System::Windows::Forms::RadioButton^  radioSpan;
	private: System::Windows::Forms::Button^  buttonOk;
	private: System::Windows::Forms::Button^  buttonCancel;
	private: System::Windows::Forms::NumericUpDown^  updownHour;
	private: System::Windows::Forms::NumericUpDown^  updownMin;
	private: System::Windows::Forms::NumericUpDown^  updownSec;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  labelHour;
	private: System::Windows::Forms::Label^  labelMin;
	private: System::Windows::Forms::Label^  labelSec;

	public:
		SetTimerForm(RX78_2::ConfigFile^ config)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクタ コードを追加します
			//
			this->Initialize(config);
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~SetTimerForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// 必要なデザイナ変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナ サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディタで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->radioTime = (gcnew System::Windows::Forms::RadioButton());
			this->radioSpan = (gcnew System::Windows::Forms::RadioButton());
			this->buttonOk = (gcnew System::Windows::Forms::Button());
			this->buttonCancel = (gcnew System::Windows::Forms::Button());
			this->updownHour = (gcnew System::Windows::Forms::NumericUpDown());
			this->updownMin = (gcnew System::Windows::Forms::NumericUpDown());
			this->updownSec = (gcnew System::Windows::Forms::NumericUpDown());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->labelHour = (gcnew System::Windows::Forms::Label());
			this->labelMin = (gcnew System::Windows::Forms::Label());
			this->labelSec = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->updownHour))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->updownMin))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->updownSec))->BeginInit();
			this->SuspendLayout();
			// 
			// radioTime
			// 
			this->radioTime->AutoSize = true;
			this->radioTime->Location = System::Drawing::Point(236, 12);
			this->radioTime->Name = L"radioTime";
			this->radioTime->Size = System::Drawing::Size(71, 16);
			this->radioTime->TabIndex = 5;
			this->radioTime->TabStop = true;
			this->radioTime->Text = L"時刻指定";
			this->radioTime->UseVisualStyleBackColor = true;
			this->radioTime->CheckedChanged += gcnew System::EventHandler(this, &SetTimerForm::radioTime_CheckedChanged);
			// 
			// radioSpan
			// 
			this->radioSpan->AutoSize = true;
			this->radioSpan->Location = System::Drawing::Point(236, 34);
			this->radioSpan->Name = L"radioSpan";
			this->radioSpan->Size = System::Drawing::Size(71, 16);
			this->radioSpan->TabIndex = 6;
			this->radioSpan->TabStop = true;
			this->radioSpan->Text = L"時間指定";
			this->radioSpan->UseVisualStyleBackColor = true;
			this->radioSpan->CheckedChanged += gcnew System::EventHandler(this, &SetTimerForm::radioSpan_CheckedChanged);
			// 
			// buttonOk
			// 
			this->buttonOk->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->buttonOk->Location = System::Drawing::Point(60, 113);
			this->buttonOk->Name = L"buttonOk";
			this->buttonOk->Size = System::Drawing::Size(75, 23);
			this->buttonOk->TabIndex = 3;
			this->buttonOk->Text = L"OK";
			this->buttonOk->UseVisualStyleBackColor = true;
			this->buttonOk->Click += gcnew System::EventHandler(this, &SetTimerForm::buttonOk_Click);
			// 
			// buttonCancel
			// 
			this->buttonCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->buttonCancel->Location = System::Drawing::Point(184, 113);
			this->buttonCancel->Name = L"buttonCancel";
			this->buttonCancel->Size = System::Drawing::Size(75, 23);
			this->buttonCancel->TabIndex = 4;
			this->buttonCancel->Text = L"キャンセル";
			this->buttonCancel->UseVisualStyleBackColor = true;
			// 
			// updownHour
			// 
			this->updownHour->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->updownHour->Location = System::Drawing::Point(53, 72);
			this->updownHour->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {23, 0, 0, 0});
			this->updownHour->Name = L"updownHour";
			this->updownHour->Size = System::Drawing::Size(50, 26);
			this->updownHour->TabIndex = 0;
			this->updownHour->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// updownMin
			// 
			this->updownMin->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->updownMin->Location = System::Drawing::Point(134, 72);
			this->updownMin->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {59, 0, 0, 0});
			this->updownMin->Name = L"updownMin";
			this->updownMin->Size = System::Drawing::Size(50, 26);
			this->updownMin->TabIndex = 1;
			this->updownMin->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// updownSec
			// 
			this->updownSec->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->updownSec->Location = System::Drawing::Point(215, 72);
			this->updownSec->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {59, 0, 0, 0});
			this->updownSec->Name = L"updownSec";
			this->updownSec->Size = System::Drawing::Size(50, 26);
			this->updownSec->TabIndex = 2;
			this->updownSec->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(109, 71);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(19, 27);
			this->label1->TabIndex = 8;
			this->label1->Text = L":";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Arial", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(190, 71);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(19, 27);
			this->label2->TabIndex = 9;
			this->label2->Text = L":";
			// 
			// labelHour
			// 
			this->labelHour->AutoSize = true;
			this->labelHour->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->labelHour->Location = System::Drawing::Point(66, 51);
			this->labelHour->Name = L"labelHour";
			this->labelHour->Size = System::Drawing::Size(24, 18);
			this->labelHour->TabIndex = 7;
			this->labelHour->Text = L"hh";
			// 
			// labelMin
			// 
			this->labelMin->AutoSize = true;
			this->labelMin->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->labelMin->Location = System::Drawing::Point(142, 51);
			this->labelMin->Name = L"labelMin";
			this->labelMin->Size = System::Drawing::Size(34, 18);
			this->labelMin->TabIndex = 10;
			this->labelMin->Text = L"mm";
			// 
			// labelSec
			// 
			this->labelSec->AutoSize = true;
			this->labelSec->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(177)));
			this->labelSec->Location = System::Drawing::Point(228, 51);
			this->labelSec->Name = L"labelSec";
			this->labelSec->Size = System::Drawing::Size(24, 18);
			this->labelSec->TabIndex = 11;
			this->labelSec->Text = L"ss";
			// 
			// SetTimerForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::GhostWhite;
			this->ClientSize = System::Drawing::Size(319, 148);
			this->Controls->Add(this->labelSec);
			this->Controls->Add(this->labelMin);
			this->Controls->Add(this->labelHour);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->updownSec);
			this->Controls->Add(this->updownMin);
			this->Controls->Add(this->updownHour);
			this->Controls->Add(this->buttonCancel);
			this->Controls->Add(this->buttonOk);
			this->Controls->Add(this->radioSpan);
			this->Controls->Add(this->radioTime);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"SetTimerForm";
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"RX78-2 Timer";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->updownHour))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->updownMin))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->updownSec))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	/// 初期化
	private: void Initialize(RX78_2::ConfigFile^ config)
			 {
				 this->config = config;

				 if (this->config->GetTimerIsSpan())
				 {
					 this->radioSpan->Checked = true;
				 }
				 else
				 {
					 this->radioTime->Checked = true;
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// OKボタン
	private: System::Void buttonOk_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 String^ separator = ":";
				 DateTime now = DateTime::Now;
				 if (this->radioTime->Checked)
				 {
					 this->endTime = DateTime(now.Year, now.Month, now.Day, static_cast<int>(this->updownHour->Value), static_cast<int>(this->updownMin->Value), static_cast<int>(this->updownSec->Value));
					 if (0 < now.CompareTo(this->endTime))
					 {
						 this->endTime = this->endTime.AddDays(1.0);
					 }
					 String^ value = String::Format("{0:D2}:{1:D2}:{2:D2}", static_cast<int>(this->updownHour->Value), static_cast<int>(this->updownMin->Value), static_cast<int>(this->updownSec->Value));
					 this->config->SetTimerIsSpan(false);
					 this->config->SetTimerDateTime(value);
				 }
				 else
				 {
					 TimeSpan span = TimeSpan(static_cast<int>(this->updownHour->Value), static_cast<int>(this->updownMin->Value), static_cast<int>(this->updownSec->Value));
					 this->endTime = now.Add(span);
					 String^ value = String::Format("{0:D2}:{1:D2}:{2:D2}", static_cast<int>(this->updownHour->Value), static_cast<int>(this->updownMin->Value), static_cast<int>(this->updownSec->Value));
					 this->config->SetTimerIsSpan(true);
					 this->config->SetTimerTimeSpan(value);
				 }
				 this->endTime = this->endTime.AddMilliseconds(-(this->endTime.Millisecond));
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// ラジオボタン 時刻
	private: System::Void radioTime_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
			 {
				 String^ value = this->config->GetTimerDateTime();
				 array<wchar_t>^ separators = { ':' };
				 array<String^>^ split = value->Split(separators);
				 if (split->Length == 3)
				 {
					 this->updownHour->Value = int::Parse(split[0]);
					 this->updownMin->Value = int::Parse(split[1]);
					 this->updownSec->Value = int::Parse(split[2]);
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// ラジオボタン 時間
	private: System::Void radioSpan_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
			 {
				 String^ value = this->config->GetTimetTimeSpan();
				 array<wchar_t>^ separators = { ':' };
				 array<String^>^ split = value->Split(separators);
				 if (split->Length == 3)
				 {
					 this->updownHour->Value = int::Parse(split[0]);
					 this->updownMin->Value = int::Parse(split[1]);
					 this->updownSec->Value = int::Parse(split[2]);
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// 設定時刻取得
	public: property DateTime EndTime
			{
				DateTime get() { return this->endTime; }
			}
			// ----------------------------------------------------------------------------------------------------
	};
}
