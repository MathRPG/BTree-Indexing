#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "BTree.h"
#include "Article.h"

TEST_SUITE("BTree")
{
	TEST_CASE("Empty tree")
	{
		SUBCASE("contains returns false")
		{
			BTree empty_tree = BTree();
			CHECK_UNARY_FALSE(empty_tree.contains("Whatever key"));
		}
	}

	TEST_CASE("Insertion")
	{
		SUBCASE("1 key: search returns true only for inserted key")
		{
			BTree tree = BTree();
			const char* key = "DOI";
			tree.insert(Article(key, "Title", "Author", 2000));
			CHECK(tree.contains(key));
			CHECK_UNARY_FALSE(tree.contains("Other_DOI"));
		}

		SUBCASE("2 keys")
		{
			BTree tree = BTree();
			const char* key_one = "DOI";
			tree.insert(Article(key_one, "Title", "Author", 2000));
			const char* key_two = "Other_DOI";
			tree.insert(Article(key_two, "Other_Title", "Other_Author", 2001));
			CHECK(tree.contains(key_one));
			CHECK(tree.contains(key_two));
		}

		SUBCASE("Filling the root")
		{
			BTree tree = BTree();
			for (int i = 0; i < (2 * NODE_T - 1); ++i)
				tree.insert(Article(std::to_string(i), "", "", 0));

			for (int i = 0; i < (2 * NODE_T - 1); ++i)
				CHECK(tree.contains(std::to_string(i)));
		}

		SUBCASE("One more than the root can take")
		{
			BTree tree = BTree();
			unsigned quantity = 2 * NODE_T;
			for (int i = 0; i < quantity; ++i)
				tree.insert(Article(std::to_string(i), "", "", i));
			for (int i = 0; i < quantity; ++i)
				CHECK(tree.contains(std::to_string(i)));
		}

		SUBCASE("Many many articles")
		{
			BTree tree = BTree();
			unsigned quantity = 1000;
			for (int i = 0; i < quantity; ++i)
				tree.insert(Article(std::to_string(i), "", "", i));
			for (int i = 0; i < quantity; ++i)
				CHECK(tree.contains(std::to_string(i)));
		}
	}
}
