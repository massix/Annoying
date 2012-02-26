//
//  rock.cpp
//  Annoying
//
//  Created by Massimo Gengarelli on 20/2/12.
//

#include "rock.h"

rock::rock ()
{
	
}

rock::~rock ()
{
	
}

char rock::id () const
{
	return 'R';
}

bool rock::beats (const move &other) const
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

bool rock::gets_beaten (const move &other) const
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

bool rock::equals(const move &other) const
{
	return (other.id () == this->id ());
}

bool rock::operator<(const move &other) const
{
	return this->gets_beaten(other);
}

bool rock::operator>(const move &other) const
{
	return this->beats(other);
}

bool rock::operator==(const move &other) const
{
	return this->equals(other);
}
