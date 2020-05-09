#include "pch.h"
#include "ExpressionProcessor.h"
#include "BigNumberDlg.h"
#include<Windows.h>
void ExpressionProcessor::Solve()
{
	_result = CalcQint();
}
int ExpressionProcessor::GetPrioritize(std::string c)

{
	const int MAX = 100;
	if ((c == "x++" || c == "x--" || c == "-x")) {
		return MAX;
	}
	else if (c == "++x" || c == "--x" || c == "~") {
		return MAX - 1;
	}
	else if (c == "*" || c == "X" || c == "÷" | c == "/" || c == "%") {
		return MAX - 2;
	}
	else if (c == "+" || c == "-") {
		return MAX - 3;
	}
	else if (c == ">>" || c == "<<" || c == "ror" || c == "rol") {
		return MAX - 4;
	}
	else if (c == "&") {
		return MAX - 5;
	}
	else if (c == "^") {
		return MAX - 6;
	}
	else if (c == "|") {
		return MAX - 7;
	}
	return MAX - 8;
}
bool ExpressionProcessor::IsNumber(char c)

{
	if (c >= '0' && c <= '9')
		return true;
	else
		return false;
}
bool ExpressionProcessor::IsOperator(std::string c)

{
	if (
		c == "rol" ||
		c == "ror" ||
		c == "x++" ||
		c == "x--" ||
		c == "++x" ||
		c == "--x" ||
		c == "~" ||
		c == "X" ||
		c == "*" ||
		c == "÷" ||
		c == "/" ||
		c == "%" ||
		c == "+" ||
		c == "-" ||
		c == ">>" ||
		c == "<<" ||
		c == "&" ||
		c == "^" ||
		c == "-x" ||
		c == "|")
		return true;
	return false;
}
std::queue<std::string> ExpressionProcessor::convertInfixToPostfix()

{
	std::stack<std::string> stackExp;
	std::queue<std::string> queueExp;

	_expression = "(" + _expression;
	_expression = _expression + ")";
	for (int i = 0; i < _expression.length(); i++)
	{
		if (_expression[i] == '(')
		{
			std::string temp(1, _expression[i]);
			stackExp.push(temp);
		}
		else if (_expression[i] == ')')
		{
			while (stackExp.top() != "(")
			{
				queueExp.push(stackExp.top());
				stackExp.pop();
			}
			stackExp.pop();
		}
		else if (IsNumber(_expression[i]))
		{
			std::string numTemp;
			/*	if (i >= 2 && _mode == DEC) {
					auto con1 = _expression[i - 1] == '-';
					auto con2 = _expression[i - 2] == '(';
					std::string temp = "";
					temp+= _expression[i - 2];
					auto con3 = IsOperator(temp);

					if (con1 == true && (con2 == true || con3 == true)) {
						if (stackExp.empty() == false && stackExp.top() == "-") stackExp.pop();
						numTemp += '-';
					}

				}*/

			while (IsNumber(_expression[i]))
			{
				std::string temp(1, _expression[i]);
				numTemp += temp;
				i++;
			}
			i--;
			queueExp.push(numTemp);
		}
		else
		{
			std::string currentOperator = "";
			bool isPostFix = true;
			std::string subStr = _expression.substr(i, std::string::npos);
			if (subStr.length() >= 2 &&
				(
					(subStr[0] == '>' && subStr[1] == '>') ||
					(subStr[0] == '<' && subStr[1] == '<'))
				) {
				currentOperator = subStr.substr(0, 2);
				i++;
			}
			else if (subStr.length() >= 3 &&
				(subStr.substr(0, 3) == "ror" || subStr.substr(0, 3) == "rol")) {
				currentOperator = subStr.substr(0, 3);
				i += 2;
			}

			else
				if (subStr.substr(0, 2) == "++" ||
					subStr.substr(0, 2) == "--") {
					currentOperator = subStr.substr(0, 2);
					if (subStr.length() >= 3) {
						if (IsNumber(subStr[2])) {
							isPostFix = false;
						}
					}
					if (isPostFix == false) {
						//Prefix
						currentOperator = currentOperator + "x";
					}
					else {
						currentOperator = "x" + currentOperator;
					}

					i++;

				}
				else {
					currentOperator = _expression[i];
					if (currentOperator == "-") {

						if (i > 0 & i < _expression.length() - 1
							) {
							std::string current = "";
							current += _expression[i - 1];
							if (
								(IsOperator(current) || current == "(") &&
								(IsNumber(_expression[i + 1]) || _expression[i + 1] == ')')
								)

								currentOperator = "-x";
						}

					}
				}



			while ((stackExp.top() != "(") &&
				(GetPrioritize(stackExp.top()) >= GetPrioritize(currentOperator)))
			{
				queueExp.push(stackExp.top());
				stackExp.pop();
			}



			stackExp.push(currentOperator);



		}
	}
	return queueExp;
}
Qint ExpressionProcessor::SimpleCalc(Qint* a, Qint b, std::string _operator)

