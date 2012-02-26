//
//  paper.h
//  Annoying
//
//  Created by Massimo Gengarelli on 20/2/12.
//

#ifndef Annoying_paper_h
#define Annoying_paper_h

#include "move.h"

class rock;
class scissor;

class paper : public move
{
protected:
	virtual bool beats (const move& other) const;
	virtual bool gets_beaten (const move& other) const;
	virtual bool equals (const move& other) const;
	
public:
	paper ();
	virtual ~paper ();
	
	virtual bool operator> (const move& other) const;
	virtual bool operator< (const move& other) const;
	virtual bool operator== (const move& other) const;
	virtual char id () const;

};

#endif
