#pragma once
#include <windows.h>
#include "C:\Users\Екатерина Иванова\source\repos\шаблон List\list.h"
using namespace std;

template<typename Key, typename Value>
class map
{
private:
	template<typename Key, typename Value>
	class NodeT
	{
	public:
		Key key;
		Value value;
		int color;   // red - 0;  black - 1
		NodeT<Key, Value>* parent;
		NodeT<Key, Value>* left;
		NodeT<Key, Value>* right;

		NodeT(Key key, Value value, NodeT<Key, Value>* parent) : color(0), left(nullptr), right(nullptr), parent(parent), key(key), value(value) {}
		~NodeT() {};
	};
	NodeT<Key, Value>* root;
	size_t size;


	// restores the properties of the red-black tree after inserting a new node
	void fixup(NodeT<Key, Value>* node)
	{
		NodeT<Key, Value> *uncle = nullptr;

		while (node != root && node->parent != nullptr && node->parent->color == 0)
		{
			if (grandparent(node) != nullptr && node->color == 0 && node->parent == grandparent(node)->left)
			{ // the node is located in the left subtree of the grandfather node
				uncle = grandparent(node)->right;
				if (uncle != nullptr && uncle->color == 0)
				{
					node->parent->color = 1;
					uncle->color = 1;
					grandparent(node)->color = 0;
					node = grandparent(node);
				}
				else
				{
					if (node == node->parent->right)
					{
						node = node->parent;
						left_rotation(node);
					}

					node->parent->color = 1;
					grandparent(node)->color = 0;
					right_rotation(grandparent(node));
				}
			}
			else
			{ // the node is located in the right subtree of the grandfather node
				uncle = grandparent(node)->left;
				if (uncle != nullptr && uncle->color == 0)
				{
					node->parent->color = 1;
					uncle->color = 1;
					grandparent(node)->color = 0;
					node = grandparent(node);
				}
				else
				{
					if (node == node->parent->left)
					{
						node = node->parent;
						right_rotation(node);
					}
					node->parent->color = 1;
					grandparent(node)->color = 0;
					left_rotation(grandparent(node));
				}
			}
		}

		root->color = 1;
	}

	void left_rotation(NodeT<Key, Value>* node)
	{
		NodeT<Key, Value> *right_child_of_node = node->right;

		right_child_of_node->parent = node->parent;
		if (node->parent != nullptr)
		{
			if (node->parent->left == node)
				node->parent->left = right_child_of_node;
			else
				node->parent->right = right_child_of_node;
		}
		else
			root = right_child_of_node;

		node->right = right_child_of_node->left;
		if (right_child_of_node->left != nullptr)
			right_child_of_node->left->parent = node;

		node->parent = right_child_of_node;
		right_child_of_node->left = node;
	}

	void right_rotation(NodeT<Key, Value>* node)
	{
		NodeT<Key, Value> *left_child_of_node = node->left;

		left_child_of_node->parent = node->parent;
		if (node->parent != nullptr)
		{
			if (node->parent->left == node)
				node->parent->left = left_child_of_node;
			else
				node->parent->right = left_child_of_node;
		}
		else
			root = left_child_of_node;

		node->left = left_child_of_node->right;
		if (left_child_of_node->right != nullptr)
			left_child_of_node->right->parent = node;

		node->parent = left_child_of_node;
		left_child_of_node->right = node;
	}

	// search for the "heir", i.e. the node whose key is the least different from the"testator" node
	NodeT<Key, Value>* find_successor(NodeT<Key, Value> *node)
	{
		if (node->left != nullptr)
		{
			node = node->left;
			while (node->right != nullptr)
				node = node->right;
		}
		else
		{
			node = node->right;
			while (node->left != nullptr)
				node = node->left;
		}
		return node;
	}

	// returns a pointer to the node's "grandfather"
	NodeT<Key, Value>* grandparent(NodeT<Key, Value>* node)
	{
		if ((node != nullptr) && (node->parent != nullptr))
			return node->parent->parent;
		else
			return nullptr;
	}

	// restores the properties of the red-black tree after deleting the node
	void delfix(NodeT <Key, Value> *node)
	{
		NodeT <Key, Value> *sibling = nullptr;
		while (node != root && node->color == 1)
		{
			if (node->parent->left == node)
			{
				sibling = node->parent->right;
				if (sibling->color == 0)
				{
					sibling->color = 1;
					node->parent->color = 0;
					left_rotation(node->parent);
					sibling = node->parent->right;
				}
				if (sibling->right->color == 1 && sibling->left->color == 1)
				{
					sibling->color = 0;
					node = node->parent;
				}
				else
				{
					if (sibling->right->color == 1)
					{
						sibling->left->color = 1;
						sibling->color = 0;
						right_rotation(sibling);
						sibling = node->parent->right;
					}
					sibling->color = node->parent->color;
					node->parent->color = 1;
					sibling->right->color = 1;
					left_rotation(node->parent);
					node = root;
				}
			}
			else
			{
				sibling = node->parent->left;
				if (sibling->color == 0)
				{
					sibling->color = 1;
					node->parent->color = 0;
					right_rotation(node->parent);
					sibling = node->parent->left;
				}
				if (sibling->left->color == 1 && sibling->right->color == 1)
				{
					sibling->color = 0;
					node = node->parent;
				}
				else
				{
					if (sibling->left->color == 1)
					{
						sibling->right->color = 1;
						sibling->color = 0;
						left_rotation(sibling);
						sibling = node->parent->left;
					}
					sibling->color = node->parent->color;
					node->parent->color = 1;
					sibling->left->color = 1;
					right_rotation(node->parent);
					node = root;
				}
			}
			node->color = 1;
			root->color = 1;
		}
	}

