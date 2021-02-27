#include <algorithm>

#include "Node.h"

bool Node::contains(const char* key) const
{
	for (int i = 0; i < n; ++i)
		if (keys[i].has_primary_key(key))
			return true;
	return (children[0] != nullptr && children[0]->contains(key))
			|| (children[1] != nullptr && children[1]->contains(key));
}

void Node::insert_non_full(const Article& article)
{
	keys[n++] = article;
	std::sort(keys.begin(), keys.begin() + n, Article::compare_article);
}

bool Node::is_full() const
{
	return n == NODE_CAPACITY;
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
 * for j = x.n + 1 downto i + 1
 * 	x.c_(j+1) = x.c_j
 * x.c_(i+1) = z
 * for j = x.n downto i
 * 	x.key_(j+1) = x.key_j
 * x.key_i = y.key_i
 * x.n = x.n + 1
 * Disk-Write(y)
 * Disk-Write(z)
 * Disk-Write(x)
 */

void Node::remove(const char* key)
{
	std::array<Article, 3> non_removed;

	int j = 0;
	for (auto& i : keys)
	{
		if (!i.has_primary_key(key))
		{
			non_removed[j] = i;
			j++;
		}
	}

	keys = non_removed;
}

Node::~Node()
{
	if (children[0] != nullptr)
		delete children[0];
	if (children[1] != nullptr)
		delete children[1];
}
