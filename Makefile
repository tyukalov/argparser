 #    This program is free software: you can redistribute it and/or modify
 #    it under the terms of the GNU General Public License as published by
 #    the Free Software Foundation, either version 3 of the License, or
 #    (at your option) any later version.

 #    This program is distributed in the hope that it will be useful,
 #    but WITHOUT ANY WARRANTY; without even the implied warranty of
 #    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 #    GNU General Public License for more details.

 #    You should have received a copy of the GNU General Public License
 #    along with this program.  If not, see <http://www.gnu.org/licenses/>.

 # Igor Tyukalov <tyukalov@bk.ru> 

all:
	gcc -c argparser.c
	ar rc libargparser.a argparser.o
	rm *.o
	mv libargparser.a ./bin
tests:
	gcc ./test/test.c argparser.c -o _test
	mv _test ./test/test
debug:
	gcc -g ./test/test.c argparser.c -o _test_debug
	mv _test_debug ./test/test_debug
clean:
	rm ./test/test ./bin/*
