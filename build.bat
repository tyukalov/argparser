@cl /c /EHsc argparser.c
@lib argparser.obj /OUT:libargparser.lib
@del *.obj
@move libargparser.lib ./bin
