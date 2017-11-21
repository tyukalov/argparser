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
#include <stdlib.h>
#include "argparser.h"
#include <string.h>


static int
FindOption(const ARGPARSE_ARG args, const char *opt)
{
	int  result = 0;
	OPTIONS var;
	for(; result < args.len; result++)
	{
		var = args.opts[result];
		if(!strcmp(var.options, opt)) return result;
	}
	return -1;
}


OPTARG
argparse(const ARGPARSE_ARG args)
{
  int count, pbuf, gonumber, valflag = TRUE, beginoptflag = TRUE, beginargflag = TRUE;
  char  *popt, *varval, buf[MAX_OPTION_SIZE];
  OPTARG RESULT;
  POPTION varopt;
  PARGUMENTS vararg;
  RESULT.result = 0;
  RESULT.opt = (POPTION)NULL;
  RESULT.arg = (PARGUMENTS)NULL;
  for(count=1; count < args.argc; count++)
    {
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
	    }							
	  gonumber = FindOption(args, buf);
	  if(gonumber >= 0)
	    {
	      INIT(beginoptflag, RESULT, varopt);
	      if(args.opts[gonumber].flag == REQUIRED || args.opts[gonumber].flag == OPTIONAL)
		{
		  if((!varval || (*varval == args.prefix)) && args.opts[gonumber].flag == REQUIRED)
		    {
		      RESULT.result = MISSING_VALUE;
		      return RESULT;
		    }
		  else if(varval && *varval == args.prefix && args.opts[gonumber].flag == OPTIONAL)
		    {
		      varval = NULL;
		    }
		  varopt->value = varval;
		  if(args.separator == SPACE && args.opts[gonumber].flag == REQUIRED) valflag = FALSE;
		}
	      varopt->option = args.opts[gonumber].options;
	    }
	  else
	    {
	      pbuf = strlen(buf) - 1;
	      for(; pbuf>=0; pbuf--)
		/*When passing an optional parameter, the option must be seperate! */ 
		{
		  gonumber = FindOption(args, buf + pbuf);
		  if(gonumber >= 0)
		    {
		      if(args.opts[gonumber].flag == REQUIRED) /* The option with the required parameter must stand alone */
			{
			  RESULT.result = ILLEGAL_USE_OPTIONS;
			  return RESULT;
			}
		      *(buf + pbuf) = 0;
		      INIT(beginoptflag, RESULT, varopt);
		      varopt->option = args.opts[gonumber].options;
		    }
		  else
		    {
		      RESULT.erropt = count;
		      RESULT.result = UNKNOWN_OPTION;
		      return RESULT;
		    }
		}
	    }
	}
      else
	{
	  if (valflag)
	    {
	      if(beginargflag)
		{
		  vararg = RESULT.arg = INITARG;
		  beginargflag = FALSE;
		}
	      else
		{
		  vararg = vararg->next = INITARG;
		}
	      VALIDATOR(vararg, RESULT);
	      vararg->argument = args.argv[count];
	    }
	  else
	    {
	      valflag = TRUE;
	    }
	}
    }
  return RESULT;
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

void
argclean(OPTARG optarg)
{
  POPTION p, popt = optarg.opt;
  PARGUMENTS a, parg = optarg.arg;
  while(popt)
    {
      p = popt -> next;
      free(popt);
      popt = p;
    };
  while(parg)
    {
      a = parg -> next;
      free(parg);
      parg = a;
    };
}
