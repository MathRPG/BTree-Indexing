#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Article.h"

static const unsigned some_year = 2000u;
static const char* const some_doi = "Doi";

Article some_article(some_doi, "", "", some_year);

TEST_CASE("Article should compare primary key")
{
	CHECK(some_article.compare_key(some_doi));

	static const char* const different_doi = "Different_Doi";
	CHECK(!some_article.compare_key(different_doi));
}

TEST_CASE("Article should write and read contents from file")
{
	std::fstream file("testfile.txt", std::fstream::app | std::fstream::in | std::fstream::out);
	file << some_article;
	file.seekg(0);

	Article read_article;
	file >> read_article;

	CHECK(read_article.compare_key(some_doi));
}

TEST_CASE("Article should give its writing size")
{
	const auto EXPECTED_SIZE = 196u;
	CHECK(some_article.size() == EXPECTED_SIZE);
}
