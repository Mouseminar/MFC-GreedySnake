
// GreedySnakeDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "GreedySnake.h"
#include "GreedySnakeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGreedySnakeDlg 对话框



CGreedySnakeDlg::CGreedySnakeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GREEDYSNAKE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGreedySnakeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_difficulty);
	DDX_Control(pDX, IDC_EDIT2, m_score);
	DDX_Control(pDX, IDC_EDIT3, m_score1);
	DDX_Control(pDX, IDC_EDIT4, m_score2);
}

BEGIN_MESSAGE_MAP(CGreedySnakeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_32771, &CGreedySnakeDlg::OnStart)
	ON_WM_TIMER()
	ON_COMMAND(ID_32772, &CGreedySnakeDlg::OnPause)
	ON_COMMAND(ID_32773, &CGreedySnakeDlg::OnContinue)
	ON_COMMAND(ID_32774, &CGreedySnakeDlg::OnAuto)
	ON_COMMAND(ID_32775, &CGreedySnakeDlg::OnExit)
	ON_COMMAND(ID_32776, &CGreedySnakeDlg::OnSingleMenu)
	ON_UPDATE_COMMAND_UI(ID_32776, &CGreedySnakeDlg::OnSingleMenu)
	ON_WM_INITMENUPOPUP()
	ON_COMMAND(ID_32777, &CGreedySnakeDlg::OnDouble)
	ON_UPDATE_COMMAND_UI(ID_32777, &CGreedySnakeDlg::OnDoubleMenu)
END_MESSAGE_MAP()


// CGreedySnakeDlg 消息处理程序

BOOL CGreedySnakeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	CWnd* pWnd;
	pWnd = GetDlgItem(IDC_GAMEAREA);
	pWnd->SetWindowPos(NULL, 0, 0, 800, 800, SWP_NOZORDER | SWP_NOMOVE);    //把编辑控件的大小设为(100,80)

	score = 0;	//分数
	difficult = 1;	//难度

	CString str;
	str.Format(TEXT("%d"), difficult);
	m_difficulty.SetWindowTextW(str);

	str.Format(TEXT("%d"), score);
	m_score.SetWindowTextW(str);

	isAuto = false;
	isSingle = true;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGreedySnakeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGreedySnakeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGreedySnakeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGreedySnakeDlg::OnStart()
{
	// TODO: 在此添加命令处理程序代码
	snake1.Init(8);

	isAuto = false;

	score = 0;	//分数
	difficult = 1;	//难度

	if (isSingle)	//单人模式
	{
		CString str;
		str.Format(TEXT("%d"), difficult);
		m_difficulty.SetWindowTextW(str);

		str.Format(TEXT("%d"), score);
		m_score.SetWindowTextW(str);
	}
	else
	{
		snake2.Init(12);

		score1 = 0;
		score2 = 0;
		CString str;
		str.Format(TEXT("%d"), score1);
		m_score1.SetWindowTextW(str);

		str.Format(TEXT("%d"), score2);
		m_score2.SetWindowTextW(str);
	}


	// 启动ID为1的定时器，定时时间为1秒   
	SetTimer(1, 200, NULL);

	if (isSingle) Food = GenerateFood(snake1.GetBody(), 20, 20);
	else Food = GenerateFood(snake1.GetBody(), snake2.GetBody(), 20, 20);

	DrawSnake();
}


void CGreedySnakeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (isAuto)
	{
		snake1.AutoMoveToFood(Food);
	}

	snake1.Move(Food);

	if(!isSingle) snake2.Move(Food);

	if (snake1.CheckCollision())	//如果发生碰撞
	{
		KillTimer(1);
		if (isSingle) MessageBox(TEXT("游戏结束"), TEXT("提示"));
		else MessageBox(TEXT("游戏结束，玩家2获胜！"), TEXT("提示"));
		return;
	}

	if (!isSingle)
	{
		if (snake2.CheckCollision())	//如果发生碰撞
		{
			KillTimer(1);
			MessageBox(TEXT("游戏结束，玩家1获胜！"), TEXT("提示"));
			return;
		}
	}


	if (snake1.ateFood)	//如果吃到了食物
	{
		if(isSingle) Food = GenerateFood(snake1.GetBody(), 20, 20);
		else Food = GenerateFood(snake1.GetBody(), snake2.GetBody(), 20, 20);

		snake1.ateFood = false;

		if (isSingle) score++;
		else score1++;

		if (score1 > 20)
		{
			KillTimer(1);
			MessageBox(TEXT("游戏结束，玩家1达成20分，获胜！"), TEXT("提示"));
			return;
		}

		if (score % 3 == 0 && isSingle)
		{
			if (difficult < 15)
			{
				difficult++;
				SetTimer(1, 200 - difficult * 10, NULL);
			}
		}

		//显示
		if (isSingle)
		{
			CString str;
			str.Format(TEXT("%d"), difficult);
			m_difficulty.SetWindowTextW(str);

			str.Format(TEXT("%d"), score);
			m_score.SetWindowTextW(str);
		}
		else
		{
			CString str;
			str.Format(TEXT("%d"), score1);
			m_score1.SetWindowTextW(str);

			str.Format(TEXT("%d"), score2);
			m_score2.SetWindowTextW(str);
		}
	}

	if (!isSingle && snake2.ateFood)
	{
		Food = GenerateFood(snake1.GetBody(), snake2.GetBody(), 20, 20);
		snake2.ateFood = false;

		score2++;
		if (score2 > 20)
		{
			KillTimer(1);
			MessageBox(TEXT("游戏结束，玩家2达成20分，获胜！"), TEXT("提示"));
			return;
		}

		CString str;
		str.Format(TEXT("%d"), score1);
		m_score1.SetWindowTextW(str);

		str.Format(TEXT("%d"), score2);
		m_score2.SetWindowTextW(str);
	}

	DrawSnake();

	CDialogEx::OnTimer(nIDEvent);
}

