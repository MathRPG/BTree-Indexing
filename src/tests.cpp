#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Article.h"
#include "BTree.h"

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

		SUBCASE("Insertion of same key twice replaces old values")
		{
			BTree tree = BTree();
			Article v1 = Article("DOI", "Title1", "Author1", 2000);
			Article v2 = Article("DOI", "Title2", "Author2", 2001);
			tree.insert(v1);
			tree.insert(v2);
			const Article* fetched = tree.fetch("DOI");
			CHECK_UNARY(*fetched == v2);
		}

		SUBCASE("Removing a key makes it fail contains")
		{
			BTree tree = BTree();
			std::string key = "DOI";
			tree.insert(Article(key, "", "", 0));
			tree.remove(key);
			CHECK_UNARY_FALSE(tree.contains(key));
		}

		SUBCASE("Article removed and inserted back exists")
		{
			BTree tree = BTree();
			std::string key = "DOI";
			Article a = Article(key, "", "", 0);
			tree.insert(a);
			tree.remove(key);
			tree.insert(a);
			CHECK_UNARY(tree.contains(key));
		}

		SUBCASE("Removing key that tree doesn't have does nothing")
		{
			BTree tree = BTree();
			const char* key = "DOI";
			Article a = Article(key, "", "", 0);
			tree.insert(a);
			tree.remove("Other_DOI");
			CHECK_UNARY(*tree.fetch(key) == a);
		}

		SUBCASE("Tree with zero articles saves correctly")
		{
			BTree tree = BTree();
			const char* file_name = "BTreeEmpty.txt";
			std::fstream f_write(file_name, std::fstream::out);

			tree.dump(f_write);
			f_write.close();

			std::fstream f_read(file_name, std::fstream::in);
			BTree read_tree(f_read);

			CHECK_UNARY_FALSE(read_tree.contains("Any_key"));
			CHECK_UNARY_FALSE(read_tree.contains(""));
		}

		SUBCASE("Tree with one article saves correctly")
		{
			BTree tree = BTree();
			const char* key = "DOI";
			Article a = Article(key, "Title", "Author", 2000);
			const char* file_name = "BTree.txt";
			std::fstream f_write(file_name, std::fstream::out);

			tree.insert(a);
			tree.dump(f_write);
			f_write.close();

			std::fstream f_read(file_name, std::fstream::in);
			BTree read_tree(f_read);

			CHECK_UNARY(read_tree.contains(key));
		}

		SUBCASE("Tree with many articles saves correctly")
		{
			BTree tree = BTree();
			const char* file_name = "BTreeMany.txt";
			std::fstream f_write(file_name, std::fstream::out);

			const int quantity = 10;
			for (int i = 0; i < quantity; ++i)
				tree.insert(Article(std::to_string(i), "t", "a", 0));
			tree.dump(f_write);
			f_write.close();

			std::fstream f_read(file_name, std::fstream::in);
			BTree read_tree(f_read);

			for (int i = 0; i < quantity; ++i)
				CHECK_UNARY(read_tree.contains(std::to_string(i)));
		}
	}
}
