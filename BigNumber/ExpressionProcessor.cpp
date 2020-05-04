#include "pch.h"
#include "ExpressionProcessor.h"

ExpressionProcessor::ExpressionProcessor(std::string input)
{
	int countOpenParentheses = 0;
	int countCloseParentheses = 0;
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == '(')  countOpenParentheses++;
		if (input[i] == ')') countCloseParentheses++;
	}
	if (countOpenParentheses - countCloseParentheses == 1) {
		input = input + ")";
	}
	expression = input;
	_result = calc();

}
