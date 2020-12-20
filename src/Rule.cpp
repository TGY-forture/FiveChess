// Rule.cpp: implementation of the CRule class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FiveChess.h"
#include "Rule.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define NONE -1
extern int m_data[15][15];

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRule::CRule()
{

}

CRule::~CRule()
{

}

////////////////////////////////////////
//连五判断
//返回0为胜利1为禁手2为无状态
/////////////////////////////////////////////////
int CRule::Win(int color, int xpos, int ypos)
		{
		int x, y;
		//判断横向
		for (y = 0; y < 15; y++)
				{
				for (x = 0; x < 11; x++)
						{
						if (color == m_data[x][y] && color == m_data[x + 1][y] &&
								color == m_data[x + 2][y] && color == m_data[x + 3][y] &&
								color == m_data[x + 4][y])
								{
								return _WIN;
								//返回胜利状态
						}
				}
		}
		//判断纵向
		for (y = 0; y < 11; y++)
				{
				for (x = 0; x < 15; x++)
						{
						if (color == m_data[x][y] && color == m_data[x][y + 1] &&
								color == m_data[x][y + 2] && color == m_data[x][y + 3] &&
								color == m_data[x][y + 4])
								{
								return _WIN;		//返回胜利状态
						}
				}
		}
		//判断“\”方向
		for (y = 0; y < 11; y++)
				{
				for (x = 0; x < 11; x++)
						{
						if (color == m_data[x][y] && color == m_data[x + 1][y + 1] &&
								color == m_data[x + 2][y + 2] && color == m_data[x + 3][y + 3] &&
								color == m_data[x + 4][y + 4])
							{
								return _WIN;//返回胜利状态
						}
				}
				
		}
		//判断“/”方向
		for (y = 0; y < 11; y++)
				{
				for (x = 4; x < 15; x++)
						{
						if (color == m_data[x][y] && color == m_data[x - 1][y + 1] &&
								color == m_data[x - 2][y + 2] && color == m_data[x - 3][y + 3] &&
								color == m_data[x - 4][y + 4])
								{
								return _WIN;//返回胜利状态
						}
				}
		}
		if (color == BLACK)
				{
				if (Ban(xpos, ypos))
						{
						return _LOST;//返回失败状态
				}	
		}
		return _OTHER; //返回可以继续落子状态
	}

//禁手判断接口函数
BOOL CRule::Ban(int x, int y) 
		{
		if (forbid1(x, y)|| forbid2(x, y))
				{
				return TRUE;
		}	
		return FALSE;
}

