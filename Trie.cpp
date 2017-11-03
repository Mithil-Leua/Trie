#include <bits/stdc++.h>

using namespace std;

struct trieNode{
	std::map<char,trieNode*> cmap;
	trieNode *parent;
	bool endFlag;
};
typedef trieNode trieNode;

struct Trie{
	trieNode *rootNode;	
};
typedef Trie Trie;

void initNewNode(trieNode **newNode,bool endFlag){
	*newNode = (trieNode *)malloc(sizeof(trieNode));
	std::map<char,trieNode*> cmap;
	(*newNode)->cmap = cmap;
	(*newNode)->parent = NULL;
	(*newNode)->endFlag = endFlag;
}

void initTrie(Trie **trie){
	*trie = (Trie *)malloc(sizeof(Trie));
	initNewNode(&(*trie)->rootNode,false);
}

void insert(trieNode **currNode,string s,int index){
	if(index == s.size())
		return ;
	bool endFlag = false;
	if(index+1 == s.size())
		endFlag = true;

	std::map<char,trieNode*>::iterator it;
	it = (*currNode)->cmap.find(s[index]);

	if(it != (*currNode)->cmap.end()){
		trieNode *nextNode = it->second;
		if(index+1 == s.size()){
			nextNode->endFlag = endFlag;
			return ;
		}
		return insert(&nextNode,s,++index);
	}
	else{
		trieNode *child;
		initNewNode(&child,endFlag);
		child->parent = (*currNode);
		pair<char,trieNode*> tmp;
		tmp.first = s[index];
		tmp.second = child;
		(*currNode)->cmap.insert(tmp);
		return insert(&child,s,++index);
	}
}

bool prefixSearch(trieNode **currNode,string s,int index){
	if(index == s.size())
		return false;

	std::map<char,trieNode*>::iterator it;
	it = (*currNode)->cmap.find(s[index]);

	if(it != (*currNode)->cmap.end()){
		if(index+1 == s.size())
			return true;
		else{
			trieNode *nextNode = it->second;
			return prefixSearch(&nextNode,s,++index);
		}
	}
	else return false;
}

bool wordSearch(trieNode **currNode,string s,int index){
	if(index == s.size())
		return false;

	std::map<char,trieNode*>::iterator it;
	it = (*currNode)->cmap.find(s[index]);

	if(it != (*currNode)->cmap.end()){
		trieNode *nextNode = it->second;
		if(index+1 == s.size())
			return nextNode->endFlag;
		else
			return wordSearch(&nextNode,s,++index);
	}
	else
		return false;
}

void deleteHelper(trieNode **currNode,string s,int index){
	if(index < 0)
		return ;

	std::map<char,trieNode*>::iterator it;

	if((*currNode)->cmap.size() == 0){
		trieNode *parent = (*currNode)->parent;
		it = parent->cmap.find(s[index]);
		parent->cmap.erase(it);
	}
	else{
		if((*currNode)->endFlag){
			(*currNode)->endFlag = false;
			return ;
		}
		trieNode *parent = (*currNode)->parent;
		it = parent->cmap.find(s[index]);
		parent->cmap.erase(it);
		deleteHelper(&parent,s,--index);
		return ;
	}
}

void deleteWord(trieNode **currNode,string s){
	trieNode *temp = *currNode;
	std::map<char,trieNode*>::iterator it;
	
	for(int i=0;i<s.size();i++){
		it = temp->cmap.find(s[i]);
		if(it != temp->cmap.end()){
			temp = it->second;
		}
		else return;
	}
	deleteHelper(&temp,s,s.size()-1);
	return ;
}

int main(){	
	Trie *trie;
	initTrie(&trie);
	trieNode *root = trie->rootNode;
	initNewNode(&root,0);
	string s1 = "123";
	string s2 = "2567";
	string s3 = "74948";
	string s4 = "1246";
	string s5 = "812";
	string s6 = "974125";
	string s7 = "43521";
	string s8 = "43";
	string s9 = "435212";
	insert(&root,s1,0);
	insert(&root,s2,0);
	insert(&root,s3,0);
	insert(&root,s4,0);
	insert(&root,s5,0);
	insert(&root,s6,0);
	insert(&root,s7,0);
	insert(&root,s8,0);
	insert(&root,s9,0);
	deleteWord(&root,s7);
	cout << wordSearch(&root,"4",0);
	return 0;
}