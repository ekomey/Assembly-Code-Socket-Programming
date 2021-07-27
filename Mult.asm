@i
A=1 //Intializes the value of i to 1
(LOOP) //Performs the repeated addition
@i
B=A //Takes the value stored at i
@R1
B=B-A //Computes R1-i

@END
B;JGT //Stays in the loop if B>0
@R0
B=A
@R2
A=A+B
@i
A=A+1 //Increments the counter
@LOOP
0;JMP
(END)
@END
0;JMP
