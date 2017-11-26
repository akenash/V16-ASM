BINREG:0x0000

# program start
CPY  A:0x0016  R%BINREG # copy the iterator for binary data
# loop start
CPY $R%BINREG  H:0x0100 # copy the binary data from at address R[0] to HW
ADD  M:0x0001 $S:0x0001 # add 1 to the binary data iterator
ADD  M:0x0001  R%BINREG # add 1 to the binary data iterator
IGQ $S:0x0007  M:0x0107 # if we copied 7 words, skip the jump
JMP  S:0x000C           # jump to beginning of copying
API  M:0x0001  M:0x0001 # send the write signal to console
JMP  S:0x0003           # print again

0x6548
0x6C6C
0x206F
0x6F57
0x6C72
0x2164
0x000A

