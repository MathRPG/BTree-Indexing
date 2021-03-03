#include <string>

#include "Article.h"

Article::Article(std::string doi, std::string title, std::string author, unsigned int year)
{
	this->doi = std::move(doi);
	this->title = std::move(title);
	this->author = std::move(author);
	this->year = year;
}

Article::Article(const Article& original)
= default;

bool Article::has_key(const std::string& key) const
{
	return this->doi == key;
}
