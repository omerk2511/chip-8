#pragma once

#include "types.h"

struct cpu
{
	union
	{
		struct
		{
			byte v0;
			byte v1;
			byte v2;
			byte v3;
			byte v4;
			byte v5;
			byte v6;
			byte v7;
			byte v8;
			byte v9;
			byte va;
			byte vb;
			byte vc;
			byte vd;
			byte ve;
			byte vf;
		};

		byte arr[16];
	} gp_regs;

	word i;

	byte dt;
	byte st;

	word pc;
};