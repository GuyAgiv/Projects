#pragma once
#include "stdafx.h"

class User : public CObject{
	
private:
	CString name;
	int clicks;
	int difficult;
	int itemFound;

public:
	User(void);

	~User(void);

	User(CString name);

	void setItemFound(int n);

	int getItemFound() const;


	void setDifficult(int n);
	int getDifficult() const;

	void setClicks(int n);
	int getClicks() const;

	void setUser(CString name);
	CString getUser() const;

	void Serialize(CArchive & ar);
	DECLARE_SERIAL(User);
};