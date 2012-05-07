/*
 * ptr.h
 *****************************************************************************
 * Copyright (C) 2011 - 2013 Alpen-Adria-Universität Klagenfurt
 *
 * Created on: April 9, 2011
 * Authors: Benjamin Rainer <benjamin.rainer@itec.aau.at>
 *
 * This file is part of ambientLib.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#ifndef _PTR_H_
#define _PTR_H_

class smartPointerException
{

};

class smartPointerRefCountException : public smartPointerException
{


};

class smartPointerNULLPointerException : public smartPointerException
{

};

template<class T> class scoped_ptr
{
private:
	T *pn;
public:
	scoped_ptr() : pn(0) {};
	~scoped_ptr() {
		delete pn;
	}
	template<class Y> explicit scoped_ptr(Y *in)
	{
		pn = (T *) in;
	};
	
	T *operator->()
	{
		return pn;
	};

	T *get_pointer()
	{
		return pn;
	};

	scoped_ptr & operator=(scoped_ptr &p)
	{
		this->pn = p.get_pointer();
		return *this;
	};

	scoped_ptr & operator=(T *p)
	{
		this->pn = p;
		return *this;
	};

	T operator*()
	{
		return *this->pn;
	};
};


template<class T> class ptr
{
private:

	T *pn;
	unsigned int count;
public:

	ptr() : pn(0), count(0){

	};
	~ptr() {

		//if(count > 0) throw smartPointerRefCountException();
		// what happens when we are deleted and there still remains a pointer to an object ...
		// this can be handled the strict way of throwing an exception or we are very kindly 
	}

	template<class Y>  explicit ptr(Y *in){	
	 if(in == NULL) throw smartPointerNULLPointerException();	
	 pn = (T *)in;	
	};

	T *operator ->() {
		return pn;
	};

	T *get_pointer(){

		return pn;
	};

	ptr & operator=(ptr &p){
		
		this->pn = p.get_pointer();
		return *this;
	};

	ptr & operator=(T *p){

		this->pn = p;
		return *this;
	};

	T operator*(){

		return *this->pn;
	};

	void addRef() { ++count;}

	void decRef() { if (count > 0) --count; else throw smartPointerRefCountException(); }

	void release() { 
		if (pn == NULL) throw smartPointerNULLPointerException(); else delete pn;}

	void unbind() { if (pn == NULL) throw smartPointerNULLPointerException(); else pn = NULL; }
	
};

#endif