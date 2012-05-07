/*
 * cpuFeatures.h
 *****************************************************************************
 * Copyright (C) 2011 - 2013 Alpen-Adria-Universitšt Klagenfurt
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
#ifndef CPU_FEATURES_H_
#define CPU_FEATURES_H_


namespace AmbientLib {

namespace CPU{

#define REG_EAX		0
#define REG_EBX		1
#define REG_ECX		2
#define REG_EDX		3


class cpuFeatures
{
private:
	unsigned int reg[4];	// the four standard registers, 0=eax,1=ebx,2=ecx,3=edx

public:
	cpuFeatures(void);
	~cpuFeatures(void);

	bool isFeatureSupported(unsigned int FEATURE);
	
	// Features

	const static unsigned int CPU_FEATURE_FPU	=		1;
	const static unsigned int CPU_FEATURE_VME	=		(1<<1);
	const static unsigned int CPU_FEATURE_DE	=		(1<<2);
	const static unsigned int CPU_FEATURE_PSE	=		(1<<3);
	const static unsigned int CPU_FEATURE_TSC	=		(1<<4);
	const static unsigned int CPU_FEATURE_MSR	=		(1<<5);
	const static unsigned int CPU_FEATURE_PAE	=		(1<<6);
	const static unsigned int CPU_FEATURE_MCE	=		(1<<7);
	const static unsigned int CPU_FEATURE_CX8	=		(1<<8);
	const static unsigned int CPU_FEATURE_APIC	=		(1<<9);
	const static unsigned int CPU_FEATURE_SEP	=		(1<<11);
	const static unsigned int CPU_FEATURE_MTRR	=		(1<<12);
	const static unsigned int CPU_FEATURE_PGE	=		(1<<13);
	const static unsigned int CPU_FEATURE_MCA	=		(1<<14);
	const static unsigned int CPU_FEATURE_CMOV	=		(1<<15);
	const static unsigned int CPU_FEATURE_PAT	=		(1<<16);
	const static unsigned int CPU_FEATURE_PSE36	=		(1<<17);
	const static unsigned int CPU_FEATURE_PSN	=		(1<<18);
	const static unsigned int CPU_FEATURE_CLFL	=		(1<<19);
	const static unsigned int CPU_FEATURE_DTES	=		(1<<21);
	const static unsigned int CPU_FEATURE_ACPI	=		(1<<22);
	const static unsigned int CPU_FEATURE_MMX	=		(1<<23);
	const static unsigned int CPU_FEATURE_FXSR	=		(1<<24);
	const static unsigned int CPU_FEATURE_SSE	=		(1<<25);
	const static unsigned int CPU_FEATURE_SSE2	=		(1<<26);
	const static unsigned int CPU_FEATURE_SS	=		(1<<27);
	const static unsigned int CPU_FEATURE_HTT	=		(1<<28);
	const static unsigned int CPU_FEATURE_TM1	=		(1<<29);
	const static unsigned int CPU_FEATURE_PBE	=		(1<<31);

};
}
}
#endif