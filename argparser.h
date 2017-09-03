/* 
   Author:
     Igor Tyukalov tyukalov@bk.ru
 
   Copyright (c) 2017, sp_r00t
 
   All rights reserved.
 
   Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 
      * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
      * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in
        the documentation and/or other materials provided with the distribution.
      * Neither the name of the [ORGANIZATION] nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/ 

#define MAX_OPTION_SIZE		0x100
#define SPACE			'\n'
#define TRUE			0x1
#define FALSE			0x0
#define ILLEGAL_USE_OPTIONS	-0x1000
#define MISSING_VALUE		-0x2000
typedef struct {
	char		prefix;
	char		separator;
	int		argc;
	char		**argv;
}ARGPARSE_ARG;

typedef struct {
	char		*options;
	union{
		char	*value;
		int	flag;
	};
} OPTIONS, *RETOPT;


int argparse(ARGPARSE_ARG, RETOPT, int);
