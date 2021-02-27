#include "B_Tree.h"

#include <fstream>

B_Tree::B_Tree(filename_t index_path, filename_t registry_path)
{
	std::fstream file(index_path, std::fstream::out);
	file.close();
	file.open(registry_path, std::fstream::out);
	file.close();
}

bool B_Tree::contains(const char* key)
{
	for (auto article : this->all_articles)
		if (article.has_primary_key(key))
			return true;
	return false;
}

void B_Tree::insert(Article& article)
{
	this->all_articles.push_back(article);
}

void B_Tree::remove_key(const char* const key)
{
	this->all_articles.pop_back();
}
