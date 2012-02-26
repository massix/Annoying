//
//  rock.h
//  Annoying
//
//  Created by Massimo Gengarelli on 20/2/12.
//

#ifndef Annoying_rock_h
#define Annoying_rock_h

#include "move.h"

class paper;
class scissor;

class rock : public move
{
protected:
	virtual bool beats (const move& other) const;
	virtual bool gets_beaten (const move& other) const;
	virtual bool equals (const move& other) const;
	
public:
	rock ();
	virtual ~rock ();
	
	virtual bool operator> (const move& other) const;
	virtual bool operator< (const move& other) const;
	virtual bool operator== (const move& other) const;
	virtual char id () const;

};

#endif
