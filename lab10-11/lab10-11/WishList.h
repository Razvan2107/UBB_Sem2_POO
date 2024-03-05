#pragma once
#include "Agentie_de_Turism.h"
#include "Observer.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using std::vector;
class WishList: public Observable
{
private:
	vector<Agentie_de_Turism> wishlist;
public:
	WishList() = default;

	/*
	Adauaga agentie in wishlist
	param a: agentie care se adauga (Agentie_de_Turism)

	post: agentie va fi adaugata in wishlist
	*/
	void addATWishList(const Agentie_de_Turism& s);

	/*
	Elimina toate agentiile din wishlist
	post: wishlist-ul este gol
	*/
	void emptyWishList();

	/*
	Adauga un numar random de agentii in wishlist

	param original: agentiile din care se alege (vector<Agentie_de_Turism)
	param nr: cate melodii se adauga (int)
	*/
	void addRandom(vector<Agentie_de_Turism> original, int nr);

	const vector<Agentie_de_Turism>& getAllWishList();
};