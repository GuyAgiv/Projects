#pragma once

#include "stdafx.h"
#include "abstractMap.h"
#include "resource.h"

class levelPro : public Map
{
public:
	// Constructor & Destructor

	levelPro(int clicks=0, int time=0);
	~levelPro(){};

	// Setters & Getters 
	void setMap();
	CBitmap* getMap() const;

	void setTimeLimit(const int& time);
	int getTimeLimit() const;

	void set_thumbs();
	CBitmap* get_thumbs() const;

	void setClicks(const int& clicks);
	int getClicks() const;

	CBitmap* get_single_thumb(int) const;

};
//Constaructor -----------------------------------------

levelPro::levelPro(int clicks, int time){
	this->time = time;
	this->clicks = clicks;
	setMap();
	set_thumbs();
}

// methods implementations ----------------------------- 

void levelPro::setMap() {
	map = new CBitmap();
	map->LoadBitmapW(IDB_MAP2);
}

//------------------------------------------------------

CBitmap* levelPro::getMap() const {
	return this->map;
}

// -----------------------------------------------------

void levelPro::setTimeLimit(const int& time) {
	this->time = time;
}

// -----------------------------------------------------

int levelPro::getTimeLimit() const {
	return this->time;
}

// -----------------------------------------------------

void levelPro::set_thumbs() {
	thumbs = new CBitmap[5];
	
	thumbs[0].LoadBitmapW(IDB_IMAP_2_1);
	thumbs[1].LoadBitmapW(IDB_IMAP_2_2);
	thumbs[2].LoadBitmapW(IDB_IMAP_2_3);
	thumbs[3].LoadBitmapW(IDB_IMAP_2_4);
	thumbs[4].LoadBitmapW(IDB_IMAP_2_5);
}

// -----------------------------------------------------

CBitmap* levelPro::get_thumbs() const {
	return thumbs;
}

// -----------------------------------------------------

CBitmap* levelPro::get_single_thumb(int th) const {
	return &thumbs[th];
}

// -----------------------------------------------------

void levelPro::setClicks(const int& clicks){
	this->clicks = clicks;
};

// -----------------------------------------------------

int levelPro::getClicks() const {
	return this->clicks;
};

