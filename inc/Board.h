// Board.h: interface for the CBoard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOARD_H__3ABEE150_2334_4541_92DD_17CF05C8EB76__INCLUDED_)
#define AFX_BOARD_H__3ABEE150_2334_4541_92DD_17CF05C8EB76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBoard : public CWnd  
{
private:
		CImageList m_iml;//����ͼ��
		int m_color;//�����ɫ
		BOOL m_bWait;//�ȴ���־
		BOOL m_bOldWait;//ԭ�ȴ�״̬

public:
	CBoard();
	virtual ~CBoard();
	void RestoreWait(); //�ָ��ȴ�״̬
	void Clear(BOOL bWait); //�������
	void SetColor(int color);//���õ�ǰ������ɫ
	int GetColor() const;//�õ���ǰ������ɫ
	void SetWait(BOOL bwait);//���õȴ�״̬
	void SetData(int x, int y, int color);//������������
	void DrawGame();//����
	void Draw(int x, int y, int color);//������
	void Receive();//���մ�����
	void Over(int x,int y);//�ж϶Է�ʤ���������
protected:
		afx_msg void OnPaint();
		afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
		DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_BOARD_H__3ABEE150_2334_4541_92DD_17CF05C8EB76__INCLUDED_)
