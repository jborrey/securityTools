# Stack Printer
Small C program to print out your machine's stack.
It will print the byte number, address, bytes in hex, words in unsiged int and finally ASCII.
This can be useful for understanding how you system is building stack frames. Understanding this can allow you to plan buffer overflow and stack smashing attacks.

Multiple dummy functions are called just to build some stack frames above `main` and in the final one (`foo3`) a function is called to print down from a bit above that stack frame. Before the stack is printed, the address of each function will be revealed.

### Installation
Compile stackPrint.c
```sh
gcc -o stackPrint stackPrint.c

# compiling without Canaries, ASLR (and no NX for fun)
gcc stackPring.c -o stackPrintUnsafe -fno-stack-protector -Wl,-no_pie,-allow_stack_execute

# -fno-stack-protector turns off Canaries.
# -Wl sends the following comma delimited arguemtns to the linker (ld)
#   -no_pie turns off ASRL
#   -allow_stack_execute turns off NX
```

### Running
Run the binary
```sh
./stackPrint 500 4 # 4 byte words
./stackPrint 500 8 # 8 byte words
```


### Example Output
```
&foo0  = 0x10c16d800
&foo1  = 0x10c16d860
&foo2  = 0x10c16d8c0
&foo3  = 0x10c16d920
&printDown = 0x10c16d980
&main = 0x10c16d6f0
[byte] ====address===: hx hx hx hx hx hx hx hx |     deci        deci    | c c c c c c c c
------------------------------------------------------------------------------------------
[0000] 0x7fff53a9263c: 08 00 00 00 3c 26 a9 53 |           8  1403594300 |         < &   S
[0008] 0x7fff53a92644: ff 7f 00 00 5a 00 00 00 |       32767          90 |         Z
[0016] 0x7fff53a9264c: 10 00 00 00 80 26 a9 53 |          16  1403594368 |           &   S
[0024] 0x7fff53a92654: ff 7f 00 00 c3 d9 16 0c |       32767   202824131 |
[0032] 0x7fff53a9265c: 01 00 00 00 28 41 a8 7a |           1  2057847080 |         ( A   z
[0040] 0x7fff53a92664: ff 7f 00 00 33 05 55 48 |       32767  1213531443 |         3   U H
[0048] 0x7fff53a9266c: 30 00 00 00 08 00 00 00 |          48           8 | 0
[0056] 0x7fff53a92674: e8 03 00 00 3c 26 a9 53 |        1000  1403594300 |         < &   S
[0064] 0x7fff53a9267c: ff 7f 00 00 b0 26 a9 53 |       32767  1403594416 |           &   S
[0072] 0x7fff53a92684: ff 7f 00 00 5f d9 16 0c |       32767   202824031 |         _
[0080] 0x7fff53a9268c: 01 00 00 00 00 00 00 00 |           1           0 |
[0088] 0x7fff53a92694: 00 00 00 00 08 00 00 00 |           0           8 |
[0096] 0x7fff53a9269c: e8 03 00 00 64 64 64 64 |        1000  1684300900 |         d d d d
[0104] 0x7fff53a926a4: 64 64 64 00 33 05 55 48 |     6579300  1213531443 | d d d   3   U H
[0112] 0x7fff53a926ac: 21 ad 00 6b e0 26 a9 53 |  1795206433  1403594464 | !     k   &   S
[0120] 0x7fff53a926b4: ff 7f 00 00 f2 d8 16 0c |       32767   202823922 |
[0128] 0x7fff53a926bc: 01 00 00 00 b1 b3 70 a5 |           1 -1519340623 |             p
[0136] 0x7fff53a926c4: 47 9f 35 33 08 00 00 00 |   859152199           8 | G   5 3
[0144] 0x7fff53a926cc: e8 03 00 00 63 63 63 63 |        1000  1667457891 |         c c c c
[0152] 0x7fff53a926d4: 63 63 63 00 33 05 55 48 |     6513507  1213531443 | c c c   3   U H
[0160] 0x7fff53a926dc: 21 ad 00 6b 10 27 a9 53 |  1795206433  1403594512 | !     k   '   S
```
