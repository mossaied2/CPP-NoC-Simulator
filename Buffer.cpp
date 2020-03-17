/*
 * Noxim - the NoC Simulator
 * 
 * (C) 2005-2010 by the University of Catania
 * For the complete list of authors refer to file ../doc/AUTHORS.txt
 * For the license applied to these sources refer to file ../doc/LICENSE.txt
 *
 * This file contains the implementation of the buffer
 */

#include "Buffer.h"

Buffer::Buffer()
{
    SetMaxBufferSize(DEFAULT_BUFFER_DEPTH);
}

void Buffer::SetMaxBufferSize(unsigned int bms)
{
    assert(bms > 0);

    max_buffer_size = bms;
}

unsigned int Buffer::GetMaxBufferSize() const
{
    return max_buffer_size;
}

bool Buffer::IsFull() const
{
    return buffer.size() == max_buffer_size;
}

bool Buffer::IsEmpty() const
{
    return buffer.size() == 0;
}

void Buffer::Push(const Flit & flit)
{
    buffer.push_back(flit);
}

Flit Buffer::Pop()
{
    Flit f;
   
	f = buffer.front();
	buffer.pop_front();
    
    return f;
}

Flit Buffer::Head() const
{
    return buffer.front();
}

Flit Buffer::Tail() const
{
    return buffer.back();
}

unsigned int Buffer::Size() const
{
    return buffer.size();
}


unsigned int Buffer::getCurrentFreeSlots() const
{
    return (GetMaxBufferSize()-Size());
}

void Buffer::Clean()
{
	while( !buffer.empty() )
		buffer.pop_front();
}

Flit Buffer::getElement(const int index) {
    assert(!buffer.empty());
    return buffer[index];
}