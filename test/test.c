/* 
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
/* Igor Tyukalov <tyukalov@bk.ru> */

#include <stdio.h>
#include "../argparser.h"
void main(int argc, char* arg[])
{
  /* В файле option.h задаются параметры marg и ptrn */
#include "option.h"
  int c;
  int num = argparse(marg, ptrn, OPT_LEN);
	printf("%d\n", num);
	if(num<0)
	{
		if(num == ILLEGAL_USE_OPTIONS)
		{
			printf("Error! Illegal use of options\n");
		}
		else if(num == MISSING_VALUE)
		{
			printf("Error! Missing value from option!\n");
		}
		else{
			printf("Unknown option '%s'\n", arg[-num]);
		}
	}
	for(c=0; c<num; c++)
	{
		printf("Option %s, value %s\n", ptrn[c].options, ptrn[c].value);
	}
}
