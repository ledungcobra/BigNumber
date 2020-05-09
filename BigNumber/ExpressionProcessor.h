#pragma once
#include <string>
#include <stack>
#include <queue>
#include <iostream>
#include "Qint.h"
#include "BigNumberDlg.h"
#include <regex>

struct PosParentheses {
	size_t begin;
	size_t end;
};
class ExpressionProcessor
{
private:
	//Biểu thức đầu vào
	std::string _expression;
	//Biểu thức kết quả
	std::string _result;
	//Chế độ tính toán Bin Dec hoặc HEX
	Mode _mode;
	//Thực hiện tính toán biểu thức
	void Solve();
	//Tính độ ưu tiên các toán tử
	int GetPrioritize(std::string c);
	//Kiểm tra 1 char có phải là số hay không
	static bool IsNumber(char c);
	//Kiểm tra có phải là toán tử không
	bool IsOperator(std::string c);
	//Thực hiện chuyển đổi về dạng post fixx
	std::queue<std::string> convertInfixToPostfix();
	//Thực hiện tính toán phù hợp đựa vào toán tử nhận vào
	Qint SimpleCalc(Qint* a, Qint b, std::string _operator);
	//Hàm hỗ trợ debug ra console
	void Print(std::queue<std::string> q);
	//Thực hiện tính toán biểu thức Qint có thể nhận vào dec hoặc bin
	std::string CalcQint();
public:
	//Chuyển đổi kiểu dữ liệu string phù hợp
	static CString ConvertStringToCString(std::string input);	
	//Hàm thực hiện debug ra console
	static void Debug(std::string message);
	//Constructor nhận vào biểu thức và chế độ tính toán
	ExpressionProcessor(std::string input,Mode mode);
	//Lấy ra kết quả sau khi đã tính toán
	std::string GetResult();
	//Hàm thực hiện khớp chuỗi bằng regex
	static bool MatchSubExpression(std::string sub, std::string regexPattern);
	//Hàm kiểm tra xem biểu thức nhận vào có hợp lệ hay không
	static bool CheckValidDecExpression(std::string ex, std::string regexPattern);
	//Thực hiện chuẩn hóa biểu thức nhận vào và khớp chuỗi theo từ kiểu dữ liệu khác nhau
	static bool CheckValidInput(std::string expression,Mode mode,DataTypeMode typeNumber) {

		expression = "(" + expression + ")";
		std::string pattern;
		if (typeNumber == QINT) {
			if (mode == Mode::DEC) {
				pattern = "^\\(((\\+{2}|\\-{0,2}|~)?\\d+(\\+{2}|\\-{2}|~)?((\\+|\\-|X|\\*|÷|&|\\||\\^|ror|rol|>>|<<|\\/)(?=((\\+{2}|\\-{0,2}|~)?\\d+(\\+{2}|\\-{2}|~)?)))?)+\\)$";

			}
			else if (mode == Mode::BIN) {
				pattern = "^\\((~?[0-1]+((\\+|\\-|X|\\*|÷|&|\\||>>|<<|\\^|\\/|~|ror|rol)(?=~?[0-1]+))?)+\\)$";
			}
			else if (Mode::HEX == mode) {
				pattern = "^\\(([0-9A-Fa-f]+)\\)$";
			}

		}
		else if (typeNumber == QFLOAT) {
			pattern = "^\\((\\-|\\+)?\\d+(\\.\\d+)?\\)$";
		}
		return CheckValidDecExpression(expression, pattern);
		
	

	}
};

