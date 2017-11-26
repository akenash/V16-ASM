BINREG:0x0000

# program start
CPY  A:0x0013  R%BINREG # copy the iterator for binary data
# loop start
CPY $I%BINREG  H:0x0100 # copy the binary data at address of binreg to hw, increment binreg
ADD  M:0x0001 $S:0x0001 # add 1 to the HW data iterator
IGQ  R%BINREG  A:0x0011 # if the binreg is at the end of binary data, exit the loop
JMP  S:0x0009           # jump to beginning of copying
# loop end
API  M:0x0001  M:0x0001 # send the write signal to console
JMP  S:0x0003           # print again

0x6548
0x6C6C
0x206F
0x6F57
0x6C72
0x2164
0x000A

