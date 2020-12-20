// SetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FiveChess.h"
#include "SetupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg dialog


CSetupDlg::CSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetupDlg)
	m_net_port = 0;
	//}}AFX_DATA_INIT
}


void CSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetupDlg)
	DDX_Control(pDX, IDC_IP_ADDRESS_EDIT, m_ip_addr);
	DDX_Text(pDX, IDC_NET_PORT_EDIT, m_net_port);
	DDV_MinMaxUInt(pDX, m_net_port, 1, 65530);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetupDlg, CDialog)
	//{{AFX_MSG_MAP(CSetupDlg)
	ON_BN_CLICKED(IDC_HOST_OPTION, OnHostOption)
	ON_BN_CLICKED(IDC_CLIENT_OPTION, OnClientOption)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg message handlers

void CSetupDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CSetupDlg::OnOK() 
{
	// TODO: Add extra validation here
		CString strIP;//定义临时字符串变量
		CString strPort;
		UpdateData(TRUE);//更新显示到变量
		m_ip_addr.GetWindowText(strIP);//得到IP地址编辑框中输入的字符
		strPort.Format("&d", m_net_port); //格式化端口号为字符串
		if(m_isHost)
		{	//判断是否选择 了主机选项
				//把主机的PORT写入配置文件
				WritePrivateProfileString("HOST", "PORT", strPort, ".\\config.ini");
		}
		else
		{	//把客户机的IP和PORT写入配置文件
				WritePrivateProfileString("CLIENT", "IP", strIP, ".\\config.ini");
				WritePrivateProfileString("CLIENT", "PORT", strPort, ".\\config.ini");
		}
		CDialog::OnOK();
}

void CSetupDlg::OnClientOption() 
{
	// TODO: Add your control notification handler code here
		char str[128] = { 0 };
		m_ip_addr.EnableWindow(TRUE);//读配置文件中的客户机IP地址
		GetPrivateProfileString("CLIENT","IP","",str, 127,".\\config.ini");
		m_ip_addr.SetWindowText(str);
		memset(str, 0, 128);
		//读配置文件中的客户机端口号
		GetPrivateProfileString("CLIENT", "PORT", "5000",str, 127, ".\\config.ini");
		m_net_port = atoi(str);
		m_isHost = FALSE; //设置连接类型变量
		UpdateData(FALSE); //把变更数据更新显示
}

void CSetupDlg::OnHostOption() 
		{
		// TODO: Add your control notification handler code here
		char str[128] = {0};
		m_ip_addr.EnableWindow(FALSE); //使IP输入编辑框无效
		GetPrivateProfileString("HOST", "IP", "",str, 127,".\\config.ini");
		m_ip_addr.SetWindowText(str);
		memset(str, 0, 128);
		GetPrivateProfileString("HOST", "PORT", "5000",str, 127, ".\\config.ini");
		m_net_port = atoi(str);
		m_isHost = TRUE;
		UpdateData(FALSE);
}

BOOL CSetupDlg::OnInitDialog()
{
		// 初始化化对话框
		CDialog::OnInitDialog();//设置默认为选中主机选项
		((CButton*)GetDlgItem(IDC_HOST_OPTION))->SetCheck(1);
		OnHostOption();
		return TRUE;//返回真，表示初始化成功
}
