#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <utility>
#include <vector>
#include <string>

#include "domino.h"
#include "table.h"

using namespace std;

class Player
{
private:
	vector<shared_ptr<Domino>> hand;
	string m_name;
	bool m_isBlocked;

public:
	Player(string name)
		: hand(), m_name(name), m_isBlocked(false)
	{}

	~Player() {}


	void draw(Table* table)
	{
		shared_ptr<Domino> dom = table->draw();
		hand.push_back(dom);
	}


	void draw(Table* table, int amount)
	{
		for(int i = 0; i < amount; ++i)
		{
			draw(table);
		}
	}


	void playTurn(Table* table)
	{
		m_isBlocked = false;

		for(size_t i = 0; i < hand.size(); ++i)
		{
			shared_ptr<Domino> dom(hand[i]); 
			if(table->playPiece(dom))
			{
				hand.erase(hand.begin()+i);
				return;
			}
		}

		// Otherwise, draw until a piece is playable
		while(true)
		{
			shared_ptr<Domino> dom = table->draw();
			if(dom == nullptr)
			{
				m_isBlocked = true;
				return;
			}

			if (table->playPiece(dom))
				return;
			else
				hand.push_back(dom);
		}
	}

	shared_ptr<Domino> takeRandom()
	{
		std::srand(std::time(nullptr));
		int domIndex = std::rand() % (hand.size() - 1);
		
		shared_ptr<Domino> dom(hand.at(domIndex));
		hand.erase(hand.begin() + domIndex);
		
		return dom;
	}


	bool handEmpty()
	{
		return hand.empty();
	}

	bool isBlocked()
	{
		return m_isBlocked;
	}

	string getName()
	{
		return m_name;
	}

	void printHand()
	{
		for (auto& dom : hand)
			cout << "[" << dom->getTail() << "|" << dom->getHead() << "] ";
		cout << endl;
	}
};

#endif /* PLAYER_H */