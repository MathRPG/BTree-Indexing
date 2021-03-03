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
	return fetch(key) != nullptr;
}

Article* Node::fetch(const std::string& key)
{
	int i = 0;

	while (i < item_count and key > items[i]->doi)
		i++;

	if (i < item_count and key == items[i]->doi)
		return items[i];

	if (is_leaf)
		return nullptr;

	return children[i]->fetch(key);
}

void Node::insert_non_full(const Article& article)
{
	unsigned i = item_count;
	std::string k = article.doi;

	if (is_leaf)
	{
		while (i >= 1 && k < items[i - 1]->doi)
		{
			items[i + 1 - 1] = items[i - 1];
			i--;
		}

		items[i + 1 - 1] = new Article(article);
		item_count++;
	}
	else
	{
		while (i >= 1 and k < items[i - 1]->doi)
			i = i - 1;
		i = i + 1;
		if (children[i - 1]->item_count == (2 * 2) - 1)
		{
			split_child(i);
			if (k > items[i - 1]->doi)
				i = i + 1;
		}
		children[i - 1]->insert_non_full(article);
	}
}

void Node::split_child(unsigned int i)
{
	Node* z = new Node();
	Node* y = children[i - 1];

	z->is_leaf = y->is_leaf;
	z->item_count = NODE_T - 1;

	for (int j = 1; j <= NODE_T - 1; ++j)
		z->items[j - 1] = y->items[j + NODE_T - 1];

	if (!y->is_leaf)
		for (int j = 1; j <= NODE_T; ++j)
			z->children[j - 1] = y->children[j + NODE_T - 1];

	y->item_count = NODE_T - 1;

	for (unsigned j = item_count + 1; j >= i + 1; --j)
		children[j + 1 - 1] = children[j - 1];

	children[i - 1 + 1] = z;

	for (unsigned j = item_count; j >= i; --j)
		items[j + 1 - 1] = items[j - 1];

	items[i - 1] = y->items[NODE_T - 1];
	item_count++;
}
