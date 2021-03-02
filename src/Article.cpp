#include <string>

#include "Article.h"

Article::Article(std::string doi, const char* title, const char* author, unsigned int year)
{
	this->doi = std::move(doi);
}

Article::Article(const Article& original)
= default;

bool Article::has_key(const std::string& key) const
{
	return this->doi == key;
}
