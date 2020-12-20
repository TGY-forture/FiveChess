// Board.cpp: implementation of the CBoard class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FiveChess.h"
#include "Board.h"
#include "Resource.h"
//#include "ConnectData.h"
#include "Rule.h"
#include "FiveChessDlg.h "

#define MAX_LEN 256 /*������󳤶�*/

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//��Ϣӳ���
BEGIN_MESSAGE_MAP(CBoard,CWnd)
//{{AFX_MSG_MAP(CBoard)
ON_WM_PAINT()
ON_WM_LBUTTONUP()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

extern int m_data[15][15];

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBoard::CBoard()
{
		//��ʼ��ͼ���б�
		m_iml.Create(24, 24, ILC_COLOR24 | ILC_MASK, 0,2);//����ڡ�����������λͼ
		CBitmap bmpBlack, bmpWhite;
		bmpBlack.LoadBitmap(IDB_BMP_BLACK);
		m_iml.Add(&bmpBlack, 0xff00ff);
		bmpWhite.LoadBitmap(IDB_BMP_WHITE);
		m_iml.Add(&bmpWhite, 0xff00ff);
}

CBoard::~CBoard()
{

}

void CBoard::OnPaint()
{
		CPaintDC dc(this);
		CDC MemDC;
		MemDC.CreateCompatibleDC(&dc);//װ������
		CBitmap bmp;
		CPen pen;
		bmp.LoadBitmap(IDB_BMP_QP); //����ͼƬ
		pen.CreatePen(PS_SOLID, 1, 0xff);
		MemDC.SelectObject(&bmp);//ѡ�����
		MemDC.SelectObject(&pen);
		MemDC.SetROP2(R2_NOTXORPEN); //��������,��ͼƬ�еı���ȥ��
		//�����������ݻ�������
		int x, y;
		POINT pt;
		for (y = 0; y < 15; y++)
				{ 
				for (x = 0; x < 15; x++)
						{
						if (-1 != m_data[x][y])
							{
								pt.x = 12 + 25 * x;
								pt.y = 84 + 25 * y;
								m_iml.Draw(&MemDC, m_data[x][y], pt, ILD_TRANSPARENT);
						}
				}
		}		
		//��ɻ���
		dc.BitBlt(0, 0,395,472,&MemDC, 0, 0, SRCCOPY);
}

void CBoard :: OnLButtonUp(UINT nFlags, CPoint point)
{
		MSGSTRUCT msg;
		CRule rule;
		CFiveChessDlg * pDlg = (CFiveChessDlg*)AfxGetMainWnd();
		BYTE buf[MAX_LEN] = { 0 };
		if (m_bWait)
		{
				MessageBeep(MB_OK);
				return;
		}
		if (pDlg->m_bIsConnect)
		{
				int x, y;
				x = (point.x - 12) / 25;
				y = (point.y-84) / 25;
				//�����(0��0)~(14, 14) ��Χ�ڣ��Ҹ�����û������
				//�������ڴˣ����������沢�˳�����
				if (x < 0 || x>14 || y < 0 || y> 14 || m_data[x][y] != -1)
				{
						MessageBeep(MB_OK);
						return;
				}
				else
				{
						//���λ�úϷ���������
						SetData(x, y, m_color);
						msg.color = m_color;
						msg.x = x;
						msg.y = y;
				}
				//��ʼ�ȴ�
				m_bWait = TRUE;
				msg.msgType = MSG_PUTSTEP;
				pDlg->Send(&msg);
				if (rule.Win(m_color,msg.x, msg.y) == _WIN)
						{//ʤ��
						pDlg->MessageBox(_T("��ϲ�� �������ʤ��! "), _T("ʤ��"), MB_ICONINFORMATION);
						pDlg->SetMenuState(TRUE);
				}
				else if (rule.Win(m_color,msg.x, msg.y) == _LOST)
						{//���ֽ���
						pDlg->MessageBox(_T("ִ�ڽ��֣�������! "),_T("ʧ��"),MB_ICONINFORMATION);
						pDlg->SetMenuState(TRUE);
				}
		}
}

//�������
void CBoard::Clear(BOOL bWait)
{
		int x, y;
		for (y = 0; y < 15; y++) {
				for (x = 0; x < 15; x++) {
						m_data[x][y] = -1;
						m_bWait = bWait;//���õȴ���־
						Invalidate();
				}
		}
}
//���������ɫ
void CBoard::SetColor(int color)
{
		m_color = color;
}

//��ȡ�����ɫ
int CBoard::GetColor() const
{
		return m_color;
}

//���õȴ���־
void CBoard :: SetWait(BOOL bwait)
{
		m_bOldWait=m_bWait;
		m_bWait = bwait;
}

