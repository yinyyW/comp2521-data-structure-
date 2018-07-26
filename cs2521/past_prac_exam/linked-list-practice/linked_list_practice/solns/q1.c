void swap(List L, int i) {
  // find the ith node
  Node prev = NULL;
  Node curr = L->head;
  int index = 0;
  while(curr != NULL) {
    if(index == i) {
      break;
    }
    prev = curr;
    curr = curr->next;
    index++;
  }
  if (curr == NULL || curr->next == NULL) {
    // i was invalid or i == end of list
    return;
  }
  Node next = curr->next;
  Node nextNext = next->next;
  // make the i+1th node point to the ith node
  next->next = curr;
  // make the ith node point to the i+2th node
  curr->next = nextNext;
  // make the i-1th node point to the i+1th node
  if(prev != NULL) prev->next = next;
  else L->head = next;
}
