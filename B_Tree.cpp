#include "B_Tree.h"

#include <fstream>

B_Tree::B_Tree(filename_t index_path, filename_t registry_path)
{
	std::fstream file(index_path, std::fstream::out);
	file.close();
	file.open(registry_path, std::fstream::out);
	file.close();
}

bool B_Tree::contains(const char* key) const
{
//	for (auto article : this->all_articles)
//		if (article.has_primary_key(key))
//			return true;
//	return false;
	return this->root.contains(key);
}

void B_Tree::insert(const Article& article)
{
//	this->all_articles.push_back(article);
	this->root.insert(article);
}

void B_Tree::remove(const char* const key)
{
//	this->all_articles.pop_back();
//	std::vector<Article> copy_all_articles(this->all_articles);
//	this->all_articles.clear();
//	for (auto article: copy_all_articles)
//		if (!article.has_primary_key(key))
//			this->all_articles.push_back(article);
	this->root.remove(key);
}
