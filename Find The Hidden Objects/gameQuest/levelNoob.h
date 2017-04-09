#pragma once

#include "stdafx.h"
#include "abstractMap.h"
#include "resource.h"

class levelNoob : public Map
{
public:
	// Constructor & Destructor

	levelNoob(int clicks=0, int time=0);
	~levelNoob(){};

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

levelNoob::levelNoob(int clicks, int time){
	this->time = time;
	this->clicks = clicks;
	setMap();
	set_thumbs();
}

// methods implementations ----------------------------- 

void levelNoob::setMap() {
	map = new CBitmap();
	map->LoadBitmapW(IDB_MAP1);
}

//------------------------------------------------------

CBitmap* levelNoob::getMap() const {
	return this->map;
}

// -----------------------------------------------------

void levelNoob::setTimeLimit(const int& time) {
	this->time = time;
}

// -----------------------------------------------------

int levelNoob::getTimeLimit() const {
	return this->time;
}

// -----------------------------------------------------

void levelNoob::set_thumbs() {
	thumbs = new CBitmap[5];
	
	thumbs[0].LoadBitmapW(IDB_IMAP1);
	thumbs[1].LoadBitmapW(IDB_IMAP2);
	thumbs[2].LoadBitmapW(IDB_IMAP3);
	thumbs[3].LoadBitmapW(IDB_IMAP4);
	thumbs[4].LoadBitmapW(IDB_IMAP5);
}

// -----------------------------------------------------

CBitmap* levelNoob::get_thumbs() const {
	return thumbs;
}

// -----------------------------------------------------

CBitmap* levelNoob::get_single_thumb(int th) const {
	return &thumbs[th];
}

// -----------------------------------------------------

void levelNoob::setClicks(const int& clicks){
	this->clicks = clicks;
};

// -----------------------------------------------------

int levelNoob::getClicks() const {
	return this->clicks;
};
