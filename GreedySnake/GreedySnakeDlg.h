
// GreedySnakeDlg.h: 头文件
//

#include "Snake.h"

#pragma once

// CGreedySnakeDlg 对话框
class CGreedySnakeDlg : public CDialogEx
{
// 构造
public:
	CGreedySnakeDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GREEDYSNAKE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStart();
	Snake snake1;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void DrawSnake();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	CPoint Food;	//食物
	CPoint GenerateFood(vector<CPoint>& snakeBody, int maxX, int maxY);
	CPoint GenerateFood(vector<CPoint>& snakeBody1, vector<CPoint>& snakeBody2, int maxX, int maxY);

	int score;	//分数
	int difficult;	//难度
	CEdit m_difficulty;
	CEdit m_score;
	afx_msg void OnPause();
	afx_msg void OnContinue();
	afx_msg void OnAuto();

	bool isAuto;
	afx_msg void OnExit();

	bool isSingle;
	afx_msg void OnSingleMenu();
	afx_msg void OnSingleMenu(CCmdUI* pCmdUI);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnDouble();
	afx_msg void OnDoubleMenu(CCmdUI* pCmdUI);

	Snake snake2;
	int score1;
	int score2;
	CEdit m_score1;
	CEdit m_score2;
};
