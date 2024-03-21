#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include "longestLineHelper.h"
#include "stackADT_LL.h"
#include "LinkedList.h"
#include <string.h>

// Function to evaluate a Reverse Polish Notation expression
int evaluateRPN(char* expression) {
    struct Stack *stack = createStack();
    //initializeStack(&stack);

    for (int i = 0; expression[i] != '\0'; i++) {
       if (isdigit((unsigned char)expression[i])) {
            push(stack, expression[i] - '0'); // Convert character to integer
        } else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            if (isEmpty(stack)) {
                printf("Invalid RPN expression. Not enough operands.1\n");
                return -1;
            }

            int operand2 = pop(stack);
            
            if (isEmpty(stack)) {
                printf("Invalid RPN expression. Too many operands.2\n");
                return -1;
            }

            int operand1 = pop(stack);

            switch (expression[i]) {
                case '+':
                    push(stack, operand1 + operand2);
                    break;
                case '-':
                    push(stack, operand1 - operand2);
                    break;
                case '*':
                    push(stack, operand1 * operand2);
                    break;
                case '/':
                    if (operand2 == 0) {
                        printf("Division by zero is not allowed.\n");
                        return -1;
                    }
                    push(stack, operand1 / operand2);
                    break;
                default:
                    printf("Invalid operator: %c\n", expression[i]);
                    return -1;
            }
        }
    }

    if (!isEmpty(stack)) {
        int result = pop(stack);
        if (isEmpty(stack)) {
            return result;
        } else {
            printf("Invalid RPN expression. Not enough operands.3\n");
            return -1;
        }
    } else {
        printf("Invalid RPN expression. Too many operands.4\n");
        return -1;
    }
}

int main() {
    char input[MAXLINE];
    int len;

    while (1) {
        printf("Enter a valid RPN equation to calculate (or type 'exit' to quit): ");
        len = getaline(input, MAXLINE);

        if (strcmp(input, "exit\n") == 0) {
            break;
        }

        int result = evaluateRPN(input);

        if (result != -1) {
            printf("Result of the RPN expression: %d\n", result);
        }
    }

    return 0;
}