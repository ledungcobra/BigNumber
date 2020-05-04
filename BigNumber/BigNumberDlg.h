
// BigNumberDlg.h : header file
//

#pragma once

#include <string>
// CBigNumberDlg dialog
class CBigNumberDlg : public CDialogEx
{
// Construction
public:
	CBigNumberDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BIGNUMBER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CString expression = _T("");
	CString result = _T("");


	public:
		CString ConvertStringToCString(std::string input);
public:
	afx_msg void OnBnClickedResultDec();
	CButton BTN_EQUAL;
	CButton BTN_PLUS;
	CButton BTN_SUBTRACT;
	CButton BTN_MULTIPLY;
	CButton BTN_DIVIDE;
	CButton BTN_DELETE_ONE_CHAR;
	CButton BTN_CLEAR_ALL;
	CButton BTN_PERCENT;
	CButton BTN_9;
	CButton BTN_6;
	CButton BTN_3;
	CButton BTN_DOT;
	CButton BTN_ZERO;
	CButton BTN_2;
	CButton BTN_5;
	CButton BTN_8;
	CButton BTN_CLOSE_PARENTHESES;
	CButton BTN_SHIFT_RIGHT;
	CButton BTN_SHIFT_LEFT;
	CButton BTN_OPEN_PARETHESES;
	CButton BTN_7;
	CButton BTN_4;
	CButton BTN_1;
	CButton BTN_POS_OR_NEGATIVE;
	CButton BTN_A;
	CButton BTN_B;
	CButton BTN_D;
	CButton BTN_C;
	CButton BTN_E;
	CButton BTN_F;

	CEdit EDT_Expression;
	CEdit EDT_RESULT;
	afx_msg void OnBnClickedEqual();
	afx_msg void OnBnClicked1();
	afx_msg void OnBnClicked2();
	afx_msg void OnBnClicked3();
	afx_msg void OnBnClicked4();
	afx_msg void OnBnClicked5();
	afx_msg void OnBnClicked6();
	afx_msg void OnBnClicked7();
	afx_msg void OnBnClicked8();
	afx_msg void OnBnClicked9();
	afx_msg void OnBnClicked0();
	afx_msg void OnBnClickedDot();
	afx_msg void OnBnClickedPlus();
	afx_msg void OnBnClickedSubtract();
	afx_msg void OnBnClickedMultiply();
	afx_msg void OnBnClickedDivide();
	afx_msg void OnBnClickedClearOneChar();
	afx_msg void OnBnClickedClearAll();
	afx_msg void OnBnClickedShiftRight();
	afx_msg void OnBnClickedShiftLeft();
	afx_msg void OnBnClickedCloseParentheses();
	afx_msg void OnBnClickedCloseParetheses();
	afx_msg void OnBnClickedPosOrNegative();
	afx_msg void OnBnClickedF();
	afx_msg void OnBnClickedE();
	afx_msg void OnBnClickedD();
	afx_msg void OnBnClickedC();
	afx_msg void OnBnClickedB();
	afx_msg void OnBnClickedA();
	afx_msg void OnBnClickedAND();
	afx_msg void OnBnClickedOR();
	afx_msg void OnBnClickedXOR();
	afx_msg void OnBnClickedNOT();
	afx_msg void OnBnClickedROR();
	afx_msg void OnBnClickedROL();
	afx_msg void OnBnClickedPercent();
};
