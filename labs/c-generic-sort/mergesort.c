void merge(void *lineptr[], int left, int middle, int right, int (*comp)(void *, void *)) {

	int subArray1 = middle - left + 1;
	int subArray2 = right - middle;
	
	void *L[subArray1];
	void *R[subArray2];

	for (int i = 0; i < subArray1; i++){
		L[i] = lineptr[left+i];
	}

	for (int i = 0; i < subArray2; i++){
		R[i] = lineptr[middle+1+i];
	}
	
	int i = 0, j = 0, k = left;

	while (i < subArray1 && j < subArray2){
		if ((*comp)(L[i], R[j]) <= 0) {
			lineptr[k] = L[i];
			i++;
		}else{
			lineptr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < subArray1){
		lineptr[k] = L[i];
		i++;
		k++;
	}

	while (j < subArray2){
		lineptr[k] = R[j];
		j++;
		k++;
	}
}

void mergesort(void *lineptr[], int left, int right,
	       int (*comp)(void *, void *)) {

	if(left < right){
		int middle = left + (right - left) / 2;
		mergesort(lineptr, left, middle,comp);
		mergesort(lineptr, middle+1, right,comp);
		merge(lineptr, left, middle, right,comp);
	}
}
