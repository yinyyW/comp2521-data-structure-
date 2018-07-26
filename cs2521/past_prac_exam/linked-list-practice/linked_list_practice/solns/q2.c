List getEven(List L) {

  List evenList = newList();
  Node curr = L->head;
  Node prev = NULL;
  while(curr != NULL) {
    // if even
    if(curr->value % 2 == 0) {
      // remove the node
      if(prev == NULL) L->head = curr->next;
      else prev->next = curr->next;
      Node tmp = curr->next;
      curr->next = NULL;
      // add it to the even list
      addNode(evenList,curr);
      // update curr (prev is still correct)
      curr = tmp;
    } else {
      // else progress
      prev = curr;
      curr = curr->next;
    }
  }
  return evenList;
}
