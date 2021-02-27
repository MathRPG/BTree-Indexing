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
	if (root.is_not_full())
	{
		root.insert_non_full(article);
	}
	else
	{
		// Cria um array de tamanho n+1
		std::array<Article, NODE_CAPACITY + 1> helperArray;

		// Copia elementos
		for (int i = 0; i < NODE_CAPACITY; ++i)
			helperArray[i] = root.keys[i];

		// Insere o artigo e ordena nessa array
		*(helperArray.rbegin()) = article;
		std::sort(helperArray.begin(), helperArray.end(), Article::compare_article);

		// NOW ITS TIME TO GET FUNKY
		root.children[0] = new Node();
		root.children[1] = new Node();

		// Primeiro elemento vai da subarvore esquerda, segundo fica com a gente, terceiro e quarto vao pra direita
		root.children[0]->insert_non_full(helperArray[0]);
		root.children[1]->insert_non_full(helperArray[2]);
		root.children[1]->insert_non_full(helperArray[3]);

		root.keys[0] = helperArray[1];
		root.n = 1;
	}
}

void B_Tree::remove(const char* const key)
{
	root.remove(key);
}
