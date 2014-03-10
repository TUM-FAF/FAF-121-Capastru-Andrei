lab#2.exe : lab#2.obj lab#2.res
     $(LINKER) $(GUIFLAGS) -OUT:lab#2.exe lab#2.obj \
	 lab#2.res $(GUILIBS)

lab#2.obj : lab#2.c resources.h
     $(CC) $(CFLAGS) lab#2.c

lab#2.res : lab#2.rc resources.h
     $(RC) $(RCVARS) resources.rc