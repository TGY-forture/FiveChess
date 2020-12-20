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
		CImageList m_iml;//棋子图像
		int m_color;//玩家颜色
		BOOL m_bWait;//等待标志
		BOOL m_bOldWait;//原等待状态

public:
	CBoard();
	virtual ~CBoard();
	void RestoreWait(); //恢复等待状态
	void Clear(BOOL bWait); //清空棋盘
	void SetColor(int color);//设置当前棋子颜色
	int GetColor() const;//得到当前棋子颜色
	void SetWait(BOOL bwait);//设置等待状态
	void SetData(int x, int y, int color);//设置棋子数据
	void DrawGame();//和棋
	void Draw(int x, int y, int color);//面棋子
	void Receive();//接收处理函数
	void Over(int x,int y);//判断对方胜负结果函数
protected:
		afx_msg void OnPaint();
		afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
		DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_BOARD_H__3ABEE150_2334_4541_92DD_17CF05C8EB76__INCLUDED_)
