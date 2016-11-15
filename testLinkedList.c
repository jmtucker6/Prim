#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "testLinkedList.h"
#include "linkedlist.h"
#include "node.h"
#include "vertex.h"

static int init_linked_list_suite(void) {
    return 0;
}
static int clean_linked_list_suite(void) {
    return 0;
}
static void create_list(void) {
    LinkedList *list = newLinkedList();
    CU_ASSERT(list -> size == 0);
}

static void insert_node(void) {
    LinkedList *list = newLinkedList();
    Vertex *vertex = newKnownVertex(1, 20);
    Node *node = newNode(vertex);
    insertNode(list, node);
    CU_ASSERT(list -> size == 1);
    CU_ASSERT(list -> head == node);
    vertex = newKnownVertex(2, 10);
    node = newNode(vertex);
    insertNode(list, node);
    CU_ASSERT(list -> size == 2);
}

static void delete_node(void) {
    LinkedList *list = newLinkedList();
    deleteNode(list, list -> head);
    CU_ASSERT_EQUAL(list -> size, 0);

    Vertex *vertex = newKnownVertex(1, 20);
    Node *node = newNode(vertex);
    insertNode(list, node);
    vertex = newKnownVertex(2, 10);
    node = newNode(vertex);
    insertNode(list, node);
    vertex = newKnownVertex(3, 5);
    Node *lastNode = newNode(vertex);
    insertNode(list, lastNode);

    deleteNode(list, list -> head);
    CU_ASSERT_EQUAL(list -> size, 2);
    CU_ASSERT_PTR_EQUAL(list -> head, node);

    deleteNode(list, lastNode);
    CU_ASSERT_EQUAL(list -> size, 1);

}

static void merge_lists(void) {
    LinkedList *leftList = newLinkedList();
    LinkedList *rightList = newLinkedList();
    
    Vertex *vertex = newKnownVertex(1, 20);
    Node *node = newNode(vertex);
    insertNode(leftList, node);
    vertex = newKnownVertex(2, 10);
    insertNode(leftList, newNode(vertex));
    vertex = newKnownVertex(3, 5);
    insertNode(rightList, newNode(vertex));
    vertex = newKnownVertex(4, 7);
    insertNode(rightList, newNode(vertex));

    LinkedList *result = mergeLists(leftList, rightList);
    CU_ASSERT_EQUAL(result -> size, 4);
    CU_ASSERT_PTR_EQUAL(result -> head, leftList -> head);
    Vertex *tailVertex = (Vertex *) result -> head -> prev -> vertex;
    CU_ASSERT_EQUAL(tailVertex -> id, 4);

}

int fillLinkedListSuite(CU_pSuite suite) {
   if ((NULL == CU_add_test(suite, "create_list", create_list)) ||
           (NULL == CU_add_test(suite, "insert_node", insert_node)) ||
           (NULL == CU_add_test(suite, "delete_node", delete_node)) ||
           (NULL == CU_add_test(suite, "mergeLists", merge_lists))) {
       CU_cleanup_registry();
       return -1;
   }
   return 0;
}

