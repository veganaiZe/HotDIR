################################################################
# NOTE: Subsystem "5.01" requires MSVC <= 19.27 (VS2019 16.7.28)
################################################################
CC = cl.exe -nologo -J -WX -W4 -sdl -arch:IA32 -O2 -D_CRT_SECURE_NO_WARNINGS
LL = link.exe -nologo -subsystem:console,"5.01" -OUT:

CFLAGS = -m32 -funsigned-char -O2 -fdiagnostics-color -Wall -Wextra \
         -pedantic-errors -Wfatal-errors -Wshadow -Wconversion \
         -Wsign-conversion -Wno-missing-braces \
         -Wno-deprecated-declarations -Wno-deprecated

#CC = g++ -std=c++98 $(CFLAGS)
#CC = gcc -std=c89 $(CFLAGS)
#LL = gcc -mconsole -o

################################################################
# NOTE: `nmake` is required to properly run `clang`, it seems...
################################################################
#CC = clang++ -std=c++17 $(CFLAGS)
#CC = clang -std=c89 $(CFLAGS)
#LL = lld-link --color-diagnostics=never -subsystem:console,"5.01" libcmt.lib -out:


all : tests hd.exe

test : tests
	hd-tests.exe

tests : hd-tests.exe

hd-tests.exe : hd-tests.obj hd.obj
	@$(LL)"hd-tests.exe" hd-tests.obj hd.obj

hd-tests.obj : hd-tests.c hd.h
	@$(CC) -c hd-tests.c -o hd-tests.obj

hd.exe : hd.obj main.obj
	@$(LL)"hd.exe" hd.obj main.obj

hd.obj : hd.c hd.h
	@$(CC) -c hd.c -o hd.obj

main.obj : main.c hd.h
	@$(CC) -c main.c -o main.obj

clean :
	@del hd-tests.obj hd-tests.exe hd.obj hd.exe main.obj 2>NUL \
	|| rm -f hd-tests.obj hd-tests.exe hd.obj hd.exe main.obj NUL
