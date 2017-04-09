#pragma once

#include "stdafx.h"
#include "abstractMap.h"

class Map1: public Map
{
public:
	// Constructor & Destructor

	Map1();
	virtual ~Map1();

	// Setters & Getters 

	int getDifficult() const
	{
		return this->difficult;
	}

	void setDifficult(const int& dif)
	{
		this->difficult = dif;
	}
	
	CBitmap getMap() const
	{
		return this->map_name;
	}

	void setMap(const CBitmap& name)
	{
		this->map_name = name;
	}

	void setTimeLimit(const int& time)
	{
		this->time = time;
	}

	int getTimeLimit() const
	{
		return this->time;
	}

	void setNum_of_items(const int& items)
	{
		this->num_of_items = items;
	}

	int getNum_of_items() const
	{
		return this->num_of_items;
	}
};