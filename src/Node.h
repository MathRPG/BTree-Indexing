#ifndef B_TREE_INDEXING_NODE_H
#define B_TREE_INDEXING_NODE_H

#include "Article.h"

#define NODE_DEGREE 5
#define MINIMUM_DEGREE 2 // TODO: Check this

class Node
{
	friend class BTree;
public:
	Node();
	~Node();
	void insert_non_full(const Article& article);
	bool contains(const std::string& key);
private:
	bool is_leaf = true;
	unsigned item_count = 0;
	Article* items[NODE_DEGREE - 1] = {};
	Node* children[NODE_DEGREE] = {};
};

#endif //B_TREE_INDEXING_NODE_H
