# FlowMap K-LUT Technology Mapping
Assignment of CS 5160-00 FPGA Architecture & CAD.

# Dependency
code portabel to all g++
checker only available on ubuntu 16.04

# Results

- alu4.aag: Area:1567 | Depth: 7
- bigkey.aag: Area:1483 | Depth: 3
- c1908: Area:183 | Depth: 8
- c5315: Area:742 | Depth: 10

# File description
```
2018f mapping project.pdf: project requirement
main.cpp: main steps of calling all functions
checker: for validating if the output if feasible
Graph_FlowNetWorks.cpp & .h: implementing agmenting path algorithm
paper/ the original paper
results/ the output results of K=4 on every testcase
testcase/ all test patterns
testcase/my_alu.aag is the schmatic netlist on original paper
```

# How to run
```
$ make ${testcase_name}
//testcase_name: alu4, bigkey, c1908, c5315
```

# Paper Reference
FlowMap: an optimal technology mapping algorithm for delay optimization in lookup-table based FPGA designs