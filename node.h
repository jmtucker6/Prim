#ifndef _NODE_H_
#define _NODE_H_
struct LinkedList;
typedef struct Node {
    void *vertex;
    struct Node *next;
    struct Node *prev;
    struct Node *parent;
    struct LinkedList *children;
} Node;

extern Node *newNode(void *);
extern void setParentofNode(Node *, Node *);
extern void setNextofNode(Node *, Node *);
extern void setPrevofNode(Node *, Node *);
extern void setChildrenofNode(Node *, struct LinkedList *);
#endif
