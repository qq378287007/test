int Sequential_Search(const int *a, int n, int key) {
	for(int i=0; i<n; i++)
		if(a[i]==key)
			return i;
	return -1;
}

int Sequential_Search2(int *a, int n, int key) {
	a[0]=key;
	int i=n-1;
	while(a[i]!=key)
		i--;
	return i;
}