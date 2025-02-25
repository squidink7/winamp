	/*
    LICENSE
    -------
	Copyright 2005 Nullsoft, Inc.
	All rights reserved.
	
	Redistribution and use in source and binary forms, with or without modification, 
	are permitted provided that the following conditions are met:
	
    * Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer. 
	
    * Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution. 
	
    * Neither the name of Nullsoft nor the names of its contributors may be used to 
endorse or promote products derived from this software without specific prior written permission. 
    
	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
	IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
	FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR 
	CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
	DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
	IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
	OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
	
	*/
	#ifdef LASER
	typedef struct
	{
    float x1, y1;
    float x2, y2;
    int color;
    int mode;
	} LineType;
	
	class C_LineListBase
	{
public:
C_LineListBase(){ };
virtual ~C_LineListBase() { };
	
virtual int GetMaxLines(void)=0;
virtual int GetUsedLines(void)=0;
virtual void SetMaxLines(int m)=0;
virtual void SetUsedLines(int usedlines)=0;
virtual void SetLines(LineType *list, int start, int length)=0;
virtual void ClearLineList(void)=0;
virtual LineType *GetLineList(void)=0;
virtual void AddLine(LineType *line)=0;
	};
	
	C_LineListBase *createLineList(void);
	extern C_LineListBase *g_laser_linelist;
	#endif