#include "pch.h"
#include "ExpressionProcessor.h"
#include "BigNumberDlg.h"
#include<Windows.h>
ExpressionProcessor::ExpressionProcessor(std::string input,Mode mode)
{
	_mode = mode;
	int countOpenParentheses = 0;
	int countCloseParentheses = 0;
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == '(')  countOpenParentheses++;
		if (input[i] == ')') countCloseParentheses++;
	}
	if (countOpenParentheses - countCloseParentheses == 1) {
		input = input + ")";
	}
	try {
		_expression = input;
		if (CheckValidInput(_expression,_mode) == false) {
			throw "Invalid input";
			return;
		}
		_result = calcQint();
	}
	catch (...) {
		AfxMessageBox(_T("Invalid Input"), 0, 0);		
		throw "Invalid input";
	}

}
