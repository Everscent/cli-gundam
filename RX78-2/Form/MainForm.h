#pragma once

#include "VersionForm.h"
#include "ExitForm.h"
#include "FtpConnectForm.h"
#include "SetTimerForm.h"
#include "ConfigFile.h"
#include "ReportBook.h"
#include "ReportEditor.h"
#include "PicturePuzzle.h"
#include "BinaryClock.h"
#include "ArrowInsectCage.h"
#include "DirectX3D.h"

namespace RX78_2
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Net;
	using namespace Report;
	using namespace Puzzle;
	using namespace Clock;
	using namespace Arrow;
	using namespace DirectX;
	using namespace Anaheim;
	using namespace Anaheim::TcpSocket;
	using namespace Anaheim::Tetris;

	/// <summary>
	/// MainForm の概要
	///
	/// 警告: このクラスの名前を変更する場合、このクラスが依存するすべての .resx ファイルに関連付けられた
	///          マネージ リソース コンパイラ ツールに対して 'Resource File Name' プロパティを
	///          変更する必要があります。この変更を行わないと、
	///          デザイナと、このフォームに関連付けられたローカライズ済みリソースとが、
	///          正しく相互に利用できなくなります。
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{

#pragma region フィールド

	private: bool isMaximized;						///< 最大化状態記憶フラグ
	private: bool canClose;							///< 終了フラグ
	private: String^ startupName;					///< スタートアップ名
	private: MenuPairList^ menuPair;				///< メニューバー，ツールバー関連付け
	private: ConfigFile^ config;					///< コンフィグファイル
	private: ReportBook^ report;					///< レポート
	private: ReportEditor^ editor;					///< レポートエディタ
	private: TcpServerSocket^ tcpServer;			///< TCPサーバソケット
	private: FtpClient^ ftpClient;					///< FTPクライアント
	private: PicturePuzzle^ puzzle;					///< ピクチャーパズル
	private: array<PictureBox^, 2>^ pictureArray;	///< パズル用分割イメージ
	private: BinaryClock^ clock;					///< バイナリクロック
	private: TetrisPackage^ tetris;					///< テトリス
	private: ArrowInsectCage^ arrow;				///< Arrow虫
	private: DirectX3D^ directX;					///< DirectX

	private: System::Windows::Forms::MenuStrip^  menuStrip;
	private: System::Windows::Forms::ToolStrip^  toolStrip;
	private: System::Windows::Forms::StatusStrip^  statusStrip;
	private: System::Windows::Forms::TabControl^  tabControl;
	private: System::Windows::Forms::TabPage^  tabReport;
	private: System::Windows::Forms::ToolStripMenuItem^  menuFile;
	private: System::Windows::Forms::ToolStripMenuItem^  menuHelp;
	private: System::Windows::Forms::ToolStripMenuItem^  menuExit;
	private: System::Windows::Forms::ToolStripButton^  toolExit;
	private: System::Windows::Forms::DataGridView^  r_gridReport;
	private: System::Windows::Forms::Button^  r_buttonLoad;
	private: System::Windows::Forms::TextBox^  r_textFileName;
	private: System::Windows::Forms::ComboBox^  r_comboSection;
	private: System::Windows::Forms::Button^  r_buttonSave;
	private: System::Windows::Forms::Button^  r_buttonRemove;
	private: System::Windows::Forms::Button^  r_buttonInsert;
	private: System::Windows::Forms::Label^  r_labelFileName;
	private: System::Windows::Forms::Label^  r_labelSection;
	private: System::Windows::Forms::Button^  r_buttonRemoveRow;
	private: System::Windows::Forms::Button^  r_buttonInsertRow;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog;
	private: System::Windows::Forms::NotifyIcon^  notifyIcon;
	private: System::Windows::Forms::ContextMenuStrip^  contextTaskTray;
	private: System::Windows::Forms::ToolStripMenuItem^  trayMenuView;
	private: System::Windows::Forms::ToolStripMenuItem^  trayMenuHide;
	private: System::Windows::Forms::ToolStripSeparator^  trayMenuSeparator;
	private: System::Windows::Forms::ToolStripMenuItem^  trayMenuExit;
	private: System::Windows::Forms::ToolStripMenuItem^  menuView;
	private: System::Windows::Forms::ToolStripMenuItem^  menuHide;
	private: System::Windows::Forms::Button^  r_buttonAdd;
	private: System::Windows::Forms::Button^  r_buttonAddRow;
	private: System::Windows::Forms::ToolStripMenuItem^  menuAction;
	private: System::Windows::Forms::ToolStripMenuItem^  menuReport;
	private: System::Windows::Forms::ToolStripMenuItem^  menuOpen;
	private: System::Windows::Forms::ToolStripMenuItem^  menuSave;
	private: System::Windows::Forms::ToolStripMenuItem^  menuSaveAs;
	private: System::Windows::Forms::ToolStripSeparator^  menuReportSeparator01;
	private: System::Windows::Forms::ToolStripMenuItem^  menuUndo;
	private: System::Windows::Forms::ToolStripMenuItem^  menuRedo;
	private: System::Windows::Forms::ToolStripSeparator^  toolSeparator01;
	private: System::Windows::Forms::ToolStripButton^  toolOpen;
	private: System::Windows::Forms::ToolStripButton^  toolSave;
	private: System::Windows::Forms::ToolStripButton^  toolUndo;
	private: System::Windows::Forms::ToolStripButton^  toolRedo;
	private: System::Windows::Forms::ToolStripSeparator^  menuReportSeparator02;
	private: System::Windows::Forms::ToolStripMenuItem^  menuClear;
	private: System::Windows::Forms::ToolStripMenuItem^  menuOption;
	private: System::Windows::Forms::ToolStripMenuItem^  menuSizeReset;
	private: System::Windows::Forms::ToolStripMenuItem^  menuMemoryRelease;
	private: System::Windows::Forms::ToolStripMenuItem^  menuStartUp;
	private: System::Windows::Forms::ToolStripMenuItem^  menuVersion;
	private: System::Windows::Forms::TabPage^  tabTcpServer;
	private: System::Windows::Forms::ListBox^  t_listMessage;
	private: System::Windows::Forms::Label^  t_labelMessage;
	private: System::Windows::Forms::Button^  t_buttonDisConnect;
	private: System::Windows::Forms::ComboBox^  t_comboRemoteIp;
	private: System::Windows::Forms::Button^  t_buttonClearList;
	private: System::Windows::Forms::TextBox^  t_textRemotePort;
	private: System::Windows::Forms::Label^  t_labelRemotePort;
	private: System::Windows::Forms::Label^  t_labelRemoteIp;
	private: System::Windows::Forms::Button^  t_buttonStop;
	private: System::Windows::Forms::Button^  t_buttonStart;
	private: System::Windows::Forms::Label^  t_labelLocalPort;
	private: System::Windows::Forms::Label^  t_labelLocalIp;
	private: System::Windows::Forms::TextBox^  t_textLocalPort;
	private: System::Windows::Forms::TextBox^  t_textLocalIp;
	private: System::Windows::Forms::Button^  t_buttonSendMessage;
	private: System::Windows::Forms::TextBox^  t_textMessage;
	private: System::Windows::Forms::ToolStripMenuItem^  menuTcpServer;
	private: System::Windows::Forms::ToolStripMenuItem^  menuTcpStart;
	private: System::Windows::Forms::ToolStripMenuItem^  menuTcpStop;
	private: System::Windows::Forms::ToolStripMenuItem^  menuTcpClient;
	private: System::Windows::Forms::ToolStripMenuItem^  menuCharCode;
	private: System::Windows::Forms::ToolStripMenuItem^  menuAscii;
	private: System::Windows::Forms::ToolStripMenuItem^  menuUtf8;
	private: System::Windows::Forms::ToolStripMenuItem^  menuDefault;
	private: System::Windows::Forms::ToolStripSeparator^  toolSeparator02;
	private: System::Windows::Forms::ToolStripButton^  toolTcpStart;
	private: System::Windows::Forms::ToolStripButton^  toolTcpStop;
	private: System::Windows::Forms::ToolStripButton^  toolTcpClient;
	private: System::Windows::Forms::TabPage^  tabFtpClient;
	private: System::Windows::Forms::Button^  f_buttonConnect;
	private: System::Windows::Forms::Button^  f_buttonDownload;
	private: System::Windows::Forms::Button^  f_buttonUpload;
	private: System::Windows::Forms::SplitContainer^  f_splitFtp;
	private: System::Windows::Forms::GroupBox^  f_gropServer;
	private: System::Windows::Forms::SplitContainer^  f_splitServer;
	private: System::Windows::Forms::TreeView^  f_treeServer;
	private: System::Windows::Forms::ListView^  f_listViewServerFiles;
	private: System::Windows::Forms::ColumnHeader^  f_columnHeaderNameServer;
	private: System::Windows::Forms::ColumnHeader^  f_columnHeaderSizeServer;
	private: System::Windows::Forms::ColumnHeader^  f_columnHeaderDateServer;
	private: System::Windows::Forms::TextBox^  f_textServerPath;
	private: System::Windows::Forms::GroupBox^  f_gropLocal;
	private: System::Windows::Forms::SplitContainer^  f_splitLocal;
	private: System::Windows::Forms::TreeView^  f_treeLocal;
	private: System::Windows::Forms::ListView^  f_listViewLocalFiles;
	private: System::Windows::Forms::ColumnHeader^  f_columnHeaderNameLocal;
	private: System::Windows::Forms::ColumnHeader^  f_columnHeaderSizeLocal;
	private: System::Windows::Forms::ColumnHeader^  f_columnHeaderDateLocal;
	private: System::Windows::Forms::TextBox^  f_textLocalPath;
	private: System::Windows::Forms::ToolStripMenuItem^  menuFtpClient;
	private: System::Windows::Forms::ToolStripMenuItem^  menuFtpConnect;
	private: System::Windows::Forms::ToolStripMenuItem^  menuFtpDisConnect;
	private: System::Windows::Forms::ToolStripSeparator^  toolSeparator03;
	private: System::Windows::Forms::ToolStripButton^  toolFtpConnect;
	private: System::Windows::Forms::ToolStripButton^  toolFtpDisConnect;
	private: System::Windows::Forms::ImageList^  imageListFtp;
	private: System::Windows::Forms::ToolStripSeparator^  toolSeparatorDebug;
	private: System::Windows::Forms::ToolStripButton^  toolDebug;
	private: System::Windows::Forms::TabPage^  tabPicturePuzzle;
	private: System::Windows::Forms::Button^  p_buttonLoad;
	private: System::Windows::Forms::Button^  p_buttonPuzzle;
	private: System::Windows::Forms::Panel^  p_panelBase;
	private: System::Windows::Forms::Panel^  p_panelBottom;
	private: System::Windows::Forms::PictureBox^  p_picturePuzzle;
	private: System::Windows::Forms::Button^  p_buttonClearPicture;
	private: System::Windows::Forms::ToolStripMenuItem^  menuPicturePuzzle;
	private: System::Windows::Forms::ToolStripMenuItem^  menuPictureLoad;
	private: System::Windows::Forms::ToolStripSeparator^  toolSeparator04;
	private: System::Windows::Forms::ToolStripButton^  toolPictureLoad;
	private: System::Windows::Forms::ToolStripMenuItem^  menuBinaryClock;
	private: System::Windows::Forms::ToolStripMenuItem^  menuTimer;
	private: System::Windows::Forms::ToolStripMenuItem^  menuColor;
	private: System::Windows::Forms::ToolStripMenuItem^  menuOnColor;
	private: System::Windows::Forms::ToolStripMenuItem^  menuOffColor;
	private: System::Windows::Forms::ToolStripSeparator^  toolSeparator05;
	private: System::Windows::Forms::ToolStripButton^  toolTimer;
	private: System::Windows::Forms::TabPage^  tabBinaryClock;
	private: System::Windows::Forms::Panel^  b_panelSec2;
	private: System::Windows::Forms::Panel^  b_panelHour20;
	private: System::Windows::Forms::Panel^  b_panelHour10;
	private: System::Windows::Forms::Panel^  b_panelHour1;
	private: System::Windows::Forms::Panel^  b_panelHour2;
	private: System::Windows::Forms::Panel^  b_panelHour4;
	private: System::Windows::Forms::Panel^  b_panelHour8;
	private: System::Windows::Forms::Panel^  b_panelMin40;
	private: System::Windows::Forms::Panel^  b_panelMin20;
	private: System::Windows::Forms::Panel^  b_panelMin10;
	private: System::Windows::Forms::Panel^  b_panelSec40;
	private: System::Windows::Forms::Panel^  b_panelMin1;
	private: System::Windows::Forms::Panel^  b_panelMin2;
	private: System::Windows::Forms::Panel^  b_panelMin4;
	private: System::Windows::Forms::Panel^  b_panelMin8;
	private: System::Windows::Forms::Panel^  b_panelSec20;
	private: System::Windows::Forms::Panel^  b_panelSec10;
	private: System::Windows::Forms::Panel^  b_panelSec1;
	private: System::Windows::Forms::Panel^  b_panelSec4;
	private: System::Windows::Forms::Panel^  b_panelSec8;
	private: System::Windows::Forms::Label^  b_labelSpanTime;
	private: System::Windows::Forms::Button^  b_buttonTimerStop;
	private: System::Windows::Forms::Button^  b_buttonTimerSet;
	private: System::Windows::Forms::Label^  b_labelColon1;
	private: System::Windows::Forms::Label^  b_labelColon2;
	private: System::Windows::Forms::Label^  b_labelSec1;
	private: System::Windows::Forms::Label^  b_labelSec2;
	private: System::Windows::Forms::Label^  b_labelMin1;
	private: System::Windows::Forms::Label^  b_labelMin2;
	private: System::Windows::Forms::Label^  b_labelHour1;
	private: System::Windows::Forms::Label^  b_labelHour2;
	private: System::Windows::Forms::Timer^  timerBinaryClock;
	private: System::Windows::Forms::Timer^  timerBinaryTimer;
	private: System::Windows::Forms::ColorDialog^  colorDialog;
	private: System::Windows::Forms::TabPage^  tabTetris;
	private: System::Windows::Forms::Label^  g_labelNext;
	private: System::Windows::Forms::Panel^  g_panelTetris;
	private: System::Windows::Forms::Label^  g_labelMessage;
	private: System::Windows::Forms::Button^  g_buttonHowTo;
	private: System::Windows::Forms::Button^  g_buttonStart;
	private: System::Windows::Forms::Button^  g_buttonEnd;
	private: System::Windows::Forms::Panel^  g_panelScore;
	private: System::Windows::Forms::Label^  g_labelScore;
	private: System::Windows::Forms::Label^  g_labelScoreTitle;
	private: System::Windows::Forms::Label^  g_labelTetris;
	private: System::Windows::Forms::Label^  g_labelTriple;
	private: System::Windows::Forms::Label^  g_labelDouble;
	private: System::Windows::Forms::Label^  g_labelSingle;
	private: System::Windows::Forms::Label^  g_labelTetrisTitle;
	private: System::Windows::Forms::Label^  g_labelTripleTitle;
	private: System::Windows::Forms::Label^  g_labelDoubleTitle;
	private: System::Windows::Forms::Label^  g_labelSingleTitle;
	private: System::Windows::Forms::Panel^  g_panelNext3;
	private: System::Windows::Forms::Panel^  g_panelNext2;
	private: System::Windows::Forms::Panel^  g_panelNext1;
	private: System::Windows::Forms::ToolStripMenuItem^  menuTetris;
	private: System::Windows::Forms::ToolStripMenuItem^  menuRanking;
	private: System::Windows::Forms::ToolStripSeparator^  toolSeparator06;
	private: System::Windows::Forms::ToolStripButton^  toolRanking;
	private: System::Windows::Forms::TabPage^  tabArrow;
	private: System::Windows::Forms::ToolStripMenuItem^  menuArrow;
	private: System::Windows::Forms::Panel^  a_panelCanvas;
	private: System::Windows::Forms::ToolStripMenuItem^  menuReset;
	private: System::Windows::Forms::ToolStripButton^  toolReset;
	private: System::Windows::Forms::ToolStripSeparator^  toolSeparator07;
	private: System::Windows::Forms::Timer^  timerArrow;
	private: System::Windows::Forms::ToolStripMenuItem^  menuRemote;
	private: System::Windows::Forms::ToolStripMenuItem^  menuSound;
	private: System::Windows::Forms::TabPage^  tabDirectX;
	private: System::Windows::Forms::Panel^  d_panelCanvas;
	private: System::Windows::Forms::ToolStripSeparator^  menuFileSeparator;

#pragma endregion

	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクタ コードを追加します
			//
			this->Initialize();
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
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
		/// 必要なデザイナ変数です。
		/// </summary>
		System::ComponentModel::IContainer^  components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナ サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディタで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->menuFile = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuView = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuHide = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuFileSeparator = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->menuExit = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuAction = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuReport = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuOpen = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuSave = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuSaveAs = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuReportSeparator01 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->menuUndo = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuRedo = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuReportSeparator02 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->menuClear = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuTcpServer = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuTcpStart = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuTcpStop = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuCharCode = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuAscii = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuUtf8 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuDefault = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuTcpClient = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuFtpClient = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuFtpConnect = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuFtpDisConnect = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuPicturePuzzle = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuPictureLoad = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuBinaryClock = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuTimer = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuColor = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuOnColor = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuOffColor = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuTetris = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuRanking = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuSound = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuRemote = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuArrow = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuReset = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuOption = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuSizeReset = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuMemoryRelease = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStartUp = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuHelp = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuVersion = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStrip = (gcnew System::Windows::Forms::ToolStrip());
			this->toolExit = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolSeparator01 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolOpen = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolSave = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolUndo = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolRedo = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolSeparator02 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolTcpStart = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolTcpStop = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolTcpClient = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolSeparator03 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolFtpConnect = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolFtpDisConnect = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolSeparator04 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolPictureLoad = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolSeparator05 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolTimer = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolSeparator06 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolRanking = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolSeparator07 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolReset = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolSeparatorDebug = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolDebug = (gcnew System::Windows::Forms::ToolStripButton());
			this->statusStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->tabControl = (gcnew System::Windows::Forms::TabControl());
			this->tabReport = (gcnew System::Windows::Forms::TabPage());
			this->r_buttonAddRow = (gcnew System::Windows::Forms::Button());
			this->r_buttonAdd = (gcnew System::Windows::Forms::Button());
			this->r_labelFileName = (gcnew System::Windows::Forms::Label());
			this->r_labelSection = (gcnew System::Windows::Forms::Label());
			this->r_buttonRemoveRow = (gcnew System::Windows::Forms::Button());
			this->r_buttonInsertRow = (gcnew System::Windows::Forms::Button());
			this->r_buttonRemove = (gcnew System::Windows::Forms::Button());
			this->r_buttonInsert = (gcnew System::Windows::Forms::Button());
			this->r_comboSection = (gcnew System::Windows::Forms::ComboBox());
			this->r_buttonSave = (gcnew System::Windows::Forms::Button());
			this->r_gridReport = (gcnew System::Windows::Forms::DataGridView());
			this->r_buttonLoad = (gcnew System::Windows::Forms::Button());
			this->r_textFileName = (gcnew System::Windows::Forms::TextBox());
			this->tabTcpServer = (gcnew System::Windows::Forms::TabPage());
			this->t_buttonSendMessage = (gcnew System::Windows::Forms::Button());
			this->t_textMessage = (gcnew System::Windows::Forms::TextBox());
			this->t_listMessage = (gcnew System::Windows::Forms::ListBox());
			this->t_labelMessage = (gcnew System::Windows::Forms::Label());
			this->t_buttonDisConnect = (gcnew System::Windows::Forms::Button());
			this->t_comboRemoteIp = (gcnew System::Windows::Forms::ComboBox());
			this->t_buttonClearList = (gcnew System::Windows::Forms::Button());
			this->t_textRemotePort = (gcnew System::Windows::Forms::TextBox());
			this->t_labelRemotePort = (gcnew System::Windows::Forms::Label());
			this->t_labelRemoteIp = (gcnew System::Windows::Forms::Label());
			this->t_buttonStop = (gcnew System::Windows::Forms::Button());
			this->t_buttonStart = (gcnew System::Windows::Forms::Button());
			this->t_labelLocalPort = (gcnew System::Windows::Forms::Label());
			this->t_labelLocalIp = (gcnew System::Windows::Forms::Label());
			this->t_textLocalPort = (gcnew System::Windows::Forms::TextBox());
			this->t_textLocalIp = (gcnew System::Windows::Forms::TextBox());
			this->tabFtpClient = (gcnew System::Windows::Forms::TabPage());
			this->f_buttonConnect = (gcnew System::Windows::Forms::Button());
			this->f_buttonDownload = (gcnew System::Windows::Forms::Button());
			this->f_buttonUpload = (gcnew System::Windows::Forms::Button());
			this->f_splitFtp = (gcnew System::Windows::Forms::SplitContainer());
			this->f_gropServer = (gcnew System::Windows::Forms::GroupBox());
			this->f_splitServer = (gcnew System::Windows::Forms::SplitContainer());
			this->f_treeServer = (gcnew System::Windows::Forms::TreeView());
			this->imageListFtp = (gcnew System::Windows::Forms::ImageList(this->components));
			this->f_listViewServerFiles = (gcnew System::Windows::Forms::ListView());
			this->f_columnHeaderNameServer = (gcnew System::Windows::Forms::ColumnHeader());
			this->f_columnHeaderSizeServer = (gcnew System::Windows::Forms::ColumnHeader());
			this->f_columnHeaderDateServer = (gcnew System::Windows::Forms::ColumnHeader());
			this->f_textServerPath = (gcnew System::Windows::Forms::TextBox());
			this->f_gropLocal = (gcnew System::Windows::Forms::GroupBox());
			this->f_splitLocal = (gcnew System::Windows::Forms::SplitContainer());
			this->f_treeLocal = (gcnew System::Windows::Forms::TreeView());
			this->f_listViewLocalFiles = (gcnew System::Windows::Forms::ListView());
			this->f_columnHeaderNameLocal = (gcnew System::Windows::Forms::ColumnHeader());
			this->f_columnHeaderSizeLocal = (gcnew System::Windows::Forms::ColumnHeader());
			this->f_columnHeaderDateLocal = (gcnew System::Windows::Forms::ColumnHeader());
			this->f_textLocalPath = (gcnew System::Windows::Forms::TextBox());
			this->tabPicturePuzzle = (gcnew System::Windows::Forms::TabPage());
			this->p_buttonClearPicture = (gcnew System::Windows::Forms::Button());
			this->p_buttonLoad = (gcnew System::Windows::Forms::Button());
			this->p_buttonPuzzle = (gcnew System::Windows::Forms::Button());
			this->p_panelBase = (gcnew System::Windows::Forms::Panel());
			this->p_panelBottom = (gcnew System::Windows::Forms::Panel());
			this->p_picturePuzzle = (gcnew System::Windows::Forms::PictureBox());
			this->tabBinaryClock = (gcnew System::Windows::Forms::TabPage());
			this->b_labelSpanTime = (gcnew System::Windows::Forms::Label());
			this->b_buttonTimerStop = (gcnew System::Windows::Forms::Button());
			this->b_buttonTimerSet = (gcnew System::Windows::Forms::Button());
			this->b_labelColon1 = (gcnew System::Windows::Forms::Label());
			this->b_labelColon2 = (gcnew System::Windows::Forms::Label());
			this->b_labelSec1 = (gcnew System::Windows::Forms::Label());
			this->b_labelSec2 = (gcnew System::Windows::Forms::Label());
			this->b_labelMin1 = (gcnew System::Windows::Forms::Label());
			this->b_labelMin2 = (gcnew System::Windows::Forms::Label());
			this->b_labelHour1 = (gcnew System::Windows::Forms::Label());
			this->b_labelHour2 = (gcnew System::Windows::Forms::Label());
			this->b_panelSec2 = (gcnew System::Windows::Forms::Panel());
			this->b_panelHour20 = (gcnew System::Windows::Forms::Panel());
			this->b_panelHour10 = (gcnew System::Windows::Forms::Panel());
			this->b_panelHour1 = (gcnew System::Windows::Forms::Panel());
			this->b_panelHour2 = (gcnew System::Windows::Forms::Panel());
			this->b_panelHour4 = (gcnew System::Windows::Forms::Panel());
			this->b_panelHour8 = (gcnew System::Windows::Forms::Panel());
			this->b_panelMin40 = (gcnew System::Windows::Forms::Panel());
			this->b_panelMin20 = (gcnew System::Windows::Forms::Panel());
			this->b_panelMin10 = (gcnew System::Windows::Forms::Panel());
			this->b_panelSec40 = (gcnew System::Windows::Forms::Panel());
			this->b_panelMin1 = (gcnew System::Windows::Forms::Panel());
			this->b_panelMin2 = (gcnew System::Windows::Forms::Panel());
			this->b_panelMin4 = (gcnew System::Windows::Forms::Panel());
			this->b_panelMin8 = (gcnew System::Windows::Forms::Panel());
			this->b_panelSec20 = (gcnew System::Windows::Forms::Panel());
			this->b_panelSec10 = (gcnew System::Windows::Forms::Panel());
			this->b_panelSec1 = (gcnew System::Windows::Forms::Panel());
			this->b_panelSec4 = (gcnew System::Windows::Forms::Panel());
			this->b_panelSec8 = (gcnew System::Windows::Forms::Panel());
			this->tabTetris = (gcnew System::Windows::Forms::TabPage());
			this->g_buttonHowTo = (gcnew System::Windows::Forms::Button());
			this->g_buttonStart = (gcnew System::Windows::Forms::Button());
			this->g_buttonEnd = (gcnew System::Windows::Forms::Button());
			this->g_panelScore = (gcnew System::Windows::Forms::Panel());
			this->g_labelScore = (gcnew System::Windows::Forms::Label());
			this->g_labelScoreTitle = (gcnew System::Windows::Forms::Label());
			this->g_labelTetris = (gcnew System::Windows::Forms::Label());
			this->g_labelTriple = (gcnew System::Windows::Forms::Label());
			this->g_labelDouble = (gcnew System::Windows::Forms::Label());
			this->g_labelSingle = (gcnew System::Windows::Forms::Label());
			this->g_labelTetrisTitle = (gcnew System::Windows::Forms::Label());
			this->g_labelTripleTitle = (gcnew System::Windows::Forms::Label());
			this->g_labelDoubleTitle = (gcnew System::Windows::Forms::Label());
			this->g_labelSingleTitle = (gcnew System::Windows::Forms::Label());
			this->g_panelNext3 = (gcnew System::Windows::Forms::Panel());
			this->g_panelNext2 = (gcnew System::Windows::Forms::Panel());
			this->g_panelNext1 = (gcnew System::Windows::Forms::Panel());
			this->g_labelNext = (gcnew System::Windows::Forms::Label());
			this->g_panelTetris = (gcnew System::Windows::Forms::Panel());
			this->g_labelMessage = (gcnew System::Windows::Forms::Label());
			this->tabArrow = (gcnew System::Windows::Forms::TabPage());
			this->a_panelCanvas = (gcnew System::Windows::Forms::Panel());
			this->tabDirectX = (gcnew System::Windows::Forms::TabPage());
			this->d_panelCanvas = (gcnew System::Windows::Forms::Panel());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->notifyIcon = (gcnew System::Windows::Forms::NotifyIcon(this->components));
			this->contextTaskTray = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->trayMenuView = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->trayMenuHide = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->trayMenuSeparator = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->trayMenuExit = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->timerBinaryClock = (gcnew System::Windows::Forms::Timer(this->components));
			this->timerBinaryTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->colorDialog = (gcnew System::Windows::Forms::ColorDialog());
			this->timerArrow = (gcnew System::Windows::Forms::Timer(this->components));
			this->menuStrip->SuspendLayout();
			this->toolStrip->SuspendLayout();
			this->tabControl->SuspendLayout();
			this->tabReport->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->r_gridReport))->BeginInit();
			this->tabTcpServer->SuspendLayout();
			this->tabFtpClient->SuspendLayout();
			this->f_splitFtp->Panel1->SuspendLayout();
			this->f_splitFtp->Panel2->SuspendLayout();
			this->f_splitFtp->SuspendLayout();
			this->f_gropServer->SuspendLayout();
			this->f_splitServer->Panel1->SuspendLayout();
			this->f_splitServer->Panel2->SuspendLayout();
			this->f_splitServer->SuspendLayout();
			this->f_gropLocal->SuspendLayout();
			this->f_splitLocal->Panel1->SuspendLayout();
			this->f_splitLocal->Panel2->SuspendLayout();
			this->f_splitLocal->SuspendLayout();
			this->tabPicturePuzzle->SuspendLayout();
			this->p_panelBase->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->p_picturePuzzle))->BeginInit();
			this->tabBinaryClock->SuspendLayout();
			this->tabTetris->SuspendLayout();
			this->g_panelScore->SuspendLayout();
			this->g_panelTetris->SuspendLayout();
			this->tabArrow->SuspendLayout();
			this->tabDirectX->SuspendLayout();
			this->contextTaskTray->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip
			// 
			this->menuStrip->BackColor = System::Drawing::Color::GhostWhite;
			this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->menuFile, this->menuAction, 
				this->menuOption, this->menuHelp});
			this->menuStrip->Location = System::Drawing::Point(0, 0);
			this->menuStrip->Name = L"menuStrip";
			this->menuStrip->Size = System::Drawing::Size(684, 26);
			this->menuStrip->TabIndex = 0;
			this->menuStrip->Text = L"menuStrip";
			// 
			// menuFile
			// 
			this->menuFile->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->menuView, this->menuHide, 
				this->menuFileSeparator, this->menuExit});
			this->menuFile->Name = L"menuFile";
			this->menuFile->Size = System::Drawing::Size(85, 22);
			this->menuFile->Text = L"ファイル(&F)";
			// 
			// menuView
			// 
			this->menuView->Enabled = false;
			this->menuView->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"menuView.Image")));
			this->menuView->Name = L"menuView";
			this->menuView->Size = System::Drawing::Size(119, 22);
			this->menuView->Text = L"表示(&V)";
			this->menuView->EnabledChanged += gcnew System::EventHandler(this, &MainForm::MenuEnabledChanged);
			this->menuView->Click += gcnew System::EventHandler(this, &MainForm::menuView_Click);
			// 
			// menuHide
			// 
			this->menuHide->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"menuHide.Image")));
			this->menuHide->Name = L"menuHide";
			this->menuHide->Size = System::Drawing::Size(119, 22);
			this->menuHide->Text = L"隠す(&H)";
			this->menuHide->EnabledChanged += gcnew System::EventHandler(this, &MainForm::MenuEnabledChanged);
			this->menuHide->Click += gcnew System::EventHandler(this, &MainForm::menuHide_Click);
			// 
			// menuFileSeparator
			// 
			this->menuFileSeparator->Name = L"menuFileSeparator";
			this->menuFileSeparator->Size = System::Drawing::Size(116, 6);
			// 
			// menuExit
			// 
			this->menuExit->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"menuExit.Image")));
			this->menuExit->Name = L"menuExit";
			this->menuExit->Size = System::Drawing::Size(119, 22);
			this->menuExit->Text = L"終了(&X)";
			this->menuExit->EnabledChanged += gcnew System::EventHandler(this, &MainForm::MenuEnabledChanged);
			this->menuExit->Click += gcnew System::EventHandler(this, &MainForm::menuExit_Click);
			// 
			// menuAction
			// 
			this->menuAction->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {this->menuReport, 
				this->menuTcpServer, this->menuFtpClient, this->menuPicturePuzzle, this->menuBinaryClock, this->menuTetris, this->menuArrow});
			this->menuAction->Name = L"menuAction";
			this->menuAction->Size = System::Drawing::Size(98, 22);
			this->menuAction->Text = L"アクション(&A)";
			// 
			// menuReport
			// 
			this->menuReport->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(8) {this->menuOpen, 
				this->menuSave, this->menuSaveAs, this->menuReportSeparator01, this->menuUndo, this->menuRedo, this->menuReportSeparator02, this->menuClear});
			this->menuReport->Name = L"menuReport";
			this->menuReport->Size = System::Drawing::Size(190, 22);
			this->menuReport->Text = L"レポート編集(&R)";
			// 
			// menuOpen
			// 
			this->menuOpen->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"menuOpen.Image")));
			this->menuOpen->Name = L"menuOpen";
			this->menuOpen->Size = System::Drawing::Size(202, 22);
			this->menuOpen->Text = L"開く(&O)";
			this->menuOpen->EnabledChanged += gcnew System::EventHandler(this, &MainForm::MenuEnabledChanged);
			this->menuOpen->Click += gcnew System::EventHandler(this, &MainForm::menuOpen_Click);
			// 
			// menuSave
			// 
			this->menuSave->Enabled = false;
			this->menuSave->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"menuSave.Image")));
			this->menuSave->Name = L"menuSave";
			this->menuSave->Size = System::Drawing::Size(202, 22);
			this->menuSave->Text = L"保存(&S)";
			this->menuSave->EnabledChanged += gcnew System::EventHandler(this, &MainForm::MenuEnabledChanged);
			this->menuSave->Click += gcnew System::EventHandler(this, &MainForm::menuSave_Click);
			// 
			// menuSaveAs
			// 
			this->menuSaveAs->Enabled = false;
			this->menuSaveAs->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"menuSaveAs.Image")));
			this->menuSaveAs->Name = L"menuSaveAs";
			this->menuSaveAs->Size = System::Drawing::Size(202, 22);
			this->menuSaveAs->Text = L"名前を付けて保存(&A)...";
			this->menuSaveAs->Click += gcnew System::EventHandler(this, &MainForm::menuSaveAs_Click);
			// 
			// menuReportSeparator01
			// 
			this->menuReportSeparator01->Name = L"menuReportSeparator01";
			this->menuReportSeparator01->Size = System::Drawing::Size(199, 6);
			// 
			// menuUndo
			// 
			this->menuUndo->Enabled = false;
			this->menuUndo->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"menuUndo.Image")));
			this->menuUndo->Name = L"menuUndo";
			this->menuUndo->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Z));
			this->menuUndo->Size = System::Drawing::Size(202, 22);
			this->menuUndo->Text = L"元に戻す(&U)";
			this->menuUndo->EnabledChanged += gcnew System::EventHandler(this, &MainForm::MenuEnabledChanged);
			this->menuUndo->Click += gcnew System::EventHandler(this, &MainForm::menuUndo_Click);
			// 
			// menuRedo
			// 
			this->menuRedo->Enabled = false;
			this->menuRedo->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"menuRedo.Image")));
			this->menuRedo->Name = L"menuRedo";
			this->menuRedo->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Y));
			this->menuRedo->Size = System::Drawing::Size(202, 22);
			this->menuRedo->Text = L"やり直し(&R)";
			this->menuRedo->EnabledChanged += gcnew System::EventHandler(this, &MainForm::MenuEnabledChanged);
			this->menuRedo->Click += gcnew System::EventHandler(this, &MainForm::menuRedo_Click);
			// 
			// menuReportSeparator02
			// 
			this->menuReportSeparator02->Name = L"menuReportSeparator02";
			this->menuReportSeparator02->Size = System::Drawing::Size(199, 6);
			// 
			// menuClear
			// 
			this->menuClear->Enabled = false;
			this->menuClear->Name = L"menuClear";
			this->menuClear->Size = System::Drawing::Size(202, 22);
			this->menuClear->Text = L"クリア(&C)";
			this->menuClear->Click += gcnew System::EventHandler(this, &MainForm::menuClear_Click);
			// 
			// menuTcpServer
			// 
			this->menuTcpServer->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->menuTcpStart, 
				this->menuTcpStop, this->menuCharCode, this->menuTcpClient});
			this->menuTcpServer->Name = L"menuTcpServer";
			this->menuTcpServer->Size = System::Drawing::Size(190, 22);
			this->menuTcpServer->Text = L"TCPサーバ(&T)";
			// 
			// menuTcpStart
			// 
			this->menuTcpStart->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"menuTcpStart.Image")));
			this->menuTcpStart->Name = L"menuTcpStart";
			this->menuTcpStart->Size = System::Drawing::Size(189, 22);
			this->menuTcpStart->Text = L"スタート(&S)";
			this->menuTcpStart->EnabledChanged += gcnew System::EventHandler(this, &MainForm::MenuEnabledChanged);
			this->menuTcpStart->Click += gcnew System::EventHandler(this, &MainForm::menuTcpStart_Click);
			// 
			// menuTcpStop
			// 
			this->menuTcpStop->Enabled = false;
			this->menuTcpStop->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"menuTcpStop.Image")));
			this->menuTcpStop->Name = L"menuTcpStop";
			this->menuTcpStop->Size = System::Drawing::Size(189, 22);
			this->menuTcpStop->Text = L"ストップ(&E)";
			this->menuTcpStop->EnabledChanged += gcnew System::EventHandler(this, &MainForm::MenuEnabledChanged);
			this->menuTcpStop->Click += gcnew System::EventHandler(this, &MainForm::menuTcpStop_Click);
			// 
			// menuCharCode
			// 
			this->menuCharCode->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->menuAscii, 
				this->menuUtf8, this->menuDefault});
			this->menuCharCode->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"menuCharCode.Image")));
			this->menuCharCode->Name = L"menuCharCode";
			this->menuCharCode->Size = System::Drawing::Size(189, 22);
			this->menuCharCode->Text = L"文字コード(&C)";
			// 
			// menuAscii
			// 
			this->menuAscii->Checked = true;
			this->menuAscii->CheckState = System::Windows::Forms::CheckState::Checked;
			this->menuAscii->Name = L"menuAscii";
			this->menuAscii->Size = System::Drawing::Size(137, 22);
			this->menuAscii->Text = L"ASCII(&A)";
			this->menuAscii->EnabledChanged += gcnew System::EventHandler(this, &MainForm::MenuEnabledChanged);
			this->menuAscii->Click += gcnew System::EventHandler(this, &MainForm::menuAscii_Click);
			// 
			// menuUtf8
			// 
			this->menuUtf8->Name = L"menuUtf8";
			this->menuUtf8->Size = System::Drawing::Size(137, 22);
			this->menuUtf8->Text = L"UTF-8(&U)";
			this->menuUtf8->EnabledChanged += gcnew System::EventHandler(this, &MainForm::MenuEnabledChanged);
			this->menuUtf8->Click += gcnew System::EventHandler(this, &MainForm::menuUtf8_Click);
			// 
			// menuDefault
			// 
			this->menuDefault->Name = L"menuDefault";
			this->menuDefault->Size = System::Drawing::Size(137, 22);
			this->menuDefault->Text = L"Default(&D)";
			this->menuDefault->Click += gcnew System::EventHandler(this, &MainForm::menuDefault_Click);
			// 
			// menuTcpClient
			// 
			this->menuTcpClient->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"menuTcpClient.Image")));
			this->menuTcpClient->Name = L"menuTcpClient";
			this->menuTcpClient->Size = System::Drawing::Size(189, 22);
			this->menuTcpClient->Text = L"TCPクライアント(&C)";
			this->menuTcpClient->EnabledChanged += gcnew System::EventHandler(this, &MainForm::MenuEnabledChanged);
			this->menuTcpClient->Click += gcnew System::EventHandler(this, &MainForm::menuTcpClient_Click);
			// 
			// menuFtpClient
			// 
			this->menuFtpClient->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->menuFtpConnect, 
				this->menuFtpDisConnect});
			this->menuFtpClient->Name = L"menuFtpClient";
			this->menuFtpClient->Size = System::Drawing::Size(190, 22);
			this->menuFtpClient->Text = L"FTPクライアント(&F)";
			// 
			// menuFtpConnect
			// 
			this->menuFtpConnect->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"menuFtpConnect.Image")));
			this->menuFtpConnect->Name = L"menuFtpConnect";
			this->menuFtpConnect->Size = System::Drawing::Size(119, 22);
			this->menuFtpConnect->Text = L"接続(&C)";
			this->menuFtpConnect->EnabledChanged += gcnew System::EventHandler(this, &MainForm::MenuEnabledChanged);
			this->menuFtpConnect->Click += gcnew System::EventHandler(this, &MainForm::menuFtpConnect_Click);
			// 
			// menuFtpDisConnect
			// 
			this->menuFtpDisConnect->Enabled = false;
			this->menuFtpDisConnect->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"menuFtpDisConnect.Image")));
			this->menuFtpDisConnect->Name = L"menuFtpDisConnect";
			this->menuFtpDisConnect->Size = System::Drawing::Size(119, 22);
			this->menuFtpDisConnect->Text = L"切断(&D)";
			this->menuFtpDisConnect->EnabledChanged += gcnew System::EventHandler(this, &MainForm::MenuEnabledChanged);
			this->menuFtpDisConnect->Click += gcnew System::EventHandler(this, &MainForm::menuFtpDisConnect_Click);
			// 
			// menuPicturePuzzle
			// 
			this->menuPicturePuzzle->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->menuPictureLoad});
			this->menuPicturePuzzle->Name = L"menuPicturePuzzle";
			this->menuPicturePuzzle->Size = System::Drawing::Size(190, 22);
			this->menuPicturePuzzle->Text = L"写真パズル(&P)";
			// 
			// menuPictureLoad
			// 
			this->menuPictureLoad->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"menuPictureLoad.Image")));
			this->menuPictureLoad->Name = L"menuPictureLoad";
			this->menuPictureLoad->Size = System::Drawing::Size(153, 22);
			this->menuPictureLoad->Text = L"写真読込み(&L)";
			this->menuPictureLoad->EnabledChanged += gcnew System::EventHandler(this, &MainForm::MenuEnabledChanged);
			this->menuPictureLoad->Click += gcnew System::EventHandler(this, &MainForm::menuPictureLoad_Click);
			// 
			// menuBinaryClock
			// 
			this->menuBinaryClock->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->menuTimer, 
				this->menuColor});
			this->menuBinaryClock->Name = L"menuBinaryClock";
			this->menuBinaryClock->Size = System::Drawing::Size(190, 22);
			this->menuBinaryClock->Text = L"バイナリクロック(&B)";
			// 
			// menuTimer
			// 
			this->menuTimer->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"menuTimer.Image")));
			this->menuTimer->Name = L"menuTimer";
			this->menuTimer->Size = System::Drawing::Size(142, 22);
			this->menuTimer->Text = L"タイマー(&T)";
			this->menuTimer->EnabledChanged += gcnew System::EventHandler(this, &MainForm::MenuEnabledChanged);
			this->menuTimer->Click += gcnew System::EventHandler(this, &MainForm::menuTimer_Click);
			// 
			// menuColor
			// 
			this->menuColor->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->menuOnColor, 
				this->menuOffColor});
			this->menuColor->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"menuColor.Image")));
			this->menuColor->Name = L"menuColor";
			this->menuColor->Size = System::Drawing::Size(142, 22);
			this->menuColor->Text = L"色設定(&C)";
			// 
			// menuOnColor
			// 
			this->menuOnColor->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"menuOnColor.Image")));
			this->menuOnColor->Name = L"menuOnColor";
			this->menuOnColor->Size = System::Drawing::Size(116, 22);
			this->menuOnColor->Text = L"ON(&O)";
			this->menuOnColor->Click += gcnew System::EventHandler(this, &MainForm::menuOnColor_Click);
			// 
			// menuOffColor
			// 
			this->menuOffColor->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"menuOffColor.Image")));
			this->menuOffColor->Name = L"menuOffColor";
			this->menuOffColor->Size = System::Drawing::Size(116, 22);
			this->menuOffColor->Text = L"OFF(&F)";
			this->menuOffColor->Click += gcnew System::EventHandler(this, &MainForm::menuOffColor_Click);
			// 
			// menuTetris
			// 
			this->menuTetris->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->menuRanking, 
				this->menuSound, this->menuRemote});
			this->menuTetris->Name = L"menuTetris";
			this->menuTetris->Size = System::Drawing::Size(190, 22);
			this->menuTetris->Text = L"TETRiS(&G)";
			// 
			// menuRanking
			// 
			this->menuRanking->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"menuRanking.Image")));
			this->menuRanking->Name = L"menuRanking";
			this->menuRanking->Size = System::Drawing::Size(166, 22);
			this->menuRanking->Text = L"ランキング(&R)";
			this->menuRanking->EnabledChanged += gcnew System::EventHandler(this, &MainForm::MenuEnabledChanged);
			this->menuRanking->Click += gcnew System::EventHandler(this, &MainForm::menuRanking_Click);
			// 
			// menuSound
			// 
			this->menuSound->Name = L"menuSound";
			this->menuSound->Size = System::Drawing::Size(166, 22);
			this->menuSound->Text = L"サウンド(&S)";
			this->menuSound->CheckedChanged += gcnew System::EventHandler(this, &MainForm::menuSound_CheckedChanged);
			this->menuSound->Click += gcnew System::EventHandler(this, &MainForm::menuSound_Click);
			// 
			// menuRemote
			// 
			this->menuRemote->Name = L"menuRemote";
			this->menuRemote->Size = System::Drawing::Size(166, 22);
			this->menuRemote->Text = L"リモート表示(&V)";
			this->menuRemote->CheckedChanged += gcnew System::EventHandler(this, &MainForm::menuRemote_CheckedChanged);
			this->menuRemote->Click += gcnew System::EventHandler(this, &MainForm::menuRemote_Click);
			// 
			// menuArrow
			// 
			this->menuArrow->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->menuReset});
			this->menuArrow->Name = L"menuArrow";
			this->menuArrow->Size = System::Drawing::Size(190, 22);
			this->menuArrow->Text = L"ARROW(&A)";
			// 
			// menuReset
			// 
			this->menuReset->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"menuReset.Image")));
			this->menuReset->Name = L"menuReset";
			this->menuReset->Size = System::Drawing::Size(142, 22);
			this->menuReset->Text = L"リセット(&R)";
			this->menuReset->EnabledChanged += gcnew System::EventHandler(this, &MainForm::MenuEnabledChanged);
			this->menuReset->Click += gcnew System::EventHandler(this, &MainForm::menuReset_Click);
			// 
			// menuOption
			// 
			this->menuOption->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->menuSizeReset, 
				this->menuMemoryRelease, this->menuStartUp});
			this->menuOption->Name = L"menuOption";
			this->menuOption->Size = System::Drawing::Size(99, 22);
			this->menuOption->Text = L"オプション(&O)";
			// 
			// menuSizeReset
			// 
			this->menuSizeReset->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"menuSizeReset.Image")));
			this->menuSizeReset->Name = L"menuSizeReset";
			this->menuSizeReset->Size = System::Drawing::Size(178, 22);
			this->menuSizeReset->Text = L"サイズリセット(&R)";
			this->menuSizeReset->Click += gcnew System::EventHandler(this, &MainForm::menuSizeReset_Click);
			// 
			// menuMemoryRelease
			// 
			this->menuMemoryRelease->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"menuMemoryRelease.Image")));
			this->menuMemoryRelease->Name = L"menuMemoryRelease";
			this->menuMemoryRelease->Size = System::Drawing::Size(178, 22);
			this->menuMemoryRelease->Text = L"メモリ解放(&M)";
			this->menuMemoryRelease->Click += gcnew System::EventHandler(this, &MainForm::menuMemoryRelease_Click);
			// 
			// menuStartUp
			// 
			this->menuStartUp->Name = L"menuStartUp";
			this->menuStartUp->Size = System::Drawing::Size(178, 22);
			this->menuStartUp->Text = L"スタートアップ(&S)";
			this->menuStartUp->Click += gcnew System::EventHandler(this, &MainForm::menuStartUp_Click);
			// 
			// menuHelp
			// 
			this->menuHelp->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->menuVersion});
			this->menuHelp->Name = L"menuHelp";
			this->menuHelp->Size = System::Drawing::Size(75, 22);
			this->menuHelp->Text = L"ヘルプ(&H)";
			// 
			// menuVersion
			// 
			this->menuVersion->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"menuVersion.Image")));
			this->menuVersion->Name = L"menuVersion";
			this->menuVersion->Size = System::Drawing::Size(178, 22);
			this->menuVersion->Text = L"バージョン情報(&A)";
			this->menuVersion->Click += gcnew System::EventHandler(this, &MainForm::menuVersion_Click);
			// 
			// toolStrip
			// 
			this->toolStrip->BackColor = System::Drawing::Color::GhostWhite;
			this->toolStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(23) {this->toolExit, this->toolSeparator01, 
				this->toolOpen, this->toolSave, this->toolUndo, this->toolRedo, this->toolSeparator02, this->toolTcpStart, this->toolTcpStop, 
				this->toolTcpClient, this->toolSeparator03, this->toolFtpConnect, this->toolFtpDisConnect, this->toolSeparator04, this->toolPictureLoad, 
				this->toolSeparator05, this->toolTimer, this->toolSeparator06, this->toolRanking, this->toolSeparator07, this->toolReset, this->toolSeparatorDebug, 
				this->toolDebug});
			this->toolStrip->Location = System::Drawing::Point(0, 26);
			this->toolStrip->Name = L"toolStrip";
			this->toolStrip->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->toolStrip->Size = System::Drawing::Size(684, 25);
			this->toolStrip->TabIndex = 1;
			this->toolStrip->Text = L"toolStrip";
			// 
			// toolExit
			// 
			this->toolExit->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolExit->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolExit.Image")));
			this->toolExit->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolExit->Name = L"toolExit";
			this->toolExit->Size = System::Drawing::Size(23, 22);
			this->toolExit->Text = L"終了";
			this->toolExit->Click += gcnew System::EventHandler(this, &MainForm::ToolButtonClick);
			// 
			// toolSeparator01
			// 
			this->toolSeparator01->Name = L"toolSeparator01";
			this->toolSeparator01->Size = System::Drawing::Size(6, 25);
			// 
			// toolOpen
			// 
			this->toolOpen->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolOpen->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolOpen.Image")));
			this->toolOpen->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolOpen->Name = L"toolOpen";
			this->toolOpen->Size = System::Drawing::Size(23, 22);
			this->toolOpen->Text = L"開く";
			this->toolOpen->Click += gcnew System::EventHandler(this, &MainForm::ToolButtonClick);
			// 
			// toolSave
			// 
			this->toolSave->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolSave->Enabled = false;
			this->toolSave->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolSave.Image")));
			this->toolSave->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolSave->Name = L"toolSave";
			this->toolSave->Size = System::Drawing::Size(23, 22);
			this->toolSave->Text = L"保存";
			this->toolSave->Click += gcnew System::EventHandler(this, &MainForm::ToolButtonClick);
			// 
			// toolUndo
			// 
			this->toolUndo->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolUndo->Enabled = false;
			this->toolUndo->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolUndo.Image")));
			this->toolUndo->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolUndo->Name = L"toolUndo";
			this->toolUndo->Size = System::Drawing::Size(23, 22);
			this->toolUndo->Text = L"元に戻す";
			this->toolUndo->Click += gcnew System::EventHandler(this, &MainForm::ToolButtonClick);
			// 
			// toolRedo
			// 
			this->toolRedo->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolRedo->Enabled = false;
			this->toolRedo->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolRedo.Image")));
			this->toolRedo->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolRedo->Name = L"toolRedo";
			this->toolRedo->Size = System::Drawing::Size(23, 22);
			this->toolRedo->Text = L"やり直し";
			this->toolRedo->Click += gcnew System::EventHandler(this, &MainForm::ToolButtonClick);
			// 
			// toolSeparator02
			// 
			this->toolSeparator02->Name = L"toolSeparator02";
			this->toolSeparator02->Size = System::Drawing::Size(6, 25);
			// 
			// toolTcpStart
			// 
			this->toolTcpStart->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolTcpStart->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolTcpStart.Image")));
			this->toolTcpStart->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolTcpStart->Name = L"toolTcpStart";
			this->toolTcpStart->Size = System::Drawing::Size(23, 22);
			this->toolTcpStart->Text = L"TCPスタート";
			this->toolTcpStart->Click += gcnew System::EventHandler(this, &MainForm::ToolButtonClick);
			// 
			// toolTcpStop
			// 
			this->toolTcpStop->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolTcpStop->Enabled = false;
			this->toolTcpStop->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolTcpStop.Image")));
			this->toolTcpStop->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolTcpStop->Name = L"toolTcpStop";
			this->toolTcpStop->Size = System::Drawing::Size(23, 22);
			this->toolTcpStop->Text = L"TCPストップ";
			this->toolTcpStop->Click += gcnew System::EventHandler(this, &MainForm::ToolButtonClick);
			// 
			// toolTcpClient
			// 
			this->toolTcpClient->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolTcpClient->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolTcpClient.Image")));
			this->toolTcpClient->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolTcpClient->Name = L"toolTcpClient";
			this->toolTcpClient->Size = System::Drawing::Size(23, 22);
			this->toolTcpClient->Text = L"TCPクライアント";
			this->toolTcpClient->Click += gcnew System::EventHandler(this, &MainForm::ToolButtonClick);
			// 
			// toolSeparator03
			// 
			this->toolSeparator03->Name = L"toolSeparator03";
			this->toolSeparator03->Size = System::Drawing::Size(6, 25);
			// 
			// toolFtpConnect
			// 
			this->toolFtpConnect->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolFtpConnect->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolFtpConnect.Image")));
			this->toolFtpConnect->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolFtpConnect->Name = L"toolFtpConnect";
			this->toolFtpConnect->Size = System::Drawing::Size(23, 22);
			this->toolFtpConnect->Text = L"FTP接続";
			this->toolFtpConnect->Click += gcnew System::EventHandler(this, &MainForm::ToolButtonClick);
			// 
			// toolFtpDisConnect
			// 
			this->toolFtpDisConnect->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolFtpDisConnect->Enabled = false;
			this->toolFtpDisConnect->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolFtpDisConnect.Image")));
			this->toolFtpDisConnect->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolFtpDisConnect->Name = L"toolFtpDisConnect";
			this->toolFtpDisConnect->Size = System::Drawing::Size(23, 22);
			this->toolFtpDisConnect->Text = L"FTP切断";
			this->toolFtpDisConnect->Click += gcnew System::EventHandler(this, &MainForm::ToolButtonClick);
			// 
			// toolSeparator04
			// 
			this->toolSeparator04->Name = L"toolSeparator04";
			this->toolSeparator04->Size = System::Drawing::Size(6, 25);
			// 
			// toolPictureLoad
			// 
			this->toolPictureLoad->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolPictureLoad->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolPictureLoad.Image")));
			this->toolPictureLoad->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolPictureLoad->Name = L"toolPictureLoad";
			this->toolPictureLoad->Size = System::Drawing::Size(23, 22);
			this->toolPictureLoad->Text = L"写真読込み";
			this->toolPictureLoad->Click += gcnew System::EventHandler(this, &MainForm::ToolButtonClick);
			// 
			// toolSeparator05
			// 
			this->toolSeparator05->Name = L"toolSeparator05";
			this->toolSeparator05->Size = System::Drawing::Size(6, 25);
			// 
			// toolTimer
			// 
			this->toolTimer->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolTimer->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolTimer.Image")));
			this->toolTimer->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolTimer->Name = L"toolTimer";
			this->toolTimer->Size = System::Drawing::Size(23, 22);
			this->toolTimer->Text = L"タイマー";
			this->toolTimer->Click += gcnew System::EventHandler(this, &MainForm::ToolButtonClick);
			// 
			// toolSeparator06
			// 
			this->toolSeparator06->Name = L"toolSeparator06";
			this->toolSeparator06->Size = System::Drawing::Size(6, 25);
			// 
			// toolRanking
			// 
			this->toolRanking->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolRanking->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolRanking.Image")));
			this->toolRanking->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolRanking->Name = L"toolRanking";
			this->toolRanking->Size = System::Drawing::Size(23, 22);
			this->toolRanking->Text = L"TETRiSランキング";
			this->toolRanking->Click += gcnew System::EventHandler(this, &MainForm::ToolButtonClick);
			// 
			// toolSeparator07
			// 
			this->toolSeparator07->Name = L"toolSeparator07";
			this->toolSeparator07->Size = System::Drawing::Size(6, 25);
			// 
			// toolReset
			// 
			this->toolReset->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolReset->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolReset.Image")));
			this->toolReset->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolReset->Name = L"toolReset";
			this->toolReset->Size = System::Drawing::Size(23, 22);
			this->toolReset->Text = L"ARROWリセット";
			this->toolReset->Click += gcnew System::EventHandler(this, &MainForm::ToolButtonClick);
			// 
			// toolSeparatorDebug
			// 
			this->toolSeparatorDebug->Name = L"toolSeparatorDebug";
			this->toolSeparatorDebug->Size = System::Drawing::Size(6, 25);
			// 
			// toolDebug
			// 
			this->toolDebug->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolDebug->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolDebug.Image")));
			this->toolDebug->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolDebug->Name = L"toolDebug";
			this->toolDebug->Size = System::Drawing::Size(23, 22);
			this->toolDebug->Text = L"デバッグ";
			this->toolDebug->Click += gcnew System::EventHandler(this, &MainForm::toolDebug_Click);
			// 
			// statusStrip
			// 
			this->statusStrip->BackColor = System::Drawing::Color::GhostWhite;
			this->statusStrip->Location = System::Drawing::Point(0, 640);
			this->statusStrip->Name = L"statusStrip";
			this->statusStrip->Size = System::Drawing::Size(684, 22);
			this->statusStrip->TabIndex = 3;
			this->statusStrip->Text = L"statusStrip";
			// 
			// tabControl
			// 
			this->tabControl->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->tabControl->Controls->Add(this->tabReport);
			this->tabControl->Controls->Add(this->tabTcpServer);
			this->tabControl->Controls->Add(this->tabFtpClient);
			this->tabControl->Controls->Add(this->tabPicturePuzzle);
			this->tabControl->Controls->Add(this->tabBinaryClock);
			this->tabControl->Controls->Add(this->tabTetris);
			this->tabControl->Controls->Add(this->tabArrow);
			this->tabControl->Controls->Add(this->tabDirectX);
			this->tabControl->Location = System::Drawing::Point(12, 52);
			this->tabControl->Name = L"tabControl";
			this->tabControl->SelectedIndex = 0;
			this->tabControl->Size = System::Drawing::Size(660, 585);
			this->tabControl->TabIndex = 2;
			this->tabControl->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::tabControl_SelectedIndexChanged);
			// 
			// tabReport
			// 
			this->tabReport->AllowDrop = true;
			this->tabReport->BackColor = System::Drawing::Color::GhostWhite;
			this->tabReport->Controls->Add(this->r_buttonAddRow);
			this->tabReport->Controls->Add(this->r_buttonAdd);
			this->tabReport->Controls->Add(this->r_labelFileName);
			this->tabReport->Controls->Add(this->r_labelSection);
			this->tabReport->Controls->Add(this->r_buttonRemoveRow);
			this->tabReport->Controls->Add(this->r_buttonInsertRow);
			this->tabReport->Controls->Add(this->r_buttonRemove);
			this->tabReport->Controls->Add(this->r_buttonInsert);
			this->tabReport->Controls->Add(this->r_comboSection);
			this->tabReport->Controls->Add(this->r_buttonSave);
			this->tabReport->Controls->Add(this->r_gridReport);
			this->tabReport->Controls->Add(this->r_buttonLoad);
			this->tabReport->Controls->Add(this->r_textFileName);
			this->tabReport->Location = System::Drawing::Point(4, 22);
			this->tabReport->Name = L"tabReport";
			this->tabReport->Padding = System::Windows::Forms::Padding(3);
			this->tabReport->Size = System::Drawing::Size(652, 559);
			this->tabReport->TabIndex = 0;
			this->tabReport->Text = L"レポート編集";
			this->tabReport->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &MainForm::tabReport_DragDrop);
			this->tabReport->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &MainForm::tabReport_DragEnter);
			// 
			// r_buttonAddRow
			// 
			this->r_buttonAddRow->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->r_buttonAddRow->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"r_buttonAddRow.Image")));
			this->r_buttonAddRow->Location = System::Drawing::Point(130, 530);
			this->r_buttonAddRow->Name = L"r_buttonAddRow";
			this->r_buttonAddRow->Size = System::Drawing::Size(25, 23);
			this->r_buttonAddRow->TabIndex = 8;
			this->r_buttonAddRow->UseVisualStyleBackColor = false;
			this->r_buttonAddRow->Visible = false;
			this->r_buttonAddRow->Click += gcnew System::EventHandler(this, &MainForm::r_buttonAddRow_Click);
			// 
			// r_buttonAdd
			// 
			this->r_buttonAdd->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->r_buttonAdd->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"r_buttonAdd.Image")));
			this->r_buttonAdd->Location = System::Drawing::Point(37, 530);
			this->r_buttonAdd->Name = L"r_buttonAdd";
			this->r_buttonAdd->Size = System::Drawing::Size(25, 23);
			this->r_buttonAdd->TabIndex = 5;
			this->r_buttonAdd->UseVisualStyleBackColor = false;
			this->r_buttonAdd->Visible = false;
			this->r_buttonAdd->Click += gcnew System::EventHandler(this, &MainForm::r_buttonAdd_Click);
			// 
			// r_labelFileName
			// 
			this->r_labelFileName->AutoSize = true;
			this->r_labelFileName->Location = System::Drawing::Point(6, 11);
			this->r_labelFileName->Name = L"r_labelFileName";
			this->r_labelFileName->Size = System::Drawing::Size(51, 12);
			this->r_labelFileName->TabIndex = 11;
			this->r_labelFileName->Text = L"ファイル名";
			// 
			// r_labelSection
			// 
			this->r_labelSection->AutoSize = true;
			this->r_labelSection->Location = System::Drawing::Point(9, 36);
			this->r_labelSection->Name = L"r_labelSection";
			this->r_labelSection->Size = System::Drawing::Size(48, 12);
			this->r_labelSection->TabIndex = 12;
			this->r_labelSection->Text = L"セクション";
			// 
			// r_buttonRemoveRow
			// 
			this->r_buttonRemoveRow->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->r_buttonRemoveRow->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"r_buttonRemoveRow.Image")));
			this->r_buttonRemoveRow->Location = System::Drawing::Point(161, 530);
			this->r_buttonRemoveRow->Name = L"r_buttonRemoveRow";
			this->r_buttonRemoveRow->Size = System::Drawing::Size(25, 23);
			this->r_buttonRemoveRow->TabIndex = 9;
			this->r_buttonRemoveRow->UseVisualStyleBackColor = false;
			this->r_buttonRemoveRow->Visible = false;
			this->r_buttonRemoveRow->Click += gcnew System::EventHandler(this, &MainForm::r_buttonRemoveRow_Click);
			// 
			// r_buttonInsertRow
			// 
			this->r_buttonInsertRow->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->r_buttonInsertRow->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"r_buttonInsertRow.Image")));
			this->r_buttonInsertRow->Location = System::Drawing::Point(99, 530);
			this->r_buttonInsertRow->Name = L"r_buttonInsertRow";
			this->r_buttonInsertRow->Size = System::Drawing::Size(25, 23);
			this->r_buttonInsertRow->TabIndex = 7;
			this->r_buttonInsertRow->UseVisualStyleBackColor = false;
			this->r_buttonInsertRow->Visible = false;
			this->r_buttonInsertRow->Click += gcnew System::EventHandler(this, &MainForm::r_buttonInsertRow_Click);
			// 
			// r_buttonRemove
			// 
			this->r_buttonRemove->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->r_buttonRemove->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"r_buttonRemove.Image")));
			this->r_buttonRemove->Location = System::Drawing::Point(68, 530);
			this->r_buttonRemove->Name = L"r_buttonRemove";
			this->r_buttonRemove->Size = System::Drawing::Size(25, 23);
			this->r_buttonRemove->TabIndex = 6;
			this->r_buttonRemove->UseVisualStyleBackColor = false;
			this->r_buttonRemove->Visible = false;
			this->r_buttonRemove->Click += gcnew System::EventHandler(this, &MainForm::r_buttonRemove_Click);
			// 
			// r_buttonInsert
			// 
			this->r_buttonInsert->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->r_buttonInsert->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"r_buttonInsert.Image")));
			this->r_buttonInsert->Location = System::Drawing::Point(6, 530);
			this->r_buttonInsert->Name = L"r_buttonInsert";
			this->r_buttonInsert->Size = System::Drawing::Size(25, 23);
			this->r_buttonInsert->TabIndex = 4;
			this->r_buttonInsert->UseVisualStyleBackColor = false;
			this->r_buttonInsert->Visible = false;
			this->r_buttonInsert->Click += gcnew System::EventHandler(this, &MainForm::r_buttonInsert_Click);
			// 
			// r_comboSection
			// 
			this->r_comboSection->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->r_comboSection->FormattingEnabled = true;
			this->r_comboSection->Location = System::Drawing::Point(63, 33);
			this->r_comboSection->Name = L"r_comboSection";
			this->r_comboSection->Size = System::Drawing::Size(121, 20);
			this->r_comboSection->TabIndex = 2;
			this->r_comboSection->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::r_comboSection_SelectedIndexChanged);
			// 
			// r_buttonSave
			// 
			this->r_buttonSave->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->r_buttonSave->Enabled = false;
			this->r_buttonSave->Location = System::Drawing::Point(571, 530);
			this->r_buttonSave->Name = L"r_buttonSave";
			this->r_buttonSave->Size = System::Drawing::Size(75, 23);
			this->r_buttonSave->TabIndex = 10;
			this->r_buttonSave->Text = L"保存";
			this->r_buttonSave->UseVisualStyleBackColor = true;
			this->r_buttonSave->Click += gcnew System::EventHandler(this, &MainForm::r_buttonSave_Click);
			// 
			// r_gridReport
			// 
			this->r_gridReport->AllowUserToAddRows = false;
			this->r_gridReport->AllowUserToDeleteRows = false;
			this->r_gridReport->AllowUserToResizeColumns = false;
			this->r_gridReport->AllowUserToResizeRows = false;
			dataGridViewCellStyle1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), 
				static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->r_gridReport->AlternatingRowsDefaultCellStyle = dataGridViewCellStyle1;
			this->r_gridReport->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->r_gridReport->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->r_gridReport->Location = System::Drawing::Point(6, 59);
			this->r_gridReport->MultiSelect = false;
			this->r_gridReport->Name = L"r_gridReport";
			this->r_gridReport->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::AutoSizeToAllHeaders;
			this->r_gridReport->RowTemplate->Height = 21;
			this->r_gridReport->Size = System::Drawing::Size(640, 465);
			this->r_gridReport->TabIndex = 3;
			this->r_gridReport->CellEndEdit += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MainForm::r_gridReport_CellEndEdit);
			this->r_gridReport->SelectionChanged += gcnew System::EventHandler(this, &MainForm::r_gridReport_SelectionChanged);
			// 
			// r_buttonLoad
			// 
			this->r_buttonLoad->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->r_buttonLoad->Location = System::Drawing::Point(571, 6);
			this->r_buttonLoad->Name = L"r_buttonLoad";
			this->r_buttonLoad->Size = System::Drawing::Size(75, 23);
			this->r_buttonLoad->TabIndex = 1;
			this->r_buttonLoad->Text = L"読み込み";
			this->r_buttonLoad->UseVisualStyleBackColor = true;
			this->r_buttonLoad->Click += gcnew System::EventHandler(this, &MainForm::r_buttonLoad_Click);
			// 
			// r_textFileName
			// 
			this->r_textFileName->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->r_textFileName->Location = System::Drawing::Point(63, 8);
			this->r_textFileName->Name = L"r_textFileName";
			this->r_textFileName->Size = System::Drawing::Size(502, 19);
			this->r_textFileName->TabIndex = 0;
			// 
			// tabTcpServer
			// 
			this->tabTcpServer->BackColor = System::Drawing::Color::GhostWhite;
			this->tabTcpServer->Controls->Add(this->t_buttonSendMessage);
			this->tabTcpServer->Controls->Add(this->t_textMessage);
			this->tabTcpServer->Controls->Add(this->t_listMessage);
			this->tabTcpServer->Controls->Add(this->t_labelMessage);
			this->tabTcpServer->Controls->Add(this->t_buttonDisConnect);
			this->tabTcpServer->Controls->Add(this->t_comboRemoteIp);
			this->tabTcpServer->Controls->Add(this->t_buttonClearList);
			this->tabTcpServer->Controls->Add(this->t_textRemotePort);
			this->tabTcpServer->Controls->Add(this->t_labelRemotePort);
			this->tabTcpServer->Controls->Add(this->t_labelRemoteIp);
			this->tabTcpServer->Controls->Add(this->t_buttonStop);
			this->tabTcpServer->Controls->Add(this->t_buttonStart);
			this->tabTcpServer->Controls->Add(this->t_labelLocalPort);
			this->tabTcpServer->Controls->Add(this->t_labelLocalIp);
			this->tabTcpServer->Controls->Add(this->t_textLocalPort);
			this->tabTcpServer->Controls->Add(this->t_textLocalIp);
			this->tabTcpServer->Location = System::Drawing::Point(4, 22);
			this->tabTcpServer->Name = L"tabTcpServer";
			this->tabTcpServer->Padding = System::Windows::Forms::Padding(3);
			this->tabTcpServer->Size = System::Drawing::Size(652, 559);
			this->tabTcpServer->TabIndex = 1;
			this->tabTcpServer->Text = L"TCPサーバ";
			// 
			// t_buttonSendMessage
			// 
			this->t_buttonSendMessage->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->t_buttonSendMessage->Enabled = false;
			this->t_buttonSendMessage->Location = System::Drawing::Point(571, 533);
			this->t_buttonSendMessage->Name = L"t_buttonSendMessage";
			this->t_buttonSendMessage->Size = System::Drawing::Size(75, 23);
			this->t_buttonSendMessage->TabIndex = 15;
			this->t_buttonSendMessage->Text = L"送信";
			this->t_buttonSendMessage->UseVisualStyleBackColor = true;
			this->t_buttonSendMessage->Click += gcnew System::EventHandler(this, &MainForm::t_buttonSendMessage_Click);
			// 
			// t_textMessage
			// 
			this->t_textMessage->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->t_textMessage->Location = System::Drawing::Point(6, 535);
			this->t_textMessage->Name = L"t_textMessage";
			this->t_textMessage->Size = System::Drawing::Size(559, 19);
			this->t_textMessage->TabIndex = 14;
			// 
			// t_listMessage
			// 
			this->t_listMessage->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->t_listMessage->FormattingEnabled = true;
			this->t_listMessage->HorizontalScrollbar = true;
			this->t_listMessage->ItemHeight = 12;
			this->t_listMessage->Location = System::Drawing::Point(6, 93);
			this->t_listMessage->Name = L"t_listMessage";
			this->t_listMessage->Size = System::Drawing::Size(640, 436);
			this->t_listMessage->TabIndex = 13;
			// 
			// t_labelMessage
			// 
			this->t_labelMessage->AutoSize = true;
			this->t_labelMessage->Location = System::Drawing::Point(6, 78);
			this->t_labelMessage->Name = L"t_labelMessage";
			this->t_labelMessage->Size = System::Drawing::Size(58, 12);
			this->t_labelMessage->TabIndex = 12;
			this->t_labelMessage->Text = L"MESSAGE";
			// 
			// t_buttonDisConnect
			// 
			this->t_buttonDisConnect->Enabled = false;
			this->t_buttonDisConnect->Location = System::Drawing::Point(450, 6);
			this->t_buttonDisConnect->Name = L"t_buttonDisConnect";
			this->t_buttonDisConnect->Size = System::Drawing::Size(75, 23);
			this->t_buttonDisConnect->TabIndex = 10;
			this->t_buttonDisConnect->Text = L"切断";
			this->t_buttonDisConnect->UseVisualStyleBackColor = true;
			this->t_buttonDisConnect->Click += gcnew System::EventHandler(this, &MainForm::t_buttonDisConnect_Click);
			// 
			// t_comboRemoteIp
			// 
			this->t_comboRemoteIp->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->t_comboRemoteIp->Enabled = false;
			this->t_comboRemoteIp->FormattingEnabled = true;
			this->t_comboRemoteIp->Location = System::Drawing::Point(344, 8);
			this->t_comboRemoteIp->Name = L"t_comboRemoteIp";
			this->t_comboRemoteIp->Size = System::Drawing::Size(100, 20);
			this->t_comboRemoteIp->TabIndex = 8;
			this->t_comboRemoteIp->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::t_comboRemoteIp_SelectedIndexChanged);
			// 
			// t_buttonClearList
			// 
			this->t_buttonClearList->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->t_buttonClearList->Location = System::Drawing::Point(571, 64);
			this->t_buttonClearList->Name = L"t_buttonClearList";
			this->t_buttonClearList->Size = System::Drawing::Size(75, 23);
			this->t_buttonClearList->TabIndex = 11;
			this->t_buttonClearList->Text = L"クリア";
			this->t_buttonClearList->UseVisualStyleBackColor = true;
			this->t_buttonClearList->Click += gcnew System::EventHandler(this, &MainForm::t_buttonClearList_Click);
			// 
			// t_textRemotePort
			// 
			this->t_textRemotePort->BackColor = System::Drawing::SystemColors::Window;
			this->t_textRemotePort->ImeMode = System::Windows::Forms::ImeMode::Disable;
			this->t_textRemotePort->Location = System::Drawing::Point(344, 37);
			this->t_textRemotePort->Name = L"t_textRemotePort";
			this->t_textRemotePort->ReadOnly = true;
			this->t_textRemotePort->Size = System::Drawing::Size(100, 19);
			this->t_textRemotePort->TabIndex = 9;
			// 
			// t_labelRemotePort
			// 
			this->t_labelRemotePort->AutoSize = true;
			this->t_labelRemotePort->Location = System::Drawing::Point(269, 40);
			this->t_labelRemotePort->Name = L"t_labelRemotePort";
			this->t_labelRemotePort->Size = System::Drawing::Size(69, 12);
			this->t_labelRemotePort->TabIndex = 7;
			this->t_labelRemotePort->Text = L"Remote Port";
			// 
			// t_labelRemoteIp
			// 
			this->t_labelRemoteIp->AutoSize = true;
			this->t_labelRemoteIp->Location = System::Drawing::Point(280, 11);
			this->t_labelRemoteIp->Name = L"t_labelRemoteIp";
			this->t_labelRemoteIp->Size = System::Drawing::Size(58, 12);
			this->t_labelRemoteIp->TabIndex = 6;
			this->t_labelRemoteIp->Text = L"Remote IP";
			// 
			// t_buttonStop
			// 
			this->t_buttonStop->Enabled = false;
			this->t_buttonStop->Location = System::Drawing::Point(175, 35);
			this->t_buttonStop->Name = L"t_buttonStop";
			this->t_buttonStop->Size = System::Drawing::Size(75, 23);
			this->t_buttonStop->TabIndex = 5;
			this->t_buttonStop->Text = L"ストップ";
			this->t_buttonStop->UseVisualStyleBackColor = true;
			this->t_buttonStop->Click += gcnew System::EventHandler(this, &MainForm::t_buttonStop_Click);
			// 
			// t_buttonStart
			// 
			this->t_buttonStart->Location = System::Drawing::Point(175, 6);
			this->t_buttonStart->Name = L"t_buttonStart";
			this->t_buttonStart->Size = System::Drawing::Size(75, 23);
			this->t_buttonStart->TabIndex = 4;
			this->t_buttonStart->Text = L"スタート";
			this->t_buttonStart->UseVisualStyleBackColor = true;
			this->t_buttonStart->Click += gcnew System::EventHandler(this, &MainForm::t_buttonStart_Click);
			// 
			// t_labelLocalPort
			// 
			this->t_labelLocalPort->AutoSize = true;
			this->t_labelLocalPort->Location = System::Drawing::Point(6, 40);
			this->t_labelLocalPort->Name = L"t_labelLocalPort";
			this->t_labelLocalPort->Size = System::Drawing::Size(57, 12);
			this->t_labelLocalPort->TabIndex = 1;
			this->t_labelLocalPort->Text = L"Local Port";
			// 
			// t_labelLocalIp
			// 
			this->t_labelLocalIp->AutoSize = true;
			this->t_labelLocalIp->Location = System::Drawing::Point(17, 11);
			this->t_labelLocalIp->Name = L"t_labelLocalIp";
			this->t_labelLocalIp->Size = System::Drawing::Size(46, 12);
			this->t_labelLocalIp->TabIndex = 0;
			this->t_labelLocalIp->Text = L"Local IP";
			// 
			// t_textLocalPort
			// 
			this->t_textLocalPort->ImeMode = System::Windows::Forms::ImeMode::Disable;
			this->t_textLocalPort->Location = System::Drawing::Point(69, 37);
			this->t_textLocalPort->Name = L"t_textLocalPort";
			this->t_textLocalPort->Size = System::Drawing::Size(100, 19);
			this->t_textLocalPort->TabIndex = 3;
			// 
			// t_textLocalIp
			// 
			this->t_textLocalIp->ImeMode = System::Windows::Forms::ImeMode::Disable;
			this->t_textLocalIp->Location = System::Drawing::Point(69, 8);
			this->t_textLocalIp->Name = L"t_textLocalIp";
			this->t_textLocalIp->Size = System::Drawing::Size(100, 19);
			this->t_textLocalIp->TabIndex = 2;
			// 
			// tabFtpClient
			// 
			this->tabFtpClient->Controls->Add(this->f_buttonConnect);
			this->tabFtpClient->Controls->Add(this->f_buttonDownload);
			this->tabFtpClient->Controls->Add(this->f_buttonUpload);
			this->tabFtpClient->Controls->Add(this->f_splitFtp);
			this->tabFtpClient->Location = System::Drawing::Point(4, 22);
			this->tabFtpClient->Name = L"tabFtpClient";
			this->tabFtpClient->Padding = System::Windows::Forms::Padding(3);
			this->tabFtpClient->Size = System::Drawing::Size(652, 559);
			this->tabFtpClient->TabIndex = 2;
			this->tabFtpClient->Text = L"FTPクライアント";
			this->tabFtpClient->UseVisualStyleBackColor = true;
			// 
			// f_buttonConnect
			// 
			this->f_buttonConnect->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->f_buttonConnect->Location = System::Drawing::Point(571, 6);
			this->f_buttonConnect->Name = L"f_buttonConnect";
			this->f_buttonConnect->Size = System::Drawing::Size(75, 23);
			this->f_buttonConnect->TabIndex = 0;
			this->f_buttonConnect->Text = L"接続";
			this->f_buttonConnect->UseVisualStyleBackColor = true;
			this->f_buttonConnect->Click += gcnew System::EventHandler(this, &MainForm::f_buttonConnect_Click);
			// 
			// f_buttonDownload
			// 
			this->f_buttonDownload->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->f_buttonDownload->Enabled = false;
			this->f_buttonDownload->Location = System::Drawing::Point(409, 6);
			this->f_buttonDownload->Name = L"f_buttonDownload";
			this->f_buttonDownload->Size = System::Drawing::Size(75, 23);
			this->f_buttonDownload->TabIndex = 1;
			this->f_buttonDownload->Text = L"ダウンロード";
			this->f_buttonDownload->UseVisualStyleBackColor = true;
			this->f_buttonDownload->Click += gcnew System::EventHandler(this, &MainForm::f_buttonDownload_Click);
			// 
			// f_buttonUpload
			// 
			this->f_buttonUpload->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->f_buttonUpload->Enabled = false;
			this->f_buttonUpload->Location = System::Drawing::Point(490, 6);
			this->f_buttonUpload->Name = L"f_buttonUpload";
			this->f_buttonUpload->Size = System::Drawing::Size(75, 23);
			this->f_buttonUpload->TabIndex = 2;
			this->f_buttonUpload->Text = L"アップロード";
			this->f_buttonUpload->UseVisualStyleBackColor = true;
			this->f_buttonUpload->Click += gcnew System::EventHandler(this, &MainForm::f_buttonUpload_Click);
			// 
			// f_splitFtp
			// 
			this->f_splitFtp->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->f_splitFtp->Location = System::Drawing::Point(6, 35);
			this->f_splitFtp->Name = L"f_splitFtp";
			this->f_splitFtp->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// f_splitFtp.Panel1
			// 
			this->f_splitFtp->Panel1->Controls->Add(this->f_gropServer);
			// 
			// f_splitFtp.Panel2
			// 
			this->f_splitFtp->Panel2->Controls->Add(this->f_gropLocal);
			this->f_splitFtp->Size = System::Drawing::Size(640, 519);
			this->f_splitFtp->SplitterDistance = 260;
			this->f_splitFtp->TabIndex = 1;
			this->f_splitFtp->SplitterMoved += gcnew System::Windows::Forms::SplitterEventHandler(this, &MainForm::f_splitFtp_SplitterMoved);
			// 
			// f_gropServer
			// 
			this->f_gropServer->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->f_gropServer->Controls->Add(this->f_splitServer);
			this->f_gropServer->Controls->Add(this->f_textServerPath);
			this->f_gropServer->Location = System::Drawing::Point(3, 3);
			this->f_gropServer->Name = L"f_gropServer";
			this->f_gropServer->Size = System::Drawing::Size(634, 254);
			this->f_gropServer->TabIndex = 0;
			this->f_gropServer->TabStop = false;
			this->f_gropServer->Text = L"サーバ";
			// 
			// f_splitServer
			// 
			this->f_splitServer->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->f_splitServer->Location = System::Drawing::Point(6, 43);
			this->f_splitServer->Name = L"f_splitServer";
			// 
			// f_splitServer.Panel1
			// 
			this->f_splitServer->Panel1->Controls->Add(this->f_treeServer);
			// 
			// f_splitServer.Panel2
			// 
			this->f_splitServer->Panel2->Controls->Add(this->f_listViewServerFiles);
			this->f_splitServer->Size = System::Drawing::Size(622, 205);
			this->f_splitServer->SplitterDistance = 311;
			this->f_splitServer->TabIndex = 3;
			this->f_splitServer->SplitterMoved += gcnew System::Windows::Forms::SplitterEventHandler(this, &MainForm::f_splitFtp_SplitterMoved);
			// 
			// f_treeServer
			// 
			this->f_treeServer->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->f_treeServer->HideSelection = false;
			this->f_treeServer->ImageIndex = 3;
			this->f_treeServer->ImageList = this->imageListFtp;
			this->f_treeServer->Location = System::Drawing::Point(3, 3);
			this->f_treeServer->Name = L"f_treeServer";
			this->f_treeServer->PathSeparator = L"/";
			this->f_treeServer->SelectedImageIndex = 0;
			this->f_treeServer->Size = System::Drawing::Size(305, 199);
			this->f_treeServer->TabIndex = 0;
			this->f_treeServer->AfterCollapse += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MainForm::f_treeServer_AfterCollapse);
			this->f_treeServer->BeforeExpand += gcnew System::Windows::Forms::TreeViewCancelEventHandler(this, &MainForm::f_treeServer_BeforeExpand);
			this->f_treeServer->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MainForm::f_treeServer_AfterSelect);
			// 
			// imageListFtp
			// 
			this->imageListFtp->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"imageListFtp.ImageStream")));
			this->imageListFtp->TransparentColor = System::Drawing::Color::Transparent;
			this->imageListFtp->Images->SetKeyName(0, L"drive.gif");
			this->imageListFtp->Images->SetKeyName(1, L"drive_net.gif");
			this->imageListFtp->Images->SetKeyName(2, L"drive_cd.gif");
			this->imageListFtp->Images->SetKeyName(3, L"folder_c.gif");
			this->imageListFtp->Images->SetKeyName(4, L"folder_o.gif");
			this->imageListFtp->Images->SetKeyName(5, L"file.gif");
			// 
			// f_listViewServerFiles
			// 
			this->f_listViewServerFiles->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->f_listViewServerFiles->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {this->f_columnHeaderNameServer, 
				this->f_columnHeaderSizeServer, this->f_columnHeaderDateServer});
			this->f_listViewServerFiles->HideSelection = false;
			this->f_listViewServerFiles->Location = System::Drawing::Point(3, 3);
			this->f_listViewServerFiles->Name = L"f_listViewServerFiles";
			this->f_listViewServerFiles->Size = System::Drawing::Size(301, 199);
			this->f_listViewServerFiles->SmallImageList = this->imageListFtp;
			this->f_listViewServerFiles->TabIndex = 0;
			this->f_listViewServerFiles->UseCompatibleStateImageBehavior = false;
			this->f_listViewServerFiles->View = System::Windows::Forms::View::Details;
			// 
			// f_columnHeaderNameServer
			// 
			this->f_columnHeaderNameServer->Text = L"名前";
			this->f_columnHeaderNameServer->Width = 160;
			// 
			// f_columnHeaderSizeServer
			// 
			this->f_columnHeaderSizeServer->Text = L"サイズ";
			this->f_columnHeaderSizeServer->Width = 55;
			// 
			// f_columnHeaderDateServer
			// 
			this->f_columnHeaderDateServer->Text = L"更新日時";
			this->f_columnHeaderDateServer->Width = 80;
			// 
			// f_textServerPath
			// 
			this->f_textServerPath->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->f_textServerPath->BackColor = System::Drawing::SystemColors::Window;
			this->f_textServerPath->Location = System::Drawing::Point(6, 18);
			this->f_textServerPath->Name = L"f_textServerPath";
			this->f_textServerPath->ReadOnly = true;
			this->f_textServerPath->Size = System::Drawing::Size(622, 19);
			this->f_textServerPath->TabIndex = 0;
			// 
			// f_gropLocal
			// 
			this->f_gropLocal->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->f_gropLocal->Controls->Add(this->f_splitLocal);
			this->f_gropLocal->Controls->Add(this->f_textLocalPath);
			this->f_gropLocal->Location = System::Drawing::Point(3, 3);
			this->f_gropLocal->Name = L"f_gropLocal";
			this->f_gropLocal->Size = System::Drawing::Size(634, 249);
			this->f_gropLocal->TabIndex = 0;
			this->f_gropLocal->TabStop = false;
			this->f_gropLocal->Text = L"ローカル";
			// 
			// f_splitLocal
			// 
			this->f_splitLocal->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->f_splitLocal->Location = System::Drawing::Point(6, 43);
			this->f_splitLocal->Name = L"f_splitLocal";
			// 
			// f_splitLocal.Panel1
			// 
			this->f_splitLocal->Panel1->Controls->Add(this->f_treeLocal);
			// 
			// f_splitLocal.Panel2
			// 
			this->f_splitLocal->Panel2->Controls->Add(this->f_listViewLocalFiles);
			this->f_splitLocal->Size = System::Drawing::Size(622, 200);
			this->f_splitLocal->SplitterDistance = 311;
			this->f_splitLocal->TabIndex = 3;
			this->f_splitLocal->SplitterMoved += gcnew System::Windows::Forms::SplitterEventHandler(this, &MainForm::f_splitFtp_SplitterMoved);
			// 
			// f_treeLocal
			// 
			this->f_treeLocal->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->f_treeLocal->HideSelection = false;
			this->f_treeLocal->ImageIndex = 3;
			this->f_treeLocal->ImageList = this->imageListFtp;
			this->f_treeLocal->Location = System::Drawing::Point(3, 3);
			this->f_treeLocal->Name = L"f_treeLocal";
			this->f_treeLocal->SelectedImageIndex = 4;
			this->f_treeLocal->Size = System::Drawing::Size(305, 194);
			this->f_treeLocal->TabIndex = 0;
			this->f_treeLocal->AfterCollapse += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MainForm::f_treeLocal_AfterCollapse);
			this->f_treeLocal->BeforeExpand += gcnew System::Windows::Forms::TreeViewCancelEventHandler(this, &MainForm::f_treeLocal_BeforeExpand);
			this->f_treeLocal->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MainForm::f_treeLocal_AfterSelect);
			// 
			// f_listViewLocalFiles
			// 
			this->f_listViewLocalFiles->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->f_listViewLocalFiles->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {this->f_columnHeaderNameLocal, 
				this->f_columnHeaderSizeLocal, this->f_columnHeaderDateLocal});
			this->f_listViewLocalFiles->HideSelection = false;
			this->f_listViewLocalFiles->Location = System::Drawing::Point(3, 3);
			this->f_listViewLocalFiles->Name = L"f_listViewLocalFiles";
			this->f_listViewLocalFiles->Size = System::Drawing::Size(301, 194);
			this->f_listViewLocalFiles->SmallImageList = this->imageListFtp;
			this->f_listViewLocalFiles->TabIndex = 0;
			this->f_listViewLocalFiles->UseCompatibleStateImageBehavior = false;
			this->f_listViewLocalFiles->View = System::Windows::Forms::View::Details;
			// 
			// f_columnHeaderNameLocal
			// 
			this->f_columnHeaderNameLocal->Text = L"名前";
			this->f_columnHeaderNameLocal->Width = 160;
			// 
			// f_columnHeaderSizeLocal
			// 
			this->f_columnHeaderSizeLocal->Text = L"サイズ";
			this->f_columnHeaderSizeLocal->Width = 55;
			// 
			// f_columnHeaderDateLocal
			// 
			this->f_columnHeaderDateLocal->Text = L"更新日時";
			this->f_columnHeaderDateLocal->Width = 80;
			// 
			// f_textLocalPath
			// 
			this->f_textLocalPath->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->f_textLocalPath->BackColor = System::Drawing::SystemColors::Window;
			this->f_textLocalPath->Location = System::Drawing::Point(6, 18);
			this->f_textLocalPath->Name = L"f_textLocalPath";
			this->f_textLocalPath->ReadOnly = true;
			this->f_textLocalPath->Size = System::Drawing::Size(622, 19);
			this->f_textLocalPath->TabIndex = 0;
			// 
			// tabPicturePuzzle
			// 
			this->tabPicturePuzzle->Controls->Add(this->p_buttonClearPicture);
			this->tabPicturePuzzle->Controls->Add(this->p_buttonLoad);
			this->tabPicturePuzzle->Controls->Add(this->p_buttonPuzzle);
			this->tabPicturePuzzle->Controls->Add(this->p_panelBase);
			this->tabPicturePuzzle->Location = System::Drawing::Point(4, 22);
			this->tabPicturePuzzle->Name = L"tabPicturePuzzle";
			this->tabPicturePuzzle->Padding = System::Windows::Forms::Padding(3);
			this->tabPicturePuzzle->Size = System::Drawing::Size(652, 559);
			this->tabPicturePuzzle->TabIndex = 3;
			this->tabPicturePuzzle->Text = L"写真パズル";
			this->tabPicturePuzzle->UseVisualStyleBackColor = true;
			// 
			// p_buttonClearPicture
			// 
			this->p_buttonClearPicture->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->p_buttonClearPicture->Location = System::Drawing::Point(6, 531);
			this->p_buttonClearPicture->Name = L"p_buttonClearPicture";
			this->p_buttonClearPicture->Size = System::Drawing::Size(75, 23);
			this->p_buttonClearPicture->TabIndex = 7;
			this->p_buttonClearPicture->Text = L"クリア";
			this->p_buttonClearPicture->UseVisualStyleBackColor = true;
			this->p_buttonClearPicture->Visible = false;
			this->p_buttonClearPicture->Click += gcnew System::EventHandler(this, &MainForm::p_buttonClearPicture_Click);
			// 
			// p_buttonLoad
			// 
			this->p_buttonLoad->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->p_buttonLoad->Location = System::Drawing::Point(490, 531);
			this->p_buttonLoad->Name = L"p_buttonLoad";
			this->p_buttonLoad->Size = System::Drawing::Size(75, 23);
			this->p_buttonLoad->TabIndex = 5;
			this->p_buttonLoad->Text = L"読込み";
			this->p_buttonLoad->UseVisualStyleBackColor = true;
			this->p_buttonLoad->Click += gcnew System::EventHandler(this, &MainForm::p_buttonLoad_Click);
			// 
			// p_buttonPuzzle
			// 
			this->p_buttonPuzzle->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->p_buttonPuzzle->Enabled = false;
			this->p_buttonPuzzle->Location = System::Drawing::Point(571, 531);
			this->p_buttonPuzzle->Name = L"p_buttonPuzzle";
			this->p_buttonPuzzle->Size = System::Drawing::Size(75, 23);
			this->p_buttonPuzzle->TabIndex = 6;
			this->p_buttonPuzzle->Text = L"パズル";
			this->p_buttonPuzzle->UseVisualStyleBackColor = true;
			this->p_buttonPuzzle->Click += gcnew System::EventHandler(this, &MainForm::p_buttonPuzzle_Click);
			// 
			// p_panelBase
			// 
			this->p_panelBase->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->p_panelBase->BackColor = System::Drawing::Color::Gainsboro;
			this->p_panelBase->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->p_panelBase->Controls->Add(this->p_panelBottom);
			this->p_panelBase->Controls->Add(this->p_picturePuzzle);
			this->p_panelBase->Location = System::Drawing::Point(6, 6);
			this->p_panelBase->Name = L"p_panelBase";
			this->p_panelBase->Size = System::Drawing::Size(640, 510);
			this->p_panelBase->TabIndex = 4;
			this->p_panelBase->SizeChanged += gcnew System::EventHandler(this, &MainForm::p_panelBase_SizeChanged);
			// 
			// p_panelBottom
			// 
			this->p_panelBottom->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->p_panelBottom->BackColor = System::Drawing::Color::DimGray;
			this->p_panelBottom->Location = System::Drawing::Point(0, 426);
			this->p_panelBottom->Name = L"p_panelBottom";
			this->p_panelBottom->Size = System::Drawing::Size(640, 85);
			this->p_panelBottom->TabIndex = 0;
			// 
			// p_picturePuzzle
			// 
			this->p_picturePuzzle->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->p_picturePuzzle->Location = System::Drawing::Point(0, 0);
			this->p_picturePuzzle->Name = L"p_picturePuzzle";
			this->p_picturePuzzle->Size = System::Drawing::Size(640, 425);
			this->p_picturePuzzle->TabIndex = 0;
			this->p_picturePuzzle->TabStop = false;
			this->p_picturePuzzle->SizeChanged += gcnew System::EventHandler(this, &MainForm::p_picturePuzzle_SizeChanged);
			// 
			// tabBinaryClock
			// 
			this->tabBinaryClock->BackColor = System::Drawing::Color::GhostWhite;
			this->tabBinaryClock->Controls->Add(this->b_labelSpanTime);
			this->tabBinaryClock->Controls->Add(this->b_buttonTimerStop);
			this->tabBinaryClock->Controls->Add(this->b_buttonTimerSet);
			this->tabBinaryClock->Controls->Add(this->b_labelColon1);
			this->tabBinaryClock->Controls->Add(this->b_labelColon2);
			this->tabBinaryClock->Controls->Add(this->b_labelSec1);
			this->tabBinaryClock->Controls->Add(this->b_labelSec2);
			this->tabBinaryClock->Controls->Add(this->b_labelMin1);
			this->tabBinaryClock->Controls->Add(this->b_labelMin2);
			this->tabBinaryClock->Controls->Add(this->b_labelHour1);
			this->tabBinaryClock->Controls->Add(this->b_labelHour2);
			this->tabBinaryClock->Controls->Add(this->b_panelSec2);
			this->tabBinaryClock->Controls->Add(this->b_panelHour20);
			this->tabBinaryClock->Controls->Add(this->b_panelHour10);
			this->tabBinaryClock->Controls->Add(this->b_panelHour1);
			this->tabBinaryClock->Controls->Add(this->b_panelHour2);
			this->tabBinaryClock->Controls->Add(this->b_panelHour4);
			this->tabBinaryClock->Controls->Add(this->b_panelHour8);
			this->tabBinaryClock->Controls->Add(this->b_panelMin40);
			this->tabBinaryClock->Controls->Add(this->b_panelMin20);
			this->tabBinaryClock->Controls->Add(this->b_panelMin10);
			this->tabBinaryClock->Controls->Add(this->b_panelSec40);
			this->tabBinaryClock->Controls->Add(this->b_panelMin1);
			this->tabBinaryClock->Controls->Add(this->b_panelMin2);
			this->tabBinaryClock->Controls->Add(this->b_panelMin4);
			this->tabBinaryClock->Controls->Add(this->b_panelMin8);
			this->tabBinaryClock->Controls->Add(this->b_panelSec20);
			this->tabBinaryClock->Controls->Add(this->b_panelSec10);
			this->tabBinaryClock->Controls->Add(this->b_panelSec1);
			this->tabBinaryClock->Controls->Add(this->b_panelSec4);
			this->tabBinaryClock->Controls->Add(this->b_panelSec8);
			this->tabBinaryClock->Location = System::Drawing::Point(4, 22);
			this->tabBinaryClock->Name = L"tabBinaryClock";
			this->tabBinaryClock->Padding = System::Windows::Forms::Padding(3);
			this->tabBinaryClock->Size = System::Drawing::Size(652, 559);
			this->tabBinaryClock->TabIndex = 4;
			this->tabBinaryClock->Text = L"バイナリクロック";
			this->tabBinaryClock->Resize += gcnew System::EventHandler(this, &MainForm::tabBinaryClock_Resize);
			// 
			// b_labelSpanTime
			// 
			this->b_labelSpanTime->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->b_labelSpanTime->AutoSize = true;
			this->b_labelSpanTime->Font = (gcnew System::Drawing::Font(L"Arial", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->b_labelSpanTime->ForeColor = System::Drawing::Color::MidnightBlue;
			this->b_labelSpanTime->Location = System::Drawing::Point(525, 496);
			this->b_labelSpanTime->Name = L"b_labelSpanTime";
			this->b_labelSpanTime->Size = System::Drawing::Size(121, 32);
			this->b_labelSpanTime->TabIndex = 47;
			this->b_labelSpanTime->Text = L"00:00:00";
			this->b_labelSpanTime->Visible = false;
			// 
			// b_buttonTimerStop
			// 
			this->b_buttonTimerStop->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->b_buttonTimerStop->Enabled = false;
			this->b_buttonTimerStop->Location = System::Drawing::Point(571, 531);
			this->b_buttonTimerStop->Name = L"b_buttonTimerStop";
			this->b_buttonTimerStop->Size = System::Drawing::Size(75, 23);
			this->b_buttonTimerStop->TabIndex = 1;
			this->b_buttonTimerStop->Text = L"ストップ";
			this->b_buttonTimerStop->UseVisualStyleBackColor = true;
			this->b_buttonTimerStop->Click += gcnew System::EventHandler(this, &MainForm::b_buttonTimerStop_Click);
			// 
			// b_buttonTimerSet
			// 
			this->b_buttonTimerSet->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->b_buttonTimerSet->Location = System::Drawing::Point(490, 531);
			this->b_buttonTimerSet->Name = L"b_buttonTimerSet";
			this->b_buttonTimerSet->Size = System::Drawing::Size(75, 23);
			this->b_buttonTimerSet->TabIndex = 0;
			this->b_buttonTimerSet->Text = L"タイマー";
			this->b_buttonTimerSet->UseVisualStyleBackColor = true;
			this->b_buttonTimerSet->Click += gcnew System::EventHandler(this, &MainForm::b_buttonTimerSet_Click);
			// 
			// b_labelColon1
			// 
			this->b_labelColon1->AutoSize = true;
			this->b_labelColon1->Font = (gcnew System::Drawing::Font(L"Arial", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->b_labelColon1->Location = System::Drawing::Point(406, 395);
			this->b_labelColon1->Name = L"b_labelColon1";
			this->b_labelColon1->Size = System::Drawing::Size(27, 37);
			this->b_labelColon1->TabIndex = 46;
			this->b_labelColon1->Text = L":";
			// 
			// b_labelColon2
			// 
			this->b_labelColon2->AutoSize = true;
			this->b_labelColon2->Font = (gcnew System::Drawing::Font(L"Arial", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->b_labelColon2->Location = System::Drawing::Point(220, 395);
			this->b_labelColon2->Name = L"b_labelColon2";
			this->b_labelColon2->Size = System::Drawing::Size(27, 37);
			this->b_labelColon2->TabIndex = 45;
			this->b_labelColon2->Text = L":";
			// 
			// b_labelSec1
			// 
			this->b_labelSec1->AutoSize = true;
			this->b_labelSec1->Font = (gcnew System::Drawing::Font(L"Arial", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->b_labelSec1->Location = System::Drawing::Point(541, 395);
			this->b_labelSec1->Name = L"b_labelSec1";
			this->b_labelSec1->Size = System::Drawing::Size(35, 37);
			this->b_labelSec1->TabIndex = 44;
			this->b_labelSec1->Text = L"0";
			// 
			// b_labelSec2
			// 
			this->b_labelSec2->AutoSize = true;
			this->b_labelSec2->Font = (gcnew System::Drawing::Font(L"Arial", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->b_labelSec2->Location = System::Drawing::Point(448, 395);
			this->b_labelSec2->Name = L"b_labelSec2";
			this->b_labelSec2->Size = System::Drawing::Size(35, 37);
			this->b_labelSec2->TabIndex = 43;
			this->b_labelSec2->Text = L"0";
			// 
			// b_labelMin1
			// 
			this->b_labelMin1->AutoSize = true;
			this->b_labelMin1->Font = (gcnew System::Drawing::Font(L"Arial", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->b_labelMin1->Location = System::Drawing::Point(355, 395);
			this->b_labelMin1->Name = L"b_labelMin1";
			this->b_labelMin1->Size = System::Drawing::Size(35, 37);
			this->b_labelMin1->TabIndex = 42;
			this->b_labelMin1->Text = L"0";
			// 
			// b_labelMin2
			// 
			this->b_labelMin2->AutoSize = true;
			this->b_labelMin2->Font = (gcnew System::Drawing::Font(L"Arial", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->b_labelMin2->Location = System::Drawing::Point(262, 395);
			this->b_labelMin2->Name = L"b_labelMin2";
			this->b_labelMin2->Size = System::Drawing::Size(35, 37);
			this->b_labelMin2->TabIndex = 41;
			this->b_labelMin2->Text = L"0";
			// 
			// b_labelHour1
			// 
			this->b_labelHour1->AutoSize = true;
			this->b_labelHour1->Font = (gcnew System::Drawing::Font(L"Arial", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->b_labelHour1->Location = System::Drawing::Point(169, 395);
			this->b_labelHour1->Name = L"b_labelHour1";
			this->b_labelHour1->Size = System::Drawing::Size(35, 37);
			this->b_labelHour1->TabIndex = 40;
			this->b_labelHour1->Text = L"0";
			// 
			// b_labelHour2
			// 
			this->b_labelHour2->AutoSize = true;
			this->b_labelHour2->Font = (gcnew System::Drawing::Font(L"Arial", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->b_labelHour2->Location = System::Drawing::Point(76, 395);
			this->b_labelHour2->Name = L"b_labelHour2";
			this->b_labelHour2->Size = System::Drawing::Size(35, 37);
			this->b_labelHour2->TabIndex = 39;
			this->b_labelHour2->Text = L"0";
			// 
			// b_panelSec2
			// 
			this->b_panelSec2->BackColor = System::Drawing::Color::Snow;
			this->b_panelSec2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->b_panelSec2->Location = System::Drawing::Point(541, 237);
			this->b_panelSec2->Name = L"b_panelSec2";
			this->b_panelSec2->Size = System::Drawing::Size(35, 35);
			this->b_panelSec2->TabIndex = 36;
			// 
			// b_panelHour20
			// 
			this->b_panelHour20->BackColor = System::Drawing::Color::Snow;
			this->b_panelHour20->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->b_panelHour20->Location = System::Drawing::Point(76, 237);
			this->b_panelHour20->Name = L"b_panelHour20";
			this->b_panelHour20->Size = System::Drawing::Size(35, 35);
			this->b_panelHour20->TabIndex = 35;
			// 
			// b_panelHour10
			// 
			this->b_panelHour10->BackColor = System::Drawing::Color::Snow;
			this->b_panelHour10->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->b_panelHour10->Location = System::Drawing::Point(76, 316);
			this->b_panelHour10->Name = L"b_panelHour10";
			this->b_panelHour10->Size = System::Drawing::Size(35, 35);
			this->b_panelHour10->TabIndex = 34;
			// 
			// b_panelHour1
			// 
			this->b_panelHour1->BackColor = System::Drawing::Color::Snow;
			this->b_panelHour1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->b_panelHour1->Location = System::Drawing::Point(169, 316);
			this->b_panelHour1->Name = L"b_panelHour1";
			this->b_panelHour1->Size = System::Drawing::Size(35, 35);
			this->b_panelHour1->TabIndex = 31;
			// 
			// b_panelHour2
			// 
			this->b_panelHour2->BackColor = System::Drawing::Color::Snow;
			this->b_panelHour2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->b_panelHour2->Location = System::Drawing::Point(169, 237);
			this->b_panelHour2->Name = L"b_panelHour2";
			this->b_panelHour2->Size = System::Drawing::Size(35, 35);
			this->b_panelHour2->TabIndex = 33;
			// 
			// b_panelHour4
			// 
			this->b_panelHour4->BackColor = System::Drawing::Color::Snow;
			this->b_panelHour4->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->b_panelHour4->Location = System::Drawing::Point(169, 158);
			this->b_panelHour4->Name = L"b_panelHour4";
			this->b_panelHour4->Size = System::Drawing::Size(35, 35);
			this->b_panelHour4->TabIndex = 32;
			// 
			// b_panelHour8
			// 
			this->b_panelHour8->BackColor = System::Drawing::Color::Snow;
			this->b_panelHour8->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->b_panelHour8->Location = System::Drawing::Point(169, 79);
			this->b_panelHour8->Name = L"b_panelHour8";
			this->b_panelHour8->Size = System::Drawing::Size(35, 35);
			this->b_panelHour8->TabIndex = 30;
			// 
			// b_panelMin40
			// 
			this->b_panelMin40->BackColor = System::Drawing::Color::Snow;
			this->b_panelMin40->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->b_panelMin40->Location = System::Drawing::Point(262, 158);
			this->b_panelMin40->Name = L"b_panelMin40";
			this->b_panelMin40->Size = System::Drawing::Size(35, 35);
			this->b_panelMin40->TabIndex = 29;
			// 
			// b_panelMin20
			// 
			this->b_panelMin20->BackColor = System::Drawing::Color::Snow;
			this->b_panelMin20->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->b_panelMin20->Location = System::Drawing::Point(262, 237);
			this->b_panelMin20->Name = L"b_panelMin20";
			this->b_panelMin20->Size = System::Drawing::Size(35, 35);
			this->b_panelMin20->TabIndex = 28;
			// 
			// b_panelMin10
			// 
			this->b_panelMin10->BackColor = System::Drawing::Color::Snow;
			this->b_panelMin10->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->b_panelMin10->Location = System::Drawing::Point(262, 316);
			this->b_panelMin10->Name = L"b_panelMin10";
			this->b_panelMin10->Size = System::Drawing::Size(35, 35);
			this->b_panelMin10->TabIndex = 27;
			// 
			// b_panelSec40
			// 
			this->b_panelSec40->BackColor = System::Drawing::Color::Snow;
			this->b_panelSec40->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->b_panelSec40->Location = System::Drawing::Point(448, 158);
			this->b_panelSec40->Name = L"b_panelSec40";
			this->b_panelSec40->Size = System::Drawing::Size(35, 35);
			this->b_panelSec40->TabIndex = 22;
			// 
			// b_panelMin1
			// 
			this->b_panelMin1->BackColor = System::Drawing::Color::Snow;
			this->b_panelMin1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->b_panelMin1->Location = System::Drawing::Point(355, 316);
			this->b_panelMin1->Name = L"b_panelMin1";
			this->b_panelMin1->Size = System::Drawing::Size(35, 35);
			this->b_panelMin1->TabIndex = 24;
			// 
			// b_panelMin2
			// 
			this->b_panelMin2->BackColor = System::Drawing::Color::Snow;
			this->b_panelMin2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->b_panelMin2->Location = System::Drawing::Point(355, 237);
			this->b_panelMin2->Name = L"b_panelMin2";
			this->b_panelMin2->Size = System::Drawing::Size(35, 35);
			this->b_panelMin2->TabIndex = 26;
			// 
			// b_panelMin4
			// 
			this->b_panelMin4->BackColor = System::Drawing::Color::Snow;
			this->b_panelMin4->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->b_panelMin4->Location = System::Drawing::Point(355, 158);
			this->b_panelMin4->Name = L"b_panelMin4";
			this->b_panelMin4->Size = System::Drawing::Size(35, 35);
			this->b_panelMin4->TabIndex = 25;
			// 
			// b_panelMin8
			// 
			this->b_panelMin8->BackColor = System::Drawing::Color::Snow;
			this->b_panelMin8->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->b_panelMin8->Location = System::Drawing::Point(355, 79);
			this->b_panelMin8->Name = L"b_panelMin8";
			this->b_panelMin8->Size = System::Drawing::Size(35, 35);
			this->b_panelMin8->TabIndex = 23;
			// 
			// b_panelSec20
			// 
			this->b_panelSec20->BackColor = System::Drawing::Color::Snow;
			this->b_panelSec20->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->b_panelSec20->Location = System::Drawing::Point(448, 237);
			this->b_panelSec20->Name = L"b_panelSec20";
			this->b_panelSec20->Size = System::Drawing::Size(35, 35);
			this->b_panelSec20->TabIndex = 20;
			// 
			// b_panelSec10
			// 
			this->b_panelSec10->BackColor = System::Drawing::Color::Snow;
			this->b_panelSec10->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->b_panelSec10->Location = System::Drawing::Point(448, 316);
			this->b_panelSec10->Name = L"b_panelSec10";
			this->b_panelSec10->Size = System::Drawing::Size(35, 35);
			this->b_panelSec10->TabIndex = 21;
			// 
			// b_panelSec1
			// 
			this->b_panelSec1->BackColor = System::Drawing::Color::Snow;
			this->b_panelSec1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->b_panelSec1->Location = System::Drawing::Point(541, 316);
			this->b_panelSec1->Name = L"b_panelSec1";
			this->b_panelSec1->Size = System::Drawing::Size(35, 35);
			this->b_panelSec1->TabIndex = 18;
			// 
			// b_panelSec4
			// 
			this->b_panelSec4->BackColor = System::Drawing::Color::Snow;
			this->b_panelSec4->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->b_panelSec4->Location = System::Drawing::Point(541, 158);
			this->b_panelSec4->Name = L"b_panelSec4";
			this->b_panelSec4->Size = System::Drawing::Size(35, 35);
			this->b_panelSec4->TabIndex = 19;
			// 
			// b_panelSec8
			// 
			this->b_panelSec8->BackColor = System::Drawing::Color::Snow;
			this->b_panelSec8->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->b_panelSec8->Location = System::Drawing::Point(541, 79);
			this->b_panelSec8->Name = L"b_panelSec8";
			this->b_panelSec8->Size = System::Drawing::Size(35, 35);
			this->b_panelSec8->TabIndex = 17;
			// 
			// tabTetris
			// 
			this->tabTetris->BackColor = System::Drawing::Color::GhostWhite;
			this->tabTetris->Controls->Add(this->g_buttonHowTo);
			this->tabTetris->Controls->Add(this->g_buttonStart);
			this->tabTetris->Controls->Add(this->g_buttonEnd);
			this->tabTetris->Controls->Add(this->g_panelScore);
			this->tabTetris->Controls->Add(this->g_panelNext3);
			this->tabTetris->Controls->Add(this->g_panelNext2);
			this->tabTetris->Controls->Add(this->g_panelNext1);
			this->tabTetris->Controls->Add(this->g_labelNext);
			this->tabTetris->Controls->Add(this->g_panelTetris);
			this->tabTetris->Location = System::Drawing::Point(4, 22);
			this->tabTetris->Name = L"tabTetris";
			this->tabTetris->Padding = System::Windows::Forms::Padding(3);
			this->tabTetris->Size = System::Drawing::Size(652, 559);
			this->tabTetris->TabIndex = 5;
			this->tabTetris->Text = L"TETRiS";
			this->tabTetris->Resize += gcnew System::EventHandler(this, &MainForm::tabTetris_Resize);
			// 
			// g_buttonHowTo
			// 
			this->g_buttonHowTo->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->g_buttonHowTo->Location = System::Drawing::Point(571, 502);
			this->g_buttonHowTo->Name = L"g_buttonHowTo";
			this->g_buttonHowTo->Size = System::Drawing::Size(75, 23);
			this->g_buttonHowTo->TabIndex = 24;
			this->g_buttonHowTo->Text = L"HOW TO";
			this->g_buttonHowTo->UseVisualStyleBackColor = true;
			this->g_buttonHowTo->Click += gcnew System::EventHandler(this, &MainForm::g_buttonHowTo_Click);
			// 
			// g_buttonStart
			// 
			this->g_buttonStart->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->g_buttonStart->Location = System::Drawing::Point(490, 531);
			this->g_buttonStart->Name = L"g_buttonStart";
			this->g_buttonStart->Size = System::Drawing::Size(75, 23);
			this->g_buttonStart->TabIndex = 22;
			this->g_buttonStart->Text = L"START";
			this->g_buttonStart->UseVisualStyleBackColor = true;
			this->g_buttonStart->Click += gcnew System::EventHandler(this, &MainForm::g_buttonStart_Click);
			// 
			// g_buttonEnd
			// 
			this->g_buttonEnd->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->g_buttonEnd->Enabled = false;
			this->g_buttonEnd->Location = System::Drawing::Point(571, 531);
			this->g_buttonEnd->Name = L"g_buttonEnd";
			this->g_buttonEnd->Size = System::Drawing::Size(75, 23);
			this->g_buttonEnd->TabIndex = 23;
			this->g_buttonEnd->Text = L"END";
			this->g_buttonEnd->UseVisualStyleBackColor = true;
			this->g_buttonEnd->Click += gcnew System::EventHandler(this, &MainForm::g_buttonEnd_Click);
			// 
			// g_panelScore
			// 
			this->g_panelScore->Controls->Add(this->g_labelScore);
			this->g_panelScore->Controls->Add(this->g_labelScoreTitle);
			this->g_panelScore->Controls->Add(this->g_labelTetris);
			this->g_panelScore->Controls->Add(this->g_labelTriple);
			this->g_panelScore->Controls->Add(this->g_labelDouble);
			this->g_panelScore->Controls->Add(this->g_labelSingle);
			this->g_panelScore->Controls->Add(this->g_labelTetrisTitle);
			this->g_panelScore->Controls->Add(this->g_labelTripleTitle);
			this->g_panelScore->Controls->Add(this->g_labelDoubleTitle);
			this->g_panelScore->Controls->Add(this->g_labelSingleTitle);
			this->g_panelScore->Location = System::Drawing::Point(286, 142);
			this->g_panelScore->Name = L"g_panelScore";
			this->g_panelScore->Size = System::Drawing::Size(220, 247);
			this->g_panelScore->TabIndex = 21;
			// 
			// g_labelScore
			// 
			this->g_labelScore->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->g_labelScore->AutoSize = true;
			this->g_labelScore->Font = (gcnew System::Drawing::Font(L"Arial", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->g_labelScore->Location = System::Drawing::Point(168, 123);
			this->g_labelScore->Name = L"g_labelScore";
			this->g_labelScore->Size = System::Drawing::Size(43, 22);
			this->g_labelScore->TabIndex = 22;
			this->g_labelScore->Text = L"000";
			// 
			// g_labelScoreTitle
			// 
			this->g_labelScoreTitle->AutoSize = true;
			this->g_labelScoreTitle->Font = (gcnew System::Drawing::Font(L"Arial", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->g_labelScoreTitle->ForeColor = System::Drawing::Color::MidnightBlue;
			this->g_labelScoreTitle->Location = System::Drawing::Point(132, 94);
			this->g_labelScoreTitle->Name = L"g_labelScoreTitle";
			this->g_labelScoreTitle->Size = System::Drawing::Size(79, 22);
			this->g_labelScoreTitle->TabIndex = 21;
			this->g_labelScoreTitle->Text = L"SCORE";
			// 
			// g_labelTetris
			// 
			this->g_labelTetris->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->g_labelTetris->AutoSize = true;
			this->g_labelTetris->Font = (gcnew System::Drawing::Font(L"Arial", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->g_labelTetris->Location = System::Drawing::Point(71, 210);
			this->g_labelTetris->Name = L"g_labelTetris";
			this->g_labelTetris->Size = System::Drawing::Size(21, 22);
			this->g_labelTetris->TabIndex = 20;
			this->g_labelTetris->Text = L"0";
			// 
			// g_labelTriple
			// 
			this->g_labelTriple->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->g_labelTriple->AutoSize = true;
			this->g_labelTriple->Font = (gcnew System::Drawing::Font(L"Arial", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->g_labelTriple->Location = System::Drawing::Point(71, 152);
			this->g_labelTriple->Name = L"g_labelTriple";
			this->g_labelTriple->Size = System::Drawing::Size(21, 22);
			this->g_labelTriple->TabIndex = 19;
			this->g_labelTriple->Text = L"0";
			// 
			// g_labelDouble
			// 
			this->g_labelDouble->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->g_labelDouble->AutoSize = true;
			this->g_labelDouble->Font = (gcnew System::Drawing::Font(L"Arial", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->g_labelDouble->Location = System::Drawing::Point(71, 94);
			this->g_labelDouble->Name = L"g_labelDouble";
			this->g_labelDouble->Size = System::Drawing::Size(21, 22);
			this->g_labelDouble->TabIndex = 18;
			this->g_labelDouble->Text = L"0";
			// 
			// g_labelSingle
			// 
			this->g_labelSingle->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->g_labelSingle->AutoSize = true;
			this->g_labelSingle->Font = (gcnew System::Drawing::Font(L"Arial", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->g_labelSingle->Location = System::Drawing::Point(71, 36);
			this->g_labelSingle->Name = L"g_labelSingle";
			this->g_labelSingle->Size = System::Drawing::Size(21, 22);
			this->g_labelSingle->TabIndex = 17;
			this->g_labelSingle->Text = L"0";
			// 
			// g_labelTetrisTitle
			// 
			this->g_labelTetrisTitle->AutoSize = true;
			this->g_labelTetrisTitle->Font = (gcnew System::Drawing::Font(L"Arial", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->g_labelTetrisTitle->ForeColor = System::Drawing::Color::MidnightBlue;
			this->g_labelTetrisTitle->Location = System::Drawing::Point(14, 181);
			this->g_labelTetrisTitle->Name = L"g_labelTetrisTitle";
			this->g_labelTetrisTitle->Size = System::Drawing::Size(78, 22);
			this->g_labelTetrisTitle->TabIndex = 16;
			this->g_labelTetrisTitle->Text = L"TETRiS";
			// 
			// g_labelTripleTitle
			// 
			this->g_labelTripleTitle->AutoSize = true;
			this->g_labelTripleTitle->Font = (gcnew System::Drawing::Font(L"Arial", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->g_labelTripleTitle->ForeColor = System::Drawing::Color::MidnightBlue;
			this->g_labelTripleTitle->Location = System::Drawing::Point(13, 123);
			this->g_labelTripleTitle->Name = L"g_labelTripleTitle";
			this->g_labelTripleTitle->Size = System::Drawing::Size(79, 22);
			this->g_labelTripleTitle->TabIndex = 15;
			this->g_labelTripleTitle->Text = L"TRIPLE";
			// 
			// g_labelDoubleTitle
			// 
			this->g_labelDoubleTitle->AutoSize = true;
			this->g_labelDoubleTitle->Font = (gcnew System::Drawing::Font(L"Arial", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->g_labelDoubleTitle->ForeColor = System::Drawing::Color::MidnightBlue;
			this->g_labelDoubleTitle->Location = System::Drawing::Point(3, 65);
			this->g_labelDoubleTitle->Name = L"g_labelDoubleTitle";
			this->g_labelDoubleTitle->Size = System::Drawing::Size(89, 22);
			this->g_labelDoubleTitle->TabIndex = 14;
			this->g_labelDoubleTitle->Text = L"DOUBLE";
			// 
			// g_labelSingleTitle
			// 
			this->g_labelSingleTitle->AutoSize = true;
			this->g_labelSingleTitle->Font = (gcnew System::Drawing::Font(L"Arial", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->g_labelSingleTitle->ForeColor = System::Drawing::Color::MidnightBlue;
			this->g_labelSingleTitle->Location = System::Drawing::Point(11, 7);
			this->g_labelSingleTitle->Name = L"g_labelSingleTitle";
			this->g_labelSingleTitle->Size = System::Drawing::Size(81, 22);
			this->g_labelSingleTitle->TabIndex = 13;
			this->g_labelSingleTitle->Text = L"SINGLE";
			// 
			// g_panelNext3
			// 
			this->g_panelNext3->BackColor = System::Drawing::Color::Black;
			this->g_panelNext3->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->g_panelNext3->Location = System::Drawing::Point(379, 93);
			this->g_panelNext3->Name = L"g_panelNext3";
			this->g_panelNext3->Size = System::Drawing::Size(87, 43);
			this->g_panelNext3->TabIndex = 20;
			// 
			// g_panelNext2
			// 
			this->g_panelNext2->BackColor = System::Drawing::Color::Black;
			this->g_panelNext2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->g_panelNext2->Location = System::Drawing::Point(286, 93);
			this->g_panelNext2->Name = L"g_panelNext2";
			this->g_panelNext2->Size = System::Drawing::Size(87, 43);
			this->g_panelNext2->TabIndex = 19;
			// 
			// g_panelNext1
			// 
			this->g_panelNext1->BackColor = System::Drawing::Color::Black;
			this->g_panelNext1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->g_panelNext1->Location = System::Drawing::Point(286, 33);
			this->g_panelNext1->Name = L"g_panelNext1";
			this->g_panelNext1->Size = System::Drawing::Size(109, 54);
			this->g_panelNext1->TabIndex = 18;
			// 
			// g_labelNext
			// 
			this->g_labelNext->AutoSize = true;
			this->g_labelNext->Font = (gcnew System::Drawing::Font(L"Arial", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->g_labelNext->ForeColor = System::Drawing::Color::MidnightBlue;
			this->g_labelNext->Location = System::Drawing::Point(308, 6);
			this->g_labelNext->Name = L"g_labelNext";
			this->g_labelNext->Size = System::Drawing::Size(64, 24);
			this->g_labelNext->TabIndex = 5;
			this->g_labelNext->Text = L"NEXT";
			// 
			// g_panelTetris
			// 
			this->g_panelTetris->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left));
			this->g_panelTetris->BackColor = System::Drawing::Color::Black;
			this->g_panelTetris->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->g_panelTetris->Controls->Add(this->g_labelMessage);
			this->g_panelTetris->Location = System::Drawing::Point(6, 6);
			this->g_panelTetris->Name = L"g_panelTetris";
			this->g_panelTetris->Size = System::Drawing::Size(274, 548);
			this->g_panelTetris->TabIndex = 1;
			// 
			// g_labelMessage
			// 
			this->g_labelMessage->AutoSize = true;
			this->g_labelMessage->BackColor = System::Drawing::Color::Transparent;
			this->g_labelMessage->Font = (gcnew System::Drawing::Font(L"Arial", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->g_labelMessage->ForeColor = System::Drawing::Color::White;
			this->g_labelMessage->Location = System::Drawing::Point(61, 262);
			this->g_labelMessage->Name = L"g_labelMessage";
			this->g_labelMessage->Size = System::Drawing::Size(152, 24);
			this->g_labelMessage->TabIndex = 0;
			this->g_labelMessage->Text = L"GAME OVER !!";
			this->g_labelMessage->Visible = false;
			// 
			// tabArrow
			// 
			this->tabArrow->BackColor = System::Drawing::Color::GhostWhite;
			this->tabArrow->Controls->Add(this->a_panelCanvas);
			this->tabArrow->Location = System::Drawing::Point(4, 22);
			this->tabArrow->Name = L"tabArrow";
			this->tabArrow->Padding = System::Windows::Forms::Padding(3);
			this->tabArrow->Size = System::Drawing::Size(652, 559);
			this->tabArrow->TabIndex = 6;
			this->tabArrow->Text = L"ARROW";
			// 
			// a_panelCanvas
			// 
			this->a_panelCanvas->Dock = System::Windows::Forms::DockStyle::Fill;
			this->a_panelCanvas->Location = System::Drawing::Point(3, 3);
			this->a_panelCanvas->Name = L"a_panelCanvas";
			this->a_panelCanvas->Size = System::Drawing::Size(646, 553);
			this->a_panelCanvas->TabIndex = 0;
			this->a_panelCanvas->MouseLeave += gcnew System::EventHandler(this, &MainForm::a_panelCanvas_MouseLeave);
			this->a_panelCanvas->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::a_panelCanvas_Paint);
			this->a_panelCanvas->MouseEnter += gcnew System::EventHandler(this, &MainForm::a_panelCanvas_MouseEnter);
			// 
			// tabDirectX
			// 
			this->tabDirectX->BackColor = System::Drawing::Color::GhostWhite;
			this->tabDirectX->Controls->Add(this->d_panelCanvas);
			this->tabDirectX->Location = System::Drawing::Point(4, 22);
			this->tabDirectX->Name = L"tabDirectX";
			this->tabDirectX->Padding = System::Windows::Forms::Padding(3);
			this->tabDirectX->Size = System::Drawing::Size(652, 559);
			this->tabDirectX->TabIndex = 7;
			this->tabDirectX->Text = L"DirectX";
			// 
			// d_panelCanvas
			// 
			this->d_panelCanvas->Dock = System::Windows::Forms::DockStyle::Fill;
			this->d_panelCanvas->Location = System::Drawing::Point(3, 3);
			this->d_panelCanvas->Name = L"d_panelCanvas";
			this->d_panelCanvas->Size = System::Drawing::Size(646, 553);
			this->d_panelCanvas->TabIndex = 0;
			this->d_panelCanvas->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::d_panelCanvas_Paint);
			// 
			// notifyIcon
			// 
			this->notifyIcon->ContextMenuStrip = this->contextTaskTray;
			this->notifyIcon->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"notifyIcon.Icon")));
			this->notifyIcon->Text = L"RX78-2";
			this->notifyIcon->Visible = true;
			this->notifyIcon->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::notifyIcon_MouseClick);
			this->notifyIcon->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::notifyIcon_MouseDoubleClick);
			// 
			// contextTaskTray
			// 
			this->contextTaskTray->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->trayMenuView, 
				this->trayMenuHide, this->trayMenuSeparator, this->trayMenuExit});
			this->contextTaskTray->Name = L"contextTaskTray";
			this->contextTaskTray->Size = System::Drawing::Size(120, 76);
			// 
			// trayMenuView
			// 
			this->trayMenuView->Enabled = false;
			this->trayMenuView->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"trayMenuView.Image")));
			this->trayMenuView->Name = L"trayMenuView";
			this->trayMenuView->Size = System::Drawing::Size(119, 22);
			this->trayMenuView->Text = L"表示(&V)";
			this->trayMenuView->Click += gcnew System::EventHandler(this, &MainForm::trayMenuView_Click);
			// 
			// trayMenuHide
			// 
			this->trayMenuHide->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"trayMenuHide.Image")));
			this->trayMenuHide->Name = L"trayMenuHide";
			this->trayMenuHide->Size = System::Drawing::Size(119, 22);
			this->trayMenuHide->Text = L"隠す(&H)";
			this->trayMenuHide->Click += gcnew System::EventHandler(this, &MainForm::trayMenuHide_Click);
			// 
			// trayMenuSeparator
			// 
			this->trayMenuSeparator->Name = L"trayMenuSeparator";
			this->trayMenuSeparator->Size = System::Drawing::Size(116, 6);
			// 
			// trayMenuExit
			// 
			this->trayMenuExit->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"trayMenuExit.Image")));
			this->trayMenuExit->Name = L"trayMenuExit";
			this->trayMenuExit->Size = System::Drawing::Size(119, 22);
			this->trayMenuExit->Text = L"終了(&X)";
			this->trayMenuExit->Click += gcnew System::EventHandler(this, &MainForm::trayMenuExit_Click);
			// 
			// timerBinaryClock
			// 
			this->timerBinaryClock->Tick += gcnew System::EventHandler(this, &MainForm::timerBinaryClock_Tick);
			// 
			// timerBinaryTimer
			// 
			this->timerBinaryTimer->Tick += gcnew System::EventHandler(this, &MainForm::timerBinaryTimer_Tick);
			// 
			// timerArrow
			// 
			this->timerArrow->Interval = 70;
			this->timerArrow->Tick += gcnew System::EventHandler(this, &MainForm::timerArrow_Tick);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::GhostWhite;
			this->ClientSize = System::Drawing::Size(684, 662);
			this->Controls->Add(this->tabControl);
			this->Controls->Add(this->statusStrip);
			this->Controls->Add(this->toolStrip);
			this->Controls->Add(this->menuStrip);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip;
			this->MinimumSize = System::Drawing::Size(580, 500);
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"RX78-2";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &MainForm::MainForm_FormClosed);
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
			this->Resize += gcnew System::EventHandler(this, &MainForm::MainForm_Resize);
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			this->toolStrip->ResumeLayout(false);
			this->toolStrip->PerformLayout();
			this->tabControl->ResumeLayout(false);
			this->tabReport->ResumeLayout(false);
			this->tabReport->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->r_gridReport))->EndInit();
			this->tabTcpServer->ResumeLayout(false);
			this->tabTcpServer->PerformLayout();
			this->tabFtpClient->ResumeLayout(false);
			this->f_splitFtp->Panel1->ResumeLayout(false);
			this->f_splitFtp->Panel2->ResumeLayout(false);
			this->f_splitFtp->ResumeLayout(false);
			this->f_gropServer->ResumeLayout(false);
			this->f_gropServer->PerformLayout();
			this->f_splitServer->Panel1->ResumeLayout(false);
			this->f_splitServer->Panel2->ResumeLayout(false);
			this->f_splitServer->ResumeLayout(false);
			this->f_gropLocal->ResumeLayout(false);
			this->f_gropLocal->PerformLayout();
			this->f_splitLocal->Panel1->ResumeLayout(false);
			this->f_splitLocal->Panel2->ResumeLayout(false);
			this->f_splitLocal->ResumeLayout(false);
			this->tabPicturePuzzle->ResumeLayout(false);
			this->p_panelBase->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->p_picturePuzzle))->EndInit();
			this->tabBinaryClock->ResumeLayout(false);
			this->tabBinaryClock->PerformLayout();
			this->tabTetris->ResumeLayout(false);
			this->tabTetris->PerformLayout();
			this->g_panelScore->ResumeLayout(false);
			this->g_panelScore->PerformLayout();
			this->g_panelTetris->ResumeLayout(false);
			this->g_panelTetris->PerformLayout();
			this->tabArrow->ResumeLayout(false);
			this->tabDirectX->ResumeLayout(false);
			this->contextTaskTray->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

#pragma region フォーム

	/// 初期化
	private: void Initialize()
			 {
				 this->isMaximized = false;
				 this->canClose = false;

				 String^ configFileName = System::IO::Path::ChangeExtension(System::Windows::Forms::Application::ExecutablePath, ".xml");
				 this->config = gcnew ConfigFile(configFileName);
				 this->config->LoadFormSizeAndLocation(this);
				 
				 String^ applicationName = System::IO::Path::GetFileNameWithoutExtension(System::Windows::Forms::Application::ExecutablePath);
				 this->startupName = System::Environment::GetFolderPath(System::Environment::SpecialFolder::Startup) + "\\" + applicationName + ".lnk";
				 this->menuStartUp->Checked = (System::IO::File::Exists(this->startupName)) ? true : false;

				 // メニュー
				 this->menuPair = gcnew MenuPairList();
				 this->menuPair->SetPair(this->menuView, this->trayMenuView);
				 this->menuPair->SetPair(this->menuHide, this->trayMenuHide);
				 this->menuPair->SetPair(this->menuExit, this->trayMenuExit, this->toolExit);
				 this->menuPair->SetPair(this->menuOpen, this->toolOpen);
				 this->menuPair->SetPair(this->menuSave, this->toolSave);
				 this->menuPair->SetPair(this->menuUndo, this->toolUndo);
				 this->menuPair->SetPair(this->menuRedo, this->toolRedo);
				 this->menuPair->SetPair(this->menuTcpStart, this->toolTcpStart);
				 this->menuPair->SetPair(this->menuTcpStop, this->toolTcpStop);
				 this->menuPair->SetPair(this->menuTcpClient, this->toolTcpClient);
				 this->menuPair->SetPair(this->menuFtpConnect, this->toolFtpConnect);
				 this->menuPair->SetPair(this->menuFtpDisConnect, this->toolFtpDisConnect);
				 this->menuPair->SetPair(this->menuPictureLoad, this->toolPictureLoad);
				 this->menuPair->SetPair(this->menuTimer, this->toolTimer);
				 this->menuPair->SetPair(this->menuRanking, this->toolRanking);
				 this->menuPair->SetPair(this->menuReset, this->toolReset);

				 // レポート編集
				 this->report = gcnew ReportBook();
				 this->editor = gcnew ReportEditor(this->report);
				 this->editor->EndAction += gcnew ReportEventHandler(this, &MainForm::EndReportAction);
				 this->r_textFileName->Text = this->config->GetReportFileName();
				 this->r_buttonInsertRow->Location = this->r_buttonInsert->Location;
				 this->r_buttonAddRow->Location = this->r_buttonAdd->Location;
				 this->r_buttonRemoveRow->Location = this->r_buttonRemove->Location;

				 // TCPサーバ
				 this->tcpServer = gcnew TcpServerSocket();
				 this->tcpServer->Connected += gcnew TcpEventHandler(this, &MainForm::ConnectedTcpClient);
				 this->tcpServer->DisConnected += gcnew TcpEventHandler(this, &MainForm::DisConnectedTcpClient);
				 this->tcpServer->Received += gcnew TcpEventHandler(this, &MainForm::ReceivedTcpMessage);
				 IPEndPoint^ endPoint = this->config->GetTcpIPEndPoint();
				 this->t_textLocalIp->Text = endPoint->Address->ToString();
				 this->t_textLocalPort->Text = endPoint->Port.ToString();
				 this->tcpServer->Encoding = this->config->GetTcpEncoding();
				 if (this->tcpServer->Encoding == System::Text::Encoding::ASCII)
				 {
					 this->menuAscii->Checked = true;
					 this->menuUtf8->Checked = false;
					 this->menuDefault->Checked = false;
				 }
				 else if (this->tcpServer->Encoding == System::Text::Encoding::UTF8)
				 {
					 this->menuAscii->Checked = false;
					 this->menuUtf8->Checked = true;
					 this->menuDefault->Checked = false;
				 }
				 else
				 {
					 this->menuAscii->Checked = false;
					 this->menuUtf8->Checked = false;
					 this->menuDefault->Checked = true;
				 }

				 // FTPクライアント
				 this->ftpClient = gcnew FtpClient();
				 this->InitializeLocalTree(this->f_treeLocal);

				 // 写真パズル
				 this->puzzle = gcnew PicturePuzzle();
				 this->pictureArray = gcnew array<PictureBox^, 2>(5, 5);
				 for (int y = 0; y < 5; y++)
				 {
					 for (int x = 0; x < 5; x++)
					 {
						 this->pictureArray[x, y] = gcnew System::Windows::Forms::PictureBox();
						 this->pictureArray[x, y]->SizeChanged += gcnew System::EventHandler(this, &MainForm::SizeChangedPuzzle);
						 this->pictureArray[x, y]->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::MouseMove);
						 this->pictureArray[x, y]->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::MouseDown);
						 this->pictureArray[x, y]->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::MouseUp);
						 this->p_panelBase->Controls->Add(this->pictureArray[x, y]);
					 }
				 }
				 this->puzzle->SetPuzzleControl(this->pictureArray);
				 this->ChangePuzzleView(false);

				 // バイナリクロック
				 array<Panel^, 2>^ sec =
				 {
					 {this->b_panelSec1,  this->b_panelSec2,  this->b_panelSec4,  this->b_panelSec8},
					 {this->b_panelSec10, this->b_panelSec20, this->b_panelSec40, nullptr}
				 };
				 array<Panel^, 2>^ min =
				 {
					 {this->b_panelMin1,  this->b_panelMin2,  this->b_panelMin4,  this->b_panelMin8},
					 {this->b_panelMin10, this->b_panelMin20, this->b_panelMin40, nullptr}
				 };
				 array<Panel^, 2>^ hour =
				 {
					 {this->b_panelHour1,  this->b_panelHour2,  this->b_panelHour4, this->b_panelHour8},
					 {this->b_panelHour10, this->b_panelHour20, nullptr,            nullptr}
				 };
				 this->clock = gcnew BinaryClock(sec, min, hour);

				 // テトリス
				 array<Control^>^ canvases = { this->g_panelNext1, this->g_panelNext2, this->g_panelNext3 };
				 this->tetris = gcnew TetrisPackage(this->g_panelTetris, canvases);
				 this->tetris->ScoreChanged += gcnew Anaheim::Tetris::TetrisScoreEventHandler(this, &MainForm::TetrisScoreChanged);
				 this->tetris->GameOver += gcnew Anaheim::Tetris::TetrisScoreEventHandler(this, &MainForm::TetrisGameOver);
				 array<Keys>^ moveDownKeys = { Keys::NumPad2, Keys::Down };
				 array<Keys>^ moveLeftKeys = { Keys::NumPad4, Keys::Left };
				 array<Keys>^ moveRightKeys = { Keys::NumPad6, Keys::Right };
				 array<Keys>^ rotateLeftKeys = { Keys::NumPad7 };
				 array<Keys>^ rotateRightKeys = { Keys::NumPad9, Keys::Up };
				 array<Keys>^ hardDropKeys = { Keys::Space };
				 this->tetris->Controller->Key->MoveDownKeys = moveDownKeys;
				 this->tetris->Controller->Key->MoveLeftKeys = moveLeftKeys;
				 this->tetris->Controller->Key->MoveRightKeys = moveRightKeys;
				 this->tetris->Controller->Key->RotateLeftKeys = rotateLeftKeys;
				 this->tetris->Controller->Key->RotateRightKeys = rotateRightKeys;
				 this->tetris->Controller->Key->HardDropKeys = hardDropKeys;
				 this->menuSound->Checked = this->config->GetTetrisSoundON();
				 this->menuRemote->Checked = this->config->GetTetrisRemoteEnabled();

				 // Arrow虫
				 this->arrow = gcnew ArrowInsectCage(this->a_panelCanvas, 10);

				 // DirectX
				 this->directX = gcnew DirectX3D();
				 this->directX->Initialize(this->d_panelCanvas);

#ifndef _DEBUG
				 // デバッグ
				 this->toolDebug->Visible = false;
				 this->toolSeparatorDebug->Visible = false;
#endif
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// クローズ時処理
	private: System::Void MainForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
			 {
				 if (this->canClose)
				 {
					 bool isRunning = this->tetris->Controller->IsRunning;
					 if (isRunning)
					 {
						 this->tetris->Controller->Pause();
					 }

					 ExitForm^ form = gcnew ExitForm();
					 if (this->Visible)
					 {
						 this->Activate();	// タスクトレイのコンテキストから実行したときに，アクティブにしないとCenterParentが動作しない．
						 form->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
					 }
					 else
					 {
						 form->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
					 }

					 this->contextTaskTray->Enabled = false;
					 if (form->ShowDialog() == System::Windows::Forms::DialogResult::Cancel)
					 {
						 e->Cancel = true;
						 this->canClose = false;
						 this->contextTaskTray->Enabled = true;
						 if (isRunning)
						 {
							 this->tetris->Controller->Start();
						 }
					 }

					 delete form;
				 }
				 else
				 {
					 // TETRiS
					 if (this->tetris->Controller->IsRunning)
					 {
						 this->g_buttonStart->PerformClick();
					 }

					 this->menuHide->PerformClick();
					 e->Cancel = true;
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// クローズ後処理
	private: System::Void MainForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e)
			 {
				 this->config->SaveFormSizeAndLocation(this);
				 this->config->Save();

				 this->tcpServer->Stop();
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// リサイズ
	private: System::Void MainForm_Resize(System::Object^  sender, System::EventArgs^  e)
			 {
				 if (this->WindowState == System::Windows::Forms::FormWindowState::Minimized)
				 {
					 // TETRiS
					 if (this->tetris->Controller->IsRunning)
					 {
						 this->g_buttonStart_Click(this->g_buttonStart, nullptr);
					 }
				 }

				 if (this->WindowState == System::Windows::Forms::FormWindowState::Maximized)
				 {
					 this->isMaximized = true;
				 }
				 else
				 {
					 this->isMaximized = false;
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// タブ切替え
	private: System::Void tabControl_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
			 {
				 // バイナリクロック
				 if (this->tabControl->SelectedTab == this->tabBinaryClock)
				 {
					 this->timerBinaryClock->Enabled = true;
				 }
				 else
				 {
					 this->timerBinaryClock->Enabled = false;
					 this->notifyIcon->Text = this->Text;
				 }

				 // TETRiS
				 if (this->tetris->Controller->IsRunning)
				 {
					 this->g_buttonStart_Click(this->g_buttonStart, nullptr);
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

#pragma endregion

#pragma region メニューバー

	/// 表示
	private: System::Void menuView_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->Show();
				 if (this->isMaximized)
				 {
					 this->WindowState = FormWindowState::Maximized;
				 }
				 else
				 {
					 this->WindowState = FormWindowState::Normal;
				 }
				 this->Activate();
				 this->menuView->Enabled = false;
				 this->menuHide->Enabled = true;
				 this->notifyIcon->ShowBalloonTip(500, this->Text, "Good morning!!", System::Windows::Forms::ToolTipIcon::Info);
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// 隠す
	private: System::Void menuHide_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 if (this->g_buttonStart->Text == "STOP")
				 {
					 this->g_buttonStart->PerformClick();
				 }
				 this->Hide();
				 this->menuView->Enabled = true;
				 this->menuHide->Enabled = false;
				 this->notifyIcon->ShowBalloonTip(500, this->Text, "Good night...", System::Windows::Forms::ToolTipIcon::Info);
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// 終了
	private: System::Void menuExit_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->canClose = true;
				 this->Close();
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// 開く
	private: System::Void menuOpen_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->tabControl->SelectedTab = this->tabReport;
				 this->r_buttonLoad->PerformClick();
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// 保存
	private: System::Void menuSave_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->tabControl->SelectedTab = this->tabReport;
				 this->r_buttonSave->PerformClick();
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// 名前を付けて保存
	private: System::Void menuSaveAs_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->tabControl->SelectedTab = this->tabReport;

				 String^ fileName = this->report->FileName;

				 if (fileName == String::Empty)
				 {
					 this->saveFileDialog->InitialDirectory = System::IO::Directory::GetCurrentDirectory();
				 }
				 else
				 {
					 this->saveFileDialog->InitialDirectory = System::IO::Path::GetDirectoryName(fileName);
				 }

				 this->saveFileDialog->FileName = System::IO::Path::GetFileName(fileName);

				 this->saveFileDialog->Filter = "CSV ファイル(*.csv)|*.csv" + "|" + "XML ファイル(*.xml)|*.xml";
				 if (String::Compare(System::IO::Path::GetExtension(fileName), ".xml", true) == 0)
				 {
					 this->saveFileDialog->FilterIndex = 2;
				 }
				 else
				 {
					 this->saveFileDialog->FilterIndex = 1;
				 }

				 if (this->saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {
					 this->Cursor = Cursors::WaitCursor;

					 this->report->SaveFile(this->saveFileDialog->FileName);
					 this->r_textFileName->Text = this->saveFileDialog->FileName;

					 this->Cursor = Cursors::Default;
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// Undo
	private: System::Void menuUndo_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->tabControl->SelectedTab = this->tabReport;
				 this->editor->Undo();
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// Redo
	private: System::Void menuRedo_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->tabControl->SelectedTab = this->tabReport;
				 this->editor->Redo();
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// クリア
	private: System::Void menuClear_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->tabControl->SelectedTab = this->tabReport;
				 this->report->Clear();
				 this->editor->Clear();
				 this->r_buttonSave->Enabled = false;
				 this->r_buttonInsert->Visible= false;
				 this->r_buttonAdd->Visible = false;
				 this->r_buttonRemove->Visible = false;
				 this->r_buttonInsertRow->Visible = false;
				 this->r_buttonAddRow->Visible = false;
				 this->r_buttonRemoveRow->Visible = false;
				 this->menuSave->Enabled = false;
				 this->menuSaveAs->Enabled = false;
				 this->menuUndo->Enabled = false;
				 this->menuRedo->Enabled = false;
				 this->menuClear->Enabled = false;

				 this->r_comboSection->Items->Clear();
				 this->r_comboSection->Text = String::Empty;
				 this->r_gridReport->Columns->Clear();
				 this->r_gridReport->Rows->Clear();
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// TCPスタート
	private: System::Void menuTcpStart_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->tabControl->SelectedTab = this->tabTcpServer;
				 this->t_buttonStart->PerformClick();
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// TCPストップ
	private: System::Void menuTcpStop_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->tabControl->SelectedTab = this->tabTcpServer;
				 this->t_buttonStop->PerformClick();
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// ASCIIコード
	private: System::Void menuAscii_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->tabControl->SelectedTab = this->tabTcpServer;
				 this->menuAscii->Checked = true;
				 this->menuUtf8->Checked = false;
				 this->menuDefault->Checked = false;
				 this->tcpServer->Encoding = System::Text::Encoding::ASCII;
				 this->config->SetTcpEncoding(this->tcpServer->Encoding);
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// UTF-8
	private: System::Void menuUtf8_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->tabControl->SelectedTab = this->tabTcpServer;
				 this->menuAscii->Checked = false;
				 this->menuUtf8->Checked = true;
				 this->menuDefault->Checked = false;
				 this->tcpServer->Encoding = System::Text::Encoding::UTF8;
				 this->config->SetTcpEncoding(this->tcpServer->Encoding);
			 }
			 // ----------------------------------------------------------------------------------------------------

	// Default
	private: System::Void menuDefault_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->tabControl->SelectedTab = this->tabTcpServer;
				 this->menuAscii->Checked = false;
				 this->menuUtf8->Checked = false;
				 this->menuDefault->Checked = true;
				 this->tcpServer->Encoding = System::Text::Encoding::Default;
				 this->config->SetTcpEncoding(this->tcpServer->Encoding);
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// TCPクライアント
	private: System::Void menuTcpClient_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->tabControl->SelectedTab = this->tabTcpServer;
				 String^ filename = System::Windows::Forms::Application::StartupPath + "\\MS-06S.exe";
				 if (System::IO::File::Exists(filename))
				 {
					 System::Diagnostics::Process::Start(filename);
				 }
				 else
				 {
					 System::Windows::Forms::MessageBox::Show("TCPクライアントの起動に失敗しました！", this->Text, MessageBoxButtons::OK, MessageBoxIcon::Error);
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// FTP接続
	private: System::Void menuFtpConnect_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->tabControl->SelectedTab = this->tabFtpClient;
				 if (this->f_buttonConnect->Text->Equals("接続"))
				 {
					 this->f_buttonConnect->PerformClick();
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// FTP切断
	private: System::Void menuFtpDisConnect_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->tabControl->SelectedTab = this->tabFtpClient;
				 if (this->f_buttonConnect->Text->Equals("切断"))
				 {
					 this->f_buttonConnect->PerformClick();
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// 写真読み込み
	private: System::Void menuPictureLoad_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->tabControl->SelectedTab = this->tabPicturePuzzle;
				 this->p_buttonLoad->PerformClick();
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// タイマー
	private: System::Void menuTimer_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->tabControl->SelectedTab = this->tabBinaryClock;
				 this->b_buttonTimerSet->PerformClick();
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// バイナリクロック色設定（ON）
	private: System::Void menuOnColor_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->tabControl->SelectedTab = this->tabBinaryClock;
				 if (this->colorDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {
					 this->clock->OnColor = this->colorDialog->Color;
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// バイナリクロック色設定（OFF）
	private: System::Void menuOffColor_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->tabControl->SelectedTab = this->tabBinaryClock;
				 if (this->colorDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {
					 this->clock->OffColor = this->colorDialog->Color;
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// TETRiSランキング
	private: System::Void menuRanking_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->tabControl->SelectedTab = this->tabTetris;

				 bool isRunning = this->tetris->Controller->IsRunning;
				 if (isRunning)
				 {
					 this->tetris->Controller->Pause();
				 }

				 int score1 = this->config->GetTetrisScore(1);
				 int score2 = this->config->GetTetrisScore(2);
				 int score3 = this->config->GetTetrisScore(3);
				 String^ message = "SCORE RANKING\n" + 
								   "\n" +
								   "BEST 1：" + String::Format("{0:D6}", score1) + "\n" + 
								   "BEST 2：" + String::Format("{0:D6}", score2) + "\n" + 
								   "BEST 3：" + String::Format("{0:D6}", score3);
				 System::Windows::Forms::MessageBox::Show(message, this->Text, MessageBoxButtons::OK, MessageBoxIcon::Information);

				 if (isRunning)
				 {
					 this->tetris->Controller->Start();
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// TETRiSサウンド
	private: System::Void menuSound_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->tabControl->SelectedTab = this->tabTetris;

				 if (this->menuSound->Checked)
				 {
					 this->menuSound->Checked = false;
				 }
				 else
				 {
					 this->menuSound->Checked = true;
				 }
				 this->config->SetTetrisSoundON(this->menuSound->Checked);
			 }
			 // ----------------------------------------------------------------------------------------------------

	private: System::Void menuSound_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->tetris->Controller->SoundON = this->menuSound->Checked;
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// TETRiSリモート
	private: System::Void menuRemote_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->tabControl->SelectedTab = this->tabTetris;

				 if (this->menuRemote->Checked)
				 {
					 this->menuRemote->Checked = false;
				 }
				 else
				 {
					 this->menuRemote->Checked = true;

					 String^ filename = System::Windows::Forms::Application::StartupPath + "\\RX77-2.exe";
					 if (System::IO::File::Exists(filename))
					 {
						 System::Diagnostics::Process::Start(filename);
					 }
					 else
					 {
						 System::Windows::Forms::MessageBox::Show("TETRiSリモート表示の起動に失敗しました！", this->Text, MessageBoxButtons::OK, MessageBoxIcon::Error);
					 }
				 }
				 this->config->SetTetrisRemoteEnabled(this->menuRemote->Checked);
			 }
			 // ----------------------------------------------------------------------------------------------------

	private: System::Void menuRemote_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
			 {
				 if (this->menuRemote->Checked)
				 {
					 if (!this->tetris->Controller->StartRemote())
					 {
						 this->menuRemote->Checked = false;
					 }
				 }
				 else
				 {
					 this->tetris->Controller->StopRemote();
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// Beetleリセット
	private: System::Void menuReset_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->tabControl->SelectedTab = this->tabArrow;
				 this->arrow->Reset();
				 this->a_panelCanvas->Refresh();
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// サイズリセット
	private: System::Void menuSizeReset_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->WindowState = FormWindowState::Normal;
				 this->Size = System::Drawing::Size(700, 700);
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// メモリ解放
	private: System::Void menuMemoryRelease_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 System::GC::Collect();
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// スタートアップ
	private: System::Void menuStartUp_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 if (this->menuStartUp->Checked)
				 {
					 if (System::IO::File::Exists(this->startupName))
					 {
						 System::IO::File::Delete(this->startupName);
						 this->menuStartUp->Checked = false;
					 }
				 }
				 else
				 {
					 String^ linkPath = System::Windows::Forms::Application::ExecutablePath;
					 ShortcutFile^ shortcut = gcnew ShortcutFile(this->startupName, linkPath);
					 shortcut->WorkDirectory = System::Windows::Forms::Application::StartupPath;
					 shortcut->Save();
					 this->menuStartUp->Checked = true;
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// バージョン情報
	private: System::Void menuVersion_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 VersionForm^ form = gcnew VersionForm();
				 form->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
				 form->Location = Point(System::Math::Max(this->Left - 50, 0), System::Math::Max(this->Top + 50, 0));
				 form->ShowDialog();
				 delete form;
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// 有効/無効切替え
	private: System::Void MenuEnabledChanged(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->menuPair->UpdateEnabled(sender);
			 }
			 // ----------------------------------------------------------------------------------------------------

#pragma endregion

#pragma region ツールバー

	/// ツールボタンクリック
	private: System::Void ToolButtonClick(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->menuPair->ExecuteToolButtont(sender);
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// デバッグ用ボタン
	private: System::Void toolDebug_Click(System::Object^  sender, System::EventArgs^  e)
			 {
			 }
			 // ----------------------------------------------------------------------------------------------------

#pragma endregion

#pragma region タスクトレイ

	/// 表示
	private: System::Void trayMenuView_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->menuPair->ExecuteContext(sender);
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// 隠す
	private: System::Void trayMenuHide_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->menuPair->ExecuteContext(sender);
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// 終了
	private: System::Void trayMenuExit_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->menuPair->ExecuteContext(sender);
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// クリック
	private: System::Void notifyIcon_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
			 {
				 if (e->Button == System::Windows::Forms::MouseButtons::Left && this->Visible)
				 {
					 this->Activate();
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// ダブルクリック
	private: System::Void notifyIcon_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
			 {
				 if (e->Button == System::Windows::Forms::MouseButtons::Left)
				 {
					 if (this->Visible)
					 {
						 this->trayMenuHide->PerformClick();
					 }
					 else
					 {
						 this->trayMenuView->PerformClick();				 
					 }
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

#pragma endregion

#pragma region レポート編集

	/// 読み込み
	private: System::Void r_buttonLoad_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 String^ fileName = this->r_textFileName->Text;

				 if (fileName == String::Empty)
				 {
					 this->openFileDialog->InitialDirectory = System::IO::Directory::GetCurrentDirectory();
				 }
				 else
				 {
					 this->openFileDialog->InitialDirectory = System::IO::Path::GetDirectoryName(fileName);
				 }

				 this->openFileDialog->FileName = System::IO::Path::GetFileName(fileName);

				 this->openFileDialog->Filter = "CSV ファイル(*.csv)|*.csv" + "|" + "XML ファイル(*.xml)|*.xml";
				 if (String::Compare(System::IO::Path::GetExtension(fileName), ".xml", true) == 0)
				 {
					 this->openFileDialog->FilterIndex = 2;
				 }
				 else
				 {
					 this->openFileDialog->FilterIndex = 1;
				 }

				 if (this->openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {
					 this->r_textFileName->Text = this->openFileDialog->FileName;
					 this->LoadReportFile(this->openFileDialog->FileName);
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// ファイル読込み
	private: bool LoadReportFile(String^ fileName)
			 {
				 if (!System::IO::File::Exists(fileName)) return false;

				 this->Cursor = Cursors::WaitCursor;

				 this->menuClear->PerformClick();

				 this->report->LoadFile(fileName);
				 this->UpdateReportComboBox();
				 this->menuSaveAs->Enabled = true;
				 this->menuClear->Enabled = true;
				 this->config->SetReportFileName(fileName);

				 this->Cursor = Cursors::Default;

				 return true;
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// ドラッグ
	private: System::Void tabReport_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
			 {
				 if (e->Data->GetDataPresent(DataFormats::FileDrop))
				 {
					 e->Effect = DragDropEffects::All;
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// ドロップ
	private: System::Void tabReport_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
			 {
				 array<String^>^ files = dynamic_cast<array<String^>^>(e->Data->GetData(DataFormats::FileDrop));

				 this->r_textFileName->Text = files[0];
				 this->LoadReportFile(files[0]);
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// コンボ更新
	private: void UpdateReportComboBox()
			 {
				 this->r_comboSection->Items->Clear();
				 
				 for each (ReportList^ list in this->report->Lists)
				 {
					 this->r_comboSection->Items->Add(list->Section);
				 }

				 if (this->r_comboSection->Items->Count == 0)
				 {
					 this->r_comboSection->Enabled = false;
				 }
				 else
				 {
					 this->r_comboSection->Enabled = true;
					 this->r_comboSection->SelectedIndex = 0;
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// コンボ選択
	private: System::Void r_comboSection_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->UpdateReportGrid();
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// グリッド更新
	private: void UpdateReportGrid()
			 {
				 ReportList^ list = this->report->Select(this->r_comboSection->Text);
				 if (list == nullptr) return;

				 this->Cursor = Cursors::WaitCursor;	// カーソル

				 // 高速化のため，いったんAutoSizeをきる．
				 this->r_gridReport->ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode::EnableResizing;
				 this->r_gridReport->RowHeadersWidthSizeMode = DataGridViewRowHeadersWidthSizeMode::EnableResizing;

				 this->r_gridReport->Columns->Clear();
				 this->r_gridReport->Rows->Clear();
				 this->r_gridReport->ColumnCount = System::Math::Max(1, list->MaxColCount);

				 // 更新
				 for each (ReportItem^ item in list->Items)
				 {
					 this->r_gridReport->Rows->Add(item->ToStringArray());
				 }

				 // 空データでもグリッドを1マス用意する
				 if (this->r_gridReport->Rows->Count == 0)
				 {
					 this->r_gridReport->ColumnCount = 1;
					 this->r_gridReport->Rows->Add(String::Empty);
				 }

				 // 列ヘッダ，ソート無効化
				 int colNo = 1;
				 for each (DataGridViewColumn^ column in this->r_gridReport->Columns)
				 {
					 column->HeaderText = colNo.ToString();
					 column->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;	// ソートしない
					 colNo++;
				 }

				 // 行ヘッダ
				 int rowNo = 1;
				 for each (DataGridViewRow^ row in this->r_gridReport->Rows)
				 {
					 row->HeaderCell->Value = rowNo.ToString();
					 rowNo++;
				 }

				 this->AdjustmentReportGridColWidth();	// 幅調整

				 // AutoSizeサイ設定
				 this->r_gridReport->ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode::AutoSize;
				 this->r_gridReport->RowHeadersWidthSizeMode = DataGridViewRowHeadersWidthSizeMode::AutoSizeToAllHeaders;

				 this->Cursor = Cursors::Default;		// カーソル
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// グリッド更新
	private: void UpdateReportGrid(Point point, String^ value)
			 {
				 this->r_gridReport->Rows[point.Y]->Cells[point.X]->Value = value;
				 this->AdjustmentReportGridColWidth();
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// グリッド列幅調整
	private: void AdjustmentReportGridColWidth()
			 {
				 int margin = 8;
				 int minimum = 40;	// 最小pixel
				 int width = minimum;

				 Graphics^ gr = this->r_gridReport->CreateGraphics();
				 System::Drawing::Font^ font = this->r_gridReport->Font;

				 int colNo = 0;
				 for each (DataGridViewColumn^ column in this->r_gridReport->Columns)
				 {
					 SizeF size = gr->MeasureString(column->HeaderText, font);
					 width = Math::Max(minimum, static_cast<int>(size.Width) + margin);

					 for each (DataGridViewRow^ row in this->r_gridReport->Rows)
					 {
						 if (row->Cells[colNo]->Value == nullptr) continue;

						 String^ string = row->Cells[colNo]->Value->ToString();
						 SizeF s = gr->MeasureString(string, font);
						 width = Math::Max(width, static_cast<int>(s.Width) + margin);
					 }

					 column->Width = width;
					 colNo++;
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// グリッド操作ボタン 有効/無効
	private: System::Void r_gridReport_SelectionChanged(System::Object^  sender, System::EventArgs^  e)
			 {
				 if (this->r_gridReport->SelectedRows->Count == 0)
				 {
					 this->r_buttonInsert->Visible = true;
					 this->r_buttonAdd->Visible = true;
					 this->r_buttonRemove->Visible = true;
					 this->r_buttonInsertRow->Visible = false;
					 this->r_buttonAddRow->Visible = false;
					 this->r_buttonRemoveRow->Visible = false;
				 }
				 else
				 {
					 this->r_buttonInsert->Visible = false;
					 this->r_buttonAdd->Visible = false;
					 this->r_buttonRemove->Visible = false;
					 this->r_buttonInsertRow->Visible = true;
					 this->r_buttonAddRow->Visible = true;
					 this->r_buttonRemoveRow->Visible = true;
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// 編集
	private: System::Void r_gridReport_CellEndEdit(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e)
			 {
				 String^ section = this->r_comboSection->Text;
				 int x = this->r_gridReport->CurrentCell->ColumnIndex;
				 int y = this->r_gridReport->CurrentCell->RowIndex;
				 Point point = Point(x, y);
				 String^ value = this->r_gridReport->CurrentCell->Value->ToString();
				 if (!this->editor->Edit(section, point, value))
				 {
					 this->r_gridReport->CurrentCell->Value = String::Empty;
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// 挿入（左から）
	private: System::Void r_buttonInsert_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 String^ section = this->r_comboSection->Text;
				 int x = this->r_gridReport->CurrentCell->ColumnIndex;
				 int y = this->r_gridReport->CurrentCell->RowIndex;
				 Point point = Point(x, y);
				 this->editor->Insert(section, point, String::Empty);
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// 挿入（右から）
	private: System::Void r_buttonAdd_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 String^ section = this->r_comboSection->Text;
				 int x = this->r_gridReport->CurrentCell->ColumnIndex + 1;
				 int y = this->r_gridReport->CurrentCell->RowIndex;
				 Point point = Point(x, y);
				 this->editor->Insert(section, point, String::Empty);
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// 削除
	private: System::Void r_buttonRemove_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 String^ section = this->r_comboSection->Text;
				 int x = this->r_gridReport->CurrentCell->ColumnIndex;
				 int y = this->r_gridReport->CurrentCell->RowIndex;
				 Point point = Point(x, y);
				 this->editor->Remove(section, point);
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// 行挿入（上から）
	private: System::Void r_buttonInsertRow_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 String^ section = this->r_comboSection->Text;
				 int index = this->r_gridReport->CurrentCell->RowIndex;
				 int count = this->report->Select(section)->MaxColCount;
				 ReportItem^ item = gcnew ReportItem(count);
				 this->editor->InsertStep(section, index, item);
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// 行挿入（下から）
	private: System::Void r_buttonAddRow_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 String^ section = this->r_comboSection->Text;
				 int index = this->r_gridReport->CurrentCell->RowIndex + 1;
				 int count = this->report->Select(section)->MaxColCount;
				 ReportItem^ item = gcnew ReportItem(count);
				 this->editor->InsertStep(section, index, item);
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// 行削除
	private: System::Void r_buttonRemoveRow_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 String^ section = this->r_comboSection->Text;
				 int index = this->r_gridReport->CurrentCell->RowIndex;
				 this->editor->RemoveStep(section, index);
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// アクション後イベントハンドラ
	private: void EndReportAction(System::Object^  sender, ReportEventArgs^  e)
			 {
				 if (e->Section->Equals(this->r_comboSection->Text))
				 {
					 if (e->IsEdit)
					 {
						 if (e->IsUndo)
						 {
							 this->UpdateReportGrid(e->Point, e->OldValue);
						 }
						 else
						 {
							 this->UpdateReportGrid(e->Point, e->NewValue);
						 }
					 }
					 else
					 {
						 this->UpdateReportGrid();
					 }
				 }
				 else
				 {
					 this->r_comboSection->SelectedItem = e->Section;
				 }

				 // セル選択
				 int col = System::Math::Min(e->Point.X, this->r_gridReport->Columns->Count - 1);
				 int row = System::Math::Min(e->Point.Y, this->r_gridReport->Rows->Count - 1);
				 if (e->Point.X == -1)
				 {
					 this->r_gridReport->CurrentCell = this->r_gridReport[0, row];
					 this->r_gridReport->Rows[row]->Selected = true;
				 }
				 else
				 {
					 this->r_gridReport->CurrentCell = this->r_gridReport[col, row];
				 }

				 this->r_buttonSave->Enabled = true;
				 this->menuSave->Enabled = true;
				 this->menuUndo->Enabled = this->editor->CanUndo();
				 this->menuRedo->Enabled = this->editor->CanRedo();
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// 保存
	private: System::Void r_buttonSave_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->Cursor = Cursors::WaitCursor;

				 this->report->SaveFile();
				 this->r_buttonSave->Enabled = false;
				 this->menuSave->Enabled = false;

				 this->Cursor = Cursors::Default;
			 }
			 // ----------------------------------------------------------------------------------------------------

#pragma endregion

#pragma region TCPサーバ

	/// スタート
	private: System::Void t_buttonStart_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 try
				 {
					 if (this->t_textLocalIp->Text->Equals(String::Empty) || this->t_textLocalPort->Text->Equals(String::Empty)) return;

					 IPEndPoint^ endPoint = gcnew IPEndPoint(IPAddress::Parse(this->t_textLocalIp->Text), int::Parse(this->t_textLocalPort->Text));
					 if (this->tcpServer->Initialize(endPoint))
					 {
						 this->tcpServer->Start();

						 this->t_listMessage->Items->Add("【" + DateTime::Now.ToString() + "】 " + this->t_textLocalIp->Text + " : " + this->t_textLocalPort->Text);
						 this->t_listMessage->Items->Add("*** START ***");
						 this->t_listMessage->SelectedIndex = this->t_listMessage->Items->Count - 1;
						 this->t_listMessage->Items->Add(String::Empty);

						 this->UpdateTcpControl();

						 this->config->SetTcpIPEndPoint(endPoint);
					 }
					 else
					 {
						 System::Windows::Forms::MessageBox::Show("初期化に失敗しました！", this->Text, MessageBoxButtons::OK, MessageBoxIcon::Error);
					 }
				 }
				 catch (Exception^)
				 {
					 System::Windows::Forms::MessageBox::Show("初期化に失敗しました！", this->Text, MessageBoxButtons::OK, MessageBoxIcon::Error);
					 return; 
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// ストップ
	private: System::Void t_buttonStop_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->tcpServer->Stop();

				 this->t_listMessage->Items->Add("【" + DateTime::Now.ToString() + "】 " + this->t_textLocalIp->Text + " : " + this->t_textLocalPort->Text);
				 this->t_listMessage->Items->Add("*** STOP ***");
				 this->t_listMessage->SelectedIndex = this->t_listMessage->Items->Count - 1;
				 this->t_listMessage->Items->Add(String::Empty);

				 this->UpdateTcpControl();
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// 切断
	private: System::Void t_buttonDisConnect_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 IPEndPoint^ endPoint = gcnew IPEndPoint(IPAddress::Parse(this->t_comboRemoteIp->Text), int::Parse(this->t_textRemotePort->Text));
				 this->tcpServer->DisConnect(endPoint);

				 this->t_listMessage->Items->Add("【" + DateTime::Now.ToString() + "】 " + endPoint->Address->ToString() + " : " + endPoint->Port.ToString());
				 this->t_listMessage->Items->Add("*** DISCONNECT ***");
				 this->t_listMessage->SelectedIndex = this->t_listMessage->Items->Count - 1;
				 this->t_listMessage->Items->Add(String::Empty);

				 this->UpdateTcpControl();
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// 送信
	private: System::Void t_buttonSendMessage_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 if (this->t_textMessage->Text->Equals(String::Empty)) return;

				 IPEndPoint^ endPoint = gcnew IPEndPoint(IPAddress::Parse(this->t_comboRemoteIp->Text), int::Parse(this->t_textRemotePort->Text));
				 this->tcpServer->SendMessage(this->t_textMessage->Text, endPoint);

				 this->t_listMessage->Items->Add("【" + DateTime::Now.ToString() + "】 " + endPoint->Address->ToString() + " : " + endPoint->Port.ToString());
				 this->t_listMessage->Items->Add(">>  " + this->t_textMessage->Text);
				 this->t_listMessage->SelectedIndex = this->t_listMessage->Items->Count - 1;
				 this->t_listMessage->Items->Add(String::Empty);
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// クリア
	private: System::Void t_buttonClearList_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->t_listMessage->Items->Clear();
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// クライアント接続
	private: void ConnectedTcpClient(System::Object ^sender, Anaheim::TcpSocket::TcpEventArgs ^e)
			 {
				 this->t_listMessage->Items->Add("【" + DateTime::Now.ToString() + "】 " + e->RemoteEndPoint->Address->ToString() + " : " + e->RemoteEndPoint->Port.ToString());
				 this->t_listMessage->Items->Add("*** CONNECTED ***");
				 this->t_listMessage->SelectedIndex = this->t_listMessage->Items->Count - 1;
				 this->t_listMessage->Items->Add(String::Empty);

				 this->UpdateTcpControl();

				 this->WakeupTcpDisplay();
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// クライアント切断
	private: void DisConnectedTcpClient(System::Object ^sender, Anaheim::TcpSocket::TcpEventArgs ^e)
			 {
				 this->t_listMessage->Items->Add("【" + DateTime::Now.ToString() + "】 " + e->RemoteEndPoint->Address->ToString() + " : " + e->RemoteEndPoint->Port.ToString());
				 this->t_listMessage->Items->Add("*** DISCONNECTED ***");
				 this->t_listMessage->SelectedIndex = this->t_listMessage->Items->Count - 1;
				 this->t_listMessage->Items->Add(String::Empty);

				 this->UpdateTcpControl();

				 this->WakeupTcpDisplay();
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// クライアント受信
	private: void ReceivedTcpMessage(System::Object ^sender, Anaheim::TcpSocket::TcpEventArgs ^e)
			 {
				 this->t_listMessage->Items->Add("【" + DateTime::Now.ToString() + "】 " + e->RemoteEndPoint->Address->ToString() + " : " + e->RemoteEndPoint->Port.ToString());
				 this->t_listMessage->Items->Add("<<  " + e->Message);
				 this->t_listMessage->SelectedIndex = this->t_listMessage->Items->Count - 1;
				 this->t_listMessage->Items->Add(String::Empty);
				 int index = 0;
				 for each (TcpClientSocket^ client in this->tcpServer->Clients)
				 {
					 if (client->RemoteEndPoint->Equals(e->RemoteEndPoint))
					 {
						 this->t_comboRemoteIp->SelectedIndex = index;
						 break;
					 }
					 index++;
				 }

				 this->WakeupTcpDisplay();
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// IPコンボボックス選択
	private: System::Void t_comboRemoteIp_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
			 {
				 int index = this->t_comboRemoteIp->SelectedIndex;
				 int port = this->tcpServer->Clients[index]->RemoteEndPoint->Port;
				 this->t_textRemotePort->Text = port.ToString();
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// コントロール更新
	private: void UpdateTcpControl()
			 {
				 try
				 {
					 this->t_comboRemoteIp->Items->Clear();
					 this->t_comboRemoteIp->Text = String::Empty;
					 this->t_textRemotePort->Text = String::Empty;
					 for each (TcpClientSocket^ client in this->tcpServer->Clients)
					 {
						 this->t_comboRemoteIp->Items->Add(client->RemoteEndPoint->Address);
					 }
					 if (this->t_comboRemoteIp->Items->Count != 0)
					 {
						 this->t_comboRemoteIp->SelectedIndex = this->t_comboRemoteIp->Items->Count - 1;
					 }

					 if (this->tcpServer->Clients->Count == 0)
					 {
						 if (this->tcpServer->Started)
						 {
							 this->t_buttonStart->Text = "接続中...";
							 this->t_buttonStart->Enabled = false;
							 this->t_buttonStop->Enabled = true;

							 this->t_textLocalIp->ReadOnly = true;
							 this->t_textLocalPort->ReadOnly = true;

							 this->menuTcpStart->Enabled = false;
							 this->menuTcpStop->Enabled = true;
						 }
						 else
						 {
							 this->t_buttonStart->Text = "スタート";
							 this->t_buttonStart->Enabled = true;
							 this->t_buttonStop->Enabled = false;
							 
							 this->t_textLocalIp->ReadOnly = false;
							 this->t_textLocalPort->ReadOnly = false;

							 this->menuTcpStart->Enabled = true;
							 this->menuTcpStop->Enabled = false;
						 }
						 this->t_buttonDisConnect->Enabled = false;
						 this->t_buttonSendMessage->Enabled = false;
						 this->t_comboRemoteIp->Enabled = false;
					 }
					 else
					 {
						 this->t_buttonStart->Text = "接続";
						 this->t_buttonDisConnect->Enabled = true;
						 this->t_buttonSendMessage->Enabled = true;
						 this->t_comboRemoteIp->Enabled = true;
					 }
				 }
				 catch (Exception^)
				 {
					 return;
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// 受信時画面表示
	private: void WakeupTcpDisplay()
			 {
				 this->menuView->PerformClick();
				 this->tabControl->SelectedTab = this->tabTcpServer;
				 this->Activate();
				 if (this->WindowState == System::Windows::Forms::FormWindowState::Minimized)
				 {
					 this->WindowState = System::Windows::Forms::FormWindowState::Normal;
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

#pragma endregion

#pragma region FTPクライアント

	/// 接続/切断
	private: System::Void f_buttonConnect_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 if (this->f_buttonConnect->Text->Equals("接続"))
				 {
					 FtpConnectForm^ form = gcnew FtpConnectForm(this->config);
					 if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK)
					 {
						 if (this->ftpClient->Connect(form->IpAddress, form->UserName, form->Password))
						 {
							 this->InitializeServerTree(this->f_treeServer);
							 this->config->SetFtpAddress(form->IpAddress);
							 this->config->SetFtpUserName(form->UserName);
							 if (form->SavePassword)
							 {
								 this->config->SetFtpPassword(form->Password);
							 }
							 else
							 {
								 this->config->SetFtpPassword(String::Empty);
							 }
							 this->f_buttonConnect->Text = "切断";
							 this->f_buttonDownload->Enabled = true;
							 this->f_buttonUpload->Enabled = true;

							 this->menuFtpConnect->Enabled = false;
							 this->menuFtpDisConnect->Enabled = true;
						 }
						 else
						 {
							 System::Windows::Forms::MessageBox::Show("FTPサーバへの接続に失敗しました！", this->Text, MessageBoxButtons::OK, MessageBoxIcon::Error);
						 }
					 }
					 delete form;
				 }
				 else
				 {
					 this->ftpClient->DisConnect();
					 this->f_buttonConnect->Text = "接続";
					 this->f_buttonDownload->Enabled = false;
					 this->f_buttonUpload->Enabled = false;

					 this->f_textServerPath->Text = String::Empty;
					 this->f_treeServer->Nodes->Clear();
					 this->f_listViewServerFiles->Items->Clear();

					 this->menuFtpConnect->Enabled = true;
					 this->menuFtpDisConnect->Enabled = false;
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// アップロード
	private: System::Void f_buttonUpload_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 String^ path = this->f_textLocalPath->Text;
				 if (System::IO::Directory::Exists(path))
				 {
					 for each (ListViewItem^ item in this->f_listViewLocalFiles->SelectedItems)
					 {
						 this->ftpClient->Upload(this->f_textServerPath->Text, path->TrimEnd('\\') + "\\" + item->Text); 
					 }
					 System::Windows::Forms::TreeNode^ temp = this->f_treeServer->SelectedNode;
					 this->f_treeServer->SelectedNode = nullptr;
					 this->f_treeServer->SelectedNode = temp;
					 this->config->SetFtpLocalPath(path);
				 }
				 else
				 {
					 System::Windows::Forms::MessageBox::Show("フォルダが存在しません！", this->Text, MessageBoxButtons::OK, MessageBoxIcon::Error);
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// ダウンロード
	private: System::Void f_buttonDownload_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 String^ path = this->f_textLocalPath->Text;
				 if (System::IO::Directory::Exists(path))
				 {
					 for each (ListViewItem^ item in this->f_listViewServerFiles->SelectedItems)
					 {
						 this->ftpClient->Download(this->f_textServerPath->Text + item->Text, path); 
					 }
					 System::Windows::Forms::TreeNode^ temp = this->f_treeLocal->SelectedNode;
					 this->f_treeLocal->SelectedNode = nullptr;
					 this->f_treeLocal->SelectedNode = temp;
					 this->config->SetFtpLocalPath(path);
				 }
				 else
				 {
					 System::Windows::Forms::MessageBox::Show("フォルダが存在しません！", this->Text, MessageBoxButtons::OK, MessageBoxIcon::Error);
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// サーバツリー 初期化
	private: void InitializeServerTree(System::Windows::Forms::TreeView^ treeView)
			 {
				 this->f_treeServer->Nodes->Clear();
				 System::Windows::Forms::TreeNode^ node = gcnew System::Windows::Forms::TreeNode("ROOT", 3, 4);
				 this->f_treeServer->Nodes->Add(node);
				 node->Nodes->Add("dummy");
				 this->f_treeServer->SelectedNode = node;
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// サーバツリー ノード設定
	private: void SetTreeViewNodeServer(System::Windows::Forms::TreeNode^ node)
			 {
				 node->Nodes->Clear();

				 String^ path = this->GetFtpServerPath(node) + "/";
				 array<String^>^ directories = this->ftpClient->GetDirectory(path);
				 for each (String^ dir in directories)
				 {
					 System::Windows::Forms::TreeNode^ nodeChild = gcnew System::Windows::Forms::TreeNode(dir, 3, 4);
					 node->Nodes->Add(nodeChild);
					 nodeChild->Nodes->Add("dummy");
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// サーバツリー パス取得
	private: String^ GetFtpServerPath(System::Windows::Forms::TreeNode^ node)
			 {
				 String^ path = node->FullPath->Substring(4);	// 先頭の"ROOT"を削除
				 path = path->Trim('/');
				 path = (path->Equals(String::Empty)) ? this->ftpClient->RootURI : this->ftpClient->RootURI + "%2f" + path + "/";
				 return path;
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// サーバツリー 展開
	private: System::Void f_treeServer_BeforeExpand(System::Object^  sender, System::Windows::Forms::TreeViewCancelEventArgs^  e)
			 {
				 if (e->Node->Nodes->Count == 1 && e->Node->Nodes[0]->Text->Equals("dummy"))
				 {
					 this->SetTreeViewNodeServer(e->Node);
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// サーバツリー 閉鎖
	private: System::Void f_treeServer_AfterCollapse(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e)
			 {
				 e->Node->Nodes->Clear();
				 e->Node->Nodes->Add("dummy");
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// サーバツリー 選択
	private: System::Void f_treeServer_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e)
			 {
				 this->Cursor = Cursors::WaitCursor;

				 this->f_listViewServerFiles->Items->Clear();

				 System::Windows::Forms::TreeNode^ node = e->Node;
				 this->f_textServerPath->Text = this->GetFtpServerPath(node);

				 String^ path = this->GetFtpServerPath(node);
				 array<String^>^ files = this->ftpClient->GetFileName(path);
				 for each (String^ file in files)
				 {
					 String^ filePath = path + file;
					 array<String^>^ fileItem =
					 {
						 file,
						 String::Format("{0, 0:N0}KB", this->ftpClient->GetFileSize(filePath)),
						 this->ftpClient->GetFileDateTime(filePath).ToString()
					 };
					 System::Windows::Forms::ListViewItem^ viewItem = gcnew System::Windows::Forms::ListViewItem(fileItem);
					 viewItem->ImageIndex = 5;
					 this->f_listViewServerFiles->Items->Add(viewItem);
				 }
				 
				 this->Cursor = Cursors::Default;
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// ローカルツリー 初期化
	private: void InitializeLocalTree(System::Windows::Forms::TreeView^ treeView)
			 {
				 this->f_treeLocal->Nodes->Clear();

				 array<System::IO::DriveInfo^>^ drives = System::IO::DriveInfo::GetDrives();
				 for each (System::IO::DriveInfo^ dir in drives)
				 {
					 System::Windows::Forms::TreeNode^ node = nullptr;
					 String^ driveName = dir->Name->Trim('\\');
					 switch (dir->DriveType)
					 {
						 case DriveType::CDRom:
							 node = gcnew System::Windows::Forms::TreeNode(driveName, 2, 2);
							 break;
						 case DriveType::Fixed:
							 node = gcnew System::Windows::Forms::TreeNode(driveName, 0, 0);
							 break;
						 case DriveType::Network:
							 node = gcnew System::Windows::Forms::TreeNode(driveName, 0, 0);
							 break;
						 case DriveType::NoRootDirectory:
							 node = gcnew System::Windows::Forms::TreeNode(driveName, 0, 0);
							 break;
						 case DriveType::Ram:
							 node = gcnew System::Windows::Forms::TreeNode(driveName, 0, 0);
							 break;
						 case DriveType::Removable:
							 node = gcnew System::Windows::Forms::TreeNode(driveName, 1, 1);
							 break;
						 case DriveType::Unknown:
							 node = gcnew System::Windows::Forms::TreeNode(driveName, 0, 0);
							 break;
						 default:
							 break;
					 }
					 if (node != nullptr)
					 {
						 this->f_treeLocal->Nodes->Add(node);
						 node->Nodes->Add("dummy");
					 }
				 }

				 String^ directoryPath = this->config->GetFtpLocalPath();
				 if (System::IO::Directory::Exists(directoryPath))
				 {
					 System::Windows::Forms::TreeNodeCollection^ nodes = this->f_treeLocal->Nodes;
					 array<String^>^ splitStr = directoryPath->Split('\\');
					 System::Windows::Forms::TreeNode^ lastNode = nullptr;
					 for each (String^ directory in splitStr)
					 {
						 System::Windows::Forms::TreeNodeCollection^ tempNodes = nullptr;
						 for each (System::Windows::Forms::TreeNode^ node in nodes)
						 {
							 if (node->Text->Equals(directory))
							 {
								 this->SetTreeViewNodeLocal(node);
								 lastNode = node;
								 tempNodes = node->Nodes;
								 break;
							 }
						 }
						 nodes = tempNodes;
					 }
					 treeView->SelectedNode = lastNode;
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// ローカルツリー ノード設定
	private: void SetTreeViewNodeLocal(System::Windows::Forms::TreeNode^ node)
			 {
				 node->Nodes->Clear();
				 try
				 {
					 String^ path = node->FullPath + "\\";
					 array<String^>^ directories = System::IO::Directory::GetDirectories(path);
					 for each (String^ dir in directories)
					 {
						 System::IO::FileAttributes atr = System::IO::File::GetAttributes(dir);
						 if ((atr & System::IO::FileAttributes::Hidden) != System::IO::FileAttributes::Hidden)
						 {
							 System::Windows::Forms::TreeNode^ nodeChild = gcnew System::Windows::Forms::TreeNode(System::IO::Path::GetFileName(dir), 3, 4);
							 node->Nodes->Add(nodeChild);
							 nodeChild->Nodes->Add("dummy");
						 }
					 }
				 }
				 catch (Exception^)	// アクセス拒否のフォルダを選択した場合
				 {
					 return;
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// ローカルツリー 展開
	private: System::Void f_treeLocal_BeforeExpand(System::Object^  sender, System::Windows::Forms::TreeViewCancelEventArgs^  e)
			 {
				 if (e->Node->Nodes->Count == 1 && e->Node->Nodes[0]->Text->Equals("dummy"))
				 {
					 this->SetTreeViewNodeLocal(e->Node);
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// ローカルツリー 閉鎖
	private: System::Void f_treeLocal_AfterCollapse(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e)
			 {
				 e->Node->Nodes->Clear();
				 e->Node->Nodes->Add("dummy");
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// ローカルツリー 選択
	private: System::Void f_treeLocal_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e)
			 {
				 this->Cursor = Cursors::WaitCursor;

				 this->f_listViewLocalFiles->Items->Clear();

				 System::Windows::Forms::TreeNode^ node = e->Node;
				 this->f_textLocalPath->Text = node->FullPath;
				 String^ path = node->FullPath + "\\";

				 if (System::IO::Directory::Exists(path))
				 {
					 try
					 {
						 array<String^>^ files = System::IO::Directory::GetFiles(path);
						 for each (String^ item in files)
						 {
							 System::IO::FileAttributes^ atr = System::IO::File::GetAttributes(item);
							 if ((*atr & System::IO::FileAttributes::Hidden) != System::IO::FileAttributes::Hidden)
							 {
								 System::IO::FileInfo^ fileInfo = gcnew System::IO::FileInfo(item);
								 array<String^>^ file =
								 {
									 fileInfo->Name,
									 String::Format("{0, 0:N0}KB", (fileInfo->Length % 1024 == 0) ? fileInfo->Length / 1024 : fileInfo->Length / 1024 + 1),
									 fileInfo->LastWriteTime.ToString()
								 };
								 System::Windows::Forms::ListViewItem^ viewItem = gcnew System::Windows::Forms::ListViewItem(file);
								 viewItem->ImageIndex = 5;
								 this->f_listViewLocalFiles->Items->Add(viewItem);
							 }
						 }
					 }
					 catch (Exception^)	// アクセス拒否のフォルダを選択した場合
					 {
						 return;
					 }
				 }

				 this->Cursor = Cursors::Default;
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// スプリッタ
	private: System::Void f_splitFtp_SplitterMoved(System::Object^  sender, System::Windows::Forms::SplitterEventArgs^  e)
			 {
				 this->tabFtpClient->Focus();
			 }
			 // ----------------------------------------------------------------------------------------------------

#pragma endregion

#pragma region 写真パズル

	/// 読み込み
	private: System::Void p_buttonLoad_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->openFileDialog->Filter = "ビットマップ(*.bmp)|*.bmp" + "|" + "JPEG(*.jpg;*.jpeg)|*.jpg;*jpeg";
				 String^ filePath = this->config->GetPicturePath();
				 if (filePath->Equals(String::Empty))
				 {
					 this->openFileDialog->InitialDirectory = System::IO::Directory::GetCurrentDirectory();
				 }
				 else
				 {
					 this->openFileDialog->InitialDirectory = System::IO::Path::GetDirectoryName(filePath);
				 }
				 this->openFileDialog->FileName = System::IO::Path::GetFileName(filePath);
				 if (System::IO::Path::GetExtension(filePath)->ToLower()->Equals(".jpg") || System::IO::Path::GetExtension(filePath)->ToLower()->Equals(".jpeg"))
				 {
					 this->openFileDialog->FilterIndex = 2;
				 }
				 else
				 {
					 this->openFileDialog->FilterIndex = 1;
				 }

				 if (this->openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {
					 this->Cursor = Cursors::WaitCursor;

					 this->puzzle->Bitmap->LoadFile(this->openFileDialog->FileName);
					 this->puzzle->Bitmap->ChangeSize(this->p_picturePuzzle->Size);
					 this->p_picturePuzzle->Image = this->puzzle->Bitmap->GetBitmap(false);

					 this->config->SetPicturePath(this->openFileDialog->FileName);
					 this->p_buttonClearPicture->Visible = true;
					 this->p_buttonPuzzle->Enabled = true;

					 this->Cursor = Cursors::Default;
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// パズル
	private: System::Void p_buttonPuzzle_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->Cursor = Cursors::WaitCursor;

				 if (this->p_buttonPuzzle->Text->Equals("パズル"))
				 {
					 this->p_buttonPuzzle->Text = "キャンセル";
					 this->p_buttonLoad->Enabled = false;
					 this->p_buttonClearPicture->Enabled = false;
					 this->menuPicturePuzzle->Enabled = false;
					 this->ChangePuzzleView(true);
				 }
				 else
				 {
					 this->p_buttonPuzzle->Text = "パズル";
					 this->p_buttonLoad->Enabled = true;
					 this->p_buttonClearPicture->Enabled = true;
					 this->menuPicturePuzzle->Enabled = true;
					 this->ChangePuzzleView(false);
				 }

				 this->Cursor = Cursors::Default;
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// クリア
	private: System::Void p_buttonClearPicture_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->p_picturePuzzle->Image = nullptr;
				 for each (PictureBox^ picture in this->pictureArray)
				 {
					 picture->Image = nullptr;
				 }
				 this->p_buttonPuzzle->Enabled = false;
				 this->p_buttonClearPicture->Visible = false;
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// リサイズ（全体）
	private: System::Void p_picturePuzzle_SizeChanged(System::Object^  sender, System::EventArgs^  e)
			 {
				 if (this->p_picturePuzzle->Image == nullptr) return;
				 if (this->p_picturePuzzle->Width == 0 || this->p_picturePuzzle->Height == 0) return;		// 最小化時対策

				 this->puzzle->Bitmap->ChangeSize(this->p_picturePuzzle->Size);
				 delete this->p_picturePuzzle->Image;
				 this->p_picturePuzzle->Image = this->puzzle->Bitmap->GetBitmap(false);
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// リサイズ（1ピース）
	private: System::Void SizeChangedPuzzle(System::Object^  sender, System::EventArgs^  e)
			 {
				 if (this->p_picturePuzzle->Image == nullptr) return;
				 if (this->p_picturePuzzle->Width == 0 || this->p_picturePuzzle->Height == 0) return;		// 最小化時対策

				 PictureBox^ picture = dynamic_cast<PictureBox^>(sender);

				 this->puzzle->Bitmap->ChangeSize(System::Drawing::Size(this->p_panelBase->Width, this->p_panelBase->Height / 6 * 5));
				 Point point = this->puzzle->GetCorrectPoint(picture);
				 bool isReverse = (this->puzzle->IsCorrect(picture)) ? false : true;
				 delete picture->Image;
				 picture->Image = this->puzzle->Bitmap->GetSmallBitmap(point, isReverse);
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// リサイズ（パネル）
	private: System::Void p_panelBase_SizeChanged(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->p_picturePuzzle->Width = this->p_panelBase->Width;
				 if (this->p_buttonPuzzle->Text->Equals("パズル"))
				 {
					 this->p_picturePuzzle->Height = this->p_panelBase->Height - 2;		// -2：微調整
				 }
				 else
				 {
					 for (int y = 0; y < 5; y++)
					 {
						 for (int x = 0; x < 5; x++)
						 {
							 Point location = this->GetPuzzleLocation(this->puzzle->GetRialPoint(this->pictureArray[x, y]));
							 Drawing::Size size = this->GetPuzzleSize();
							 this->pictureArray[x, y]->Location = location;
							 this->pictureArray[x, y]->Size = size;
						 }
					 }
				 }
				 Drawing::Size size = this->GetPuzzleSize();
				 this->p_panelBottom->Width = size.Width * 4;
				 this->p_panelBottom->Height = size.Height;
				 this->p_panelBottom->Top = size.Height * 5;
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// マウスダウン
	private: System::Void MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
			 {
				 if (e->Button != System::Windows::Forms::MouseButtons::Left) return;

				 PictureBox^ picture = dynamic_cast<PictureBox^>(sender);
				 PuzzleDrag::Direction direction = this->puzzle->GetDirectionCanMove(picture);

				 switch (direction)
				 {
					 case PuzzleDrag::Direction::Up:
						 this->Cursor = Cursors::PanNorth;
						 break;
					 case PuzzleDrag::Direction::Down:
						 this->Cursor = Cursors::PanSouth;
						 break;
					 case PuzzleDrag::Direction::Left:
						 this->Cursor = Cursors::PanWest;
						 break;
					 case PuzzleDrag::Direction::Right:
						 this->Cursor = Cursors::PanEast;
						 break;
					 default:
						 this->Cursor = Cursors::Default;
						 break;
				 }

				 if (direction != PuzzleDrag::Direction::Non)
				 {
					 Point clickPoint = Point(picture->Left + e->X, picture->Top + e->Y);
					 this->puzzle->Drag->Begin(picture, clickPoint, direction);
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// マウスムーブ
	private: System::Void MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
			 {
				 if (this->Cursor == Cursors::Default) return;

				 PictureBox^ picture = dynamic_cast<PictureBox^>(sender);
				 Point point = Point(picture->Left + e->X, picture->Top + e->Y);
				 this->puzzle->Drag->Move(point);
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// マウスアップ
	private: System::Void MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
			 {
				 if (e->Button != System::Windows::Forms::MouseButtons::Left) return;

				 if (this->puzzle->Drag->End())
				 {
					 PictureBox^ picture = dynamic_cast<PictureBox^>(sender);
					 this->puzzle->MovePuzzle(picture);

					 bool isReverse = (this->puzzle->IsCorrect(picture)) ? false : true;
					 Point point = this->puzzle->GetCorrectPoint(picture);
					 picture->Image = this->puzzle->Bitmap->GetSmallBitmap(point, isReverse);
				 }

				 this->Cursor = Cursors::Default;
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// パズルの頂点取得
	private: Point GetPuzzleLocation(Point point)
			 {
				 return Point(this->p_panelBase->Width / 5 * point.X, this->p_panelBase->Height / 6 * point.Y);
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// パズルのサイズ取得
	private: Drawing::Size GetPuzzleSize()
			 {
				 return Drawing::Size(this->p_panelBase->Width / 5, this->p_panelBase->Height / 6);
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// 通常/パズル用表示切り替え
	private: void ChangePuzzleView(bool isPuzzleMode)
			 {
				 if (isPuzzleMode)
				 {
					 // 下部パネル
					 Drawing::Size size = this->GetPuzzleSize();
					 this->p_panelBottom->Width = size.Width * 4;
					 this->p_panelBottom->Height = size.Height;
					 this->p_panelBottom->Top = size.Height * 5;
					 this->p_panelBottom->Visible = true;

					 // イメージ
					 this->p_picturePuzzle->Visible = false;

					 // パズル
					 this->puzzle->Bitmap->ChangeSize(System::Drawing::Size(this->p_panelBase->Width, this->p_panelBase->Height / 6 * 5));
					 for (int y = 0; y < 5; y++)
					 {
						 for (int x = 0; x < 5; x++)
						 {
							 Point point = this->GetPuzzleLocation(Point(x, y));
							 this->pictureArray[x, y]->Location = point;
							 this->pictureArray[x, y]->Size = size;
							 this->pictureArray[x, y]->Visible = true;
						 }
					 }
					 this->ShuffleImage();
				 }
				 else
				 {
					 // 下部パネル
					 this->p_panelBottom->Visible = false;
					 
					 // イメージ
					 this->puzzle->Bitmap->ChangeSize(this->p_picturePuzzle->Size);
					 this->p_picturePuzzle->Width = this->p_panelBase->Width;
					 this->p_picturePuzzle->Height = this->p_panelBase->Height;
					 this->p_picturePuzzle->Image = this->puzzle->Bitmap->GetBitmap(false);
					 this->p_picturePuzzle->Visible = true;

					 // パズル
					 for (int y = 0; y < 5; y++)
					 {
						 for (int x = 0; x < 5; x++)
						 {
							 this->pictureArray[x, y]->Visible = false;
						 }
					 }
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// パズルシャッフル
	private: void ShuffleImage()
			 {
				 // シャッフル
				 this->puzzle->Shuffle();

				 //	パネル配置
				 for (int y = 0; y < 5; y++)
				 {
					 for (int x = 0; x < 5; x++)
					 {
						 Point point = this->puzzle->GetRialPoint(this->pictureArray[x, y]);
						 this->pictureArray[x, y]->Location = this->GetPuzzleLocation(point);
					 }
				 }

				 // イメージ更新
				 for (int y = 0; y < 5; y++)
				 {
					 for (int x = 0; x < 5; x++)
					 {
						 bool isReverse = (this->puzzle->IsCorrect(this->pictureArray[x, y])) ? false : true;
						 this->pictureArray[x, y]->Image = this->puzzle->Bitmap->GetSmallBitmap(Point(x, y), isReverse);
					 }
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

#pragma endregion

#pragma region バイナリクロック

	/// タイマー
	private: System::Void b_buttonTimerSet_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 SetTimerForm^ form = gcnew SetTimerForm(this->config);
				 if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {
					 DateTime time = form->EndTime;
					 this->clock->EndTime = time;
					 this->timerBinaryTimer->Interval = 100;
					 this->timerBinaryTimer->Enabled = true;
					 this->b_buttonTimerSet->Enabled = false;
					 this->menuTimer->Enabled = false;
					 this->b_buttonTimerStop->Enabled = true;
					 this->b_labelSpanTime->Visible = true;
					 this->timerBinaryTimer->Tag = true;	// タイムアップ時に表示
				 }
				 delete form;
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// ストップ
	private: System::Void b_buttonTimerStop_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->timerBinaryTimer->Enabled = false;
				 this->b_buttonTimerSet->Enabled = true;
				 this->menuTimer->Enabled = true;
				 this->b_buttonTimerStop->Enabled = false;
				 this->b_labelSpanTime->Visible = false;
				 this->timerBinaryTimer->Tag = false;
				 this->b_labelSpanTime->Text = "00:00:00";
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// リサイズ
	private: System::Void tabBinaryClock_Resize(System::Object^  sender, System::EventArgs^  e)
			 {
				 // サイズ
				 int min = System::Math::Min(this->Width / 20, this->Height / 20);
				 System::Drawing::Size size = System::Drawing::Size(min, min);
				 this->b_panelHour10->Size = size;
				 this->b_panelHour20->Size = size;
				 this->b_panelHour1->Size  = size;
				 this->b_panelHour2->Size  = size;
				 this->b_panelHour4->Size  = size;
				 this->b_panelHour8->Size  = size;
				 this->b_panelMin10->Size  = size;
				 this->b_panelMin20->Size  = size;
				 this->b_panelMin40->Size  = size;
				 this->b_panelMin1->Size   = size;
				 this->b_panelMin2->Size   = size;
				 this->b_panelMin4->Size   = size;
				 this->b_panelMin8->Size   = size;
				 this->b_panelSec10->Size  = size;
				 this->b_panelSec20->Size  = size;
				 this->b_panelSec40->Size  = size;
				 this->b_panelSec1->Size   = size;
				 this->b_panelSec2->Size   = size;
				 this->b_panelSec4->Size   = size;
				 this->b_panelSec8->Size   = size;

				 // 位置
				 int x = this->tabBinaryClock->Width / 7;
				 int y = this->tabBinaryClock->Height / 7;
				 int offsetX = this->b_panelHour1->Width / 2;
				 this->b_panelHour10->Location = Point(x * 1 - offsetX, y * 4);
				 this->b_panelHour20->Location = Point(x * 1 - offsetX, y * 3);
				 this->b_panelHour1->Location  = Point(x * 2 - offsetX, y * 4);
				 this->b_panelHour2->Location  = Point(x * 2 - offsetX, y * 3);
				 this->b_panelHour4->Location  = Point(x * 2 - offsetX, y * 2);
				 this->b_panelHour8->Location  = Point(x * 2 - offsetX, y * 1);
				 this->b_panelMin10->Location  = Point(x * 3 - offsetX, y * 4);
				 this->b_panelMin20->Location  = Point(x * 3 - offsetX, y * 3);
				 this->b_panelMin40->Location  = Point(x * 3 - offsetX, y * 2);
				 this->b_panelMin1->Location   = Point(x * 4 - offsetX, y * 4);
				 this->b_panelMin2->Location   = Point(x * 4 - offsetX, y * 3);
				 this->b_panelMin4->Location   = Point(x * 4 - offsetX, y * 2);
				 this->b_panelMin8->Location   = Point(x * 4 - offsetX, y * 1);
				 this->b_panelSec10->Location  = Point(x * 5 - offsetX, y * 4);
				 this->b_panelSec20->Location  = Point(x * 5 - offsetX, y * 3);
				 this->b_panelSec40->Location  = Point(x * 5 - offsetX, y * 2);
				 this->b_panelSec1->Location   = Point(x * 6 - offsetX, y * 4);
				 this->b_panelSec2->Location   = Point(x * 6 - offsetX, y * 3);
				 this->b_panelSec4->Location   = Point(x * 6 - offsetX, y * 2);
				 this->b_panelSec8->Location   = Point(x * 6 - offsetX, y * 1);
				 this->b_labelHour2->Location  = Point(x * 1 - offsetX, y * 5);
				 this->b_labelHour1->Location  = Point(x * 2 - offsetX, y * 5);
				 this->b_labelMin2->Location   = Point(x * 3 - offsetX, y * 5);
				 this->b_labelMin1->Location   = Point(x * 4 - offsetX, y * 5);
				 this->b_labelSec2->Location   = Point(x * 5 - offsetX, y * 5);
				 this->b_labelSec1->Location   = Point(x * 6 - offsetX, y * 5);
				 int colon1X = (this->b_labelMin1->Left + this->b_labelMin1->Width + this->b_labelSec2->Left) / 2 - this->b_labelColon1->Width / 2;
				 this->b_labelColon1->Location = Point(colon1X, y * 5);
				 int colon2X = (this->b_labelHour1->Left + this->b_labelHour1->Width + this->b_labelMin2->Left) / 2 - this->b_labelColon2->Width / 2;
				 this->b_labelColon2->Location = Point(colon2X, y * 5);
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// タイマー処理（時計表示）
	private: System::Void timerBinaryClock_Tick(System::Object^  sender, System::EventArgs^  e)
			 {
				 String^ now = this->clock->Display();

				 array<wchar_t>^ separator = { ':' };
				 array<String^>^ split = now->Split(separator);
				 if (split[0]->Length == 1)
				 {
					 split[0] = "0" + split[0];
				 }
				 this->b_labelHour2->Text = split[0]->Substring(0, 1);
				 this->b_labelHour1->Text = split[0]->Substring(1, 1);
				 this->b_labelMin2->Text = split[1]->Substring(0, 1);
				 this->b_labelMin1->Text = split[1]->Substring(1, 1);
				 this->b_labelSec2->Text = split[2]->Substring(0, 1);
				 this->b_labelSec1->Text = split[2]->Substring(1, 1);

				 this->notifyIcon->Text = now;
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// タイマー処理（タイマー機能）
	private: System::Void timerBinaryTimer_Tick(System::Object^  sender, System::EventArgs^  e)
			 {
				 TimeSpan span = this->clock->GetTimerSpan();
				 if (0 < span.Ticks)
				 {
					 this->b_labelSpanTime->Text = String::Format("{0:D2}:{1:D2}:{2:D2}", span.Hours, span.Minutes, span.Seconds);
				 }
				 else
				 {
					 this->timerBinaryTimer->Interval = 500;
					 if (this->b_labelSpanTime->Visible)
					 {
						 this->b_labelSpanTime->Visible = false;
					 }
					 else
					 {
						 this->b_labelSpanTime->Visible = true;
					 }

					 if (static_cast<bool>(this->timerBinaryTimer->Tag))
					 {
						 this->menuView_Click(this->menuView, nullptr);
						 this->tabControl->SelectedTab = this->tabBinaryClock;
						 this->timerBinaryTimer->Tag = false;
					 }
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

#pragma endregion

#pragma region TETRiS

	/// Start/Stop/Restartボタン
	private: System::Void g_buttonStart_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 if (this->g_buttonStart->Text == "START")
				 {
					 this->tetris->Controller->Initialize();
					 this->ShowTetrisMessage("TETRiS START !!");
					 this->Refresh();
					 System::Threading::Thread::Sleep(1000);
					 this->g_labelMessage->Visible = false;
					 this->tetris->Controller->Start();
					 this->g_buttonStart->Text = "PAUSE";
					 this->g_buttonEnd->Enabled = true;
				 }
				 else if (this->g_buttonStart->Text == "RESTART")
				 {
					 this->g_labelMessage->Visible = false;
					 this->tetris->Controller->Start();
					 this->g_buttonStart->Text = "PAUSE";
				 }
				 else if (this->g_buttonStart->Text == "PAUSE")
				 {
					 this->ShowTetrisMessage("PAUSE !!");
					 this->tetris->Controller->Pause();
					 this->g_buttonStart->Text = "RESTART";
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// Endボタン
	private: System::Void g_buttonEnd_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 bool isRunning = this->tetris->Controller->IsRunning;
				 if (isRunning)
				 {
					 this->g_buttonStart->PerformClick();
				 }

				 String^ message = "TETRiSを終了しますか？";
				 if (System::Windows::Forms::MessageBox::Show(message, this->Text, MessageBoxButtons::OKCancel, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::OK)
				 {
					 this->tetris->Controller->Clear();
					 this->g_labelMessage->Visible = false;
				 }
				 else
				 {
					 if (isRunning)
					 {
						 this->g_buttonStart->PerformClick();
					 }
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// How Toボタン
	private: System::Void g_buttonHowTo_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 bool isRunning = this->tetris->Controller->IsRunning;
				 if (isRunning)
				 {
					 this->g_buttonStart->PerformClick();
				 }

				 String^ message = "Down\t  ： Num2 or ↓\n" +
								   "Left\t  ： Num4 or ←\n" + 
								   "Right\t  ： Num6 or →\n" +
								   "Turn Left\t  ： Num7\n" +
								   "Turn Right ： Num9 or ↑\n" +
				                   "Hard Drop ： Space";
				 System::Windows::Forms::MessageBox::Show(message, this->Text, MessageBoxButtons::OK, MessageBoxIcon::Information);

				 if (isRunning)
				 {
					 this->g_buttonStart->PerformClick();
				 }
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// メッセージ表示
	private: void ShowTetrisMessage(String^ message)
			 {
				 this->g_labelMessage->Text = message;
				 this->g_labelMessage->Left = (this->g_panelTetris->Width - this->g_labelMessage->Width) / 2;
				 this->g_labelMessage->Top = (this->g_panelTetris->Height - this->g_labelMessage->Height) / 2;
				 this->g_labelMessage->Visible = true;
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// スコア更新　イベントハンドラ
	private: void TetrisScoreChanged(System::Object^  sender, Anaheim::Tetris::TetrisScoreEventArgs^  e)
			 {
				 this->g_labelScore->Text = String::Format("{0:D3}", e->Score->Score);
				 this->g_labelSingle->Text = e->Score->SingleCount.ToString();
				 this->g_labelDouble->Text = e->Score->DoubleCount.ToString();
				 this->g_labelTriple->Text = e->Score->TripleCount.ToString();
				 this->g_labelTetris->Text = e->Score->TetrisCount.ToString();

				 this->g_labelScore->Left = this->g_labelScoreTitle->Left + this->g_labelScoreTitle->Width - this->g_labelScore->Width;
				 this->g_labelSingle->Left = this->g_labelSingleTitle->Left + this->g_labelSingleTitle->Width - this->g_labelSingle->Width;
				 this->g_labelDouble->Left = this->g_labelDoubleTitle->Left + this->g_labelDoubleTitle->Width - this->g_labelDouble->Width;
				 this->g_labelTriple->Left = this->g_labelTripleTitle->Left + this->g_labelTripleTitle->Width - this->g_labelTriple->Width;
				 this->g_labelTetris->Left = this->g_labelTetrisTitle->Left + this->g_labelTetrisTitle->Width - this->g_labelTetris->Width;
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// ゲームオーバー　イベントハンドラ
	private: void TetrisGameOver(System::Object^  sender, Anaheim::Tetris::TetrisScoreEventArgs^  e)
			 {
				 this->tabTetris->Focus();	// スペースキーで続けてスタートボタンが押下されるのを防止

				 this->g_buttonStart->Text = "START";
				 this->g_buttonEnd->Enabled = false;

				 this->config->SetTetrisScore(e->Score->Score);

				 this->ShowTetrisMessage("GAME OVER !!");
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// リサイズ
	private: System::Void tabTetris_Resize(System::Object^  sender, System::EventArgs^  e)
			 {
				 if (this->WindowState == FormWindowState::Minimized) return;

				 const int margin = 6;
				 this->g_panelTetris->Width = this->g_panelTetris->Height / 2;
				 this->g_panelNext1->Width = static_cast<int>(this->g_panelTetris->Width / 10.0 * 4);
				 this->g_panelNext1->Height = this->g_panelNext1->Width / 2;
				 this->g_panelNext2->Width = static_cast<int>(this->g_panelNext1->Width * 0.8);
				 this->g_panelNext2->Height = this->g_panelNext2->Width / 2;
				 this->g_panelNext3->Width = this->g_panelNext2->Width;
				 this->g_panelNext3->Height = this->g_panelNext2->Height;
				 this->g_panelNext1->Left = this->g_panelTetris->Left + this->g_panelTetris->Width + margin;
				 this->g_panelNext2->Left = this->g_panelNext1->Left;
				 this->g_panelNext2->Top = this->g_panelNext1->Top + this->g_panelNext1->Height + margin;
				 this->g_panelNext3->Left = this->g_panelNext2->Left + this->g_panelNext2->Width + margin;
				 this->g_panelNext3->Top = this->g_panelNext2->Top;
				 this->g_labelNext->Left = this->g_panelNext1->Left + (this->g_panelNext1->Width - this->g_labelNext->Width) / 2;

				 this->g_panelScore->Left = this->g_panelNext1->Left;
				 this->g_panelScore->Top = this->g_panelNext2->Top + this->g_panelNext2->Height + margin;

				 this->g_labelMessage->Left = (this->g_panelTetris->Width - this->g_labelMessage->Width) / 2;
				 this->g_labelMessage->Top = (this->g_panelTetris->Height - this->g_labelMessage->Height) / 2;
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// キーダウン（ダイアログ文字）
	protected: virtual bool ProcessDialogKey(System::Windows::Forms::Keys keyData) override
			   {
				   if (this->tetris->Controller->IsRunning && this->tetris->Controller->Key->IsRegisteredKey(keyData))
				   {
					   return this->tetris->Controller->Key->Execute(keyData);
				   }

				   return Form::ProcessDialogKey(keyData);
			   }
			   // ----------------------------------------------------------------------------------------------------

#pragma endregion

#pragma region ARROW

	/// タイマー処理
	private: System::Void timerArrow_Tick(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->arrow->Move();
				 this->arrow->Draw();
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// マウスEnter
	private: System::Void a_panelCanvas_MouseEnter(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->timerArrow->Enabled = true;
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// マウスLeave
	private: System::Void a_panelCanvas_MouseLeave(System::Object^  sender, System::EventArgs^  e)
			 {
				 this->timerArrow->Enabled = false;
			 }
			 // ----------------------------------------------------------------------------------------------------

	/// 描画
	private: System::Void a_panelCanvas_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
			 {
				 this->arrow->Draw();
			 }
			 // ----------------------------------------------------------------------------------------------------

#pragma endregion

#pragma region DirectX

	/// 描画
	private: System::Void d_panelCanvas_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
			 {
				 this->directX->Draw();
			 }
			 // ----------------------------------------------------------------------------------------------------

#pragma endregion

	};
}
