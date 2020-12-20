// FiveChessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FiveChess.h"
#include "FiveChessDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int m_data[15][15];

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFiveChessDlg dialog

CFiveChessDlg::CFiveChessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFiveChessDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFiveChessDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFiveChessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFiveChessDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFiveChessDlg, CDialog)
	//{{AFX_MSG_MAP(CFiveChessDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_DRAW_GAME_MENU, OnDrawGameMenu)
	ON_COMMAND(ID_EXIT_GAME_MENU, OnExitGameMenu)
	ON_COMMAND(ID_NEW_GAME_MENU, OnNewGameMenu)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFiveChessDlg message handlers

BOOL CFiveChessDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	m_main_menu.LoadMenu(IDR_MAIN_MENU);//加载主菜单资源
	SetMenu(&m_main_menu);//设置主菜单
	m_main_menu.EnableMenuItem(ID_DRAW_GAME_MENU, MF_GRAYED | MF_DISABLED);//在游戏开始前，使和棋菜单栏为灰
	m_bIsConnect = FALSE;//连接状态标志为假
	CRect rect(0, 0, 200, 200);
	m_board.CreateEx( WS_EX_CLIENTEDGE, _T("ChessBoard"), NULL, WS_VISIBLE | WS_BORDER | WS_CHILD,
	CRect( 0, 0, 401, 478 ), this, IDC_BOARD );
	//清空棋盘
	m_board.Clear( TRUE );
	GetDlgItem( IDC_BOARD )->SetFocus(); //设置棋盘窗口对象得到焦点
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFiveChessDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFiveChessDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFiveChessDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFiveChessDlg::OnDrawGameMenu() 
{
	// TODO: Add your command handler code here
		if(m_bIsConnect)
		{
				m_board.DrawGame();
			}
}

void CFiveChessDlg::OnExitGameMenu() 
{
	// TODO: Add your command handler code here
	//SetMenu(NULL);//清空主菜单对象
	CDialog::OnCancel();//调用父类对话框的退出函数

}

void CFiveChessDlg::OnNewGameMenu() 
{
	// TODO: Add your command handler code here
	if(IDOK==m_setup_dlg.DoModal())
	{
		Restart();
		NewGameStart(m_setup_dlg.m_isHost);//单击确定按钮，调用开始新游戏函数
	}
}

void CFiveChessDlg::Restart()//系统菜单栏响应函数
{
		m_conncet.Close();//连接监听关闭 
		m_sock.Close();//使用端口关闭
}

void CFiveChessDlg::NewGameStart(BOOL isHost)
		{
		if(isHost)
				{//当前选择的是主机
				m_conncet.Create(m_setup_dlg.m_net_port);	//建立端口对象
				m_conncet.Listen();							//监听
		}
		else
				{//当前选择的是客户机
				m_sock.Create();							//建立端口对象
				//建立连接
				m_sock.Connect(m_setup_dlg.m_strHostIP, m_setup_dlg.m_net_port);
		}
}

void CFiveChessDlg::Accept()
{
		//接受连接
		m_conncet.Accept(m_sock);
		//设置连接成功标志
		m_bIsConnect = TRUE;
		//设置当前棋子颜色
		m_board.SetColor(BLACK);
		m_board.Clear(FALSE);
		//弹出提示对话框
		MessageBox( _T("连接成功,可以开始游戏."), _T("五子棋"), MB_ICONINFORMATION);
}

void CFiveChessDlg::Connect()
{
		//设置连接成功标志
		m_bIsConnect = TRUE;
		//设置当前棋子颜色
		m_board.SetColor(WHITE);
		m_board.Clear(TRUE);
		//弹出提示对话框
		MessageBox( _T("连接成功,可以开始游戏."), _T("五子棋"), MB_ICONINFORMATION);
}

void CFiveChessDlg::Send(MSGSTRUCT * pmsg)
{
		m_sock.Send((LPVOID)pmsg, sizeof(MSGSTRUCT));
}

void CFiveChessDlg::SetMenuState(BOOL bEnable)
{
		UINT uEnable, uDisable;
    if ( bEnable )
				{
        uEnable = MF_ENABLED;
        uDisable = MF_GRAYED | MF_DISABLED;
    }
    else
				{
        uEnable = MF_GRAYED | MF_DISABLED;
        uDisable = MF_ENABLED;
    }
    
    m_main_menu.EnableMenuItem( ID_NEW_GAME_MENU, uEnable );
		m_main_menu.EnableMenuItem( ID_DRAW_GAME_MENU, uDisable );
}