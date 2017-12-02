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

ALTSEP = =
BIN = ./bin
MTEST = ./test

all:
	gcc -DALT_SEPARATOR="'$(ALTSEP)'" -c argparser.c
	ar rc libargparser.a argparser.o
	rm *.o
	mv libargparser.a $(BIN)
tests:
	gcc  -DALT_SEPARATOR="'$(ALTSEP)'" $(MTEST)/test.c argparser.c -o _test
	mv _test $(MTEST)/test
debug:
	gcc -g -DALT_SEPARATOR="'$(ALTSEP)'" $(MTEST)/test.c argparser.c -o _test_debug
	mv _test_debug $(MTEST)/test_debug
clean:
	rm $(MTEST)/test $(BIN)/*
