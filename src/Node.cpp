#include "Node.h"

Node::Node()
= default;

Node::~Node()
{
//	for (int i = 0; i < item_count; ++i)
//		delete items[i];
//
//	if (is_leaf)
//		return;
//
//	for (int i = 0; i < item_count + 1; ++i)
//		delete children[i];
}

bool Node::contains(const std::string& key)
{
	// TODO: optimize
//	for (int i = 0; i < item_count; ++i)
//		if (items[i]->has_key(key))
//			return true;
//
//	if (is_leaf)
//		return false;
//
//	for (int i = 0; i < item_count + 1; ++i)
//		if (children[i]->contains(key))
//			return true;
//
//	return false;

	int i = 1;

	while (i <= item_count and key > items[i - 1]->doi)
		i = i + 1;

	if (i <= item_count and key == items[i - 1]->doi)
		return true;

	if (is_leaf)
		return false;

	return children[i - 1]->contains(key);
}

/*
 * B-TREE-SEARCH(x,k)
 * i = 1
 * while i <=x.n and k > x.key[i]
 * 	i = i +1;
 * 	if i <= x.n and k == x.key[i]
 * 		return(x,i)
 * 	elseif x.leaf
 * 		return NIL
 * 	else DISK-READ(x.c_i)
 * 		return B-TRE-SEARCH(x.c_i, k)
 */

void Node::insert_non_full(const Article& article)
{
//	items[item_count++] = new Article(article);

	int i = (int) item_count;
	std::string k = article.doi;

	if (is_leaf)
	{
		while (i >= 1 && k < items[i - 1]->doi)
		{
			// TODO: do we need to free any of this stuff?
			items[i + 1 - 1] = items[i - 1];
			i--;
		}

		items[i + 1 - 1] = new Article(article);
		item_count++;
	}
	else
	{
		while (i >= 1 and k < items[i - 1]->doi)
			i = i - 1;
		i = i + 1;
		if (children[i - 1]->item_count == (2 * 2) - 1)
		{
			split_child(i);
			if (k > items[i - 1]->doi)
				i = i + 1;
		}
		children[i - 1]->insert_non_full(article);
	}
}

/*
 * B-Tree INSERT NON FULL(x,k)
 * i = x.n
 * if x.leaf
 * 		while i>= 1 and k < x.key[i]
 * 			x.key[i+1] = x.key[i]
 * 			i = i -1
 * 		x.key[i+1] = k
 * 		x.n = x.n + 1;
 * 		Disk-Write(x)
 * 	else while i >= 1 and k < x.key[i]
 * 			i = i-1
 * 		i = i+ 1
 * 		Dik-Read(x.c[1])
 * 		if x.c[i].n == 2t -1
 * 			B-TREE-SPLIT-CHILD(x,i)
 * 			if k > x.key[i]
 * 				i = i+1
 * 		B-TREE-INSERT-NON FULL(x.c[i].k)
 */

void Node::split_child(unsigned int i) // it do be one more tho
{
	Node* z = new Node();
	Node* y = children[i - 1];

	z->is_leaf = y->is_leaf;
	z->item_count = NODE_T - 1;

	for (int j = 1; j <= NODE_T - 1; ++j) // TODO: maybe t-1?
		z->items[j - 1] = y->items[j + NODE_T - 1];

	if (!y->is_leaf)
		for (int j = 1; j <= NODE_T; ++j)
			z->children[j - 1] = y->children[j + NODE_T - 1];

	y->item_count = NODE_T - 1;

	for (unsigned j = item_count + 1; j >= i + 1; --j)
		children[j + 1 - 1] = children[j - 1]; // Don't judge me

	children[i + 1 - 1] = z; // Again, don't judge me

	for (unsigned j = item_count; j >= i; --j)
		items[j + 1 - 1] = items[j - 1]; // FOR THE LAST TIME, DON'T JUDGE ME

	items[i - 1] = y->items[NODE_T - 1];
	item_count++;
}

/*
 * Split-Child(x, i)
 * z = Allocate-Node()
 * y = x.c_i
 * z.leaf = y.leaf
 * z.n = t-1
 * for j = 1 to t - 1
 * 	z.key_j = y.key_(j+t)
 * if not y.leaf
 * 	for j = 1 to t
 * 		z.c_j = y.c_(j+t)
 * y.n = t - 1
 * for j = x.n + 1 down to i + 1
 * 	x.c_(j+1) = x.c_j
 * x.c_(i+1) = z
 * for j = x.n down to i
 * 	x.key_(j+1) = x.key_j
 * x.key_i = y.key_i
 * x.n = x.n + 1
 * Disk-Write(y)
 * Disk-Write(z)
 * Disk-Write(x)
 */
