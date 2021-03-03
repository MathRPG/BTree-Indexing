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

Article::Article(std::fstream& f)
{
	std::getline(f, this->doi);
	std::getline(f, this->title);
	std::getline(f, this->author);
	std::string year_line;
	std::getline(f, year_line);
	this->year = atoi(year_line.c_str());
}

bool Article::operator==(const Article& other) const
{
	if (this->doi != other.doi)
		return false;
	if (this->title != other.title)
		return false;
	if (this->author != other.author)
		return false;
	if (this->year != other.year)
		return false;
	return true;
}

void operator<<(std::fstream& out, const Article& article)
{
	out << article.doi << '\n';
	out << article.title << '\n';
	out << article.author << '\n';
	out << article.year << '\n';
}
