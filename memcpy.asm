SRCREG:0x0000
DSTREG:0x0001
SIZREG:0x0002
ITEREG:0x0003

MOV  M:0x0000  R%ITEREG # iterator = 0
# loop start
CPY $I%SRCREG $I%DSTREG # copy from source to destination and increment both iterators
ILT  I%ITEREG  R%SIZREG # if iterator < size skip return
RET
JMP  S:0x0007
