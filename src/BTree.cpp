#include "BTree.h"

#include <string>

BTree::BTree()
{
	root = new Node();
}

BTree::~BTree()
{
	delete root;
}

bool BTree::contains(const std::string& key) const
{
	return root->contains(key);
}

Article* BTree::fetch(const std::string& key)
{
	return root->fetch(key);
}

void BTree::insert(const Article& article)
{
	Article* fetched = fetch(article.doi);

	if (fetched != nullptr)
	{
		*fetched = article;
		return;
	}

	Node* r = root;

	if (r->item_count != 2 * NODE_T - 1)
	{
		r->insert_non_full(article);
		return;
	}

	Node* s = new Node();
	root = s;
	s->is_leaf = false;
	s->item_count = 0;
	s->children[1 - 1] = r;
	s->split_child(1);
	s->insert_non_full(article);
}
