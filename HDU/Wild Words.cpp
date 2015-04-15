#include<cstdio>
#include<string.h>
#include<malloc.h>
using namespace std;
struct trie{
	trie* next[26];
	int count;
};
trie *thead;

inline trie* newnode(){
	int i;
	trie *t;
	t = (trie*)malloc(sizeof(trie));
	memset(t,0,sizeof(trie));
	return t;
}
/*void insert(trie *s,char x[]){
	int i;
	trie *t;
	for(i=0;x[i];i++){
		if(s->next[x[i]-'a']){
			s = s->next[x[i]-'a'];	
			s->count ++;
		}
		else{
			//t = newnode();
			s->next[x[i]-'a'] = newnode();
			s->count
			s = t;
		}
	}
}*/

void insert(trie *s,char x[]){
	int i;
	for(i=0;x[i]!=0;i++){
		//printf("%c", x[i]);
		int k = x[i] - 'a';
		if(s->next[k] == NULL){
			s->next[k] = newnode();
		}
		(s->next[k])->count += 1;
		s = s->next[k];
	}
}

void debug(trie * s){
	if(!s) return;
	
	for(int i=0;i<26;i++){
		if(s->next[i]){
			printf("%c\t%d\n", i+'a', s->next[i]->count);
			debug(s->next[i]);
		}
	}
}

void deltrie(trie *s){
	int i;
	for(i=0;i<26;i++){
		if(s->next[i]){
			deltrie(s->next[i]);
		}
	}
	free(s);
	s=NULL;
}

/*int find(trie *s,char x[]){
	int i;
	if(x[0] == 0) return -1;
	int res = 0;
	for(i=0;x[i];i++){
		if(s->next[x[i]-'a']){
			res = s->count;
			s = s->next[x[i]-'a'];
		}
		else return -1;
	}
	return res;
}*/

int find(trie *s,char x[]){
	int i, k;
	if(x[0] == 0) return 0;
	int res = 0;
	for(i=0;x[i];i++){
		k = x[i]-'a';
		if(s->next[k]){
			res = s->next[k]->count;
			s = s->next[k];
		}else{
			return 0;	
		}
	}
	return res;
}

int main(){
	freopen("trie.txt","r",stdin);
	int n,m;
	char word[100];
	thead = newnode(); 
	while(fgets(word,100,stdin)!=NULL&&word[0]!='\n'){
		word[strlen(word)-1] = 0;
		//printf("%s\n",word);
		insert(thead,word);
	}
	//debug(thead);
	while(scanf("%s",word)!=EOF){
		int t = find(thead,word);
		printf("%d\n",t);
	}
	return 0;
} 
