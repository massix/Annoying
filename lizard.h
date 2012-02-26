//
//  lizard.h
//  Annoying
//
//  Created by Massimo Gengarelli on 20/2/12.
//

#ifndef Annoying_lizard_h
#define Annoying_lizard_h

#include "move.h"

class paper;
class scissor;

class lizard : public move
{
protected:
	virtual bool beats (const move& other) const;
	virtual bool gets_beaten (const move& other) const;
	virtual bool equals (const move& other) const;
	
public:
	lizard ();
	virtual ~lizard ();
	
	virtual bool operator> (const move& other) const;
	virtual bool operator< (const move& other) const;
	virtual bool operator== (const move& other) const;
	virtual char id () const;
	
};


#endif
