#include "Node.h"

Node::Node()
= default;

Node::~Node()
{
	for (int i = 0; i < item_count; ++i)
		delete items[i];

	if (is_leaf)
		return;

	for (int i = 0; i < item_count + 1; ++i)
		delete children[i];
}

bool Node::contains(const std::string& key)
{
	// TODO: optimize
	for (int i = 0; i < item_count; ++i)
		if (items[i]->has_key(key))
			return true;

	if (is_leaf)
		return false;

	for (int i = 0; i < item_count + 1; ++i)
		if (children[i]->contains(key))
			return true;

	return false;
}

void Node::insert_non_full(const Article& article)
{
	items[item_count++] = new Article(article);
}
