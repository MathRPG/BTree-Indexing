#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Article.h"

static const unsigned some_year = 2000u;
static const char* const some_doi = "Doi";

Article some_article(some_doi, "Name", "Author", some_year);

TEST_CASE("Article should be able to compare primary key")
{
	CHECK(some_article.compare_key(some_doi));

	static const char* const different_doi = "Different_Doi";
	CHECK(!some_article.compare_key(different_doi));
}

TEST_CASE("Article should write to file")
{
	std::ofstream file("testfile.txt", std::fstream::app | std::fstream::in);
//	some_article.dump(file);
//	file.close();
}
