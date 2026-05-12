#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

// 1. 스택 구조체 설계
typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

// 스택 초기화
void initStack(Stack* s) {
    s->top = -1;
}

// 스택이 비어있는지 확인
int isEmpty(Stack* s) {
    return s->top == -1;
}

// 스택이 꽉 찼는지 확인
int isFull(Stack* s) {
    return s->top == MAX_SIZE - 1;
}

// 데이터 삽입 (Push)
void push(Stack* s, int item) {
    if (isFull(s)) {
        printf("스택이 가득 찼습니다.\n");
        return;
    }
    s->data[++(s->top)] = item;
}

// 데이터 추출 (Pop)
int pop(Stack* s) {
    if (isEmpty(s)) {
        return -1; // 에러 값 반환
    }
    return s->data[(s->top)--];
}

// 2. 괄호 매칭 수행 함수
void matchParentheses(const char* expr) {
    Stack s;
    initStack(&s);
    int len = strlen(expr);

    printf("수식: %s\n", expr);
    printf("매칭된 괄호 쌍 (여는 위치, 닫는 위치):\n");

    for (int i = 0; i < len; i++) {
        if (expr[i] == '(') {
            push(&s, i); // 여는 괄호의 인덱스를 스택에 푸시
        } else if (expr[i] == ')') {
            if (isEmpty(&s)) {
                printf("오류: 닫는 괄호에 매칭되는 여는 괄호가 없습니다. (인덱스: %d)\n", i);
                return;
            }
            int start_idx = pop(&s); // 스택에서 여는 괄호의 인덱스를 팝
            printf("Pair: (%d, %d)\n", start_idx, i);
        }
    }

    // 3. 스택의 결과 출력
    printf("스택의 결과: ");
    if (isEmpty(&s)) {
        printf("Empty (모든 괄호가 성공적으로 매칭되었습니다.)\n\n");
    } else {
        printf("Not Empty (여는 괄호가 남아있어 매칭에 실패했습니다.)\n\n");
    }
}

int main() {
    // 주어진 문제의 식
    const char* expr1 = "(((a + b) * c + d - e) / (f + g) - (h + j) * (k - l)) / (m - n)";
    const char* expr2 = "(a - b * c) + d - (e - (f - g) / h) / (i * j) - k";

    printf("=== Problem 4: 식 1번 ===\n");
    matchParentheses(expr1);

    printf("=== Problem 4: 식 2번 ===\n");
    matchParentheses(expr2);

    return 0;
}