	// delete nodes of a tree
	void delete_RBtree(NodeT<Key, Value> *node)
	{
		if (node != nullptr)
		{
			delete_RBtree(node->left);
			delete_RBtree(node->right);
			delete node;
			size--;
			node = nullptr;
		}
		root = nullptr;
	}

	// generate a list of keys
	void set_keys(List<Key> &list, NodeT<Key, Value>* node)
	{
		if (node != nullptr)
		{
			set_keys(list, node->left);
			list.push_back(node->key);
			set_keys(list, node->right);
			return;
		}
	}

	// generate a list of values
	void set_values(List<Value> &list, NodeT<Key, Value>* node)
	{
		if (node != nullptr)
		{
			set_values(list, node->left);
			list.push_back(node->value);
			set_values(list, node->right);
			return;
		}
	}

	// output of nodes (key, value) to the console
	void print_node(NodeT<Key, Value>* node)
	{
		if (node != nullptr)
		{
			print_node(node->left);
			if (node)
			{
				if (node->color == 0)
					set_color(15, 4);
				else set_color(15, 0);
				cout << node->key << " : " << node->value << endl;
			}
			print_node(node->right);
			return;
		}
	}

	// coloring text and its background to a specific color
	void set_color(int background, int text) // background -- background color, text -- text color
	{
		HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleHandle, (WORD)((background << 4) | text));
	}

public:
	map() : root(nullptr), size(0) {}
	~map() { delete_RBtree(root); }

	// adding an element with a key and value
	void insert(Key key, Value value)
	{
		NodeT<Key, Value>* parent = nullptr;

		for (NodeT<Key, Value> *node = root; node != nullptr; )
		{
			if (key == node->key)
				throw invalid_argument("A node with the specified key is already contained in the map.");
			else
			{
				parent = node;
				if (key < node->key)
					node = node->left;
				else
					node = node->right;
			}
		}

		NodeT<Key, Value>* current = new NodeT<Key, Value>(key, value, parent);
		size++;

		if (parent != nullptr)
		{
			if (key < parent->key)
				parent->left = current;
			else
				parent->right = current;
		}
		else  root = current;

		fixup(current);
	}

	// the removal of the tree element by key
	void remove(Key key_to_remove)
	{
		if (root == nullptr)
			throw invalid_argument("Map is empty.");

		NodeT<Key, Value> *node_for_delete = root, *successor = nullptr, *node = nullptr;

		int found = 0;
		while (node_for_delete != nullptr && found == 0)
		{
			if (node_for_delete->key == key_to_remove)
				found = 1;
			if (found == 0)
			{
				if (node_for_delete->key < key_to_remove)
					node_for_delete = node_for_delete->right;
				else
					node_for_delete = node_for_delete->left;
			}
		}

		if (found == 0)
			throw invalid_argument("This element isn't in the map.");
		else
		{
			if (node_for_delete->left == nullptr || node_for_delete->right == nullptr)
				successor = node_for_delete;
			else
				successor = find_successor(node_for_delete);  // узел, который после удаления node, займёт его место

			if (successor->left != nullptr)
				node = successor->left;
			else
			{
				if (successor->right != nullptr)
					node = successor->right;
				else
					node = nullptr;
			}
			if (node != nullptr)
				node->parent = successor->parent;
			if (successor->parent == nullptr)
				root = node;
			else
			{
				if (successor == successor->parent->left)
					successor->parent->left = node;
				else
					successor->parent->right = node;
			}
			if (successor != node_for_delete)
			{
				node_for_delete->color = successor->color;
				node_for_delete->key = successor->key;
			}
			if (successor->color == 1 && node != nullptr)
				delfix(node);

			delete successor;
			size--;
		}
	}

	// searching for an element by key
	Value find(Key key_to_search)
	{
		if (root == nullptr)
			throw invalid_argument("Map is empty.");

		NodeT<Key, Value> *current = root;
		while (current != nullptr && current->key != key_to_search)
		{
			if (current->key < key_to_search)
				current = current->right;
			else
				current = current->left;
		}
		if (current == nullptr)
			throw invalid_argument("This element isn't in the map.");

		return current->value;
	}

	// clearing map
	void clear()
	{
		if (root == nullptr)
			throw invalid_argument("Map is empty.");

		delete_RBtree(root);
	}

	// returns a list of keys
	List<Key> get_keys()
	{
		List<Key> list;
		set_keys(list, root);
		return list;
	}

	// returns a list of values
	List<Value> get_values()
	{
		List<Value> list;
		set_values(list, root);
		return list;
	}

	// output the tree to the console
	void print()
	{
		if (root == nullptr)
			throw invalid_argument("Map is empty.");

		print_node(root);
		cout << endl;
	}

	// returns the number of elements in map
	size_t get_size() { return size; }

	Value & operator [] (const Key key)
	{
		if (root == nullptr)
			throw invalid_argument("Map is empty");

		NodeT<Key, Value> *current = root;
		while (current != nullptr && current->key != key)
		{
			if (current->key < key)
				current = current->right;
			else
				current = current->left;
		}
		if (current == nullptr)
			throw invalid_argument("This element isn't in the map");

		return current->value;
	}
};
