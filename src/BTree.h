#ifndef B_TREE_INDEXING_BTREE_H
#define B_TREE_INDEXING_BTREE_H

#include "Article.h"
#include "Node.h"

class BTree
{
public:
	BTree();
	~BTree();
	[[nodiscard]] bool contains(const std::string& key) const;
	void insert(const Article& article);
	[[nodiscard]] const Article* fetch(const std::string& key) const;
	void remove(const std::string& key);
private:
	Node* root;
};

#endif
