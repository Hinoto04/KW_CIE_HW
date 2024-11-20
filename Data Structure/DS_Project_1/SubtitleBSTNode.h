#pragma once
#include "Subtitle.h"
#include <iostream>
#include <iomanip>

class SubtitleBSTNode
{
private:

	SubtitleBSTNode*	left;
	SubtitleBSTNode*	right;

public:
	Subtitle sub;

	SubtitleBSTNode(Subtitle s) : left(nullptr), right(nullptr) {
		this->sub = s;
	}
	~SubtitleBSTNode() {}

	void print(ostream& os) { //Recursive In-Order Print
		if(!this->left) this->left->print(os);
		os << setfill('0');
        os << setw(2) << this->sub.h << ':';
        os << setw(2) << this->sub.m << ':';
        os << setw(2) << this->sub.s << " - ";
		os << this->sub.str << endl;
	}

	SubtitleBSTNode*	getLeft()				{ return left; }
	SubtitleBSTNode*	getRight()				{ return right; }

	void setLeft(SubtitleBSTNode* left)		{ this->left = left; }
	void setRight(SubtitleBSTNode* right)	{ this->right = right; }
};
