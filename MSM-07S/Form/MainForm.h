#pragma once

#include "ConfigFile.h"

namespace MSM_07S 
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Anaheim::UdpSocket;

	/// <summary>
	/// MainForm �̊T�v
	///
	/// �x��: ���̃N���X�̖��O��ύX����ꍇ�A���̃N���X���ˑ����邷�ׂĂ� .resx �t�@�C���Ɋ֘A�t����ꂽ
	///          �}�l�[�W ���\�[�X �R���p�C�� �c�[���ɑ΂��� 'Resource File Name' �v���p�e�B��
	///          �ύX����K�v������܂��B���̕ύX���s��Ȃ��ƁA
	///          �f�U�C�i�ƁA���̃t�H�[���Ɋ֘A�t����ꂽ���[�J���C�Y�ς݃��\�[�X�Ƃ��A
	///          ���������݂ɗ��p�ł��Ȃ��Ȃ�܂��B
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{

#pragma region �t�B�[���h

	private: ConfigFile^ config;			///< �R���t�B�O�t�@�C��
	private: UdpClientSocket^ udpClient;	///< UDP�N���C�A���g

	private: System::Windows::Forms::Label^  labelLocalIp;
	private: System::Windows::Forms::Label^  labelLocalPort;
	private: System::Windows::Forms::Label^  labelRemoteIp;
	private: System::Windows::Forms::Label^  labelRemotePort;
	private: System::Windows::Forms::TextBox^  textLocalIp;
	private: System::Windows::Forms::TextBox^  textLocalPort;
	private: System::Windows::Forms::TextBox^  textRemoteIp;
	private: System::Windows::Forms::TextBox^  textRemotePort;
	private: System::Windows::Forms::Button^  buttonStop;
	private: System::Windows::Forms::Button^  buttonStart;
	private: System::Windows::Forms::RadioButton^  radioDefault;
	private: System::Windows::Forms::RadioButton^  radioUtf8;
	private: System::Windows::Forms::RadioButton^  radioAscii;
	private: System::Windows::Forms::Button^  buttonClear;
	private: System::Windows::Forms::Label^  labelMessage;
	private: System::Windows::Forms::ListBox^  listMessage;
	private: System::Windows::Forms::Button^  buttonSend;
	private: System::Windows::Forms::TextBox^  textMessage;

#pragma endregion

	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: �����ɃR���X�g���N�^ �R�[�h��ǉ����܂�
			//
			this->Initialize();
		}

	protected:
		/// <summary>
		/// �g�p���̃��\�[�X�����ׂăN���[���A�b�v���܂��B
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// �K�v�ȃf�U�C�i�ϐ��ł��B
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �f�U�C�i �T�|�[�g�ɕK�v�ȃ��\�b�h�ł��B���̃��\�b�h�̓��e��
		/// �R�[�h �G�f�B�^�ŕύX���Ȃ��ł��������B
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->labelLocalIp = (gcnew System::Windows::Forms::Label());
			this->labelLocalPort = (gcnew System::Windows::Forms::Label());
			this->labelRemoteIp = (gcnew System::Windows::Forms::Label());
			this->labelRemotePort = (gcnew System::Windows::Forms::Label());
			this->textLocalIp = (gcnew System::Windows::Forms::TextBox());
			this->textLocalPort = (gcnew System::Windows::Forms::TextBox());
			this->textRemoteIp = (gcnew System::Windows::Forms::TextBox());
			this->textRemotePort = (gcnew System::Windows::Forms::TextBox());
			this->buttonStop = (gcnew System::Windows::Forms::Button());
			this->buttonStart = (gcnew System::Windows::Forms::Button());
			this->radioDefault = (gcnew System::Windows::Forms::RadioButton());
			this->radioUtf8 = (gcnew System::Windows::Forms::RadioButton());
			this->radioAscii = (gcnew System::Windows::Forms::RadioButton());
			this->buttonClear = (gcnew System::Windows::Forms::Button());
			this->labelMessage = (gcnew System::Windows::Forms::Label());
			this->listMessage = (gcnew System::Windows::Forms::ListBox());
			this->buttonSend = (gcnew System::Windows::Forms::Button());
			this->textMessage = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// labelLocalIp
			// 
			this->labelLocalIp->AutoSize = true;
			this->labelLocalIp->Location = System::Drawing::Point(23, 9);
			this->labelLocalIp->Name = L"labelLocalIp";
			this->labelLocalIp->Size = System::Drawing::Size(46, 12);
			this->labelLocalIp->TabIndex = 0;
			this->labelLocalIp->Text = L"Local IP";
			// 
			// labelLocalPort
			// 
			this->labelLocalPort->AutoSize = true;
			this->labelLocalPort->Location = System::Drawing::Point(12, 38);
			this->labelLocalPort->Name = L"labelLocalPort";
			this->labelLocalPort->Size = System::Drawing::Size(57, 12);
			this->labelLocalPort->TabIndex = 1;
			this->labelLocalPort->Text = L"Local Port";
			// 
			// labelRemoteIp
			// 
			this->labelRemoteIp->AutoSize = true;
			this->labelRemoteIp->Location = System::Drawing::Point(308, 9);
			this->labelRemoteIp->Name = L"labelRemoteIp";
			this->labelRemoteIp->Size = System::Drawing::Size(58, 12);
			this->labelRemoteIp->TabIndex = 2;
			this->labelRemoteIp->Text = L"Remote IP";
			// 
			// labelRemotePort
			// 
			this->labelRemotePort->AutoSize = true;
			this->labelRemotePort->Location = System::Drawing::Point(297, 38);
			this->labelRemotePort->Name = L"labelRemotePort";
			this->labelRemotePort->Size = System::Drawing::Size(69, 12);
			this->labelRemotePort->TabIndex = 3;
			this->labelRemotePort->Text = L"Remote Port";
			// 
			// textLocalIp
			// 
			this->textLocalIp->Location = System::Drawing::Point(75, 6);
			this->textLocalIp->Name = L"textLocalIp";
			this->textLocalIp->Size = System::Drawing::Size(100, 19);
			this->textLocalIp->TabIndex = 4;
			// 
			// textLocalPort
			// 
			this->textLocalPort->Location = System::Drawing::Point(75, 35);
			this->textLocalPort->Name = L"textLocalPort";
			this->textLocalPort->Size = System::Drawing::Size(100, 19);
			this->textLocalPort->TabIndex = 5;
			// 
			// textRemoteIp
			// 
			this->textRemoteIp->Location = System::Drawing::Point(372, 6);
			this->textRemoteIp->Name = L"textRemoteIp";
			this->textRemoteIp->Size = System::Drawing::Size(100, 19);
			this->textRemoteIp->TabIndex = 6;
			// 
			// textRemotePort
			// 
			this->textRemotePort->Location = System::Drawing::Point(372, 35);
			this->textRemotePort->Name = L"textRemotePort";
			this->textRemotePort->Size = System::Drawing::Size(100, 19);
			this->textRemotePort->TabIndex = 7;
			// 
			// buttonStop
			// 
			this->buttonStop->Enabled = false;
			this->buttonStop->Location = System::Drawing::Point(181, 33);
			this->buttonStop->Name = L"buttonStop";
			this->buttonStop->Size = System::Drawing::Size(75, 23);
			this->buttonStop->TabIndex = 19;
			this->buttonStop->Text = L"�X�g�b�v";
			this->buttonStop->UseVisualStyleBackColor = true;
			this->buttonStop->Click += gcnew System::EventHandler(this, &MainForm::buttonStop_Click);
			// 
			// buttonStart
			// 
			this->buttonStart->Location = System::Drawing::Point(181, 4);
			this->buttonStart->Name = L"buttonStart";
			this->buttonStart->Size = System::Drawing::Size(75, 23);
			this->buttonStart->TabIndex = 18;
			this->buttonStart->Text = L"�X�^�[�g";
			this->buttonStart->UseVisualStyleBackColor = true;
			this->buttonStart->Click += gcnew System::EventHandler(this, &MainForm::buttonStart_Click);
			// 
			// radioDefault
			// 
			this->radioDefault->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->radioDefault->AutoSize = true;
			this->radioDefault->Location = System::Drawing::Point(412, 60);
			this->radioDefault->Name = L"radioDefault";
			this->radioDefault->Size = System::Drawing::Size(60, 16);
			this->radioDefault->TabIndex = 35;
			this->radioDefault->Text = L"Default";
			this->radioDefault->UseVisualStyleBackColor = true;
			this->radioDefault->CheckedChanged += gcnew System::EventHandler(this, &MainForm::CharCodeRadioCheckedChanged);
			// 
			// radioUtf8
			// 
			this->radioUtf8->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->radioUtf8->AutoSize = true;
			this->radioUtf8->Location = System::Drawing::Point(349, 60);
			this->radioUtf8->Name = L"radioUtf8";
			this->radioUtf8->Size = System::Drawing::Size(57, 16);
			this->radioUtf8->TabIndex = 34;
			this->radioUtf8->Text = L"UTF-8";
			this->radioUtf8->UseVisualStyleBackColor = true;
			this->radioUtf8->CheckedChanged += gcnew System::EventHandler(this, &MainForm::CharCodeRadioCheckedChanged);
			// 
			// radioAscii
			// 
			this->radioAscii->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->radioAscii->AutoSize = true;
			this->radioAscii->Checked = true;
			this->radioAscii->Location = System::Drawing::Point(291, 60);
			this->radioAscii->Name = L"radioAscii";
			this->radioAscii->Size = System::Drawing::Size(52, 16);
			this->radioAscii->TabIndex = 33;
			this->radioAscii->TabStop = true;
			this->radioAscii->Text = L"ASCII";
			this->radioAscii->UseVisualStyleBackColor = true;
			this->radioAscii->CheckedChanged += gcnew System::EventHandler(this, &MainForm::CharCodeRadioCheckedChanged);
			// 
			// buttonClear
			// 
			this->buttonClear->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->buttonClear->Location = System::Drawing::Point(397, 82);
			this->buttonClear->Name = L"buttonClear";
			this->buttonClear->Size = System::Drawing::Size(75, 23);
			this->buttonClear->TabIndex = 32;
			this->buttonClear->Text = L"�N���A";
			this->buttonClear->UseVisualStyleBackColor = true;
			this->buttonClear->Click += gcnew System::EventHandler(this, &MainForm::buttonClear_Click);
			// 
			// labelMessage
			// 
			this->labelMessage->AutoSize = true;
			this->labelMessage->Location = System::Drawing::Point(12, 93);
			this->labelMessage->Name = L"labelMessage";
			this->labelMessage->Size = System::Drawing::Size(58, 12);
			this->labelMessage->TabIndex = 36;
			this->labelMessage->Text = L"MESSAGE";
			// 
			// listMessage
			// 
			this->listMessage->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->listMessage->FormattingEnabled = true;
			this->listMessage->HorizontalScrollbar = true;
			this->listMessage->ItemHeight = 12;
			this->listMessage->Location = System::Drawing::Point(12, 109);
			this->listMessage->Name = L"listMessage";
			this->listMessage->Size = System::Drawing::Size(460, 316);
			this->listMessage->TabIndex = 39;
			// 
			// buttonSend
			// 
			this->buttonSend->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonSend->Enabled = false;
			this->buttonSend->Location = System::Drawing::Point(397, 429);
			this->buttonSend->Name = L"buttonSend";
			this->buttonSend->Size = System::Drawing::Size(75, 23);
			this->buttonSend->TabIndex = 38;
			this->buttonSend->Text = L"���M";
			this->buttonSend->UseVisualStyleBackColor = true;
			this->buttonSend->Click += gcnew System::EventHandler(this, &MainForm::buttonSend_Click);
			// 
			// textMessage
			// 
			this->textMessage->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textMessage->Location = System::Drawing::Point(12, 431);
			this->textMessage->Name = L"textMessage";
			this->textMessage->Size = System::Drawing::Size(379, 19);
			this->textMessage->TabIndex = 37;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Snow;
			this->ClientSize = System::Drawing::Size(484, 462);
			this->Controls->Add(this->listMessage);
			this->Controls->Add(this->buttonSend);
			this->Controls->Add(this->textMessage);
			this->Controls->Add(this->labelMessage);
			this->Controls->Add(this->radioDefault);
			this->Controls->Add(this->radioUtf8);
			this->Controls->Add(this->radioAscii);
			this->Controls->Add(this->buttonClear);
			this->Controls->Add(this->buttonStop);
			this->Controls->Add(this->buttonStart);
			this->Controls->Add(this->textRemotePort);
			this->Controls->Add(this->textRemoteIp);
			this->Controls->Add(this->textLocalPort);
			this->Controls->Add(this->textLocalIp);
			this->Controls->Add(this->labelRemotePort);
			this->Controls->Add(this->labelRemoteIp);
			this->Controls->Add(this->labelLocalPort);
			this->Controls->Add(this->labelLocalIp);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MinimumSize = System::Drawing::Size(500, 500);
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"MSM-07";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &MainForm::MainForm_FormClosed);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	/// ������
	private: void Initialize()
			 {
				 String^ filename = System::IO::Path::ChangeExtension(System::Windows::Forms::Application::ExecutablePath, ".ini");
				 this->config = gcnew ConfigFile(filename);
				 this->config->LoadFormSizeAndLocation(this);
				 this->textLocalIp->Text = this->config->GetUdpLocalIPEndPoint()->Address->ToString();
				 this->textLocalPort->Text = this->config->GetUdpLocalIPEndPoint()->Port.ToString();
				 this->textRemoteIp->Text = this->config->GetUdpRemoteIPEndPoint()->Address->ToString();
				 this->textRemotePort->Text = this->config->GetUdpRemoteIPEndPoint()->Port.ToString();

				 this->udpClient = gcnew UdpClientSocket();
				 this->udpClient->Received += gcnew UdpEventHandler(this, &MainForm::ReceivedClient);

				 this->udpClient->Encoding = this->config->GetUdpEncoding();
				 if (this->udpClient->Encoding == System::Text::Encoding::ASCII)
				 {
					 this->radioAscii->Checked = true;
					 this->radioUtf8->Checked = false;
					 this->radioDefault->Checked = false;
				 }
				 else if (this->udpClient->Encoding == System::Text::Encoding::UTF8)
				 {
					 this->radioAscii->Checked = false;
					 this->radioUtf8->Checked = true;
					 this->radioDefault->Checked = false;
				 }
				 else
				 {
					 this->radioAscii->Checked = false;
					 this->radioUtf8->Checked = false;
					 this->radioDefault->Checked = true;
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// �N���[�Y�㏈��
	private: System::Void MainForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e)
			 {
				 if (this->udpClient->Connected)
				 {
					 this->udpClient->Stop();
				 }
				 this->config->SaveFormSizeAndLocation(this);
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// �X�^�[�g
	private: System::Void buttonStart_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 if (this->textRemoteIp->Text->Equals(String::Empty) || this->textRemotePort->Text->Equals(String::Empty)) return;

				 try
				 {
					 IPEndPoint^ endPoint = gcnew IPEndPoint(IPAddress::Parse(this->textLocalIp->Text), int::Parse(this->textLocalPort->Text));
					 if (this->udpClient->Start(endPoint))
					 {
						 this->listMessage->Items->Add("�y" + DateTime::Now.ToString() + "�z " + this->udpClient->LocalEndPoint->Address->ToString() + " : " + this->udpClient->LocalEndPoint->Port.ToString());
						 this->listMessage->Items->Add("*** START ***");
						 this->listMessage->SelectedIndex = this->listMessage->Items->Count - 1;
						 this->listMessage->Items->Add(String::Empty);
						 this->UpdateControl();
						 this->config->SetUdpLocalIPEndPoint(endPoint);
					 }
					 else
					 {
						 System::Windows::Forms::MessageBox::Show("�������Ɏ��s���܂����I", this->Text, MessageBoxButtons::OK, MessageBoxIcon::Error);
					 }
				 }
				 catch (Exception^)
				 {
					 System::Windows::Forms::MessageBox::Show("�������Ɏ��s���܂����I", this->Text, MessageBoxButtons::OK, MessageBoxIcon::Error);
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// �X�g�b�v
	private: System::Void buttonStop_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 if (this->udpClient->Stop())
				 {
					 this->listMessage->Items->Add("�y" + DateTime::Now.ToString() + "�z " + this->textLocalIp->Text + " : " + this->textLocalPort->Text);
					 this->listMessage->Items->Add("*** STOP ***");
					 this->listMessage->SelectedIndex = this->listMessage->Items->Count - 1;
					 this->listMessage->Items->Add(String::Empty);
					 this->UpdateControl();
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// �N���A
	private: System::Void buttonClear_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->listMessage->Items->Clear();
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// ���M
	private: System::Void buttonSend_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 if (this->textMessage->Text->Equals(String::Empty)) return;

				 try
				 {
					 IPEndPoint^ endPoint = gcnew IPEndPoint(IPAddress::Parse(this->textRemoteIp->Text), int::Parse(this->textRemotePort->Text));
					 this->udpClient->SendMessage(this->textMessage->Text, endPoint);
					 this->listMessage->Items->Add("�y" + DateTime::Now.ToString() + "�z " + endPoint->Address->ToString() + " : " + endPoint->Port.ToString());
					 this->listMessage->Items->Add(">>  " + this->textMessage->Text);
					 this->listMessage->SelectedIndex = this->listMessage->Items->Count - 1;
					 this->listMessage->Items->Add(String::Empty);
					 this->config->SetUdpRemoteIPEndPoint(endPoint);
				 }
				 catch (Exception^)
				 {
					 System::Windows::Forms::MessageBox::Show("���M�Ɏ��s���܂����I", this->Text, MessageBoxButtons::OK, MessageBoxIcon::Error);
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// ��M
	private: void ReceivedClient(System::Object ^sender, Anaheim::UdpSocket::UdpEventArgs ^e)
			 {
				 this->listMessage->Items->Add("�y" + DateTime::Now.ToString() + "�z " + e->RemoteEndPoint->Address->ToString() + " : " + e->RemoteEndPoint->Port.ToString());
				 this->listMessage->Items->Add("<<  " + e->Message);
				 this->listMessage->SelectedIndex = this->listMessage->Items->Count - 1;
				 this->listMessage->Items->Add(String::Empty);
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// �R���g���[���X�V
	private: void UpdateControl()
			 {
				 try
				 {
					 if (this->udpClient->Connected)
					 {
						 this->buttonStart->Enabled = false;
						 this->buttonStop->Enabled = true;
						 this->buttonSend->Enabled = true;
						 this->textLocalIp->ReadOnly = true;
						 this->textLocalPort->ReadOnly = true;
					 }
					 else
					 {
						 this->buttonStart->Enabled = true;
						 this->buttonStop->Enabled = false;
						 this->buttonSend->Enabled = false;
						 this->textLocalIp->ReadOnly = false;
						 this->textLocalPort->ReadOnly = false;
					 }
				 }
				 catch (Exception^)
				 {
					 return;
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// �����R�[�h
	private: System::Void CharCodeRadioCheckedChanged(System::Object^  sender, System::EventArgs^  e)
			 {
				 if (this->radioAscii->Checked)
				 {
					 this->udpClient->Encoding = System::Text::Encoding::ASCII;
				 }
				 else if (this->radioUtf8->Checked)
				 {
					 this->udpClient->Encoding = System::Text::Encoding::UTF8;
				 }
				 else if (this->radioDefault->Checked)
				 {
					 this->udpClient->Encoding = System::Text::Encoding::Default;
				 }
				 this->config->SetUdpEncoding(this->udpClient->Encoding);				 
			 }
			 // ----------------------------------------------------------------------------------------------------

	};
}
