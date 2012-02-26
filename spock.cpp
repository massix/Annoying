//
//  spock.cpp
//  Annoying
//
//  Created by Massimo Gengarelli on 20/2/12.
//

#include "spock.h"

spock::spock ()
{
	
}

spock::~spock ()
{
	
}

char spock::id () const
{
	return 'R';
}

bool spock::beats (const move &other) const
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

bool spock::gets_beaten (const move &other) const
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

bool spock::equals(const move &other) const
{
	return (other.id () == this->id ());
}

bool spock::operator<(const move &other) const
{
	return this->gets_beaten(other);
}

bool spock::operator>(const move &other) const
{
	return this->beats(other);
}

bool spock::operator==(const move &other) const
{
	return this->equals(other);
}
