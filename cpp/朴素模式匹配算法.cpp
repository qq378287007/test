int Index(const char * S, const char * T, int i=0) {
	int S0 = strlen(S);
	int T0 = strlen(T);
	
	int j;	
	for(j=0; i<S0&&j<T0; i++, j++) {
		if(S[i] != T[j]) {	
         	i = i-j;	
         	j = -1; 
      	}
	}
	
	if(j>=T0) 
		return i-T0;
	else 
		return -1;
}