#include <algorithm>
#include<stdio.h>
#include <stdlib.h>
#include<malloc.h>
#include<string.h>
#include <string>
#include <iostream>
#include <time.h>
using namespace std;
enum class TH { AB, AC, BB, EA, EB, EC, EE, CC };
#define SIDE 100
typedef struct Node_array
{
	char state[SIDE];
	struct Node_array* parent;
	int depth;
	TH buoc;
	struct Node_array* nextNode;
	int value;
} Node;
int lenghtInput;
int lenghtInput2;
int complete;
struct NodeList {
	unsigned int nodeCount;
	Node* head;
	Node* tail;
};
int heuristic(Node* node);
int heuristic2(Node* node);
void Copy(char a[], char b[])
{
	int len = strlen(b);
	a[len] = '\0';
	for (int i = 0; i < len; i++)
		a[i] = b[i];
}
int is_equal(char a[])
{
	int flag = 0;
	if (strcmp(a, "E") == 0)
		flag = 1;
	return flag;
}
void reverseList(Node*& n)
{
	if (n == NULL)
		return;

	Node* current = NULL;
	Node* previous = NULL;

	while (n != NULL) {
		current = n;
		n = n->parent;
		current->parent = previous;
		previous = current;
	}
	n = current;
}
void BuocDi(Node* node)
{
	if (node->buoc == TH::AC)
	{
		printf("(AC --> E)");
	}
	else if (node->buoc == TH::AB)
	{
		printf("(AB --> BC)");
	}
	else if (node->buoc == TH::BB)
	{
		printf("(BB --> E)");
	}
	else if (node->buoc == TH::EA)
	{
		printf("(EA --> A)");
	}
	else if (node->buoc == TH::EB)
	{
		printf("(EB --> B)");
	}
	else if (node->buoc == TH::EC)
	{
		printf("(EC --> C)");
	}
	else if (node->buoc == TH::EE)
	{
		printf("(EE --> E)");
	}
}
void Solution(Node* node) {
	reverseList(node);
	printf("-------------------------------------");
	printf("\nLoi Giai: ");
	printf("%s", node->state);
	node = node->parent;
	while (node->state != NULL)
	{
		printf("-->%s", node->state);
		BuocDi(node);
		node = node->parent;
	}
	//puts(node->state);

}
Node* Child_node(Node* node, int x)
{
	Node* child = (Node*)malloc(sizeof(Node));
	int len = strlen(node->state);
	//printf("%d", len);
	Copy(child->state, node->state);
	int i = x;
	int j = i + 1;
	child->parent = node;
	if (child->state[i] == 'A' && child->state[j] == 'B')
	{
		child->state[i] = 'B';
		child->state[j] = 'C';
		child->buoc = TH::AB;
	}
	else if (child->state[i] == 'A' && child->state[j] == 'C')
	{
		child->state[i] = 'E';
		for (int h = j; h < len - 1; h++)
		{
			child->state[h] = child->state[h + 1];
		}
		child->state[len - 1] = '\0';
		child->buoc = TH::AC;
	}
	else if (child->state[i] == 'B' && child->state[j] == 'B')
	{
		child->state[i] = 'E';
		for (int h = j; h < len - 1; h++)
		{
			child->state[h] = child->state[h + 1];
		}
		child->state[len - 1] = '\0';
		child->buoc = TH::BB;
	}
	else if (child->state[i] == 'E' && child->state[j] == 'A')
	{
		child->state[i] = 'A';
		for (int h = j; h < len - 1; h++)
		{
			child->state[h] = child->state[h + 1];
		}
		child->state[len - 1] = '\0';
		child->buoc = TH::EA;
	}
	else   if (child->state[i] == 'E' && child->state[j] == 'B')
	{
		child->state[i] = 'B';
		for (int h = j; h < len - 1; h++)
		{
			child->state[h] = child->state[h + 1];
		}
		child->state[len - 1] = '\0';
		child->buoc = TH::EB;
	}
	else if (child->state[i] == 'E' && child->state[j] == 'C')
	{
		child->state[i] = 'C';
		for (int h = j; h < len - 1; h++)
		{
			child->state[h] = child->state[h + 1];
		}
		child->state[len - 1] = '\0';
		child->buoc = TH::EC;
	}
	else if (child->state[i] == 'E' && child->state[j] == 'E')
	{
		child->state[i] = 'E';
		for (int h = j; h < len - 1; h++)
		{
			child->state[h] = child->state[h + 1];
		}
		child->state[len - 1] = '\0';
		child->buoc = TH::EE;
	}
	return child;
}
Node* Heu_Child_node(Node* node, int x)
{
	Node* child = (Node*)malloc(sizeof(Node));
	int len = strlen(node->state);
	//printf("%d", len);
	Copy(child->state, node->state);
	int i = x;
	int j = i + 1;
	child->parent = node;
	if (child->state[i] == 'A' && child->state[j] == 'B')
	{
		child->state[i] = 'B';
		child->state[j] = 'C';
		child->buoc = TH::AB;
	}
	else if (child->state[i] == 'A' && child->state[j] == 'C')
	{
		child->state[i] = 'E';
		for (int h = j; h < len - 1; h++)
		{
			child->state[h] = child->state[h + 1];
		}
		child->state[len - 1] = '\0';
		child->buoc = TH::AC;
	}
	else if (child->state[i] == 'B' && child->state[j] == 'B')
	{
		child->state[i] = 'E';
		for (int h = j; h < len - 1; h++)
		{
			child->state[h] = child->state[h + 1];
		}
		child->state[len - 1] = '\0';
		child->buoc = TH::BB;
	}
	else if (child->state[i] == 'E' && child->state[j] == 'A')
	{
		child->state[i] = 'A';
		for (int h = j; h < len - 1; h++)
		{
			child->state[h] = child->state[h + 1];
		}
		child->state[len - 1] = '\0';
		child->buoc = TH::EA;
	}
	else   if (child->state[i] == 'E' && child->state[j] == 'B')
	{
		child->state[i] = 'B';
		for (int h = j; h < len - 1; h++)
		{
			child->state[h] = child->state[h + 1];
		}
		child->state[len - 1] = '\0';
		child->buoc = TH::EB;
	}
	else if (child->state[i] == 'E' && child->state[j] == 'C')
	{
		child->state[i] = 'C';
		for (int h = j; h < len - 1; h++)
		{
			child->state[h] = child->state[h + 1];
		}
		child->state[len - 1] = '\0';
		child->buoc = TH::EC;
	}
	else if (child->state[i] == 'E' && child->state[j] == 'E')
	{
		child->state[i] = 'E';
		for (int h = j; h < len - 1; h++)
		{
			child->state[h] = child->state[h + 1];
		}
		child->state[len - 1] = '\0';
		child->buoc = TH::EE;
	}
	child->value = heuristic(child) + heuristic2(child);
	return child;
}
int heuristic(Node* node)
{
	if (node->buoc == TH::EA || node->buoc == TH::EB || node->buoc == TH::EC || node->buoc == TH::EE)
		return 3;
	else if (node->buoc == TH::AC)
		return 2;
	else if (node->buoc == TH::BB)
		return 1;
	else
		return 0;
}
int heuristic2(Node* node)
{
	return lenghtInput - strlen(node->state);
}
NodeList* FIFO_initial()
{
	NodeList* list;
	list = (NodeList*)malloc(sizeof(NodeList));
	list->nodeCount = 0;
	list->head = NULL;
	list->tail = NULL;
	return list;
}
void FIFO_add(NodeList* list, Node* node) {
	if (list->nodeCount <= 0) {
		list->head = node;
		list->tail = node;
		list->nodeCount += 1;
		return;
	}

	list->tail->nextNode = node;


	list->tail = node;
	list->nodeCount += 1;
}
Node* FIFO_pop(NodeList* list) {
	if (list->nodeCount <= 0) {
		return NULL;
	}
	Node* temp = list->head;
	list->nodeCount -= 1;
	if (list->nodeCount <= 0) {
		list->head = NULL;
		list->tail = NULL;
	}
	else {
		list->head = temp->nextNode;
	}
	return temp;
}
void LIFO_add(NodeList* list, Node* node)
{
	if (list->nodeCount <= 0)
	{
		list->head = node;
		list->tail = node;
		list->nodeCount += 1;
		return;
	}
	node->nextNode = list->head;
	list->head = node;
	list->nodeCount += 1;
}
Node* LIFO_pop(NodeList* list)
{
	if (list->nodeCount <= 0)
	{
		return NULL;
	}
	Node* temp = list->head;
	if (list->nodeCount <= 0)
	{
		list->head = NULL;
		list->tail = NULL;
	}
	else
	{
		list->head = temp->nextNode;
	}
	list->nodeCount -= 1;
	return temp;
}
Node* MAXVALUE_pop(NodeList* list)
{
	Node* temp = list->head;
	if (list->nodeCount == 1)
	{

		list->head = NULL;
		list->tail = NULL;
		return temp;
	}
	Node* MAX = temp;
	for (temp; temp != NULL; temp = temp->nextNode)
	{
		if (temp->value > MAX->value)
		{
			MAX = temp;
		}
	}
	if (list->head == MAX)
	{
		list->head = list->head->nextNode;
	}
	else
	{
		for (temp = list->head; temp != NULL; temp = temp->nextNode)
		{
			if (temp == MAX)
			{
				temp->nextNode = MAX->nextNode;
				break;
			}
		}
	}
	list->nodeCount--;
	return MAX;
}
bool Goal_test(Node* node)
{
	return is_equal(node->state);
}
bool checkExist(NodeList* list, Node* node) {
	Node* _node;
	int i = 0;
	_node = list->head;
	while (i < list->nodeCount)
	{
		if (strcmp(node->state, _node->state) == 0)
		{
			return true;
		}
		_node = _node->nextNode;
		i++;
	}
	return false;
}
bool Heu_checkExist(NodeList* list, Node* node) {
	Node* _node;
	_node = list->head;
	while (_node != NULL)
	{
		if (strcmp(node->state, _node->state) == 0)
		{
			return true;
		}
		_node = _node->nextNode;
	}
	return false;
}
void Heuristic(Node* root)
{
	Node* node = root;
	if (Goal_test(node)) {
		return;
	}
	int count = 0;
	NodeList* frontier;
	NodeList* explorer;
	frontier = FIFO_initial();
	explorer = FIFO_initial();
	node->nextNode = NULL;
	LIFO_add(frontier, node);
	do {
		node = (MAXVALUE_pop(frontier));
		if (node == NULL)
		{
			break;
		}
		Node* nNode = new Node();
		nNode->buoc = node->buoc;
		nNode->parent = node->parent;
		nNode->nextNode = NULL;
		nNode->value = node->value;
		strcpy_s(nNode->state, node->state);
		LIFO_add(explorer, nNode);
		for (int i = 0; i < strlen(node->state) - 1; i++)
		{
			Node* child = (Heu_Child_node(node, i));
			if (Heu_checkExist(explorer, child) == false && Heu_checkExist(frontier, child) == false)
			{
				child->depth = node->depth + 1;
				if (Goal_test(child))
				{
					Solution(child);
					complete++;
					printf("\nCount = %d\n", count);
					return;
				}
				count++;
				Node* nNode = new Node();
				nNode = (Node*)malloc(sizeof(Node));
				nNode->buoc = child->buoc;
				nNode->parent = child->parent;
				nNode->nextNode = NULL;
				nNode->value = child->value;
				strcpy_s(nNode->state, child->state);
				LIFO_add(frontier, nNode);
			}
		}
	} while (frontier->nodeCount > 0);
	printf("Khong co loi giai\n");
}
void DFS(Node* root)
{
	Node* node = root;
	if (Goal_test(node)) {
		return;
	}
	int count = 0;
	NodeList* frontier;
	NodeList* explorer;
	frontier = FIFO_initial();
	explorer = FIFO_initial();
	LIFO_add(frontier, node);
	do {
		node = (LIFO_pop(frontier));
		LIFO_add(explorer, node);
		for (int i = 0; i < strlen(node->state) - 1; i++)
		{
			Node* child = (Child_node(node, i));
			if (checkExist(explorer, child) == false || checkExist(frontier, child) == false)
			{
				child->depth = node->depth + 1;
				if (Goal_test(child))
				{
					Solution(child);
					complete++;
					printf("\nCount = %d\n", count);
					return;
				}
				count++;
				if (child->depth < strlen(root->state) - 1)
				{
					LIFO_add(frontier, child);
				}
				//printf("%d ", count);
				/*if (count == 1000000)
				{
					printf("Khong co loi giai");
					return;
				}*/
			}
		}
	} while (frontier->nodeCount > 0);
	printf("Khong co loi giai\n");
}
int main()
{
	int i;
	int m;
	printf("Nhap Do Dai Chuoi:");
	scanf_s("%d", &i);
	printf("Nhap So Chuoi:");
	scanf_s("%d", &m);
	int temp = m;
	srand(0);
	clock_t start, end;
	double timeused;
	start = clock();
	while (m != 0)
	{

		Node* ChuoiE;
		ChuoiE = (Node*)malloc(sizeof(Node));
		lenghtInput = strlen(ChuoiE->state);
		//_strupr_s(ChuoiE->state);
		for (int j = 0; j < i; j++)
		{
		go:
			int ran = rand() % 4 + 1;
			{
				if (ran == 1)
				{
					ChuoiE->state[j] = 'A';
				}
				else if (ran == 2)
				{
					ChuoiE->state[j] = 'B';
				}
				else if (ran == 3)
				{
					ChuoiE->state[j] = 'C';
				}
				else
				{
					ChuoiE->state[j] = 'E';
				}
			}
		}
		ChuoiE->state[i] = '\0';
		int n = strlen(ChuoiE->state);
		ChuoiE->parent = NULL;
		ChuoiE->depth = 0;
		puts(ChuoiE->state);
		Heuristic(ChuoiE);
		m--;
	}
	end = clock();
	timeused = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("So Lan Hoan Thanh:%d/%d voi chuoi %d ky tu voi thoi gian %.3f", complete, temp, i, timeused);
}