### LLVM IR
The goal of this task is gaining exposure to LLVM in general and the LLVM IR. You will implement a simple analysis based on LLVM IR that extracts all the variables in each basic block of a program and stores them in a text file.

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
            c=num*3
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

### Task
Your task is to extract the variables that are used in each basic block as shown above. Detailed instructions for the implementation are found as comments in `easy_task.cpp`. Please complete the empty functions in the skeleton code and test it with the examples above. You can create your own functions if you need.

Commands for the compilation and execution:
```
$ clang++ ./easy_task.cpp -o easy_task `llvm-config --cxxflags` `llvm-config --ldflags` `llvm-config --libs` -lpthread -lncurses -ldl
$ clang -fno-discard-value-names -emit-llvm -S -o example1.ll ./example1.c
$ ./easy_task example1.ll
```

### Hints
There are some functions that might be useful:

* `llvm::BasicBlock *llvm::Instruction::getSuccessor(unsigned int Idx) const`
* `llvm::Instruction *llvm::BasicBlock::getTerminator()`
* `unsigned int llvm::Instruction::getNumSuccessors() const`

And we have implemented some functions that you can reuse in `easy_task.cpp`:
```c
std::string getSimpleNodeLabel(const BasicBlock *Node)
std::string getVarName(const Instruction *ins)
```
