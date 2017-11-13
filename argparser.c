/* argparser - a small library for parsing command-line arguments
   
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/* Igor 'sp_r00t' Tyukalov <tyukalov@bk.ru> */

#include <stdio.h>
#include "argparser.h"
#include <string.h>


static void transpose(RETOPT, RETOPT);
int FindOption(RETOPT, char*, int);

static void
transpose(RETOPT x, RETOPT y)
{
	if(x!=y)
	{
		OPTIONS var 	= *x;
		x->value	= y->value;
		x->options	= y->options;
		y->value	= var.value;
		y->options	= var.options;
	}
}

int
FindOption(RETOPT ptrn, char *opt, int len)
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

int
argparse(ARGPARSE_ARG args, RETOPT ptrn, int len)
{
	char	*popt, *varval, buf[MAX_OPTION_SIZE];
	int	gonumber, pbuf, count, result = 0;
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

void
fprinterror(FILE *fd, errcode err, char **argv)
{
  /* TODO Изменить реализацию! */
	switch(err)
	{
		case ILLEGAL_USE_OPTIONS: {fprintf(fd, "Incorrect use of the option\n"); break;};
		case MISSING_VALUE: {fprintf(fd, "Missing option value\n"); break;};
		default: fprintf(fd, "Unknown options %s\n", argv[-err]);
	}
}
