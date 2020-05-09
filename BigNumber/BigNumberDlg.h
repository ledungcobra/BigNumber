
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

 enum  DataTypeMode {
	QINT,
	QFLOAT
};
 //Cache data để không phải thực hiện tính toán lại

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
	//Biểu thức nhận vào input của người dùng
	CString expression = _T("");
	//Biểu thức chứa kết quả sau khi tính toán
	CString result = _T("");
	//Chế độ nhập vào của biểu thức
	Mode expressionMode = Mode::DEC;
	//Chế độ lấy ra kết quả
	Mode resultMode = Mode::DEC;
	//Kiểu dữ liệu đang thao tác
	DataTypeMode dataTypeMode = DataTypeMode::QINT;
	//Kiểm soát việc biểu thức bị thay đổi giá trị
	bool expressionChanged = false;
	//Lưu lại dữ liệu đã tính toán trước đó
	CacheResult* cache = NULL;
	//Thực hiện tính toán với kiểu dữ liệu Qfloat
	void CalculateQFloat();
	//Hàm dùng với mục đích debug ra console
	void Debug(std::string message) {
		_cwprintf(_T("%s"), ConvertStringToCString(message));
	}
	//Kiểm tra xem đã có kết quả ở dữ liệu cache chưa 
	//Dùng cho mục đích nếu chưa có kết quả thì thực hiện tính toán
	//đảm bảo không lãng phí tài nguyên
	bool CheckHasDesiredResult();
	//Lấy ra kết quả output dựa vào chế độ của kết quả 
	std::string GetSolvedOuputBasedOnResultMode(Qint rawOutput);
	//Lấy ra kết quả output dựa vào chế độ của kết quả 
	std::string GetSolvedOuputBasedOnResultMode(Qfloat rawOutput);
	//Hiện thị hộp thoại lỗi
	void ShowErrorDialog(std::string message);
	private:
		//Chuyển đổi String phù hợp với môi trường đang thao tác
		CString ConvertStringToCString(std::string input);
		std::string ConvertCStringToString(CString cstring);
		
		//Bật tất cả các button ngoại trừ button data type
		void EnableAllButton();
		//Tắt các toán tử liên quan tới dec và bit
		void DisableDecBitOperatorButton();
		//Thay đổi UI theo Hex mode
		void OnHexMode();
		//Thay đôi UI theo DecMode
		void OnDecMode();
		//Thay đổi UI theo BinMode
		void OnBinMode();
		//Khôi phục lại UI
		void ResetUI();		
		//Giải phóng vùng nhớ cache khi biểu thức nhập vào thay đổi hoặc người dùng nhấn clear
		void FreeCache();
		//Cập nhật UI khi có dữ liệu nhập vào
		void UpdateUI();
		//Thực hiện tính toán theo kiểu dữ liệu Qint
		void CalculateQInt();

public:
	//Các button quản lí UI
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
	CButton BTN_DEC_EX;
	CButton BTN_HEX_EX;
	CButton BTN_BIN_EX;
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
	//Các hàm chức năng của các button khi nhận thao tác click
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
	afx_msg void OnBnClickedHexEx();
	afx_msg void OnBnClickedBinEx();	
	afx_msg void OnBnClickedDecRadioBtn();
	afx_msg void OnBnClickedBinRadioBtn();
	afx_msg void OnBnClickedHexRadioBtn();
	afx_msg void OnChangeInput();
	afx_msg void OnBnClickedQintMode();
	afx_msg void OnBnClickedQFloatMode();

	//Khi người dùng nhấn Enter thì thực hiện tính toán biểu thức
	void OnOK();
	
};