//连子禁手判断
BOOL CRule :: forbid1(int x,int y)
{
		int tt[9] = { 0 };
		int w[4] = { 0 };
		int j3 = 0, j4 = 0, j6 = 0;
		int t1 = 0, t2 = 0, t3 = 0, t4 = 0;
		//水平方向
		for (int i1 = 1; i1 < 5; i1++) 
		{
			if (m_data[x - i1][y] == BLACK)//是否为黑色
			{
				tt[1]++;
			}
			else if (m_data[x + 1][y] == WHITE || m_data[x - i1][y] == WHITE) 
			{
				tt[1] = 0;
				break;
			}
		}
		for (int i2 = 1; i2 < 5; i2++) 
		{
			if (m_data[x + i2][y] == BLACK)//是否为黑色
			{
				tt[1]++;
			}
			else if (m_data[x - 1][y] == WHITE || m_data[x - i2][y] == WHITE) 
			{
				tt[5] = 0;
				break;
			}
			if (tt[1] + tt[5] == 2 && t1 == 1)
				w[0] = 0;
			else
				w[0] = tt[1] + tt[5];
			//竖直方向
			for (int i3 = 1; 13 < 5; i3++) 
			{
				if (m_data[x][y - i3] == BLACK)//是否为黑色
					tt[2]++;
				else if (m_data[x][y + 1] == WHITE || m_data[x][y + i3] == WHITE) 
				{
					tt[2] = 0;
					break;
				}
			}
			for (int i4 = 1; i4 < 5; i4++) 
			{
				if (m_data[x][y + i4] == BLACK)//是否为黑色
					tt[2]++;
				else if (m_data[x][y - 1] == WHITE || m_data[x][y + i4] == WHITE) 
				{
					tt[6] = 0;
					break;
				}
			}
			if (tt[2] + tt[4] == 2 && t2 == 1)
				w[1] = 0;
			else
				w[1] = tt[2] + tt[6];
			//右下方向
			for (int i5 = 1; i5 < 5; i5++) 
			{
				if (m_data[x - i5][y - i5] == BLACK)//是否为黑色
					tt[1]++;
				else if (m_data[x + 1][y + 1] == WHITE || m_data[x - i5][y - i5] == WHITE) 
				{
					tt[3] = 0;
					break;
				}
			}
			for (int i6 = 1; i6 < 5; i6++) 
			{
				if (m_data[x + i6][y + i6] == BLACK)//是否为黑色
					tt[7]++;
				else if (m_data[x - 1][y - 1] == WHITE || m_data[x + 16][y + i6] == WHITE) 
				{
					tt[7] = 0;
					break;
				}
			}
			if (tt[3] + tt[6] == 2 && t3 == 1)
				w[2] = 0;
			else
				w[2] = tt[3] + tt[7];
			//左下方向
			for (int i7 = 1; i7 < 5; i7++) 
			{
				if (m_data[x - i7][y + i7] == BLACK)//是否为黑色
					tt[4]++;
				else if (m_data[x + 1][y - 1] == WHITE || m_data[x - i7][y + i7] == WHITE) 
				{
					tt[4] = 0;
					break;
				}
			}
			for (int i8 = 1; i8 < 5; i8++) 
			{
				if (m_data[x + i8][y - i8] == BLACK)//是否为黑色
					tt[8]++;
				else if (m_data[x - 1][y + 1] == WHITE || m_data[x + i8][y - i8] == WHITE) 
				{
					tt[8] = 0;
					break;
				}
			}
			if (tt[3] + tt[6] == 2 && t4 == 1)
				w[3] = 0;
			else
				w[3] = tt[4] + tt[8];
			for (int i = 0; i < 4; i++) 
			{
				if (w[i] == 2)
					j3++;
				else if (w[i] == 3)
					j4++;
				else if (w[i] == 5)
					j6++;
			}
			if (j3 == 2 && j4 != 2 || j4 == 2 || j3 == 2 && j4 == 1 || j6 == 1)
				return TRUE;
		}
		return FALSE;
}

