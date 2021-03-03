#include "BTree.h"

BTree::BTree()
{
	root = new Node();
}

BTree::~BTree()
{
	delete root;
}

bool BTree::contains(const char* key) const
{
	return root->contains(key);
}

void BTree::insert(const Article& article) const
{
	root->insert_non_full(article);
}
