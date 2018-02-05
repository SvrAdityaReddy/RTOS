# Process Address Space

The program will fork 3 child process. Let parent process be p, three child process be child0,child1,child2. Let global variables be g_first, g_second, g_third. Let local variables be a, b, c in parent process, j, k, l in child processes. <br>

On running program it will generate four files named parent.sh, child0.sh, child1.sh, child2.sh. On running these scripts corresponding processes gets killed and shell script file also gets removed. <br>

# Addresses of global variables and local variables of parent process and child processes

The program is run thrice. In the following tables we will look at addresses of local, global variables of processes p, child0, child1, child2. <br>

## Iteration 1

Process | local variable | local variable | local variable | g_first | g_second | g_third
----------|--------|-------|------|------|------|------
parent (p) | 0x7ffda7e429b8 | 0x7ffda7e429bc | 0x7ffda7e429c0 | 0x60208c | 0x602090 | 0x602094 
child0 | 0x7ffda7e4298c | 0x7ffda7e42990 | 0x7ffda7e42994 | 0x60208c | 0x602090 | 0x602094
child1 | 0x7ffda7e4298c | 0x7ffda7e42990 | 0x7ffda7e42994 | 0x60208c | 0x602090 | 0x602094
child2 | 0x7ffda7e4298c | 0x7ffda7e42990 | 0x7ffda7e42994 | 0x60208c | 0x602090 | 0x602094

## Iteration 2

Process | local variable | local variable | local variable | g_first | g_second | g_third
----------|--------|-------|------|------|------|------
parent (p) | 0x7fffc3466998 | 0x7fffc346699c | 0x7fffc34669a0 | 0x60208c | 0x602090 | 0x602094 
child0 | 0x7fffc346696c | 0x7fffc3466970 | 0x7fffc3466974 | 0x60208c | 0x602090 | 0x602094
child1 | 0x7fffc346696c | 0x7fffc3466970 | 0x7fffc3466974 | 0x60208c | 0x602090 | 0x602094
child2 | 0x7fffc346696c | 0x7fffc3466970 | 0x7fffc3466974 | 0x60208c | 0x602090 | 0x602094

## Iteration 3

Process | local variable | local variable | local variable | g_first | g_second | g_third
----------|--------|-------|------|------|------|------
parent (p) | 0x7ffe2ec3b688 | 0x7ffe2ec3b68c | 0x7ffe2ec3b690 | 0x60208c | 0x602090 | 0x602094 
child0 | 0x7ffe2ec3b65c | 0x7ffe2ec3b660 | 0x7ffe2ec3b664 | 0x60208c | 0x602090 | 0x602094
child1 | 0x7ffe2ec3b65c | 0x7ffe2ec3b660 | 0x7ffe2ec3b664 | 0x60208c | 0x602090 | 0x602094
child2 | 0x7ffe2ec3b65c | 0x7ffe2ec3b660 | 0x7ffe2ec3b664 | 0x60208c | 0x602090 | 0x602094

## Observations

As we know that when a process forks another process the parent process and child process shares text segment but child process gets a seperate copy of data, stack, heap segments.<br>
But we had observed that global variables are located in same addresses for both parent and child process eventhough global variables belong to data segment which should have ideally different addresses because the address printed is virtual address.
