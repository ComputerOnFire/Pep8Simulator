BR main 
val1: .BLOCK 2
val2: .BLOCK 2
str1: .ASCII "w = \x00"
str2: .ASCII "l = \x00"
str3: .ASCII "p = \x00"
val3: .BLOCK 2
main: DECI val1, d
DECI val2, d
LDA val1,d
ADDA val2,d
STA val3, d 
LDA val3, d
ADDA val3, d
STA val3, d
STRO str1, d
DECO val1, d
CHARO '\n',i
STRO str2, d
DECO val2, d
CHARO '\n',i
STRO str3, d
DECO val3, d
STOP 
.END
