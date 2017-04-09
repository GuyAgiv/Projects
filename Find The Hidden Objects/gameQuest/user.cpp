#include "stdafx.h"
#include "user.h"
#include "gameQuestDlg.h"
#include "gameQuest.h"

IMPLEMENT_SERIAL(User,CObject,0)

User::User(CString name) {
	this->name = name;
	difficult= 1; 
	clicks= 0;
	itemFound = 0;
}

User::User(void) : clicks(0), itemFound(0), difficult(1), name(_T("")){}

User::~User(void){}

void User::setItemFound(int n){ 
	this->itemFound = n; 
}

int User::getItemFound() const { 
	return itemFound; 
}


void User::setDifficult(int n) { 
	difficult = n; 
}
int User::getDifficult() const { return difficult; }

void User::setClicks(int n) { clicks = n; }
int User::getClicks() const { return clicks; }

void User::setUser(CString name) { 
	this->name = name; 
}

CString User::getUser() const { return this->name; }

void User::Serialize(CArchive& ar){
	CObject::Serialize(ar);

	if(ar.IsStoring())
		ar << name << clicks  << difficult << itemFound;
	else
		ar >> name >> clicks >> difficult >> itemFound;
}
