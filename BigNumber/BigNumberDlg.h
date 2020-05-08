
// BigNumberDlg.h : header file
//

#pragma once

#include <string>
#include "Qint.h"
#include "Qfloat.h"
#include <sstream>
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
 enum  DataTypeMode {
	QINT,
	QFLOAT
};
 struct CacheResult {
	 std::string* decResult;
	 std::string* binResult;
	 std::string* hexResult;
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
	DataTypeMode dataTypeMode = DataTypeMode::QINT;
	bool expressionChanged = false;
	CacheResult* cache = NULL;
	void CalculateQFloat();

	//For debug purpose

	void Debug(std::string message) {
		_cwprintf(_T("%s"), ConvertStringToCString(message));
	}
	//D
	bool CheckHasDesiredResult() {
		if (resultMode == DEC) {
			if (cache != NULL) {
				return cache->decResult != NULL;
			}
			else {
				return false;
			}
		}
		else if (resultMode == HEX) {
			if (cache != NULL) {
				return cache->hexResult != NULL;
			}
			else {
				return false;
			}
		}
		else if (resultMode == BIN) {
			if (cache != NULL) {
				return cache->binResult != NULL;
			}
			else {
				return false;
			}
		}
	}
	std::string GetSolvedOuputBasedOnResultMode(Qint rawOutput) {
		
		if (expressionChanged) {
			FreeCache();
		}
		auto flag = CheckHasDesiredResult();

		if (flag == false) {

			if (cache == NULL) {
				cache = new CacheResult;
				cache->binResult = new std::string;
				cache->decResult = new std::string;
				cache->hexResult = new std::string;
				cache->binResult = NULL;
				cache->decResult = NULL;
				cache->hexResult = NULL;
			}

			if (dataTypeMode == QINT) {

				if (resultMode == Mode::DEC) {
					std::string* temp = new std::string;
					*temp = rawOutput.ToString();
					cache->decResult = temp;
					return *temp;
				}
				else if (resultMode == Mode::BIN) {
					std::string* temp = new std::string;
					*temp = rawOutput.DecToBin(true);
					std::string formatedResult = "";
					for (int i = 0; i < temp->length(); i++) {

						if (i != 0 && i % 81 == 0) {
							formatedResult += "\r\n";
						}
						formatedResult += temp->at(i);

					}
					*temp = formatedResult;
					cache->binResult = temp;
  					return *temp;
					return formatedResult;
				}
				else if (resultMode == Mode::HEX) {
					std::string* temp = new std::string;
					*temp = rawOutput.DecToHex();
					cache->hexResult = temp;
					return *temp;
				}


			}	

		}
		else {
		
			if (resultMode == HEX){

				return *(cache->hexResult);

			}
			else if (resultMode == DEC) {

				return *(cache->decResult);

			}
			else if (resultMode == BIN) {

				return *(cache->binResult);

			}
			
			

		}
	
		
	}
	std::string GetSolvedOuputBasedOnResultMode(Qfloat rawOutput) {


		
		if (expressionChanged) {
			FreeCache();
		}
		auto flag = CheckHasDesiredResult();

		if (flag == false) {

			if (cache == NULL) {
				cache = new CacheResult;
				cache->binResult = new std::string;
				cache->decResult = new std::string;
				cache->hexResult = new std::string;
				cache->binResult = NULL;
				cache->decResult = NULL;
				cache->hexResult = NULL;
			}


			if (resultMode == DEC) {
				std::string* temp = new std::string;
				std::stringstream out;
				out << rawOutput;
				*temp = out.str();
				if (temp->length() > 82) {
					(*temp).insert(81, "\r\n");
				}
				
				cache->decResult = temp;
				return *temp;

			}
			else if (resultMode == BIN) {
				std::string *result = new std::string;
				bool* bits = rawOutput.DecToBin(rawOutput);

				for (int i = 0; i < 128; i++) {
					*result += bits[i] ? '1' : '0';
				}
				(*result).insert(81, "\r\n");
				cache->binResult = result;
				return *result;
			}

		}
		else {
		
			if (resultMode == DEC) {

				return *(cache->decResult);

			}
			else if (resultMode == BIN) {

				return *(cache->binResult);

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
		void FreeCache() {
			if (cache) {
				if (cache->hexResult) {
					delete(cache->hexResult);
					cache->hexResult = NULL;
				}
				else if (cache->decResult) {
					delete(cache->decResult);
					cache->decResult = NULL;
				}
				else if (cache->binResult) {
					delete(cache->binResult);
					cache->binResult = NULL;
				}
				delete(cache);
				cache = NULL;
			}
		}
		void UpdateUI();
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
	void OnOK();
	
};
