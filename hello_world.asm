# the values are ORed with 0x0100 because thats the append command for HostConsole HW

H:     0x0148
e:     0x0165
l:     0x016C
o:     0x016F
SPACE: 0x0120
W:     0x0157
r:     0x0172
d:     0x0164
EXCLAM:0x0121
NEWLIN:0x010A
CONSOL:0x0001
WRITE: 0x0200

API  M%H       M%CONSOL
API  M%e       M%CONSOL
API  M%l       M%CONSOL
API  M%l       M%CONSOL
API  M%o       M%CONSOL
API  M%SPACE   M%CONSOL
API  M%W       M%CONSOL
API  M%o       M%CONSOL
API  M%r       M%CONSOL
API  M%l       M%CONSOL
API  M%d       M%CONSOL
API  M%EXCLAM  M%CONSOL
API  M%NEWLIN  M%CONSOL
API  M%WRITE   M%CONSOL
JMP  M:0x0000
