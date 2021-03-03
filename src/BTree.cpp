#include "BTree.h"

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

void BTree::insert(const Article& article)
{
	Node* r = root;

	if (r->item_count != (2 * 2) - 1)
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

/*
 * B-Tree Insert(T, k)
 *
 *	r = T.root
 *	if r.n == 2t -1;
 * 		s = ALLOCATE-NODE();
 * 		T.root = s
 * 		s.leaf = FALSE
 * 		s.n = 0
 * 		s.c1 = r
 * 		B-TREE-SPLIT-CHILD(s, 1)
 * 		B-TREE-INSERT-NONFULL(s, k)
 *	else
 *		B-TREE-INSERT-NONFULL(r, k)
 */
