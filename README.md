# COL216 Assignment 2 Report

## By Viraaj Narolia: 2023CS10552 and Nishant Ranjan: 2023CS10607

---

## Design Decisions

1. **Simulations**  
   We used classes to model hardware with data members as the ports and member functions as processes.

2. **Without Forwarding**  
   We implemented a **Hazard Detection Unit**. Once a hazard was detected, we used the `flush()` function to introduce stalls until the instruction reached the WB stage.

3. **With Forwarding**  
   - We used a **Branch Forwarding Unit** and an **ALU Forwarding Unit**.
   - The Hazard Detection Unit was modified to generate stalls for **load-use dependencies**.

4. **Branch Resolution**  
   - Branches and jump instructions are resolved in the **ID stage** of the pipeline.
   - The next instruction is determined after the **ID stage**, as specified in the problem statement.

5. **Registers**  
   - Modeled using an `int` array of size **32**.
   - Initialized to `0` at the start of execution.

6. **Data Memory**  
   - Implemented as an **unordered map**, where:
     - **Keys** → Memory addresses.
     - **Values** → Corresponding byte values.
   - Initially, all values are set to `0`.
  
7. **Note: All values have been calculated and all the branch and ALU operations have been carried out according to the values in the registers and data memory**

---

## Known Issues

1. **Floating-Point Instructions Not Supported**  
   - Current implementation only supports **integer operations**.
   - Could be extended by using a **union** of `float` and `int` in registers.

2. **32-Bit Processor Limitation**  
   - Instructions like `ld` and `sd` (used in 64-bit processors) are **not supported**.

3. **System Calls Not Implemented**  
   - No support for syscalls like `ecall`.


---

## Challenges Faced

1. **Debugging Issues**  
   - Debugging was difficult due to incorrect forwarding logic or misconfigured pipeline connections.

2. **Simulating Parallelism in C++**  
   - C++ is inherently sequential, making it challenging to **simulate parallel execution** in a pipelined processor.

---

## Sources

1. **[Computer Organization and Design RISC-V Edition](https://www.elsevier.com/books/computer-organization-and-design-risc-v-edition/patterson/978-0-12-820331-6)**  
   - Used for reference on:
     - 32-bit RISC-V processor pipeline (with and without forwarding).
     - Forwarding logic for control and ALU units.
     - Hazard detection logic and stalling algorithm.

2. **[RISC-V Reference](https://www.cs.sfu.ca/~ashriram/Courses/CS295/assets/notebooks/RISCV/RISCV_CARD.pdf)**  
   - Used to get instruction formats and opcodes.

3. **[Web RISC-V](https://webriscv.dii.unisi.it/)**  
   - Helped visualize processor components.
   - Used the factorial program from this site for testing.

4. **[Example RISC-V Programs](https://marz.utk.edu/my-courses/cosc230/book/example-risc-v-assembly-programs/)**  
   - Used as a test suite for verifying correctness.

---
