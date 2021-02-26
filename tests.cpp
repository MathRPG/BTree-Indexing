#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <filesystem>
#include "doctest.h"
#include "Article.h"
#include "B_Tree.h"

TEST_SUITE("Article")
{
	static const char* const some_doi = "Doi";
	static const char* const some_name = "Name";
	static const char* const some_author = "Author";
	static const unsigned some_year = 2000u;
	Article some_article(some_doi, some_name, some_author, some_year);

	static const char* const other_doi = "Other-Doi";
	static const char* other_name = "Other-Name";
	static const char* other_author = "Other-Author";
	static const unsigned other_year = 2001u;

	TEST_CASE("should compare its primary key with others")
	{
		CHECK(some_article.has_primary_key(some_doi));
		CHECK_FALSE(some_article.has_primary_key(other_doi));
	}

	TEST_CASE("should compare if it is identical to other articles")
	{
		SUBCASE("it returns false if DOIs are different")
		{
			Article some_article_different_doi(other_doi, some_name, some_author, some_year);
			CHECK_EQ(some_article == some_article_different_doi, false);
		}

		SUBCASE("it returns false if Names are different")
		{
			Article some_article_different_name(some_doi, other_name, some_author, some_year);
			CHECK_EQ(some_article == some_article_different_name, false);
		}

		SUBCASE("it returns false if Authors are different")
		{
			Article some_article_different_author(some_doi, some_name, other_author, some_year);
			CHECK_EQ(some_article == some_article_different_author, false);
		}

		SUBCASE("it returns false if Years are different")
		{
			Article some_article_different_year(some_doi, some_name, some_author, other_year);
			CHECK_EQ(some_article == some_article_different_year, false);
		}

		SUBCASE("it returns true if all fields are equal")
		{
			Article some_article_identical(some_doi, some_name, some_author, some_year);
			CHECK_EQ(some_article == some_article_identical, true);
		}
	}

	TEST_CASE("should write and read from files")
	{
		std::fstream file("testfile.txt", std::fstream::in | std::fstream::out);
		file << some_article;

		file.seekp(0);
		Article other_article;
		file >> other_article;

		SUBCASE("writes to file infile_size bytes")
		{
			CHECK(file.tellg() == some_article.infile_size());
		}

		SUBCASE("read from file infile_size bytes")
		{
			CHECK(file.tellp() == some_article.infile_size());
		}

		SUBCASE("data written in file is readable")
		{
			CHECK(some_article.is_identical(other_article));
		}

		file.close();
	}
}

TEST_SUITE("B-Tree")
{
	TEST_CASE("Is able to initialize B-tree")
	{
		B_Tree tree("index.txt", "registry.txt");
	}

	TEST_CASE("should create index file if it doesn't exist")
	{
		const char* nonexistent_filepath = "this_file_does_not_exist.txt";
		remove(nonexistent_filepath);

		B_Tree tree(nonexistent_filepath, "some_file.txt");

		CHECK(std::filesystem::exists(nonexistent_filepath));
		remove(nonexistent_filepath);
	}

	TEST_CASE("should create registry file if it doesn't exist")
	{
		const char* nonexistent_filepath = "this_file_does_not_exist.txt";
		remove(nonexistent_filepath);

		B_Tree tree("some_file.txt", nonexistent_filepath);

		CHECK(std::filesystem::exists(nonexistent_filepath));
		remove(nonexistent_filepath);
	}

//	TEST_CASE("should only close file when tree object is destructed")
}
