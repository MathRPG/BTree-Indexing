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

size_t Article::infile_size()
{
	return MAX_DOI_LEN + MAX_NAME_LEN + MAX_AUTHOR_LEN + sizeof(this->year);
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
	out.write(this->name, MAX_NAME_LEN);
	out.write(this->author, MAX_AUTHOR_LEN);
	out.write(reinterpret_cast<char*> (&this->year), sizeof(this->year));
}

std::fstream& operator<<(std::fstream& out, Article& article)
{
	article.write(out);
	return out;
}

void Article::read(std::fstream& in)
{
	in.read(this->doi, MAX_DOI_LEN);
	in.read(this->name, MAX_NAME_LEN);
	in.read(this->author, MAX_AUTHOR_LEN);
	in.read(reinterpret_cast<char*> (&this->year), sizeof(this->year));
}
void operator>>(std::fstream& in, Article& article)
{
	article.read(in);
}
