//32220033 Kangminsu datastructure hw2-2
#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 128

void ArrayMath(float first[], float second[], float last[], int n, int fn) {
    int maxn = (n > fn) ? n : fn;
    // 같은 번호(i)에 있으면 계산하고 아니면 넘어가는 반복문 구상 중
    for(int i = 0; i < maxn; i++){
        last[i] = first[i] + second[i];
    }
    int firstTerm = 1;
    for (int i = maxn - 1; i >= 0; i--) {
        if (last[i] != 0) { 
            if(!firstTerm){
                if (last[i] > 0) printf(" + ");
                else if (last[i] < 0) printf(" - ");
            }
            else{
                if (last[i] < 0) printf("-");
                firstTerm = 0;
            }
            float absVal = (last[i] < 0) ? -last[i] : last[i];

            if (i == 0) printf("%.2f", absVal);
            else if (i == 1) printf("%.2fx", absVal);
            else printf("%.2fx^%d", absVal, i);
            
        }
    }
    printf("\n");
    //여기까지 배열을 활용한 문제해결
}
    //링크드 리스트를 이용한 연산

typedef struct Node {
    float coef;
    int degree;
    struct Node* next;
} Node;

Node* createNode(float coef, int degree) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coef = coef;
    newNode->degree = degree;
    newNode->next = NULL;
    return newNode;
}

void freePoly(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head->next;
        free(head);
        head = temp;
    }
}

void appendNode(Node** head, float coef, int degree) {
    if (coef == 0) return;
    Node* newNode = createNode(coef, degree);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = newNode;
}

Node* addPoly(Node* p1, Node* p2) {
    Node* result = NULL;
    while (p1 != NULL || p2 != NULL) {
        int deg;
        float coef = 0;

        if (p1 != NULL && (p2 == NULL || p1->degree < p2->degree)) {
            deg = p1->degree;
            coef = p1->coef;
            p1 = p1->next;
        } else if (p2 != NULL && (p1 == NULL || p2->degree < p1->degree)) {
            deg = p2->degree;
            coef = p2->coef;
            p2 = p2->next;
        } else {
            deg = p1->degree;
            coef = p1->coef + p2->coef;
            p1 = p1->next;
            p2 = p2->next;
        }
        appendNode(&result, coef, deg);
    }
    return result;
}

void printPolyHelper(Node* head, int* firstTerm) {
    if (head == NULL) return;

    printPolyHelper(head->next, firstTerm);

    if (!(*firstTerm)) {
        if (head->coef > 0) printf(" + ");
        else printf(" - ");
    } else {
        if (head->coef < 0) printf("-");
        *firstTerm = 0;
    }

    float absVal = (head->coef < 0) ? -head->coef : head->coef;
    if (head->degree == 0)      printf("%.2f", absVal);
    else if (head->degree == 1) printf("%.2fx", absVal);
    else                        printf("%.2fx^%d", absVal, head->degree);
}

void printPoly(Node* head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }
    int firstTerm = 1;
    printPolyHelper(head, &firstTerm);
    printf("\n");
}


int main(){
    float first[MAX_LENGTH] ={0};
    float second[MAX_LENGTH] = {0};
    float last[MAX_LENGTH] = {0};
    int n = 0;
    float hereIn = 0.0;
    int AoL; // 배열과 링크드 리스트 선택 
    printf("input size of first multinomial");
    scanf("%d", &n); //배열 크기 설정
    printf("input number (degree order 0 -> ...)");
    for(int i = 0; i < n; i++){ //상수항 부터 올라가는 구조 다음 차수의 항이 없으면 0 입력
        scanf("%f", &hereIn); //음수를 입력하면 알아서 빼고 아니면 더하는 것을 예상 중
        first[i] = hereIn;
    }
    int fn = n;
    n = 0;
    printf("input size of second multinomial");
    scanf("%d", &n); //배열 생성
    
    printf("input number (degree order 0 -> ...)");
    for(int i = 0; i < n; i++){ 
        scanf("%f", &hereIn);
        second[i] = hereIn;
    }

    printf("0 = Array, 1 = linkedList");
    scanf("%d", &AoL);
    if(AoL == 0) ArrayMath(first, second, last, n, fn);
    if(AoL == 1) {
        Node* poly1 = NULL;
        Node* poly2 = NULL;
        for (int i = 0; i < fn; i++) appendNode(&poly1, first[i], i);
        for (int i = 0; i < n; i++) appendNode(&poly2, second[i], i);
        Node* result = addPoly(poly1, poly2);
        printPoly(result);
        freePoly(poly1);
        freePoly(poly2);
        freePoly(result);
    }
    return 0;
}