//�����������ݣ�����������
void CBoard::SetData(int x, int y, int color)
{
		m_data[x][y] = color;
		Draw(x, y, color);
}

//�������
void CBoard::DrawGame()
{
		CFiveChessDlg * pDlg = (CFiveChessDlg*)AfxGetMainWnd();  //���õȴ���־
		SetWait(TRUE);
		MSGSTRUCT msg;
		msg.msgType = MSG_DRAW;
		pDlg->m_sock.Send((LPCVOID) &msg, sizeof(MSGSTRUCT));
}

//��ָ���������괦����ָ����ɫ������
void CBoard::Draw(int x, int y, int color)
{
		POINT pt;
		pt.x = 12 + 25 * x;
		pt.y = 84 + 25*y;
		CDC *pDC = GetDC();
		CPen pen;
		pen.CreatePen(PS_SOLID, 1, 0xff);
		pDC->SelectObject(&pen);
		pDC->SetROP2(R2_NOTXORPEN);
		m_iml.Draw(pDC, color, pt, ILD_TRANSPARENT);
		ReleaseDC(pDC);
}

//�������ԶԷ�������
void CBoard::Receive() {
		
		CFiveChessDlg * pDlg = (CFiveChessDlg*)AfxGetMainWnd();
		MSGSTRUCT msg;
		if (pDlg->m_sock.Receive((LPVOID)&msg, sizeof(MSGSTRUCT)) == SOCKET_ERROR)
				{
				AfxGetMainWnd()->MessageBox(_T("��������ʱ�����������������������ӡ�"), _T("����"), MB_ICONSTOP);
				return;
		}
		switch (msg.msgType)
				{
		case MSG_PUTSTEP:
				SetData(msg.x, msg.y, msg.color);
				Over(msg.x, msg.y);
				break;
		case MSG_DRAW:
				if (IDYES == GetParent()->MessageBox(_T("�Է�������壬������������� ? "), _T("����"), MB_ICONQUESTION | MB_YESNO))
						{
						//�������������Ϣ
						MSGSTRUCT msg;
						msg.msgType = MSG_AGREE_DRAW;
						pDlg->m_sock.Send((LPCVOID)&msg, sizeof(MSGSTRUCT));
						SetWait(TRUE);
						//ʹ�����桱�˵���Ч
						pDlg->SetMenuState(TRUE);
				}
				else
						{
						//���;ܾ�������Ϣ
						MSGSTRUCT msg;
						msg.msgType = MSG_REFUSE_DRAW;
						pDlg->m_sock.Send((LPCVOID)&msg, sizeof(MSGSTRUCT));
				}
				break;
		case MSG_AGREE_DRAW:
				pDlg->MessageBox(_T("�������������֣� �Է����������ĺ�������."), _T("����"), MB_ICONINFORMATION);
				//�����ʹ�����桱�˵���Ч
				pDlg->SetMenuState(TRUE);
				break;
		case MSG_REFUSE_DRAW:
				pDlg->MessageBox(_T("�����Է���������ȡ��ʤ�������Ծܾ������ĺ�������."), _T("����"), MB_ICONINFORMATION);
				RestoreWait();
				pDlg->SetMenuState(FALSE);
				break;
		case MSG_EXTERN:
				break;
		default:
				break;
		}
}

//����Է����Ӻ�Ĺ���
void CBoard::Over(int x,int y)
{
		CRule rule;
		CFiveChessDlg *pDlg=(CFiveChessDlg *)GetParent();
		//�ж϶Է��Ƿ�ʤ��
		if (rule.Win(1 - m_color,x,y) == _WIN)
				{
				pDlg->MessageBox(_T("�����ˣ� ������Ҫ���ģ�ʧ���˳ɹ�֮ĸŶ"),_T("ʧ��"),MB_ICONINFORMATION);
				//����������ս������Ч�����桱
				if (pDlg->m_bIsConnect)
						{
						pDlg->SetMenuState(TRUE);
				}
				return;
		}	
		//�ж϶Է��Ƿ���ֽ���
		else if (rule.Win(1 - m_color,x,y) == _LOST)
				{
				pDlg->MessageBox(_T("��ϲ�����Է����ֽ�������! "), _T("ʤ��"), MB_ICONINFORMATION);
				//����������ս������Ч�����桱
				if (pDlg->m_bIsConnect)
						{ 
						pDlg->SetMenuState(TRUE);
				}	
				return;
		}
		m_bWait = FALSE;
}

//����������ǰ�ĵȴ���־
void CBoard::RestoreWait() {
		SetWait(m_bOldWait);
}
