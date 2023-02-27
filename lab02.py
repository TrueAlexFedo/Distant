import re

#зададим несколько функций для определения, цифра или символ
def is_number(str):
    try:
        int(str)
        return True
    except ValueError:
        return False


def is_symb(str):
    return re.match("\w+", str) # любая буква 1 или более

#проверить следующий элемент
def peek(stack):
    return stack[-1] if stack else None

#вычисление чисел справа и слева от знака, в зависимости от знака
def apply_operator(operators, values):
    operator = operators.pop()
    right = values.pop()
    left = values.pop()
    if operator == '/' and right == 0:
        print("Division by zero occured")
    else:
        values.append(eval("{0}{1}{2}".format(left, operator, right)))

#проверка на приоритет операций
def greater_precedence(op1, op2):
    precedences = {'+': 0, '-': 0, '*': 1, '/': 1}
    return precedences[op1] > precedences[op2]
#проверка на скобки
def check(expression):
    s = expression
    stack = []
    is_true = True
    for i in s:
        if i == '(':
            stack.append(i)
        elif i == ')':
            if not stack:
                is_true = False
                break
            open_bracket = stack.pop()
            if open_bracket == '(' and i == ')':
                continue
            is_true = False
            break


    return is_true

#проверка деления на ноль
def check2(expression):
    s = expression
    stack = []
    is_true = True
    for i, j in enumerate(s):
        if j == '/' and s[i+1] == '0':

            is_true = False
            break


    return is_true

#проходим через строку и добавляем знаки и числа сортируем их на два массива, проводим вычисления
def evaluate(expression):
    if "=" in expression:
        expression.replace("=", "")
    tokens = re.findall("[+/*()-]|\d+", expression)
    values = []
    operators = []
    for token in tokens:
        if is_number(token):
            values.append(int(token))
        elif token == '(':
            operators.append(token)

        elif token == ')':
            top = peek(operators)
            while top is not None and top != '(':
                apply_operator(operators, values)
                top = peek(operators)
            operators.pop()  # избавиться от (
        else:
            # оператор
            top = peek(operators)
            while top is not None and top not in "()" and greater_precedence(top, token):
                apply_operator(operators, values)
                top = peek(operators)
            operators.append(token)
    while peek(operators) is not None:
        apply_operator(operators, values)

    return values[0]

expression = '2+2+(2-4)+10+(150/(10*5))='

if check(expression) and check2(expression):
    print(evaluate(expression))
else:
    print("Incorrect expression")