void CGreedySnakeDlg::DrawSnake()
{
	CWnd* pWnd = GetDlgItem(IDC_GAMEAREA);
	pWnd->Invalidate(); // 标记控件为无效
	pWnd->UpdateWindow(); // 强制刷新控件
	CDC* pDC = pWnd->GetDC();

	snake1.Draw(pDC, RGB(0, 255, 0));
	snake2.Draw(pDC, RGB(0, 0, 255));

	CBrush brush(RGB(255, 0, 0)); // 使用红色画刷绘制食物
	int left = Food.x * BodySize; // 食物的大小为BodySize*BodySize，计算绘制位置
	int top = Food.y * BodySize;
	int right = left + BodySize;
	int bottom = top + BodySize;
	pDC->SelectObject(&brush);
	pDC->Rectangle(left, top, right, bottom); // 绘制食物

	ReleaseDC(pDC);
}


BOOL CGreedySnakeDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN) 
	{
		switch (pMsg->wParam) {
		case VK_UP:
			snake1.SetDirection(Direction::UP);
			break;
		case VK_DOWN:
			snake1.SetDirection(Direction::DOWN);
			break;
		case VK_LEFT:
			snake1.SetDirection(Direction::LEFT);
			break;
		case VK_RIGHT:
			snake1.SetDirection(Direction::RIGHT);
			break;
		case 65:	//A 左
			snake2.SetDirection(Direction::LEFT);
			break;
		case 68:	//D 右
			snake2.SetDirection(Direction::RIGHT);
			break;
		case 87:	//W 上
			snake2.SetDirection(Direction::UP);
			break;
		case 83:	//S 下
			snake2.SetDirection(Direction::DOWN);
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

CPoint CGreedySnakeDlg::GenerateFood(vector<CPoint>& snakeBody, int maxX, int maxY)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> xDist(0, maxX - 1); // 食物的 x 坐标范围
	uniform_int_distribution<int> yDist(0, maxY - 1); // 食物的 y 坐标范围

	int foodX, foodY;
	do {
		// 随机生成食物坐标
		foodX = xDist(gen);
		foodY = yDist(gen);
		// 检查生成的食物是否在蛇的身体上，如果是，重新生成
	} while (any_of(snakeBody.begin(), snakeBody.end(), [&](const CPoint& p) {
		return p.x == foodX && p.y == foodY;
		}));

	return CPoint(foodX, foodY);
}

CPoint CGreedySnakeDlg::GenerateFood(vector<CPoint>& snakeBody1, vector<CPoint>& snakeBody2, int maxX, int maxY)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> xDist(0, maxX - 1); // 食物的 x 坐标范围
	uniform_int_distribution<int> yDist(0, maxY - 1); // 食物的 y 坐标范围

	int foodX, foodY;
	do {
		// 随机生成食物坐标
		foodX = xDist(gen);
		foodY = yDist(gen);
		// 检查生成的食物是否在蛇的身体上，如果是，重新生成
	} while (any_of(snakeBody1.begin(), snakeBody1.end(), [&](const CPoint& p) {
		return p.x == foodX && p.y == foodY;
		}) || any_of(snakeBody2.begin(), snakeBody2.end(), [&](const CPoint& p) {
			return p.x == foodX && p.y == foodY;
			})
		);

	return CPoint(foodX, foodY);
}



void CGreedySnakeDlg::OnPause()
{
	// TODO: 在此添加命令处理程序代码
	KillTimer(1);
}


void CGreedySnakeDlg::OnContinue()
{
	// TODO: 在此添加命令处理程序代码
	SetTimer(1, 200 - difficult * 10, NULL);
}


void CGreedySnakeDlg::OnAuto()
{
	// TODO: 在此添加命令处理程序代码
	isAuto = true;
}


void CGreedySnakeDlg::OnExit()
{
	// TODO: 在此添加命令处理程序代码
	exit(0);
}


void CGreedySnakeDlg::OnSingleMenu()
{
	// TODO: 在此添加命令处理程序代码
	isSingle = true;
}


void CGreedySnakeDlg::OnSingleMenu(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(isSingle);
}


void CGreedySnakeDlg::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	CDialogEx::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	// TODO: Add your message handler code here
	if (!bSysMenu && pPopupMenu)
	{
		CCmdUI cmdUI;
		cmdUI.m_pOther = NULL;
		cmdUI.m_pMenu = pPopupMenu;
		cmdUI.m_pSubMenu = NULL;

		UINT count = pPopupMenu->GetMenuItemCount();
		cmdUI.m_nIndexMax = count;
		for (UINT i = 0; i < count; i++)
		{
			UINT nID = pPopupMenu->GetMenuItemID(i);
			if (-1 == nID || 0 == nID)
			{
				continue;
			}
			cmdUI.m_nID = nID;
			cmdUI.m_nIndex = i;
			cmdUI.DoUpdate(this, FALSE);
		}
	}
}


void CGreedySnakeDlg::OnDouble()
{
	// TODO: 在此添加命令处理程序代码
	isSingle = false;
}


void CGreedySnakeDlg::OnDoubleMenu(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(!isSingle);
}
