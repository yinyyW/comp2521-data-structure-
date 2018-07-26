
/**

Algorithm below for hint, you need to of course implement it in C:


int isHeap(BTree  t){

	if(t==NULL) return 1;

	int l_Heap = isHeap(t->left);
	int r_Heap = isHeap(t->right);
	
	curOK = 1;
	if(t->left != NULL) { 
		if(t->data < t->left->data){
			curOK = 0;
		}
	}

	if(t->right != NULL) { 
		if(t->data < t->right->data){
			curOK = 0;
		}
	}

	if(curOK && l_Heap && r_Heap) {
		return 1;
	}
	else {
		return 0;
	}



**/
