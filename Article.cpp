#include <cstring>
#include <fstream>
#include "Article.h"

Article::Article() = default;

Article::Article(const char* doi, const std::string& name, const std::string& author, unsigned int year)
{
	strncpy(this->doi, doi, FIELD_MAX_STR_LEN);
}

size_t Article::size()
{
	return 3 * FIELD_MAX_STR_LEN + sizeof(unsigned);
}

bool Article::compare_key(const char* other_doi)
{
	return !strncmp(this->doi, other_doi, FIELD_MAX_STR_LEN);
}

void Article::write(std::fstream& out)
{
	out.write(this->doi, FIELD_MAX_STR_LEN);
}

std::fstream& operator<<(std::fstream& out, Article& article)
{
	article.write(out);
	return out;
}

void Article::read(std::fstream& in)
{
	in.read(this->doi, FIELD_MAX_STR_LEN);
}

void operator>>(std::fstream& in, Article& article)
{
	article.read(in);
}
