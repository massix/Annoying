//
//  scissor.cpp
//  Annoying
//
//  Created by Massimo Gengarelli on 20/2/12.
//

#include "scissor.h"

scissor::scissor ()
{
	
}

scissor::~scissor ()
{
	
}

char scissor::id () const
{
	return 'S';
}

bool scissor::beats (const move &other) const
{
	switch (other.id ())
	{
		case 'L': return true; break;
		case 'K': return false; break;
		case 'R': return false; break;
		case 'S': return false; break;
		case 'P': return true; break;
		default: return false; break;
	}
	
	return false;
}

bool scissor::gets_beaten (const move &other) const
{
	switch (other.id ())
	{
		case 'L': return false; break;
		case 'K': return true; break;
		case 'R': return true; break;
		case 'S': return false; break;
		case 'P': return false; break;
		default: return false; break;
	}
	
	return false;
}

bool scissor::equals(const move &other) const
{
	return (other.id () == this->id ());
}

bool scissor::operator<(const move &other) const
{
	return this->gets_beaten(other);
}

bool scissor::operator>(const move &other) const
{
	return this->beats(other);
}

bool scissor::operator==(const move &other) const
{
	return this->equals(other);
}
