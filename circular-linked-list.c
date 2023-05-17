#include<stdio.h>
#include<stdlib.h>

// Node 구조체 정의
typedef struct Node {
	int key;
	struct Node* llink; // 이전 노드를 가리키는 포인터
	struct Node* rlink; // 다음 노드를 가리키는 포인터
} listNode;

// 함수 프로토타입 선언
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);
int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);
void printList(listNode* h);


int main()
{	
	printf("[----- [Choi Gaeun] [2022078054] -----]\n");

	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		// 명령에 따라 해당 기능 수행
		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // 'q' 또는 'Q'가 입력될 때까지 반복

	return 1;
}

// 리스트 초기화 함수
int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){
	if(h->rlink==h){
		free(h);
		return 0;
	}
	listNode* p = h->rlink;
	listNode* prev = NULL;
	while(p != NULL && p != h){
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);
	return 0;
}

// 리스트 출력 함수
void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n"); // 리스트가 비어있는 경우 출력
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key); // 리스트의 원소 출력
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i); // 리스트의 총 원소 개수 출력


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}


/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	if(h==NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if(h->rlink == h){
		h->rlink = node;
		h->llink = node;
		node->rlink = h;
		node->llink = h;
	}else{
		h->llink->rlink = node;
		node->llink = h->llink;
		h->llink = node;
		node->rlink = h;
	}
	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	if(h->llink == h || h == NULL){
		printf("nothing to delete.\n"); // 리스트가 비어있는 경우 출력
		return 1;
	}
	listNode* remove = h->llink;

	remove->llink->rlink = h;
	h->llink = remove->llink;

	free(remove);

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로운 노드 생성
	node->key = key; //노드의 키에 입력받은 key 저장
	node->rlink = NULL; // 새 노드의 rlink를 NULL로 초기화
	node->llink = NULL; // 새 노드의 llink를 NULL로 초기화
	node->rlink = h->rlink; // 새 노드의 rlink를 헤드 노드의 rlink로 설정
	h->rlink->llink = node; // 헤드 노드의 rlink의 llink를 새 노드로 설정
	node->llink = h; //새 노드의 llink를 헤드 노드로 설정
	h->rlink = node; // 헤드 노드의 rlink를 새 노드로 설정

	return 1;
} 


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
	if (h == NULL || h->rlink == h)	{
		printf("nothing to delete.\n"); // 리스트가 비어있는 경우 출력
		return 0;
	}
	listNode* remove = h->rlink; // 삭제할 노드를 헤드 노드의 rlink로 설정
	remove->rlink->llink = h; // 삭제할 노드의 rlink의 llink를 헤드 노드로 설정
	h->rlink = remove->rlink; // 헤드 노드의 rlink를 삭제할 노드의 rlink로 설정
	free(remove); // 삭제할 노드 해제

	return 1;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
	if(h->rlink == h || h == NULL) {
		printf("nothing to invert...\n"); // 리스트가 비어있는 경우 출력
		return 0;
	}
	listNode *n = h->rlink; // n을 헤드 노드의 rlink로 설정
	listNode *middle = h; // middle을 헤드 노드로 설정
	listNode *trail = h; // trail을 헤드 노드로 설정

	h->llink = h->rlink; // 헤드 노드의 llink를 헤드 노드의 rlink로 설정

	while(n != NULL && n != h){
		trail = middle; 
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}
	h->rlink = middle; // 헤드 노드의 rlink를 middle로 설정

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {
	if(h == NULL) return -1; // 헤드 노드가 NULL이면 -1 리턴

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 새 노드 생성
	node->key = key; // 노드의 키에 입력받은 key 저장
	node->llink = node->rlink = NULL; // 새 노드의 llink와 rlink를 NULL로 초기화

	if (h->rlink == h) { // 헤드 노드의 rlink가 헤드 노드를 가리키면 (리스트가 비어있으면)
		insertFirst(h, key); // 리스트의 처음에 삽입
		return 1;
	}
	listNode* n = h->rlink; // n을 헤드 노드의 rlink로 설정

	while(n != NULL && n != h) { // n이 NULL이 아니고, n이 헤드 노드가 아닐 때 까지
		if(n->key >= key) { // n의 키가 입력받은 key보다 크거나 같으면
			if(n == h->rlink) { // n이 헤드 노드의 rlink면 (리스트의 처음이면)
				insertFirst(h, key); // 리스트의 처음에 삽입
			} else { // 그 외의 경우
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
				n->llink = node;
			}
			return 0;
		}
		n = n->rlink;
	}
	insertLast(h, key); // 리스트의 마지막에 삽입

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	if (h->rlink == h || h == NULL)	{ // 리스트가 비어있으면
		printf("nothing to delete.\n"); // 출력 메시지
		return 0;
	}
	listNode* n = h->rlink; // n을 헤드 노드의 rlink로 설정
	while(n != NULL && n != h) { // n이 NULL이 아니고, n이 헤드 노드가 아닐 때 까지
		if(n->key == key) { // n의 키가 입력받은 key와 같으면
			if(n == h->rlink) { // n이 헤드 노드의 rlink면 (리스트의 처음이면)
				deleteFirst(h); 
			} else if (n->rlink == h){ // n의 rlink가 헤드 노드를 가리키면 (리스트의 마지막이면)
				deleteLast(h);
			} else { // 그 외의 경우
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n); // n 노드 해제
			}
			return 0;
		}
		n = n->rlink;
	}
	printf("cannot find the node for key = %d\n", key);

	return 0;
}