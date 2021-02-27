#include "B_Tree.h"

#include <fstream>
#include <algorithm>

B_Tree::B_Tree(filename_t index_path, filename_t registry_path)
{
	std::fstream file(index_path, std::fstream::out);
	file.close();
	file.open(registry_path, std::fstream::out);
	file.close();
}

bool B_Tree::contains(const char* key) const
{
	return root.contains(key);
}

void B_Tree::insert(const Article& article)
{
	if (!root.is_full())
	{
		root.insert_non_full(article);
		return;
	}

	std::array<Article, NODE_CAPACITY + 1> helperArray = make_helper_array(article);
	split_root(helperArray);
}

void B_Tree::split_root(const std::array<Article, NODE_CAPACITY + 1>& helperArray)
{// NOW ITS TIME TO GET FUNKY
	root.children[0] = new Node();
	root.children[1] = new Node();

	// Primeiro elemento vai da subarvore esquerda, segundo fica com a gente, terceiro e quarto vao pra direita
	root.children[0]->insert_non_full(helperArray[0]);
	root.children[1]->insert_non_full(helperArray[2]);
	root.children[1]->insert_non_full(helperArray[3]);

	root.keys[0] = helperArray[1];
	root.n = 1;
}

std::array<Article, NODE_CAPACITY + 1> B_Tree::make_helper_array(const Article& article)
{
	std::array<Article, NODE_CAPACITY + 1> helperArray;

	// Copia elementos
	for (int i = 0; i < NODE_CAPACITY; ++i)
		helperArray[i] = root.keys[i];

	*(helperArray.rbegin()) = article;
	std::sort(helperArray.begin(), helperArray.end(), Article::compare_article);
	return helperArray;
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

void B_Tree::remove(const char* const key)
{
	root.remove(key);
}
