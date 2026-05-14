##보고서 초안
##p1
연산자 우선순위를 반영하는 산술식을 이진트리로 만드는 프로그램을 작성하였다.

입력받은 Infix 수식을 분석하여 연산자는 부모 노드, 피연산자는 자식 노드가 되도록 트리를 구성하였다.

이진트리는 `TreeNode` 구조체와 `BinaryTree` 클래스를 이용하여 표현하였다.

![tree](./img/img1.png)

`BinaryTree` 클래스에는 Infix, Prefix, Postfix 순회 함수가 구현되어 있다.

Infix 출력에서는 연산자 노드에 괄호를 붙여 계산 순서가 유지되도록 하였다.

![traversal](./img/img2.png)

Level order 출력은 queue를 이용하여 루트부터 같은 깊이의 노드를 차례대로 방문하도록 구현하였다.

![level](./img/img3.png)

수식 파싱은 `ExpressionParser` 클래스에서 처리하였다.

`+`, `-`는 expression 단계에서 처리하고, `*`, `/`는 term 단계에서 처리하여 연산자 우선순위가 반영되도록 하였다.

괄호가 나오면 괄호 안의 수식을 먼저 파싱하여 우선순위를 바꾸도록 구현하였다.

![parser](./img/img4.png)

피연산자는 문자, 숫자, `_`, `.`을 포함할 수 있도록 처리하였다.

잘못된 피연산자나 닫는 괄호가 없는 경우에는 예외를 발생시킨다.

![operand](./img/img5.png)

실행 흐름

사용자가 산술식을 입력한다.

`ExpressionParser`가 입력 문자열을 분석하여 이진트리의 root 노드를 만든다.

생성된 root를 `BinaryTree` 객체에 넣고 Infix order 결과를 출력한다.

![main](./img/img6.png)

실행 예시

```
입력: ((a+b)*c-d)/(e+f)
출력: ((((a+b)*c)-d)/(e+f))
```

위 결과처럼 입력된 산술식이 이진트리로 구성된 뒤 Infix order로 다시 출력되는 것을 확인할 수 있다.

현재 코드에는 Prefix, Postfix, Level order 출력 함수도 구현되어 있으므로 `main.cpp`에서 해당 함수들을 추가로 호출하면 네 가지 방문 결과를 모두 확인할 수 있다.

개선점

현재 파서는 `+`, `-`, `*`, `/`, 괄호 중심의 기본 산술식을 처리한다.

추후 거듭제곱 연산자나 단항 음수까지 처리하도록 확장할 수 있다.

또한 과제 조건을 더 잘 만족하려면 5개 이상의 산술식을 테스트하고, Infix, Prefix, Postfix, Level order 결과를 모두 출력하도록 main 함수를 확장할 수 있다.




##p2

허프만 코딩(Huffman Coding) 알고리즘을 구현하여 텍스트를 압축하고 복원하는 프로그램을 작성하였다.

입력 파일(paragraph.txt)을 읽어 각 문자의 빈도수를 계산한 뒤, 빈도수가 낮은 문자부터 결합하여 허프만 트리를 구성하였다.

허프만 트리는 Node와 Tree 클래스를 이용하여 표현하였다.

![nodeclass](./P2/img/nodeClass.png)
![treeclass](./P2/img/treeClass.png)


Tree 클래스는 빈도 배열을 기반으로 트리를 생성하고, 각 문자에 대한 허프만 코드를 추출하는 기능을 제공한다.

Huffman 클래스는 텍스트 인코딩, 디코딩, 단어별 코드 정보 계산, 전체 압축 비율 계산을 담당한다.
![huffmanclass](./P2/img/huffmanClass.png)

실행 흐름

main.cpp에서 paragraph.txt를 읽는다.

Huffman::makeHuffmanCode()가 빈도수를 계산하고 트리를 생성한다.
![hufcodemake](./P2/img/makehufcode.png)
Huffman::encode()가 입력 텍스트를 허프만 코드로 변환한다.
![hufencode](./P2/img/hufencode.png)
Huffman::decode()가 허프만 코드 비트를 다시 원문으로 복원한다.
![hufdecode](./P2/img/hufdecode.png)
선택된 단어 5개에 대해 허프만 코드와 ASCII 코드 길이를 비교한다.

전체 텍스트의 허프만 인코딩 길이와 ASCII 길이를 비교하여 압축 비율을 출력한다.
![hufresult](./P2/img/hufresult.png)
위 결과처럼 허프만 인코딩은 ASCII 대비 적은 비트를 사용하며, 디코딩 결과가 원문과 동일함을 확인할 수 있다.