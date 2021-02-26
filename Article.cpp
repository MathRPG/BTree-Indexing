#include <cstring>
#include <fstream>
#include "Article.h"

Article::Article() = default;

Article::Article(const char* doi, const char* name, const char* author, unsigned int year)
{
	strncpy(this->doi, doi, MAX_DOI_LEN);
	strncpy(this->name, name, MAX_NAME_LEN);
	strncpy(this->author, author, MAX_AUTHOR_LEN);
	this->year = year;
}

size_t Article::writing_size()
{
	return sizeof(doi);
}

bool Article::has_primary_key(const char* other_doi)
{
	return strncmp(this->doi, other_doi, MAX_DOI_LEN) == EQUAL_STRINGS;
}

bool Article::is_identical(Article& other)
{
	if (!this->has_primary_key(other.doi))
		return false;
	if (strncmp(this->name, other.name, MAX_NAME_LEN) != EQUAL_STRINGS)
		return false;
	if (strncmp(this->author, other.author, MAX_AUTHOR_LEN) != EQUAL_STRINGS)
		return false;
	if (this->year != other.year)
		return false;
	return true;
}

void Article::write(std::fstream& out)
{
	out.write(this->doi, MAX_DOI_LEN);
}

std::fstream& operator<<(std::fstream& out, Article& article)
{
	article.write(out);
	return out;
}

void Article::read(std::fstream& in)
{
	in.read(this->doi, MAX_DOI_LEN);
}
void operator>>(std::fstream& in, Article& article)
{
	article.read(in);
}
