/*
 * singly linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;
	printf("[----- [황슬비] [2018032027] -----]");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout); //이클립스 입력받을 때 printf문 출력 안되는 문제 해결용
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			fflush(stdout); //이클립스 입력받을 때 printf문 출력 안되는 문제 해결용
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			fflush(stdout); //이클립스 입력받을 때 printf문 출력 안되는 문제 해결용
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			fflush(stdout); //이클립스 입력받을 때 printf문 출력 안되는 문제 해결용
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			fflush(stdout); //이클립스 입력받을 때 printf문 출력 안되는 문제 해결용
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

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //리스트노드 생성
	node->key = key; //key값 추가

	node->link = h->first; //node가 head가리키도록 함
	h->first = node; //head에 node주소 넣음
	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
/*비교연산, 링크따라 옮김 필요*/
	if( h->first==NULL){ //공백리스트인경우
		insertFirst(h,key);
	}
	listNode* node = (listNode*)malloc(sizeof(listNode)); //리스트노드 생성
	listNode* temp = (listNode*)malloc(sizeof(listNode)); //임시노드 생성
	node->key=key;
	temp=h->first;
	if(temp->key>=key){ //비교연산
		node->link=temp;
		h->first=node;
		}
	else{
		while(1){
			if (temp->link ==NULL){ //노드가 한개인 경우
				temp->link=node;
				node->link=NULL;
				break;
			}
			else if (temp->link->key>key){//temp->key <= key < temp->link->key
				node->link=temp->link;
				temp->link=node;
				break;
			}
			else //범위에 해당하지 않으면 temp 한칸 옮김
				temp=temp->link;
		}
	}
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	if(h==NULL){ //전처리검사
		insertFirst(h,key);
	}
	else{
		listNode* node = (listNode*)malloc(sizeof(listNode)); //리스트노드 생성
		listNode* temp = (listNode*)malloc(sizeof(listNode)); //임시노드 생성
		node->key=key;
		node->link=NULL; //node는 마지막 값이므로 link에 NULL을 넣어준다.
		temp=h->first;
			while(temp->link !=NULL){ //temp가 마지막에 위치하도록
				temp=temp->link;
			}
			temp->link=node; //NULL인 링크에 node연결
	}
	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	if(h==NULL){
		printf("Linked List is empty!!!!!");
		return 0;
	}

	listNode* temp = (listNode*)malloc(sizeof(listNode)); //임시노드 생성
	temp=h->first;
	h->first=temp->link;
	free(temp);
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	if(h->first==NULL){
			printf("Linked List is empty!!!!!");
			return 0;
		}
	else{
	listNode* previous = (listNode*)malloc(sizeof(listNode)); //삭제할 노드의 선행노드
	listNode* delete = (listNode*)malloc(sizeof(listNode)); //삭제할 노드
	previous=h->first; //previous->delete 순
	if(previous->key == key){ //첫번 째 노드가 key일 때
		deleteFirst(h);
	}
	while(previous->link !=NULL){ //노드검색
		if(previous->link->key == key){
			delete=previous->link;
			previous->link=previous->link->link;
			free(delete);
		}
		previous=previous->link; //한칸씩 옮김
	}
		if(previous->link==NULL){//key값이 노드에 없는 경우
			printf("Key is not founded in linked list\n");
		}
	}

	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	if(h==NULL){
				printf("Linked List is empty!!!!!");
				return 0;
			}
	listNode* previous = (listNode*)malloc(sizeof(listNode)); //삭제할 노드의 선행노드
	listNode* delete = (listNode*)malloc(sizeof(listNode)); //삭제할 노드
	delete=h->first;
	if(delete->link==NULL){ //리스트에 노드가 하나인 경우
		free(delete);
		h->first = NULL;
		return 0;
	}
	else{ //노드 두개 이상인 경우
		previous = h->first; //선행노드 : 첫번째 노드로 지정
		delete=delete->link; //선행노드 뒤의 노드
		while(delete->link !=NULL){
			previous = delete; //삭제할 노드 한칸씩 옮겨가며 선행노드도 함께 옮겨감
			delete = delete ->link;
		} //삭제할 노드의 링크가 NULL인 경우 (마지막 노드인 경우)
		free(delete); //노드 삭제
		previous->link=NULL; //선행노드의 링크를 NULL로 설정
	}

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */

int invertList(headNode* h) {
	listNode *p, *q, *r;

	p=h;
	q=NULL;
	while(p !=NULL){
		r = q;
		q = p;
		p = p->link;
		q->link = r;
	}
	return q;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

