//Question: https://www.spoj.com/problems/ADAINDEX/

 #include<bits/stdc++.h>//adds all libraries 
using namespace std;


struct trie{
	struct trie* arr[26];//cause the num of letters in alphabet
	int count;
};
trie* make(){//make said trie 
	struct trie *root = NULL;
	root = (trie *)malloc(sizeof(struct trie));//allocate space for trie root
	for(int i = 0; i < 26; i++){//26 cause letters of alphabet/alphabet size 
		root->arr[i]=NULL;
	}
	root->count = 0;
	return root;
}
void add(trie *root,string s){//adds it to the trie 
	int len = s.length();
	if(len != 0){//valid add
		int index = 0;
		for(index = 0;index < len;index++){
			if(root->arr[s[index]-'a'] == NULL){
				root->arr[s[index]-'a'] = make();
			}
			root = root->arr[s[index]-'a'];
			root->count++;
		}
	}
}
long long  find(trie *root,string s){//finds the trie node
	int  len = s.length();
	if(len == 0){
		return 0;
	}
	int  index;
	for(index = 0;index < len; index++){
		if(root->arr[s[index]-'a']==NULL){
			return 0;
		}
		root = root->arr[s[index]-'a'];
	}
	return root->count;
}
int main(){
	long long  n,q;
	scanf("%lld%lld",&n,&q);//gets n and q names given in description 
	trie *root=make();
	while(n--){
		string s;//gets the string
		cin>>s;
		int  len = s.length();
		if(len != 0){//valid lenght 
			add(root,s);
		}
	}
	while(q--){
		string s;
		cin>>s;
		printf("%lld\n",find(root,s));
	}
	return 0;
}