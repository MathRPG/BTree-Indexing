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

void Node::insert(const Article& article)
{
	if (is_not_full())
	{
		insert_non_full(article);
	}
	else
	{
		// Cria um array de tamanho n+1
		std::array<Article, NODE_CAPACITY + 1> helper_array;

		// Copia elementos
		for (int i = 0; i < NODE_CAPACITY; ++i)
			helper_array[i] = keys[i];

		// Insere o artigo e ordena nessa array
		*(helper_array.rbegin()) = article;
		std::sort(helper_array.begin(), helper_array.end(), Article::compare_article);

		// NOW ITS TIME TO GET FUNKY
		children[0] = new Node();
		children[1] = new Node();

		// Primeiro elemento vai da subarvore esquerda, segundo fica com a gente, terceiro e quarto vao pra direita
		children[0]->insert(helper_array[0]);
		children[1]->insert(helper_array[2]);
		children[1]->insert(helper_array[3]);

		keys[0] = helper_array[1];
		n = 1;
	}
}
void Node::insert_non_full(const Article& article)
{
	keys[n++] = article;
	std::sort(keys.begin(), keys.begin() + n, Article::compare_article);
}
bool Node::is_not_full() const
{
	return n != NODE_CAPACITY;
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