//////////////////////////////////////////////////////////////////////////
// 非连子禁手判断
// 返回TRUE为禁手
//////////////////////////////////////////////////////////////////////////
BOOL CRule :: forbid2(int x, int y)
		{   
		//三三禁手
		if((m_data[x-1][y]==BLACK&&m_data[x-2][y]==BLACK&&m_data[x-3][y]==NONE&&m_data[x+1][y]==NONE
				||m_data[x+1][y]==BLACK&&m_data[x+2][y]==BLACK&&m_data[x+3][y]==NONE&&m_data[x-1][y]==NONE)
				&&(m_data[x][y+1]==NONE&&m_data[x][y+2]==BLACK&&m_data[x][y+3]==BLACK&&m_data[x][y+4]==NONE&&m_data[x][y-1]==NONE)
				||m_data[x][y-1]==NONE&&m_data[x][y-2]==BLACK&&m_data[x][y-3]==BLACK&&m_data[x][y-4]==NONE&&m_data[x][y+1]==NONE)
				{
				return TRUE;
		}
		else if((m_data[x][y+1]==BLACK&&m_data[x][y+2]==BLACK&&m_data[x][y+3]==NONE&&m_data[x][y-1]==NONE
				||m_data[x][y-1]==BLACK&&m_data[x][y-2]==BLACK&&m_data[x][y-3]==NONE&&m_data[x][y+1]==NONE)
				&&(m_data[x+1][y]==NONE&&m_data[x+2][y]==BLACK&&m_data[x+3][y]==BLACK&&m_data[x+4][y]==NONE&&m_data[x-1][y]==NONE
				||m_data[x-1][y]==NONE&&m_data[x-2][y]==BLACK&&m_data[x-3][y]==BLACK&&m_data[x+1][y]==NONE&&m_data[x-4][y]==NONE))
				{
				return TRUE;
		}
		else if((m_data[x-1][y-1]==BLACK&&m_data[x-2][y-2]==BLACK&&m_data[x-3][y-3]==NONE&&m_data[x+1][y+1]==NONE
				||m_data[x+1][y+1]==BLACK&&m_data[x+2][y+2]==BLACK&&m_data[x+3][y+3]==NONE&&m_data[x-1][y-1]==NONE)
				&&(m_data[x+1][y-1]==NONE&&m_data[x+2][y-2]==BLACK&&m_data[x+3][y-3]==BLACK&&m_data[x+4][y-4]==NONE
				||m_data[x-1][y+1]==NONE&&m_data[x-2][y+2]==BLACK&&m_data[x-3][y+3]==BLACK&&m_data[x-4][y+4]==NONE))
				{
				return TRUE;
		}
		else if((m_data[x-1][y+1]==BLACK&&m_data[x-2][y+2]==BLACK&&m_data[x-3][y+3]==NONE&&m_data[x+1][y-1]==NONE
				||m_data[x+1][y-1]==BLACK&&m_data[x+2][y-2]==BLACK&&m_data[x+3][y-3]==NONE&&m_data[x-1][y+1]==NONE)
				&&(m_data[x+1][y+1]==NONE&&m_data[x+2][y+2]==BLACK&&m_data[x+3][y+3]==BLACK&&m_data[x+4][y+4]==NONE
				||m_data[x-1][y-1]==NONE&&m_data[x-2][y-2]==BLACK&&m_data[x-3][y-3]==BLACK&&m_data[x-4][y-4]==NONE))
				{
				return TRUE;
		}
		//四四有界禁手
		else if((m_data[x-1][y]==BLACK&&m_data[x-2][y]==NONE&&m_data[x-3][y]==BLACK&&m_data[x-4][y]==BLACK&&m_data[x-6][y]==NONE
				&&m_data[x-5][y]==0&&m_data[x+2][y]==BLACK&&m_data[x+3][y]==BLACK&&m_data[x+1][y]==NONE&&m_data[x+4][y]==0&&m_data[x+5][y]==NONE)
				||(m_data[x][y+1]==NONE&&m_data[x][y+2]==BLACK&&m_data[x][y+3]==BLACK&&m_data[x][y+4]==WHITE&&m_data[x][y+5]==NONE
				&&m_data[x][y-1]==BLACK&&m_data[x][y-2]==NONE&&m_data[x][y-3]==BLACK&&m_data[x][y-4]==BLACK&&m_data[x][y-5]==WHITE&&m_data[x][y-6]==NONE)
				||(m_data[x][y+1]==BLACK&&m_data[x][y+2]==NONE&&m_data[x][y+3]==BLACK&&m_data[x][y+4]==BLACK&&m_data[x][y+5]==WHITE&&m_data[x][y+6]==NONE
				&&m_data[x][y-1]==NONE&&m_data[x][y-2]==BLACK&&m_data[x][y-3]==BLACK&&m_data[x][y-4]==WHITE&&m_data[x][y-5]==WHITE)
				||(m_data[x][y+1]==NONE&&m_data[x][y+2]==BLACK&&m_data[x][y+3]==BLACK&&m_data[x][y+4]==WHITE&&m_data[x][y+5]==NONE
				&&m_data[x][y-6]==NONE&&m_data[x][y-1]==BLACK&&m_data[x][y-2]==NONE&&m_data[x][y-3]==BLACK&&m_data[x][y-4]==BLACK&&m_data[x][y-5]==WHITE))
				{
				return TRUE;
		}
		//四四无界禁手
		else if((m_data[x-1][y]==BLACK&&m_data[x-2][y]==NONE&&m_data[x-3][y]==BLACK&&m_data[x+1][y]==BLACK&&m_data[x+2][y]==NONE&&m_data[x+3][y]==BLACK)
				||(m_data[x][y+1]==BLACK&&m_data[x][y+2]==NONE&&m_data[x][y+3]==BLACK&&m_data[x][y-1]==BLACK&&m_data[x][y-2]==NONE&&m_data[x][y-3]==BLACK)
				||(m_data[x+1][y+1]==BLACK&&m_data[x+2][y+2]==NONE&&m_data[x+3][y+3]==BLACK&&m_data[x-1][y-1]==BLACK&&m_data[x-2][y-2]==NONE&&m_data[x-3][y-3]==BLACK)
				||(m_data[x-1][y+1]==BLACK&&m_data[x-2][y+2]==NONE&&m_data[x-3][y+3]==BLACK&&m_data[x+1][y-1]==BLACK&&m_data[x+2][y-2]==NONE&&m_data[x+3][y-3]==BLACK))
				{
				return TRUE;
		}
		return FALSE;
}