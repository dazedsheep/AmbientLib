/*
 * cpuFeatures.cpp
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

#include "StdAfx.h"
#include "cpuFeatures.h"

using namespace AmbientLib::CPU;

cpuFeatures::cpuFeatures(void)
{
	
	// get the cpu capabilities
	// we will just get the cpuid with eax = 1, this will return us a list of features in edx

	unsigned int *regs = reg;
	reg[REG_EAX] = 1; // feature list
	reg[REG_EBX] = reg[REG_ECX] = reg[REG_EDX] = 0;

	__asm {

		push ebx
		push ecx
		push edx
		push edi

		mov edi, regs

		mov eax, [edi]
		mov ebx, [edi+4]
		mov ecx, [edi+8]
		mov edx, [edi+12]

		cpuid

		mov [edi], eax
		mov [edi+4], ebx
		mov [edi+8], ecx
		mov [edi+12], edx

		pop edi
		pop edx
		pop ecx
		pop ebx

	}

	

}

bool cpuFeatures::isFeatureSupported(unsigned int FEATURE){

	// the feature list is stored in the edx register

	if((reg[REG_EDX] & FEATURE) > 0) return true;
	else 
		return false;

}

cpuFeatures::~cpuFeatures(void)
{


}

