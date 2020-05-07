
// BigNumberDlg.h : header file
//

#pragma once

#include <string>
#include "Qint.h"
enum  Mode {
	DEC,
	HEX,
	BIN
};
enum TypeInput {
	NUMBER,
	OPERATOR,
	CLOSE_PARENTHESES,
	OPEN_PARENTHESES,
	DOT
};
 enum  TypeNumericMode {
	QINT,
	QFLOAT
};
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
	//DEFINE MEMBER
	CString expression = _T("");
	CString result = _T("");
	Mode exMode = Mode::DEC;
	Mode resultMode = Mode::DEC;
	TypeNumericMode dataTypeMode = TypeNumericMode::QINT;

	void CalculateQFloat();

	//For debug purpose

	void Debug(std::string message) {
		_cwprintf(_T("%s"), ConvertStringToCString(message));
	}
	//D
	template<class T>
	std::string GetSolvedOuputBasedOnResultMode(T rawOutput) {
		if (dataTypeMode == QINT &&typeid(T).name() == "Qint") {

			if (resultMode == Mode::DEC) {
				return rawOutput.ToString();
			}
			else if (resultMode == Mode::BIN) {
				std::string temp = rawOutput.DecToBin(true);
				std::string formatedResult = "";
				for (int i = 0; i < temp.length(); i++) {

					if (i != 0 && i % 81 == 0) {
						formatedResult += "\r\n";
					}
					formatedResult += temp[i];

				}

				return formatedResult;
			}
			else if (resultMode == Mode::HEX) {

				return rawOutput.DecToHex();
			}
			

		}
		else if (dataTypeMode == QFLOAT &&typeid(T).name() == "Qfloat") {
			
			if (resultMode == DEC) {	

				std::stringstream out;
				out << rawOutput;	
				return out.str();

			}
			else if (resultMode == BIN) {
				std::string result = "";
				std::string bits = rawOutput.DecToBin(true);

				for (int i = 0; i < 128; i++) {
					result += bits[i] ? '1' : '0';
				}
				return result;
			}
			
		}
		
	}

	void ShowErrorDialog(std::string message) {

		AfxMessageBox((ConvertStringToCString(message)));

	}
	private:
		CString ConvertStringToCString(std::string input);
		std::string ConvertCStringToString(CString cstring) ;
		
		//Bật tất cả các button ngoại trừ button data type

		void EnableAllButton() {

			BTN_EQUAL.EnableWindow(TRUE);
			BTN_PLUS.EnableWindow(TRUE);;
			BTN_SUBTRACT.EnableWindow(TRUE);;
			BTN_MULTIPLY.EnableWindow(TRUE);;
			BTN_DIVIDE.EnableWindow(TRUE);;
			BTN_DELETE_ONE_CHAR.EnableWindow(TRUE);;
			BTN_CLEAR_ALL.EnableWindow(TRUE);;
			BTN_PERCENT.EnableWindow(TRUE);;
			BTN_9.EnableWindow(TRUE);;
			BTN_6.EnableWindow(TRUE);;
			BTN_3.EnableWindow(TRUE);;
			BTN_DOT.EnableWindow(TRUE);;
			BTN_ZERO.EnableWindow(TRUE);;
			BTN_2.EnableWindow(TRUE);;
			BTN_5.EnableWindow(TRUE);;
			BTN_8.EnableWindow(TRUE);;
			BTN_CLOSE_PARENTHESES.EnableWindow(TRUE);
			BTN_SHIFT_RIGHT.EnableWindow(TRUE);;
			BTN_SHIFT_LEFT.EnableWindow(TRUE);;
			BTN_OPEN_PARETHESES.EnableWindow(TRUE);;
			BTN_7.EnableWindow(TRUE);
			BTN_4.EnableWindow(TRUE);
			BTN_1.EnableWindow(TRUE);
			
			BTN_A.EnableWindow(TRUE);
			BTN_B.EnableWindow(TRUE);
			BTN_D.EnableWindow(TRUE);
			BTN_C.EnableWindow(TRUE);
			BTN_E.EnableWindow(TRUE);
			BTN_F.EnableWindow(TRUE);
		}
		void DisableDecBitOperatorButton() {
			BTN_AND.EnableWindow(0);
			BTN_OR.EnableWindow(0);
			BTN_NOT.EnableWindow(0);
			BTN_ROR.EnableWindow(0);
			BTN_ROL.EnableWindow(0);
			BTN_PLUS.EnableWindow(0);
			BTN_SUBTRACT.EnableWindow(0);
			BTN_MULTIPLY.EnableWindow(0);
			BTN_DIVIDE.EnableWindow(0);
			BTN_PERCENT.EnableWindow(0);
			BTN_SHIFT_LEFT.EnableWindow(0);
			BTN_SHIFT_RIGHT.EnableWindow(0);
		
			BTN_OPEN_PARETHESES.EnableWindow(0);
			BTN_CLOSE_PARENTHESES.EnableWindow(0);
			BTN_XOR.EnableWindow(0);

		}
		void OnHexMode(){
			EnableAllButton();
			DisableDecBitOperatorButton();
			BTN_DOT.EnableWindow(FALSE);

		}
		void OnDecMode() {
			EnableAllButton();
			BTN_A.EnableWindow(FALSE);
			BTN_B.EnableWindow(FALSE);
			BTN_D.EnableWindow(FALSE);
			BTN_C.EnableWindow(FALSE);
			BTN_E.EnableWindow(FALSE);
			BTN_F.EnableWindow(FALSE);
			BTN_DOT.EnableWindow(FALSE);

			
		}
		void OnBinMode() {
			BTN_EQUAL.EnableWindow(TRUE);
			BTN_PLUS.EnableWindow(TRUE);;
			BTN_SUBTRACT.EnableWindow(TRUE);;
			BTN_MULTIPLY.EnableWindow(TRUE);;
			BTN_DIVIDE.EnableWindow(TRUE);;
			BTN_DELETE_ONE_CHAR.EnableWindow(TRUE);;
			BTN_CLEAR_ALL.EnableWindow(TRUE);;
			BTN_PERCENT.EnableWindow(TRUE);;
			BTN_9.EnableWindow(FALSE);;
			BTN_6.EnableWindow(FALSE);;
			BTN_3.EnableWindow(FALSE);;
			BTN_DOT.EnableWindow(FALSE);;
			BTN_ZERO.EnableWindow(TRUE);;
			BTN_2.EnableWindow(FALSE);;
			BTN_5.EnableWindow(FALSE);;
			BTN_8.EnableWindow(FALSE);;
			BTN_CLOSE_PARENTHESES.EnableWindow(TRUE);
			BTN_SHIFT_RIGHT.EnableWindow(TRUE);;
			BTN_SHIFT_LEFT.EnableWindow(TRUE);;
			BTN_OPEN_PARETHESES.EnableWindow(TRUE);;
			BTN_7.EnableWindow(FALSE);
			BTN_4.EnableWindow(FALSE);
			BTN_1.EnableWindow(TRUE);
			BTN_A.EnableWindow(FALSE);
			BTN_B.EnableWindow(FALSE);
			BTN_D.EnableWindow(FALSE);
			BTN_C.EnableWindow(FALSE);
			BTN_E.EnableWindow(FALSE);
			BTN_F.EnableWindow(FALSE);
		}
		void ResetUI() {
			expression = _T("");
			result = _T("");
		}
		void UpdateUI();
		bool CheckValidInput(TypeInput type) {
			int lastIndex = expression.GetLength() - 1;

			if (type ==TypeInput:: NUMBER) {

				if (lastIndex >= 0 && expression.GetAt(lastIndex) == ')') return false;

			}
			else if (type ==TypeInput:: OPERATOR) {
				
				if ((lastIndex >= 1&&expression.GetAt(lastIndex) == '(') || lastIndex == 0) return false;

			}
			else if (type ==TypeInput:: CLOSE_PARENTHESES) {

				int countClose = 0;
				int countOpen = 0;
				for (int i = 0; i < expression.GetLength(); i++) {
					if (expression.GetAt(lastIndex) == '(') countOpen++;
					if (expression.GetAt(lastIndex) == ')') countClose++;
				}

				if (countOpen - countClose != 1) {
					return false;
				}

			}
			else if (type ==TypeInput:: DOT) {
				auto lastChar = expression.GetAt(lastIndex);
				if (lastChar == ')' ||
					lastChar == '>'||
					lastChar == '<' ||
					lastChar == '|'||
					lastChar == '^'||
					lastChar == '~'||
					lastChar == '&') return false;
			}
			return true;
	
		}
		void CalculateQInt();