{
	if (_operator == "+")
		return b + *a;
	if (_operator == "-")
		return  b - *a;
	//Debug
	if (_operator == "-x")
		return Qint("0") - b;

	if (_operator == "X" || _operator == "*")
		return b * *a;
	if (_operator == "÷" || _operator == "/")
		return b / (*a);
	if (_operator == "^")
		return b ^ *a;
	if (_operator == "~")
		return ~b;
	if (_operator == ">>") {
		return b >> std::stoi(a->ToString());
	}
	if (_operator == "<<") {
		return b << std::stoi(a->ToString());
	}
	if (_operator == "&") {
		return*a & b;
	}
	if (_operator == "|") {
		return *a | b;
	}

	if (_operator == "x++") {
		return b++;
	}
	if (_operator == "x--") {
		return b++;
	}
	if (_operator == "++x") {
		return ++b;
	}
	if (_operator == "--x") {
		return --b;
	}
	if (_operator == "ror") {
		return b.ror(std::stoi(a->ToString()));

	}
	if (_operator == "rol") {
		return b.rol(std::stoi(a->ToString()));
	}

}
void ExpressionProcessor::Print(std::queue<std::string> q)
{
	while (q.empty() == false) {
		Debug(q.front() + "  "); q.pop();
	}
}
std::string ExpressionProcessor::CalcQint()

{
	if (_expression == "") throw "Emty";

	auto expression = convertInfixToPostfix();
	Print(expression);
	if (expression.empty()) throw "Empty queue";

	std::stack<Qint> s;
	std::string temp;
	while (!expression.empty())
	{
		temp = expression.front();
		if (!IsOperator(temp))
		{
			//Là số
			Qint n(temp, _mode == Mode::BIN);
			s.push(n);
			expression.pop();
		}
		else
		{

			if (temp == "~" ||
				temp == "x++" ||
				temp == "x--" ||
				temp == "++x" ||
				temp == "--x" ||
				temp == "-x"
				) {

				Qint b;
				b = s.top();
				s.pop();
				auto result = SimpleCalc(NULL, b, temp);
				s.push(result);
				expression.pop();
			}
			else {
				Qint a;
				Qint b;
				a = s.top();
				s.pop();
				b = s.top();
				s.pop();
				Qint result = SimpleCalc(&a, b, temp);
				s.push(result);
				expression.pop();
			}

		}
	}
	return s.top().ToString();
}
CString ExpressionProcessor::ConvertStringToCString(std::string input)
{
	return CString(input.c_str());
}
void ExpressionProcessor::Debug(std::string message)
{
	_cwprintf(_T("%s"), ConvertStringToCString(message));
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

std::string ExpressionProcessor::GetResult()
{
	return _result;
}

bool ExpressionProcessor::MatchSubExpression(std::string sub, std::string regexPattern)
{
	std::regex pattern(regexPattern);
	std::regex_iterator<std::string::iterator> rit(sub.begin(), sub.end(), pattern);
	std::regex_iterator<std::string::iterator> rend;

	if (rit == rend) {
		return false;
	}
	else {
		return true;
	}
	return false;

}

bool ExpressionProcessor::CheckValidDecExpression(std::string ex, std::string regexPattern)
{

	std::stack<PosParentheses> bucket;


	for (int i = 0; i < ex.length(); i++) {

		if (ex[i] == '(') {
			if (i >= 1 && IsNumber(ex[i - 1])) {
				return false;
			}
			PosParentheses temp;
			temp.begin = i;
			bucket.push(temp);
		}
		else if (ex[i] == ')') {

			if (i <= ex.length() - 2 && IsNumber(ex[i + 1])) {
				return false;
			}
			if (bucket.empty() == true) {
				return false;
			}
			else {
				auto current = bucket.top(); bucket.pop();
				current.end = i;
				auto sub = ex.substr(current.begin, current.end - current.begin + size_t(1));
				if (MatchSubExpression(sub, regexPattern) == false) {
					return false;
				}
				else {



					ex.erase(current.begin, current.end - current.begin + 1);
					ex.insert(current.begin, "0");
					i -= sub.length() - 1;

				}
			}

		}

	}
	return bucket.empty();


}