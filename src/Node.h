#ifndef B_TREE_INDEXING_NODE_H
#define B_TREE_INDEXING_NODE_H

#include "Article.h"

#define NODE_DEGREE 5

class Node
{
public:
	Node();
	~Node();
	void insert(const Article& article);
	bool contains(const char* key);
	bool is_leaf = false;
	unsigned key_count = 0;
	Article* values[NODE_DEGREE - 1]{};
	Node* children[NODE_DEGREE]{};
};

#endif //B_TREE_INDEXING_NODE_H
