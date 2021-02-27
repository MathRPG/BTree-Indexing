#include "Node.h"

bool Node::contains(const char* key) const
{
	for (int i = 0; i < n; ++i)
		if (keys[i].has_primary_key(key))
			return true;
	return false;
}

void Node::insert(const Article& article)
{
	keys[n] = article;
	n++;
}

void Node::remove(const char* key)
{
	std::array<Article, 3> non_removed;

	int j = 0;
	for (auto& i : keys)
	{
		if (!i.has_primary_key(key))
		{
			non_removed[j] = i;
			j++;
		}
	}

	keys = non_removed;
}
