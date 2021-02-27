#ifndef BTREE_H
#define BTREE_H

#include "Article.h"

#include <vector>

typedef const char* filename_t;

class B_Tree
{
public:
	B_Tree(filename_t index_path, filename_t registry_path);
	bool contains(const char* key) const;
	void insert(const Article& article);
	void remove(const char* key);
private:
	std::vector<Article> all_articles;
};

#endif

/*
 Search(x, k)
 i = 1
 while i <= x.n and k > x.key_i
   i = i + 1
 if i <= x.n and k == x.key_i
   return (x, i)
 elseif x.leaf
   return NIL
 else Disk-Read(x.c_i)
   return B-Tree-Search(x.c_i, k)
*/

/*
 * Create(T)
 * x = Allocate-Node()
 * x.leaf = True
 * x.n = 0
 * Disk-Write(x)
 * T.root = x
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

/* Deletion: to be continued... */
