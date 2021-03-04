#ifndef B_TREE_INDEXING_NODE_H
#define B_TREE_INDEXING_NODE_H

#include "Article.h"

#define NODE_T 2 // Minimum degree

class Node
{
	friend class BTree;
public:
	Node();
	~Node();
private:
	bool is_leaf = true;
	unsigned item_count = 0;
	Article* items[(2 * NODE_T) - 1] = {};
	Node* children[(2 * NODE_T)] = {};
	void insert_non_full(const Article& article);
	void split_child(unsigned int i);
	Article* fetch(const std::string& key);
	void dump(std::fstream& f) const;
};

#endif //B_TREE_INDEXING_NODE_H
