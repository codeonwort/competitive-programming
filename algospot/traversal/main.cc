// ID:  TRAVERSAL (트리 순회 순서 변경)
// URL: https://algospot.com/judge/problem/read/TRAVERSAL

#include <iostream>
#include <vector>
using namespace std;

struct tree {
	int key;
	tree *left, *right;
};

tree* build(vector<int>& preorder, int l1, int r1,
			vector<int>& inorder, int l2, int r2) {
	if(l1 > r1 || l2 > r2) return NULL;
	int root = preorder[l1];
	tree* T = new tree;
	T->key = root;
	if(l1 == r1){
		T->left = NULL; T->right = NULL;
	}else{
		int k;
		for(k=l2; k<=r2; k++){
			if(inorder[k] == root) break;
		}
		int numLeft = k - l2;
		T->left = build(preorder, l1+1, l1+numLeft, inorder, l2, k-1);
		T->right = build(preorder, l1+numLeft+1, r1, inorder, k+1, r2);
	}
	return T;
}

void visitPostorder(tree* T) {
	if(T->left) visitPostorder(T->left);
	if(T->right) visitPostorder(T->right);
	cout << T->key << ' ';
}

void solve() {
	int n;
	cin >> n;
	vector<int> preorder(n);
	vector<int> inorder(n);
	for(int i=0; i<n; i++) cin >> preorder[i];
	for(int i=0; i<n; i++) cin >> inorder[i];

	tree *T = build(preorder,0,n-1, inorder,0,n-1);
	visitPostorder(T);
	cout << endl;
}

int main() {
	int t;
	cin >> t;
	while(t --> 0) solve();
	return 0;
}
