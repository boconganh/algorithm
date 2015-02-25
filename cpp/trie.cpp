#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <string>
#include <ctime>
#include <map>


	
using namespace std;


#define CONVERT(c) (\
	isdigit(c)? (c)-'0':\
	isupper(c)? (c)-'A'+10:\
	islower(c)? (c)-'a'+ 36:\
	62\
	)
#define INVERT(c) (\
	(c)<10?(c)+'0':\
	(c)<36?(c)-10+'A':\
	(c)-36+'a')
	
using namespace std;

#define MAX_CHAR 64
struct node{
	node *child[MAX_CHAR];
	bool word;
	node(){
		for(int i=0;i<MAX_CHAR;++i){
			child[i]=NULL;
		}
		word=false;
	}
	~node(){
		int i;
		for(i=0;i<MAX_CHAR;++i){
			if(child[i]) delete child[i];
		}
	}
	void insert(char *s){
		int n=strlen(s);
		node *cur=this;
		for(int i=0;i<n;++i){
			int c=CONVERT(s[i]);
			if(cur->child[c]==NULL){
				cur->child[c]=new node();
			}
			cur=cur->child[c];
			if(i==n-1){
				cur->word=true;
			}
		}
	}
	bool isword(){
		return word;
	}
	bool isleaf(){
		int i;
		for(i=0;i<MAX_CHAR;++i){
			if(child[i]) return false;
		}
		return true;
	}
	static void show(node *t,const string &prefix){
		for(int i=0;i<MAX_CHAR;++i){
			if(!t->child[i]) continue;
			string out=prefix +(char)INVERT(i);
			if(t->child[i]->isword()){
				for(int k=0;k<out.size();++k) putchar_unlocked(out[k]);
				putchar_unlocked('\n');
			}
			show(t->child[i],out);
		}
	}
};


int get_s(char *s){
	int i=0;
	int c;
	for(;;){
		c=getchar_unlocked();
		if(isalpha(c)) break;
		if(c==EOF) return c;
	}
	while(isalpha(c)){
		s[i++]=tolower(c);
		c=getchar_unlocked();
	}
	s[i]=0;
	return i;
}
int main() {
	node *t=new node();
	char s[300];
	while(1){
		int c=get_s(s);
		if(c==EOF) break;
		if(c){
			t->insert(s);
		}
	}
	node::show(t,"");
	
	return 0;
}
