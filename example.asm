#sample comment

TEST:0x0000
	ADDREG:0x0000           # this register will be used for the addition
CPY  M:0x0000  R%ADDREG # we clear the addition register
     ADD  P:        M%0x0003               # we add the PC to the offest which addresses the next instruction
     #kek
ADD  M:0x0001  R%ADDREG # we increment addition register
SND  R%ADDREG  M:0x0001 # we send the state of addition register to HW[0x01]
     JMP $M:0x0005           # we jump to the saved address
