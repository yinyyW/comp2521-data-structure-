void reverseList(List L) {
  Node curr = L->head;
  Node temp = NULL;
  while(curr != NULL) {
    temp = curr->next;
    curr->next = curr->prev;
    curr->prev = temp;
    curr = temp;
  }
  temp = L->head;
  L->head = L->tail;
  L->tail = temp;
}
