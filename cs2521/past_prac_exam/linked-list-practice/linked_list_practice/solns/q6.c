char* getNextPatient(List L) {
  int best = L->head->p->priority;
  char* name = L->head->p->name;
  Node curr = L->head;
  while(curr != NULL) {
    if(curr->p->priority > best) {
      best = curr->p->priority;
      name = curr->p->name;
    }
    curr = curr->next;
  }
  return name;
}
