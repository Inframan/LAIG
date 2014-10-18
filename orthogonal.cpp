#include "orthogonal.h"


orthogonal::orthogonal(string id, char direction,float near,float far,float left,float right,float top,float bottom ):camera(id,near,far)
{
	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
	this->direction = direction;
	setType("ortho");
}


float orthogonal::getLeft()const
{
	return left;
}

float orthogonal::getRight()const
{
	return right;
}

float orthogonal::getTop()const
{
	return top;
}


float orthogonal::gotBot()const
{
	return bottom;
}


char orthogonal::getDirection()const
{
	return direction;
}

orthogonal::~orthogonal(void)
{
}
