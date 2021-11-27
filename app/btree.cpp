#define BOOST_LOG_DYN_LINK 1
#include <boost/log/trivial.hpp>
#include <jsoncpp/json/json.h>
#include <iostream>
#include <fstream>

#include <iostream>

using namespace std;

template<typename T>
struct node
{
	T value;
	node *left;
	node *right;
};

template<typename T>
class btree{
public:
	btree();
	~btree();

	void insert(T& key);
	node<T> *search(const T& key);
	void destroy_tree();
	void inorder_print();
	void postorder_print();
	void preorder_print();

private:
	void destroy_tree(node<T> *leaf);
	void insert(T& key, node<T> *leaf);
	node<T> *search(const T& key, node<T> *leaf);
	void inorder_print(node<T> *leaf);
	void postorder_print(node<T> *leaf);
	void preorder_print(node<T> *leaf);

	node<T> *root;
};

template<typename T>
btree<T>::btree(){
	root = NULL;
}

template<typename T>
btree<T>::~btree(){
	destroy_tree();
}

template<typename T>
void btree<T>::destroy_tree(node<T> *leaf){
	if(leaf != NULL){
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
	}
}

template<typename T>
void btree<T>::insert(T& key, node<T> *leaf){

	if(key < leaf->value){
		if(leaf->left != NULL){
			insert(key, leaf->left);
		}else{
			leaf->left = new node<T>;
			leaf->left->value = key;
			leaf->left->left = NULL;
			leaf->left->right = NULL;
		}
	}else if(key >= leaf->value){
		if(leaf->right != NULL){
			insert(key, leaf->right);
		}else{
			leaf->right = new node<T>;
			leaf->right->value = key;
			leaf->right->right = NULL;
			leaf->right->left = NULL;
		}
	}

}

template<typename T>
void btree<T>::insert(T& key){
	if(root != NULL){
		insert(key, root);
	}else{
		root = new node<T>;
		root->value = key;
		root->left = NULL;
		root->right = NULL;
	}
}

template<typename T>
node<T> *btree<T>::search(const T& key, node<T> *leaf){
	if(leaf != NULL){
		if(key == leaf->value){
			return leaf;
		}
		if(key < leaf->value){
			return search(key, leaf->left);
		}else{
			return search(key, leaf->right);
		}
	}else{
		return NULL;
	}
}

template<typename T>
node<T> *btree<T>::search(const T& key){
	return search(key, root);
}

template<typename T>
void btree<T>::destroy_tree(){
	destroy_tree(root);
}

template<typename T>
void btree<T>::inorder_print(){
	inorder_print(root);
	cout << "\n";
}

template<typename T>
void btree<T>::inorder_print(node<T> *leaf){
	if(leaf != NULL){
		inorder_print(leaf->left);
		cout << leaf->value << ",";
		inorder_print(leaf->right);
	}
}

template<typename T>
void btree<T>::postorder_print(){
	postorder_print(root);
	cout << "\n";
}

template<typename T>
void btree<T>::postorder_print(node<T> *leaf){
	if(leaf != NULL){
		inorder_print(leaf->left);
		inorder_print(leaf->right);
		cout << leaf->value << ",";
	}
}

template<typename T>
void btree<T>::preorder_print(){
	preorder_print(root);
	cout << "\n";
}

template<typename T>
void btree<T>::preorder_print(node<T> *leaf){
	if(leaf != NULL){
		cout << leaf->value << ",";
		inorder_print(leaf->left);
		inorder_print(leaf->right);
	}
}

int main(){


	btree<int> *tree = new btree<int>();

    int val1 = 10;
    int val2 = 24;
    int val3 = 949;
    int val4 = 904;
    int val5 = 89;
    int val6 = 78;

	tree->insert(val1);
	tree->insert(val2);
	tree->insert(val3);
	tree->insert(val4);
	tree->insert(val5);
	tree->insert(val6);

	tree->preorder_print();
	tree->inorder_print();
	tree->postorder_print();

	delete tree;

}
