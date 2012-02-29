//
//  lizard.cpp
//  Annoying
//
//  Created by Massimo Gengarelli on 20/2/12.
//

#include "lizard.h"

lizard::lizard ()
{
	
}

lizard::~lizard ()
{
	
}

char lizard::id () const
{
	return 'L';
}

bool lizard::beats (const move &other) const
{
	switch (other.id ())
	{
		case 'L': return false; break;
		case 'K': return true; break;
		case 'R': return false; break;
		case 'S': return false; break;
		case 'P': return true; break;
		default: return false; break;
	}
	
	return false;
}

bool lizard::gets_beaten (const move &other) const
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

bool lizard::equals(const move &other) const
{
	return (other.id () == this->id ());
}

bool lizard::operator<(const move &other) const
{
	return this->gets_beaten(other);
}

bool lizard::operator>(const move &other) const
{
	return this->beats(other);
}

bool lizard::operator==(const move &other) const
{
	return this->equals(other);
}
