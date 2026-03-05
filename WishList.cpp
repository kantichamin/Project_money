#include "WishList.h"

WishList::WishList(const wxString& w, double a, int acindex, double currentam) 
	: wish(w), amount(a), accountindex(acindex), currentAmount(currentam) {
	
}

void WishList::Addw(double money) {
	amount += money;
}