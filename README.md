## LLVM Coding Task
The goal of this task is gaining exposure to LLVM in general and the LLVM IR. You will implement a simple analysis based on LLVM IR that extracts all the variables in each basic block of a program and stores them in a text file.

### Estimated Effort
* 30 minutes, if familiar with LLVM IR
* 2 - 3 hours, if new to LLVM, most of which is taken to get familiar with LLVM.



### Useful Links
* [LLVM IR](https://llvm.org/docs/LangRef.html)
* [Tutorial 1](https://llvm.org/docs/GettingStarted.html)
* [Tutorial 2](https://www.cs.umd.edu/class/fall2017/cmsc430/slides/LLVM.pdf)


### Getting Started
To get started, you may refer [this](https://llvm.org/docs/GettingStarted.html) to setup the environment for your LLVM system.

### Overview
#### Example 1: For example, consider the `c` program below:
```c
int main() {
    int num,a,b,c;
    scanf("%d", &num);

    a=10;
    b=num*2;
    c=0;
    if (b>10){
        c=num*2;
    }
    
    printf("%d\n",c);
    return 0;
}
```
The generated LLVM IR will have four basic blocks with labels: `entry`, `if.then`, `if.else` and `if.end`.
In the end of each of the basic blocks the list of used variables would be as follows (registers are skipped for brevity):
* entry: {num, a, b, c}
* if.then: {c, num}
* if.else: {c}

Since it is not like any typical data flow analysis, we only care about the variables that show up in each basic block.

#### Example 2: In this example, consider the C program with a more complex structure below:
```c
int main() {
    int num,a,b,c;
    scanf("%d", &num);

    a=10;
    b=num*10;
    c=1;
    while (b>c){
        if (c%5 == 0){
            c=num*2;
        } else {
            c=num*3;
        }
    }
    printf("%d\n",c);
    return 0;
}
```
Simply get all variables in each of the basic blocks:
* entry: {num, a, b, c}
* while.cond: {b, c}
* while.body: {c}
* if.then: {c, num}
* if.else: {c, num}
* while.end: {c}

### Task 1
Your task is to extract the variables that are used in each basic block as shown above. Detailed instructions for the implementation are found as comments in `VarsAnalysis.cpp`. Please complete the empty functions in the skeleton code and test it with the examples above. You can create your own functions if you need.

### Test Steps
You can use the following commands to test your solution.
1. Compile `VarsAnalysis.cpp` to an executable file `VarsAnalysis`:
```
$ clang++ ./VarsAnalysis.cpp -o VarsAnalysis `llvm-config --cxxflags` `llvm-config --ldflags` `llvm-config --libs` -lpthread -lncurses -ldl
```
2. Compile the target program `example1.c` or `example2.c` to bitcode files:
```
$ clang -fno-discard-value-names -emit-llvm -S -o example1.ll ./example1.c
```
3. Execute your program and check the result:
```
$ ./VarsAnalysis example1.ll
```
Expected analysis results for `example1.c` and `example2.c` should be: (the order does not matter)
```
$ ./VarsAnalysis example1.ll
entry: {num, a, b, c}
if.then: {c, num}
if.else: {c}

$ ./VarsAnalysis example2.ll
entry: {num, a, b, c}
while.cond: {b, c}
while.body: {c}
if.then: {c, num}
if.else: {c, num}
while.end: {c}
```

### Hints
There are some functions that might be useful:

* `llvm::BasicBlock *llvm::Instruction::getSuccessor(unsigned int Idx) const`
* `llvm::Instruction *llvm::BasicBlock::getTerminator()`
* `unsigned int llvm::Instruction::getNumSuccessors() const`

And we have implemented some functions that you can reuse in `VarsAnalysis.cpp`:
```c
std::string getSimpleNodeLabel(const BasicBlock *Node)
std::string getVarName(const Instruction *ins)
```
