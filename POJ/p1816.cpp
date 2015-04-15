#include <stdio.h>
#include <string.h>

#define MAX 100000

inline int max(int a, int b) { return a>b?a:b; }

struct node {
	int next[28];
	int leaf;
	int id;	
};

struct node q[MAX];
int len = 0;

int alloc(){
	memset(&q[len], 0, sizeof(struct node));
	q[len].id = -1;
	len += 1;
	return len-1;
}

void insert(char * str, int id){
	int p = 0;
	for(int i=0;str[i];i++){
		char k;
		if(str[i] == '*'){
			k = 27;
		}else if(str[i] == '?'){
			k = 26;
		}else{
			k = str[i] - 'a';	
		}
		if(q[p].next[k] == 0){
			q[p].next[k] = alloc();
		}
		//q[q[p].next[k]].id = id;
		p = q[p].next[k];
	}
	q[p].id = id;
	q[p].leaf = 1;
}

int find(int p, char * str, int len){
	if(len == 0){
		return -1;	
	}
	char k;
	int result = 0;
	k = str[0] - 'a';
	if(q[p].next[k] != 0){
		result = max(result, find(q[p].next[k], str+1, len-1));
	}
	if(q[p].next[26] != 0){
		result = max(result, find(q[p].next[26], str+1, len-1));
	}
	if(q[p].next[27] != 0){
		for(int i=0;i<len;i++){
			result = max(result, find(q[p].next[27], str+1, len-1));
		}
	}
	return result;
}

void debug(int n){
	if(q[n].leaf) return;
	int i;
	for(i=0;i<28;i++){
		if(q[n].next[i]){
			printf("%c\t%d\n", (i<26)? i+'a':((i==26)?'?':'*'), q[q[n].next[i]].id);
			debug(q[n].next[i]);
		}
	}
}

void solution(int n, int m){
	char str[25];
	int i;
	printf("INSERT:\n");
	for(i=0;i<n;i++){
		scanf("%s", str);
		printf("%s\n", str);
		insert(str, i);
	}
	debug(0);
	printf("\nFIND:\n");
	for(i=0;i<m;i++){
		scanf("%s", str);
		printf("%s\n", str);
		find(0, str, strlen(str));
	}
}

int main(void){
	freopen("p1816.in", "r", stdin);
	int n,m;
	while(scanf("%d %d", &n, &m) != EOF){
		solution(n, m);
	}
	return 0;
}

