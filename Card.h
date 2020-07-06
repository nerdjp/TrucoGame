#pragma once

struct Card {
	int id;
	int naipe;
	int player;

	bool operator==(Card& rhs) { return id == rhs.id; };
	bool operator!=(Card& rhs) { return id != rhs.id; };
	bool operator<(Card& rhs) { return id < rhs.id; };
	bool operator>(Card& rhs) { return id > rhs.id; };
	Card operator=(Card& rhs) { id = rhs.id; naipe = rhs.naipe; player = rhs.player; return *this; };

};