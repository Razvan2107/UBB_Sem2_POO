#include "WishList.h"
using std::shuffle;

void WishList::addATWishList(const Agentie_de_Turism& a)
{
	this->wishlist.push_back(a);
	notify();
}

void WishList::emptyWishList()
{
	this->wishlist.clear();
	notify();
}

void WishList::addRandom(vector<Agentie_de_Turism> original, int nr)
{
	shuffle(original.begin(), original.end(), std::default_random_engine(std::random_device{}()));
	while (wishlist.size() < nr && original.size() > 0)
	{
		wishlist.push_back(original.back());
		original.pop_back();
	}
	notify();
}

const vector<Agentie_de_Turism>& WishList::getAllWishList()
{
	return this->wishlist;
}