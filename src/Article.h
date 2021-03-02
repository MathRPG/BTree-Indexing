#ifndef B_TREE_INDEXING_ARTICLE_H
#define B_TREE_INDEXING_ARTICLE_H

#include <string>

class Article
{
public:
	Article(std::string doi, const char* title, const char* author, unsigned year);
	Article(Article const &original);
	bool has_key(const std::string& key) const;
	std::basic_string<char> doi;
};

#endif //B_TREE_INDEXING_ARTICLE_H
