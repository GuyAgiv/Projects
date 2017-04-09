#pragma once

#include "stdafx.h"

// abstract class
class Map{

public:

	Map(){};
	virtual ~Map(){};

	virtual void setMap() = 0;
	virtual CBitmap* getMap() const = 0;

	virtual CBitmap* get_thumbs() const = 0;
	virtual void set_thumbs() = 0;

	virtual void setTimeLimit(const int& time) = 0;
	virtual int getTimeLimit() const = 0;

	virtual void setClicks(const int& clicks) = 0;
	virtual int getClicks() const = 0;

	virtual CBitmap* get_single_thumb(int) const = 0;
	
protected:
	int time;
	int clicks;
	CBitmap *thumbs;
	CBitmap *map;
};