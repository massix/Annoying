//
//  move.h
//  Annoying
//
//  Created by Massimo Gengarelli on 20/2/12.
//

#ifndef Annoying_move_h
#define Annoying_move_h

class move
{
protected:
	virtual bool beats (const move& other) const = 0;
	virtual bool gets_beaten (const move& other) const = 0;
	virtual bool equals (const move& other) const = 0;
	
public:
	virtual ~move () {};
	
	virtual bool operator> (const move& other) const = 0;
	virtual bool operator< (const move& other) const = 0;
	virtual bool operator== (const move& other) const = 0;
	
	virtual char id () const = 0;
};

#endif
