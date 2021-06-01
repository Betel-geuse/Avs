#include "ll_cycle.h"
#define NULL 0
bool ll_has_cycle(node* head) {

    node* slow = head, * fast = head;

    while (slow != NULL && fast != NULL && fast->next != NULL) {

        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
            return true;
    }

    return false;
}
