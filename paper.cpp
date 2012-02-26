//
//  paper.cpp
//  Annoying
//
//  Created by Massimo Gengarelli on 20/2/12.
//

#include "paper.h"

paper::paper ()
{
	
}

paper::~paper ()
{
	
}

char paper::id () const
{
	return 'P';
}

bool paper::beats (const move &other) const
{
	switch (other.id ())
	{
		case 'L': return false; break;
		case 'K': return false; break;
		case 'R': return true; break;
		case 'S': return true; break;
		case 'P': return false; break;
		default: return false; break;
	}
	
	return false;
}

bool paper::gets_beaten (const move &other) const
{
	switch (other.id ())
	{
		case 'L': return true; break;
		case 'K': return false; break;
		case 'R': return false; break;
		case 'S': return true; break;
		case 'P': return false; break;
		default: return false; break;
	}
	
	return false;
}

bool paper::equals(const move &other) const
{
	return (other.id () == this->id ());
}

bool paper::operator<(const move &other) const
{
	return this->gets_beaten(other);
}

bool paper::operator>(const move &other) const
{
	return this->beats(other);
}

bool paper::operator==(const move &other) const
{
	return this->equals(other);
}
