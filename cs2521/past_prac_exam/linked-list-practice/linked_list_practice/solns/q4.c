void removeMemes(List L) {
  Node prev = NULL;
  Node curr = L->head;
  while(curr != NULL) {
    if(strcmp(curr->word,"MEMES") == 0) {
      Node next = curr->next;
      freeNode(curr);
      curr = next;
      if(prev != NULL) prev->next = next;
      else L->head = next;
      if(next == NULL) L->tail = prev;
    }else{
      prev = curr;
      curr = curr->next;
    }
  }
}
