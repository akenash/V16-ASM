PTRREG:0x000F
VAL:0xFFFF
CPY  P:        R%PTRREG
ADD  M:0x0002  R:0x0000
SND  M%VAL     H:0x0001
JMP  R%PTRREG

