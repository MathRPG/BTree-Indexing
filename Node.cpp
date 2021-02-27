#include "Node.h"

bool Node::contains(const char* key) const
{
	for (int i = 0; i < n; ++i)
		if (keys[i].has_primary_key(key))
			return true;
	return false;
}

void Node::insert(const Article& article)
{
	if (n != NODE_CAPACITY)
	{
		keys[n] = article;
		n++;
	}
	else
	{
		// NOW ITS TIME TO GET FUNKY
		children[0] = new Node();
		children[1] = new Node();

		children[0]->insert(keys[0]);
		children[1]->insert(keys[1]);
		children[1]->insert(keys[2]);

		keys[0] = article;
		n = 1;
	}
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
 * 		B-TREE-SPLIT-CHILD(s.1)
 * 		B-TREE-INSERT-NONFULL(s,k)
 *	else
 *		B-TREE-INSERT-NONFULL(r,k)
 */

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



/*
 * Insert-Nonfull(x,k)
 * i = x.n
 * if x.leaf
 * 	while i>= 1 and k < x.key_i
 * 		x.key_(i+1) = k.key_i
 * 		i = i - 1
 * 	x.key_(i+1) = k
 * 	x.n = x.n + 1
 * 	Disk-Write(x)
 * else
 * 	while i >= 1 and k < x.key_i
 * 		i = i - 1
 * 	i = i + 1
 * 	Disk-Read(x.c_i)
 * 	if x.c_i.n == 2t - 1
 * 		Split-Child(x, i)
 * 		if k > k.key_i
 * 			i = i + 1
 * 		Insert-Nonfull(x.c_i, k)
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
