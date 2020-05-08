#include "pch.h"
#include "ExpressionProcessor.h"
#include "BigNumberDlg.h"
#include<Windows.h>
void ExpressionProcessor::Solve()
{
	_result = CalcQint();
}
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
		if (CheckValidInput(_expression,_mode,QINT) == false) {
			throw "Invalid input";
			return;
		}
		Solve();
		
	}
	catch (...) {
		AfxMessageBox(_T("Error"), 0, 0);		
		throw "Invalid input";
	}

}
