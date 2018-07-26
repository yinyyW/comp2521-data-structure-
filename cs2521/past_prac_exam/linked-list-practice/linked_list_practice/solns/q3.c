Node getIth(List L, int i) {
  int count = 0;
  Node curr = L->head;
  while(curr != NULL){
    if(count == i) break;
    count++;
    curr = curr->next;
  }
  return curr;
}

void insertAtI(List L, int v, int i) {
  // lets find the node before where
  // we want to insert
  i--;
  Node new = makeNode(v);

  // insert at head case
  if(i == -1) {
    new->next = L->head;
    L->head = new;
    return;
  }

  // find
  Node curr = getIth(L,i);

  // insert
  Node temp = curr->next;
  curr->next = new;
  new->next = temp;

  // insert at tail case
  if(temp == NULL) L->tail = new;
}
