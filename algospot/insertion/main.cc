// ID:  INSERTION (삽입 정렬 뒤집기)
// URL: https://algospot.com/judge/problem/read/INSERTION

#include <iostream>
#include <vector>
using namespace std;

// implementation of treap //
template<typename T>
class Treap {
public:
	T key;
	int priority, size;
	Treap *left, *right;
public:
	Treap(const T& key): key(key), priority(rand()), size(1), left(nullptr), right(nullptr) {}
	void setLeft(Treap* left) { this->left = left; calcSize(); }
	void setRight(Treap* right) { this->right = right; calcSize(); }
	void calcSize() { size = 1 + (left ? left->size : 0) + (right ? right->size : 0); }
};

template<typename T>
Treap<T>* insert(Treap<T>* root, T key) {
	Treap<T> *node = new Treap<T>(key);
	return insert_sub(root, node);
}
template<typename T>
Treap<T>* insert_sub(Treap<T>* root, Treap<T>* node) {
	if(root == nullptr) return node;
	if(root->priority >= node->priority){
		if(root->key > node->key){
			root->left = insert_sub(root->left, node);
			root->left->calcSize();
			root->calcSize();
		}else if(root->key < node->key){
			root->right = insert_sub(root->right, node);
			root->right->calcSize();
			root->calcSize();
		}
		else throw "duplicate key";
		return root;
	}else{
		Treap<T> *trail, *lead;
		// new node will be a new root
		lead = root; trail = nullptr;
		while(lead){
			if(lead->key < node->key) break;
			else{
				trail = lead;
				lead = lead->left;
			}
		}
		if(!lead){
			node->left = nullptr;
			node->right = root;
			node->calcSize();
		}else{
			node->left = lead;
			if(trail){
				node->right = trail;
				trail->left = nullptr;
				node->right->calcSize();
			}
			node->calcSize();
		}
		return node;
	}
}

template<typename T>
Treap<T>* merge(Treap<T>* a, Treap<T>* b) {
	if(a == nullptr) return b;
	if(b == nullptr) return a;
	if(a->priority < b->priority){
		b->setLeft(merge(a, b->left));
		return b;
	}
	a->setRight(merge(a->right, b));
	return a;
}

template<typename T>
Treap<T>* remove(Treap<T>* root, T key) {
	if(root == nullptr) return root;

	if(root->key == key){
		Treap<T>* ret = merge(root->left, root->right);
		delete root;
		return ret;
	}
	if(key < root->key) root->setLeft(remove(root->left, key));
	else root->setRight(remove(root->right, key));
	return root;
}

// k-th smallest key (k starts from 1)
template<typename T>
Treap<T>* kth(Treap<T>* root, int k) {
	if(k <= 0 || root->size < k) throw "k is less than 1 or greater than tree size";
	int smalls = root->left ? root->left->size : 0;
	if(smalls == k-1) return root;
	else if(smalls > k-1) return kth(root->left, k);
	else return kth(root->right, k - smalls - 1);
}
/////////////////////////////

/*template<typename T>
void print(Treap<T> *tree, int depth) {
	if(tree == nullptr) return;
	for(int i=0; i<depth; i++) cout << ' ';
	cout << tree->key << '(' << tree->size << ')' << endl;
	if(tree->left){ cout << 'L'; print(tree->left, depth+1); }
	if(tree->right){ cout << 'R'; print(tree->right, depth+1); }
}*/

void solve() {
	// input
	int n;
	cin >> n;
	vector<int> moves(n), soln(n);
	for(int i=0; i<n; i++) cin >> moves[i];
	// solve
	Treap<int>* candidates = nullptr;
	for(int i=0; i<n; i++){
		candidates = insert(candidates, i+1);
	}
	for(int i=n-1; i>=0; i--){
		int larger = moves[i];
		Treap<int>* k = kth(candidates, i + 1 - larger);
		soln[i] = k->key;
		candidates = remove(candidates, k->key);
	}
	// output
	for(int i=0; i<n; i++) cout << soln[i] << ' ';
	cout << endl;
}

int main() {
	int t;
	cin >> t;
	while(t --> 0) solve();
	return 0;
}
