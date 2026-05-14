# 보고서 초안

## Problem 1
주어진 다항식 `f(x) = 6.7x^4 + 3.2x^3 - x^2 + x - 2`를 계산하고 그래프, 근, 최소값을 출력하는 프로그램을 작성하였다.

다항식 계산은 `f()` 함수로 분리하였고, 최소값을 구하기 위해 도함수 `df()` 함수도 작성하였다.

![function](./img/img1.png)

`f(x) = 0`을 만족하는 값을 찾기 위해 이분법을 사용하였다.

구간을 절반씩 줄여가며 근을 찾는 방식이다.

![bisection](./img/img2.png)

`findRoots()`는 `[-10, 10]` 구간을 작은 간격으로 나누어 부호가 바뀌는 지점을 찾고, 해당 구간에 이분법을 적용한다.

![findroots](./img/img3.png)

최소값은 구간의 양 끝점과 `f'(x)=0`이 되는 지점의 함수값을 비교하여 구하였다.

![minimum](./img/img4.png)

그래프는 `drawGraph()` 함수를 통해 ASCII 형태로 출력하였다.

`[-10, 10]` 전체 구간에서는 함수값이 크게 증가하므로 근 주변을 보기 위해 y 범위는 `[-10, 30]`으로 제한하였다.

![graph](./img/img5.png)

실행 흐름 - 그래프 출력 - 근 탐색- 최소값 탐색 - 결과 출력 
순서로 실행된다.

![main](./img/img6.png)

실행 결과

```
x =  -1.03289583, f(x) =    -0.00000000
x =   0.62119004, f(x) =    -0.00000000
Minimum on [-10, 10]: x = -0.59119710, f(x) = -2.78346016
```

근은 약 `-1.03289583`, `0.62119004`이고, 최소값은 `x = -0.59119710`에서 약 `-2.78346016`이다.

현재 방식은 부호 변화가 없는 중근을 찾기 어렵기 때문에 Newton-Raphson 방법 등을 추가하면 개선할 수 있다.

## Problem 2
배열로 계산하는 부분과 Linked List로 계산하는 부분을 나누어서 계산하는 프로그램을 작성하였음

배열은 ArrayMath()함수를 통해 연산함
![last = first + second](./P2/img/img6.png)


first와 second의 같은 차수 항을 더해 last에 저장함

![arraym](./P2/img/img5.png)

이후 높은 차수 항부터 출력함

Linked List는 Node 구조체를 비롯한 여러가지 함수를 통해 계산

appendNode()로 항을 리스트에 추가.
![append](./P2/img/img7.png)
addPoly()에서 두 리스트를 병합하며 같은 차수 항은 계수를 합산.
![addpol](./P2/img/img8.png)
printPoly()는 재귀적으로 역순 출력하여 다항식 형태로 표시.
![prinpol](./P2/img/img9.png)
freePoly()로 메모리 해제.
![freepol](./P2/img/img10.png)

실행 흐름

첫 번째 다항식 크기와 각 항 계수 입력.

두 번째 다항식 크기와 각 항 계수 입력.

계산방식 선택

0 → 배열 방식 계산 및 출력

1 → 링크드 리스트 방식 계산 및 출력

결과 다항식 출력 후 종료.
![resultm](./P2/img/img11.png)

## Problem 3

원형 큐를 구현하기 전 어떤 메서드가 필요할지 고민하였다.

Queue의 핵심 기능인 enqueue, dequeue가 필요할 것이고 가장 앞에 있는 값을 읽을 front가 필요할 것이다.
그리고 Queue의 상태를 확인하기 위해 empty, full, size, capacity 메서드도 필요할 것이다.
마지막으로 Queue의 생성자와 소멸자, clear 메서드까지 있다면 충분히 쓸만한 큐가 될 것이다.

![CircularQueuePrivateVariable](img/img1.png)

원형 큐를 구성하기 위한 최소한의 맴버 변수를 사용하였다.

![CircularQueueConstructor](img/img2.png)

full 상태일 때 배열의 1칸이 비기 때문에 Queue 크기를 _capacity에 맞추기 위해 _capacity+1 크기의 배열을 _data에 선언하였다.

