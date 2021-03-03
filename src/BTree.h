#ifndef B_TREE_INDEXING_BTREE_H
#define B_TREE_INDEXING_BTREE_H

#include "Article.h"
#include "Node.h"

class BTree
{

public:
	BTree();
	~BTree();
	bool contains(const char* key) const;
	void insert(const Article& article) const;
private:
	Node* root;
};

#endif
