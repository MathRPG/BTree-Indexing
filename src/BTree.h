#ifndef B_TREE_INDEXING_BTREE_H
#define B_TREE_INDEXING_BTREE_H

#include "Article.h"
#include "Node.h"

class BTree
{
public:
	BTree();
	explicit BTree(std::fstream& f);
	~BTree();
	[[nodiscard]] bool contains(const std::string& key) const;
	void insert(const Article& article);
	[[nodiscard]] const Article* fetch(const std::string& key) const;
	void remove(const std::string& key);
	void dump(std::fstream& f);
private:
	Node* root;
};

#endif
