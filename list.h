#pragma once

#define STRLEN 512

typedef unsigned char u8;
typedef unsigned int u32;

typedef float timeData;
typedef char *strData;

typedef struct _LrcData{
	timeData time;
	char str[STRLEN];
} LrcData;

typedef struct _ListNode{
	LrcData Data;
	struct _ListNode *next;
} Node;


Node *InitList(Node *node);
Node *InsertList(Node *first, LrcData data);
Node *DeleteNode(Node *, timeData, strData);
void traverselist(Node *first);
int DestroyNode(Node *node);
