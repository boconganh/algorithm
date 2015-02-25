#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <string>
#include <ctime>
#include <map>
#include <list>
#include <queue>
#include <climits>
#include <queue>

	
using namespace std;


#define max_char 55

inline int cti(char c){
	if(isupper(c)){
		return c-'A';
	}else{
		return c-'a'+26;
	}
}
inline char itc(int i){
	if(i<26){
		return i+'A';
	}else{
		return i-26+'a';
	}
}

int N;
struct node{
	bool word;
	int index;
	node* child[max_char];
	node(){
		int i;
		for(i=0;i<max_char;++i){
			child[i]=NULL;
		}
		index=-1;
		word=false;
	}
	~node(){
		int i;
		for(i=0;i<max_char;++i){
			if(child[i]) delete child[i];
		}
	}
	void insert(char *s){
		int n=strlen(s);
		node *cur=this;
		for(int i=0;i<n;++i){
			int id=cti(s[i]);
			if(cur->child[id]==NULL){
				cur->child[id]=new node();
			}
			cur=cur->child[id];
			if(i==n-1){
				cur->word=true;
			}
		}
	}
	int find(char *s){
		int n=strlen(s);
		node *cur=this;
		for(int i=0;i<n;++i){
			int id=cti(s[i]);
			if(cur->child[id]==NULL){
				return -1;
			}
			cur=cur->child[id];
			if(i==n-1){
				return cur->index;
			}
		}
		return -1;
	}
	static void show(node *n,string &prev){
		for(int i=0;i<max_char;++i){
			if(n->child[i]==NULL) continue;
			string out=prev+ itc(i);
			if(n->child[i]->word){
				cout<<out<<endl;
			}
			show(n->child[i],out);
		}
	}
	static void sort(node *n){
		for(int i=0;i<max_char;++i){
			if(n->child[i]==NULL) continue;
			if(n->child[i]->word){
				n->child[i]->index=N++;
			}
			sort(n->child[i]);
		}
	}
	
	
};


#define maxlen 55
#define maxn 2100

char mem[maxn][2][maxlen];
int len[maxn];
char src[maxlen],dst[maxlen];

typedef long long ll;
typedef pair<int,int> ii;
typedef list<ii> lii;
typedef pair<int,ll> il;

lii adj[2*maxn];

int st,nd;

void read(){
	int n;
	scanf("%d",&n);
	if(n==0) exit(0);
	node * t=new node();
	
	N=0;
	scanf("%s%s",src,dst);
	char tmp[maxlen];
	int i;
	for(i=0;i<n;++i){
		scanf("%s%s%s",mem[i][0],mem[i][1],tmp);
		len[i]=strlen(tmp);
		//puts(tmp);
		t->insert(mem[i][0]);
		t->insert(mem[i][1]);
	}
	node::sort(t);
	for(i=0;i<n;++i){
		int u=t->find(mem[i][0]),v=t->find(mem[i][1]);
		//printf("%d %d: %d\n",u+1,v+1,len[i]);
		adj[u].push_back(ii(v,len[i]));
		adj[v].push_back(ii(u,len[i]));
	}
	st=t->find(src);
	nd=t->find(dst);
	
	delete t;
}

void show(){
	int i;
	
	for(i=0;i<N;++i){
		for(lii::iterator it=adj[i].begin();it!=adj[i].end();++it){
			printf("%d %d: %d\n",i,it->first,it->second);
		}
	}
}

#define maxc LONG_MAX
ll dijkstra(int s,int p){
	if(s<0 or p<0) return maxc;
	vector<ll> D(N+1,maxc);
	D[s]=0;
	priority_queue<il,vector<il>,greater<il> > Q;
	Q.push(il(s,0));
	
	while(Q.size()){
		il top=Q.top();
		Q.pop();
		int u=top.first;
		ll d=top.second;
		D[u]=top.second;
		//cout<<"#"<<top.first<<" "<<top.second<<endl;
		for(lii::iterator it=adj[u].begin();it!=adj[u].end();++it){
			int v=it->first;
			ll cost=it->second;
			if(d+cost<D[v]){
				Q.push(il(v,d+cost));
				D[v]=d+D[u];
			}
		}
	}
	return D[p];
}

int main(){
	for(;;){
		read();
		printf("%d %d\n",st,nd);
		show();
		ll res=dijkstra(st,nd);
		if(res<maxc){
			printf("%lld\n",res);
		}else{
			printf("impossivel\n");
		}
		for(int i=0;i<N;++i) adj[i].clear();
		
	}
	return 0;
}
