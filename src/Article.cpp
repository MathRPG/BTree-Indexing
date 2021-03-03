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
{
	this->doi = original.doi;
	this->title = original.title;
	this->author = original.author;
	this->year = original.year;
}

