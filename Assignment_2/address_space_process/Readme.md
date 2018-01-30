# Process Address Space

The program will fork 3 child process. Let parent process be p, three child process be child0,child1,child2. Let global variables be g_first, g_second, g_third. Let local variables be a, b, c. <br>

# Addressess of global variables and local variables of parent process and child processes.

The program is run thrice. In the following tables we will look at addresses of local, global variables of processes p, child0, child1, child2. <br>

## Iteration 1

Process | a (local variable) | b (local variable) | c (local variable) | g_first | g_second | g_third
----------|--------|-------|------|------|------|------|------|
parent (p) | 0x7ffcd0051718 | 0x7ffcd005171c | 0x7ffcd0051720 | 0x602088 | 0x60208c | 0x602090 
child0 | 0x7ffcd00516f8 | 0x7ffcd00516f0 | 0x7ffcd00516e8 | 0x602088 | 0x60208c | 0x602090
child1 | 0x7ffcd00516f8 | 0x7ffcd00516f0 | 0x7ffcd00516e8 | 0x602088 | 0x60208c | 0x602090
child2 | 0x7ffcd00516f8 | 0x7ffcd00516f0 | 0x7ffcd00516e8 | 0x602088 | 0x60208c | 0x602090

## Iteration 2

Process | a (local variable) | b (local variable) | c (local variable) | g_first | g_second | g_third
----------|--------|-------|------|------|------|------|------|
parent (p) | 0x7ffebb7688b8 | 0x7ffebb7688bc | 0x7ffebb7688c0 | 0x602088 | 0x60208c | 0x602090 
child0 | 0x7ffebb768898 | 0x7ffebb768890 | 0x7ffebb768888 | 0x602088 | 0x60208c | 0x602090
child1 | 0x7ffebb768898 | 0x7ffebb768890 | 0x7ffebb768888 | 0x602088 | 0x60208c | 0x602090
child2 | 0x7ffebb768898 | 0x7ffebb768890 | 0x7ffebb768888 | 0x602088 | 0x60208c | 0x602090

## Iteration 3

Process | a (local variable) | b (local variable) | c (local variable) | g_first | g_second | g_third
----------|--------|-------|------|------|------|------|------|
parent (p) | 0x7fffb99e0538 | 0x7fffb99e053c | 0x7fffb99e0540 | 0x602088 | 0x60208c | 0x602090 
child0 | 0x7fffb99e0518 | 0x7fffb99e0510 | 0x7fffb99e0508 | 0x602088 | 0x60208c | 0x602090
child1 | 0x7fffb99e0518 | 0x7fffb99e0510 | 0x7fffb99e0508 | 0x602088 | 0x60208c | 0x602090
child2 | 0x7fffb99e0518 | 0x7fffb99e0510 | 0x7fffb99e0508 | 0x602088 | 0x60208c | 0x602090

## Obseravations

From the above tables we can observe that when a process is forked 