public:

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
	CButton BTN_A;
	CButton BTN_B;
	CButton BTN_D;
	CButton BTN_C;
	CButton BTN_E;
	CButton BTN_F;
	CEdit EDT_Expression;
	CEdit EDT_Result;
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
	afx_msg void OnBnClickedOpenParentheses();
	
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
	afx_msg void OnBnClickedDecEx();
	CButton BTN_DEC_EX;
	CButton BTN_HEX_EX;
	CButton BTN_BIN_EX;
	afx_msg void OnBnClickedHexEx();
	afx_msg void OnBnClickedBinEx();	
	afx_msg void OnBnClickedDecRadioBtn();
	afx_msg void OnBnClickedBinRadioBtn();
	afx_msg void OnBnClickedHexRadioBtn();
	afx_msg void OnChangeInput();
	afx_msg void OnBnClickedQintMode();
	afx_msg void OnBnClickedQFloatMode();
	CButton BTN_QintMode;
	CButton BTN_QfloatMode;
	CButton BTN_AND;
	CButton BTN_OR;
	CButton BTN_XOR;
	CButton BTN_NOT;
	CButton BTN_ROR;
	CButton BTN_ROL;
	CButton BTN_DEC_RADIO;
	CButton BTN_BIN_RADIO;
	CButton BTN_HEX_RADIO;
};
