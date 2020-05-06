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
		expression = input;
		if (CheckValidInput() == false) {
			throw "Invalid input";
		}
		_result = calc();
	}
	catch (char* e) {

		AfxMessageBox(_T("Invalid Input"), 0, 0);		
		throw "Invalid input";
	}

}