![CircularQueueFunction](img/img3.png)

_data 배열의 크기가 _capacity+1 이기 때문에 모듈러 연산에 _capacity+1을 사용하였다.

queuetest.cpp 코드를 작성해 _capacity가 20인 Queue에 20개 알파멧으로 enqueue, dequeue 테스트를 수행하여 정상 동작함을 확인하였다.

## Problem 4

먼저 빈 스택을 하나 만들고, 입력받은 수식 문자열(expr)의 전체 길이를 계산합니다. 
<img width="197" height="69" alt="스크린샷 2026-05-07 오전 8 50 17" src="https://github.com/user-attachments/assets/ec9a9a79-4981-4a85-b31a-e7176b11022a" />

문자가 여는 괄호라면, 현재 위치하는 인덱스 번호 i를 스택에 저장(Push)합니다.
<img width="348" height="46" alt="스크린샷 2026-05-07 오전 8 50 47" src="https://github.com/user-attachments/assets/db2865b4-f552-4937-a575-51589a214a2b" />

닫는 괄호를 만나면 스택에서 값을 빼내어(Pop) 짝을 맞춥니다.

예외 처리: 만약 값을 빼내려고 했는데 스택이 비어있다면(isEmpty), 여는 괄호보다 닫는 괄호가 먼저 나왔거나 더 많다는 뜻이므로 오류를 출력하고 함수를 종료합니다.

정상 처리: 스택이 비어있지 않다면 가장 위에 있는 값(가장 최근에 저장된 여는 괄호의 인덱스)을 뽑아냅니다. 뽑아낸 인덱스(start_idx)와 현재 닫는 괄호의 인덱스(i)가 올바른 한 쌍이 됩니다.

<img width="531" height="142" alt="스크린샷 2026-05-07 오전 8 51 09" src="https://github.com/user-attachments/assets/45856354-a4f2-44c6-a777-1cb5ca31abbd" />

<img width="683" height="368" alt="스크린샷 2026-05-13 오후 1 28 22" src="https://github.com/user-attachments/assets/ef8956de-30fc-480f-b1d0-34792da16d7c" />

## Problem 5

`((1+2)*(3-4))/5` 형태의 Infix 수식을 `12+34-*5/` 형태의 Postfix로 변환해야 한다.

수식은 `0~9`의 피연산자와 `+-*/`의 연산자 `()`의 괄호로 이루어져 있다.

변환을 위해 String의 각 index의 요소를 하나의 token으로 다루었다.

토큰의 연산자, 피연산자 구분을 위해 isOperand 함수와 isOperator 함수를 구성하였다.

또한 연산자의 우선순위를 파악하기 위해 precedence 함수를 구성하여 `+-`의 경우 1을 `*/`의 경우 2를 반환하도록 구성하였다.

![infixToPostfix](img/img4.png)

infix String의 각 index를 순회하며 각 index의 값을 ch에 저장한다.

ch가 피연산자일 경우 postfix에 값을 추가한다.

ch가 `(`일 경우 stack에 push한다.

ch가 `)`일 경우 `(`가 나오기 전까지의 연산자를 stack에서 pop하여 순서대로 postfix에 추가한다.

ch가 연산자일 경우 ch보다 우선순위가 낮은 연산자 또는 `(`가 나오기 전까지 stack 에서 연산자를 꺼내 postfix에 추가한 뒤 ch를 stack에 추가한다.

String 을 모두 순회하면 stack에 남은 연산자를 순서대로 꺼내어 postfix에 추가한다.

```
1+2 -> 12+
1+2*3 -> 123*+
(1+2)*3 -> 12+3*
1*(2+3)-4/5 -> 123+*45/-
((1+2)*(3-4))/5 -> 12+34-*5/
```

위와 같은 테스트 결과를 얻을 수 있었다.

위 버전은 하나의 문자를 토큰으로 다루기 대문에 2자리 수 이상의 숫자를 처리할 수 없다.
이 문제를 해결하기 위해 2글자 이상을 하나의 토큰으로 다루도록 코드를 수정할 수 있다.
