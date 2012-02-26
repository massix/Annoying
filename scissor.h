//
//  scissor.h
//  Annoying
//
//  Created by Massimo Gengarelli on 20/2/12.
//

#ifndef Annoying_scissor_h
#define Annoying_scissor_h

#include "move.h"

class rock;
class paper;

class scissor : public move
{
protected:
	virtual bool beats (const move& other) const;
	virtual bool gets_beaten (const move& other) const;
	virtual bool equals (const move& other) const;
	
public:
	scissor ();
	virtual ~scissor ();
	
	virtual bool operator> (const move& other) const;
	virtual bool operator< (const move& other) const;
	virtual bool operator== (const move& other) const;
	virtual char id () const;
	
};

#endif
