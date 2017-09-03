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
#include <stdio.h>
#include "argparser.h"
#include <string.h>

//#define DEB

static void transpose(RETOPT, RETOPT);
static int FindOption(RETOPT, char*, int);

static void transpose(RETOPT x, RETOPT y)
{
	if(x!=y)
	{
#ifdef DEB
		printf("Bylo x %s\n", x->options);
		printf("Bylo y %s\n", y->options);
#endif
		OPTIONS var 	= *x;
		x->value	= y->value;
		x->options	= y->options;
		y->value	= var.value;
		y->options	= var.options;
#ifdef DEB
		printf("Stalo x %s\n", x->options);
		printf("Stalo y %s\n", y->options);
#endif
	}
}

static int FindOption(RETOPT ptrn, char *opt, int len)
{
	int  result = 0;
	OPTIONS var;
	for(; result < len; result++)
	{
		var = ptrn[result];
		if(!strcmp(var.options, opt)) return result;
	}
	return -1;
}

int argparse(ARGPARSE_ARG args, RETOPT ptrn, int len)
{
	char	*popt, *varval, buf[MAX_OPTION_SIZE];
	int	gonumber, pbuf, count, result = 0;
#ifdef DEB
					printf("%s\n", args.argv[1]);
#endif
	for(count=1; count < args.argc; count++)
	{
		if(result == len) return result;
		if(*(args.argv[count]) == args.prefix)
		{
			popt = args.argv[count] + 1;
			if(args.separator == SPACE)
			{
				varval = args.argv[count+1];
				strcpy(buf, popt);
			}
			else
			{
				if(varval=strchr(popt, (int)args.separator))
				{
					strncpy(buf, popt, (varval - popt));
					buf[varval-popt] = 0;			/* Завершающий ноль */
					varval++;				/* Вырезаем символ разделителя */
				}
				else
				{
					strcpy(buf, popt);
#ifdef DEB
					printf("%s\n", popt);
#endif
				}
			}								/* TODO Отрефакторить! Два раза strcpy(buf, popt) */
			gonumber = FindOption(ptrn, buf, len);
			if(gonumber >= 0)
			{
				if(ptrn[gonumber].flag == TRUE)
				{
					if(!varval || (*varval == args.prefix)) return MISSING_VALUE;
					ptrn[gonumber].value = varval;
				}
				transpose(&ptrn[gonumber], &ptrn[result]);
				result++;
			}
			else
			{
				pbuf = strlen(buf) - 1;
				for(; pbuf>=0; pbuf--)
				{
					gonumber = FindOption(ptrn, buf + pbuf, len);
					if(gonumber >= 0)
					{
						if(ptrn[gonumber].flag == TRUE) return ILLEGAL_USE_OPTIONS;
						*(buf + pbuf) = 0;
						transpose(&ptrn[gonumber], &ptrn[result]);
						result++;				/* TODO Отрефакторить! */
					}
					else
					{
						return (-count);
					}
				}
			}
		}
	}
	return result;
}



