#ifndef components_hpp
#include<bits/stdc++.h>
using namespace std;
# define ll long long
#define llu long long unsigned


class IF_ID{
    public:
    int PC;
    int instruction;

    IF_ID(){
        this->PC = INT_MIN;
        this->instruction = 0;
    }

    void set_values(int PC, int instruction){
        this->PC = PC;
        this->instruction = instruction;
    }

    void Flush(){
        this->PC = -1;
        this->instruction = 0;
    }
};

class ID_EX{
    public:
    int PC;
    int rs1, rs2;
    int read_data1, read_data2, sign_extended_value;
    int funct7, funct3; 
    int Branch, MemRead, MemtoReg, AluOp, MemWrite, AluSrc, RegWrite;
    int rd;

    ID_EX(){
        this->PC = INT_MIN;
        this->rs1 = 0;
        this->rs2 = 0;
        this->read_data1 = 0;
        this->read_data2 = 0;
        this->sign_extended_value = 0;
        this->funct7 = 0;
        // this->thirtieth_bit = 0;
        // this->twentyninth_bit = 0;
        this->funct3 = 0;
        this->Branch = 0;
        this->MemRead = 0;
        this->MemtoReg = 0;
        this->AluOp = 0;
        this->MemWrite = 0;
        this->AluSrc = 0;
        this->RegWrite = 0;
        this->rd = 0;
    }

    void set_values(int PC, int rs1, int rs2, int read_data1, int read_data2, int sign_extended_value, int funct7, /*int thirtieth_bit, int twentyninth_bit, */ int funct3, int Branch, int MemRead, int MemtoReg, int AluOp, int MemWrite, int AluSrc, int RegWrite, int rd){
        this->PC = PC;
        this->rs1 = rs1;
        this->rs2 = rs2;
        this->read_data1 = read_data1;
        this->read_data2 = read_data2;
        this->sign_extended_value = sign_extended_value;
        this->funct7 = funct7;
        // this->thirtieth_bit = thirtieth_bit;
        // this->twentyninth_bit = twentyninth_bit;
        this->funct3 = funct3;
        this->Branch = Branch;
        this->MemRead = MemRead;
        this->MemtoReg = MemtoReg;
        this->AluOp = AluOp;
        this->MemWrite = MemWrite;
        this->AluSrc = AluSrc;
        this->RegWrite = RegWrite;
        this->rd = rd;
    }

    void Flush(){
        this->PC = -1;
        this->rs1 = 0;
        this->rs2 = 0;
        this->read_data1 = 0;
        this->read_data2 = 0;
        this->sign_extended_value = 0;
        this->funct7 = 0;
        // this->thirtieth_bit = 0;
        // this->twentyninth_bit = 0;
        this->funct3 = 0;
        this->Branch = 0;
        this->MemRead = 0;
        this->MemtoReg = 0;
        this->AluOp = 0;
        this->MemWrite = 0;
        this->AluSrc = 0;
        this->RegWrite = 0;
        this->rd = 0;
    }
};

class EX_MEM{
    public:
    int PC;
    int ALU_result;
    int read_data2;
    int MemRead, MemtoReg, MemWrite, RegWrite;
    int rd;
    int funct3;

    EX_MEM(){
        this->PC = INT_MIN;
        this->ALU_result = 0;
        this->read_data2 = 0;
        this->MemRead = 0;
        this->MemtoReg = 0;
        this->MemWrite = 0;
        this->RegWrite = 0;
        this->rd = 0;
        this->funct3 = 0;
    }

    void set_values(int PC, int ALU_result, int read_data2, int MemRead, int MemtoReg, int MemWrite, int RegWrite, int rd, int funct3){
        this->PC = PC;
        this->ALU_result = ALU_result;
        this->read_data2 = read_data2;
        this->MemRead = MemRead;
        this->MemtoReg = MemtoReg;
        this->MemWrite = MemWrite;
        this->RegWrite = RegWrite;
        this->rd = rd;
        this->funct3 = funct3;
    }
    
    void Flush(){
        this->PC = -1;
        this->ALU_result = 0;
        this->read_data2 = 0;
        this->MemRead = 0;
        this->MemtoReg = 0;
        this->MemWrite = 0;
        this->RegWrite = 0;
        this->rd = 0;
        this->funct3 = 0;
    }
};


class MEM_WB{
    public:
    int PC;
    int ALU_result;
    int read_data;
    int MemtoReg, RegWrite;
    int rd;
    MEM_WB(){
        this->ALU_result = 0;
        this->read_data = 0;
        this->MemtoReg = 0;
        this->RegWrite = 0;
        this->rd = 0;
        this->PC = INT_MIN;
    }

    void set_values(int ALU_result, int read_data, int MemtoReg, int RegWrite, int rd, int PC){
        this->ALU_result = ALU_result;
        this->read_data = read_data;
        this->MemtoReg = MemtoReg;
        this->RegWrite = RegWrite;
        this->rd = rd;
        this->PC = PC;
    }

    void Flush(){
        this->ALU_result = 0;
        this->read_data = 0;
        this->MemtoReg = 0;
        this->RegWrite = 0;
        this->rd = 0;
        this->PC = -1;
    }
};


class Instruction_Memory{
    public:
    vector<int> instruction_memory;
    vector<string> instructions;
    Instruction_Memory(const string& filename){
        ifstream file(filename);
        if (!file) {
            cerr << "Error: Could not open file " << filename << endl;
            return;
        }
        string line;
        while(getline(file, line)){
            // size_t firstSpace = line.find(' ');            
            // size_t secondSpace = line.find(' ', firstSpace + 1);
            // if (firstSpace == string::npos || secondSpace == string::npos) continue; 
            // while(line[firstSpace] == ' ') firstSpace++;
            // while(line[secondSpace] == ' ') secondSpace++;

            int firstspace = 0;
            while(line[firstspace] == ' ') firstspace++;
            while(line[firstspace] != ' ') firstspace++;
            while(line[firstspace] == ' ') firstspace++;
            string hexCol = line.substr(firstspace, 8); 
            firstspace+=9;
            while(line[firstspace] == ' ') firstspace++;
            string instruction_name = line.substr(firstspace);
            instruction_memory.push_back(hextoint(hexCol));
            instructions.push_back(instruction_name);
        }
    }

    int hextoint(const string& hex){
        int binary = 0;
        for(char c : hex){
            if(c >='0' && c <= '9')  binary = binary*16 + (c - '0');
            else binary = binary*16 + (c - 'a' + 10);
        }
        return binary;
    }
    
    int read_instruction(int pc){
        if(pc/4 >= instruction_memory.size()) return -1;
        return instruction_memory[pc/4];    
    }

    string get_instruction_name(int pc){
        if(pc/4 >= instruction_memory.size()) return "";
        return instructions[pc/4];
    }

    int get_instruction_count(){
        return instruction_memory.size();
    }

    // write in IF_ID register
    void step(int pc,int instruction, IF_ID* if_id){
        if_id->set_values(pc, instruction);
    }

};

//DEPENDENT ON: pipeline_registers.cpp

int int_slice(int i, int a, int b){
	//a>=b, a and b can be between 31 and 0, 0 means the rightmost bit, 31 is the leftmost bit
	int temp = i>>b;
	int ff = ~0;
	ff = ff<<(a-b+1);
	ff = ~ff; 
	return (temp & ff);
}

// unsigned int to_unsigned(int a){
// 	if(a>=0) return (unsigned int)a;
// 	long long int temp = 1<<32; //2^32
// 	return (unsigned int)(temp + a);
// }

bool check_branch(int rs1, int rs2, int funct3) {
	switch(funct3) {
		case 0: return(rs1==rs2);
		
		case 1: return(rs1!=rs2);

		case 4: return(rs1<rs2);
		
		case 5: return(rs1>=rs2);

		case 6: return(((unsigned) rs1) < ((unsigned) rs2));

		case 7: return(((unsigned) rs1) >= ((unsigned) rs2));

		default: return 0;
	}
}

class Register_file {
	public:
		int regfile[32];
		int rr1, rr2, write_reg, write_data; //all are to be written
		int read_data1, read_data2;

		Register_file() {
			for(int i=0; i<32; i++) this->regfile[i]=0; //ONE TIME CHANGE FOR CHECKING THE CORRECTNESS
			this->rr1 = this->rr2 = this->write_reg = this->write_data = 0;
		}

		void read_data(){
			this->read_data1 = (this->regfile)[rr1];
			this->read_data2 = (this->regfile)[rr2];
		}
};

class Control {
	public:
		int opcode;
		int Branch, MemRead, MemtoReg, ALUOp, MemWrite, ALUSrc, RegWrite;
        int isJal; int isJalr;
	
		Control() {
			this->opcode = this->Branch = this->MemRead = this->MemtoReg = 0;
			this->ALUOp = this->MemWrite = this->ALUSrc = this->RegWrite=0;
            this->isJal = 0; this->isJalr = 0;
        }

		void setvalues(int instruction){
			int myop = int_slice(instruction, 6, 0);
			int Branch, MemRead, MemtoReg, ALUOp, MemWrite, ALUSrc, RegWrite;
			if(myop == 0b0110011){
				Branch = 0; MemRead = 0; MemtoReg=0; 
				ALUOp = 2;
				MemWrite = 0;
				ALUSrc = 0;
				RegWrite = 1; isJal=0; isJalr=0;
			}

			else if(myop == 0b0010011){
				Branch = 0; MemRead = 0; MemtoReg = 0; 
				ALUOp = 3; //SAME AS BEFORE
				MemWrite = 0;
				ALUSrc = 1; RegWrite = 1; isJal=0; isJalr=0;
			}

			else if(myop == 0b0000011){
				Branch = 0; MemRead = 1; MemtoReg = 1; //Because the value to be written comes from the memory
				ALUOp = 0;
				MemWrite = 0;
				ALUSrc = 1; //Immediate
				RegWrite = 1; isJal=0; isJalr=0;
			}

			else if(myop == 0b0100011){ //Store word
				Branch = 0; MemRead = 0; MemtoReg = 0; //don't care for memtoreg
				ALUOp = 0;
				MemWrite = 1;
				ALUSrc = 1;
				RegWrite = 0; isJal=0; isJalr=0;//no register writing
			}

			else if(myop == 0b1100011){
				Branch = 1; MemRead = 0; MemtoReg = 0;
				ALUOp = 1;
				MemWrite = 0;
				ALUSrc = 0;
				RegWrite = 0; isJal=0; isJalr=0;//No register writing
			}
			
			//MAYBE WE SHOULD HAVE A JUMP TYPE IN CONTROL TOO
			else if(myop == 0b1101111){ //JAL
				Branch = 0; MemRead = 0; MemtoReg = 0;
				ALUOp = 2; //NOTE: for now, it is 2 same as that for addition
				MemWrite = 0;
				ALUSrc = 0;
				RegWrite = 1; isJal=1; isJalr=0;
			}

            else if(myop == 0b1100111) { //JALR
                Branch = 0; MemRead = 0; MemtoReg = 0;
                ALUOp = 2;  //PC+4 store karne ke liye
                MemWrite = 0;
                ALUSrc = 0;
                RegWrite = 1; isJal=0; isJalr=1;
            }
			
			//CHECK IF COMPATIBLE WITH VIRAAJ'S CODE MAYBE, the OPCODE will be needed
			else if(myop == 0b0110111) { //LOAD UPPER IMMEDIATE
				Branch = 0; MemRead = 0; MemtoReg = 0;
				ALUOp = 2; //IT MUST BE SHIFT LEFT BY 12
				MemWrite = 0;
				ALUSrc = 1;
				RegWrite = 1; isJal=0; isJalr = 0;
			}

			else if (myop == 0){
				Branch = MemRead = MemtoReg = ALUOp = MemWrite = ALUSrc = RegWrite = 0;
                isJal=0; isJalr=0;
			}
			
			else {
				std::cout << "COMMAND NOT FOUND" << opcode << "\n";
				throw std::invalid_argument("Invalid");
			}
			//TODO: ADD A NO-OP CASE, + think about the implementation of lui.
			this->Branch = Branch; this->MemRead = MemRead; this->MemtoReg = MemtoReg;
			this->ALUOp = ALUOp; this->MemWrite = MemWrite; this->ALUSrc = ALUSrc;
			this->RegWrite = RegWrite;
		}

};

class Imm_Gen {
	public:
		int imm;
	
		Imm_Gen() {
			this->imm = 0;
		}
		
		void set_12(int imm_12){
			int temp = int_slice(imm_12, 11 ,11);
			this->imm = (-temp)*(1<<11) + (imm_12)%(1<<11);
		}

		void set_20(int imm_20) {
			int temp = int_slice(imm_20, 19, 19);
			this->imm = (-temp)*(1<<19) + (imm_20)%(1<<19);
		}
};

//Desired functionality: we set the instruction in one clock cycle, then we call the step()
//this will cause the following changes:
//1. input1 and input2 to the ALU
//2. all the control unit outputs
//3. immediate generation outputs
//4. ALU control outputs

class ID {
	public:
		int instruction;//can be changed to long long if needed
		Register_file registers;
		Control c_u;
		Imm_Gen im_generator;
		int id_new_pc; //this will be used to give the new pc value when branching occurs.
					//at the time of branching (whent the condition is true), the branch value would be 1
		int funct7, funct3; int rd;
        int curr_PC; int branch_taken;
		ID() {
			this->instruction = 0;
			this->id_new_pc = 0;
            this->funct7 = 0;
            this->funct3 = 0;
            this->rd = 0;
            this->curr_PC = INT_MIN;
            this->branch_taken=0;
        }
		
		void detect_op(IF_ID* if_id){ //taken from the IF/ID register
            this->curr_PC = if_id->PC;
			this->instruction = if_id->instruction;
			this->id_new_pc = if_id->PC; int instruction = this->instruction;

			int opcode = int_slice(instruction,6,0);
			this->funct3 = int_slice(instruction, 14, 12);
			this->funct7 = int_slice(instruction, 31, 25);
			if(opcode == 0b0110011){
				int rs1 = int_slice(instruction,19, 15);
				int rs2 = int_slice(instruction,24, 20);
				int rd = int_slice(instruction, 11, 7); this->rd = rd;
				this->funct7 = int_slice(instruction, 31, 25);
				this->c_u.setvalues(instruction); 
				this->registers.rr1 = rs1;
				this->registers.rr2 = rs2;
				this->registers.read_data();
				this->im_generator.imm = 0;
			}

			else if(opcode == 0b0010011 || opcode == 0b0000011 || opcode == 0b1100111){ //IMMEDIATE TYPE AND LOAD TYPE AND JALR TYPE
				int rs1 = int_slice(instruction, 19, 15);
                int rs2 = 0;
				int rd = int_slice(instruction, 11, 7); this->rd = rd;
				int immediate = int_slice(instruction, 31, 20); //these are 12 bits only, these need to be extended
				this->c_u.setvalues(instruction);
				this->registers.rr1 = rs1;
                this->registers.rr2 = rs2;
				this->registers.read_data(); 
				this->im_generator.set_12(immediate);//TODO IMMEDIATE GEN
                if(opcode == 0b1100111) { //JALR
                    this->id_new_pc = this->registers.read_data1 + this->im_generator.imm; //JALR function
                    
                    this->registers.read_data1 = if_id->PC;
                    this->registers.read_data2 = 4; //PC+4 will be stored in rd
                    this->funct3=0; this->funct7=0; //For addition                    
                }
			}

			else if(opcode == 0b0100011){ //STORE WORD
				int rd = int_slice(instruction, 11, 7); this->rd = rd;
				int rs1 = int_slice(instruction, 19,15);
				int rs2 = int_slice(instruction, 24, 20);
				int imm_11_5 = int_slice(instruction, 31, 25);
				int imm_4_0 = int_slice(instruction, 11, 7);
				int immediate_12bit = (imm_11_5<<5)|imm_4_0; //got the 12 bit immediate

				this->c_u.setvalues(instruction);
				this->registers.rr1 = rs1; this->registers.rr2 = rs2; this->registers.read_data();
				this->im_generator.set_12(immediate_12bit);//TODO IMMEDIATE GEN
			}

			else if(opcode == 0b1100011){ //BRANCH TYPE
				int rs1 = int_slice(instruction, 19, 15);
				int rs2 = int_slice(instruction, 24, 20);
				int imm_12 = int_slice(instruction, 31, 31);
				int imm_11 = int_slice(instruction, 7, 7);
				int imm_10_5 = int_slice(instruction, 30, 25);
				int imm_4_1 = int_slice(instruction, 11, 8);
				int immediate_12bit = (imm_12<<11) | (imm_11<<10) |(imm_10_5<<4) | (imm_4_1);
				
				this->c_u.setvalues(instruction);
				this->registers.rr1 = rs1; this->registers.rr2 = rs2; this->registers.read_data();
				this->im_generator.set_12(immediate_12bit);
				this->id_new_pc = if_id->PC + (this->im_generator.imm<<1); //NOTE: updated the PC value here
				this->registers.read_data();	
				this->branch_taken = check_branch(this->registers.read_data1, this->registers.read_data2, funct3) ? 1 : 0; //Branch will be zero if no branch
			}

			else if(opcode == 0b1101111){ //JUMP AND LINK
				int rd = int_slice(instruction, 11, 7); this->rd = rd;
				int imm_20 = int_slice(instruction, 31, 31);
				int imm_10_1 = int_slice(instruction, 30, 21);
				int imm_11 = int_slice(instruction, 20, 20);
				int imm_19_12 = int_slice(instruction, 19, 12);
				int immediate_20bit = (imm_20<<19) | (imm_19_12<<11 )| (imm_11<<10) | (imm_10_1);
				
				this->c_u.setvalues(instruction);
				this->im_generator.set_20(immediate_20bit);

                this->id_new_pc = if_id->PC + (this->im_generator.imm<<1);
                this->registers.rr1 = 0; this->registers.rr2 = 0;
                this->registers.read_data1=if_id->PC;
                this->registers.read_data2=4;
                this->funct3 = 0; this->funct7 = 0; //For addition
				// here, we have to this->registers.rr1 = PC. How to do that?
				//TODO : 1. think about how to give the rd to ID/EX
				//		 2. think about how to give the 30th bit and the funct3 to the ID/EX
			}

			else if(opcode == 0b0110111){ //LOAD UPPER IMMEDIATE
				int rd = int_slice(instruction, 11, 7); this->rd = rd;
				int imm_31_12 = int_slice(instruction, 31, 12);

				this->c_u.setvalues(instruction);
				this->im_generator.set_20(imm_31_12);
			}

            else if (opcode==0) {
                this->c_u.setvalues(instruction);
                this->branch_taken=0;
                this->funct3=0;
                this->funct7=0;
                this->rd=0;
                this->im_generator.imm=0;
                this->id_new_pc=0;
            }
		}

		void step(ID_EX* id_ex) {
			int PC = this->curr_PC; //if branch then that PC itself
            int opcode = int_slice(this->instruction, 6, 0);
            int rs1;
			if(opcode == 0b1100111){ rs1=0;}
            else {
                rs1 = (this->registers).rr1;
            }
			int rs2 = (this->registers).rr2;
			int read_data1 = (this->registers).read_data1;
			int read_data2 = (this->registers).read_data2;
			int imm = (this->im_generator).imm;
			int funct7 = this->funct7;
			int funct3 = this->funct3;
			int Branch = (this->c_u).Branch;
			int MemRead = (this->c_u).MemRead;
			int MemtoReg = (this->c_u).MemtoReg;
			int AluOp = (this->c_u).ALUOp;
			int MemWrite = (this->c_u).MemWrite;
			int AluSrc = (this->c_u).ALUSrc;
			int RegWrite = (this->c_u).RegWrite;
			int rd = this->rd;
			id_ex->set_values(PC, rs1, rs2, read_data1, read_data2, imm, funct7, funct3, Branch, MemRead, MemtoReg, AluOp, MemWrite, AluSrc, RegWrite, rd);
		}

};


class MUX2x1{
    public:
    int input1, input2, select;
    MUX2x1(){
        this->input1 = 0;
        this->input2 = 0;
        this->select = 0;
    }
    void set_MUX(int input1, int input2, int select){
        this->input1 = input1;
        this->input2 = input2;
        this->select = select;
    }
    int get_output(){
        return select ? input2 : input1;
    }
};


class ALU{
    public:
    int ALUresult;
    // int newPC;
    
    int AluControl(ID_EX* id_ex){
        // ll result = 0;
        int result = 0;
        if(id_ex->AluSrc){
            if(id_ex->AluOp == 0){
                // load and store instructions
                result = id_ex->read_data1 + id_ex->sign_extended_value;
            }
            else if (id_ex->AluOp == 3){
                // I-type
                // addi
                if(id_ex->funct3 == 0){
                    result = id_ex->read_data1 + id_ex->sign_extended_value;
                }
                // xori 
                else if(id_ex->funct3 == 4){
                    result = id_ex->read_data1 ^ id_ex->sign_extended_value;
                }
                // ori
                else if(id_ex->funct3 == 6){
                    result = id_ex->read_data1 | id_ex->sign_extended_value;
                }
                //andi 
                else if(id_ex->funct3 == 7){
                    result = id_ex->read_data1 & id_ex->sign_extended_value;
                }
                //slli 
                else if(id_ex->funct3 == 1){
                    result = id_ex->read_data1 << id_ex->sign_extended_value;
                }
                //srli 
                else if((id_ex->funct3 == 5) && (id_ex->funct7 == 0b0000000)){
                    result = (uint32_t)id_ex->read_data1 >> id_ex->sign_extended_value;
                }
                //srai 
                else if((id_ex->funct3 == 5) && (id_ex->funct7 == 0b0100000)){
                    result = id_ex->read_data1 >> id_ex->sign_extended_value;
                }
                // slti
                else if(id_ex->funct3 == 2){
                    if(id_ex->read_data1 < id_ex->sign_extended_value) result = 1;
                    else result = 0;
                }
                // sltiu
                else if(id_ex->funct3 == 3){
                    if((unsigned)id_ex->read_data1 < (unsigned)id_ex->sign_extended_value) result = 1;
                    else result = 0;
                }
            }
        }
        else{
            if(id_ex->AluOp == 1){
                // Branch type
                // TO BE DONE IN ID NOT IN EX STAGE
                // bne
                // if(id_ex->funct3 == 1){ 
                //     if(id_ex->read_data1 != id_ex->read_data2) result = 1;
                //     else result = 0;
                // }
                // // blt
                // if(id_ex->funct3 == 4){
                //     if(id_ex->read_data1 < id_ex->read_data2) result = 1;
                //     else result = 0;
                // }
                // // bge 
                // else if(id_ex->funct3 == 5){
                //     if(id_ex->read_data1 >= id_ex->read_data2) result = 1;
                //     else result = 0;
                // }
                // //bltu 
                // else if(id_ex->funct3 == 6){
                //     if((unsigned)id_ex->read_data1 < (unsigned)id_ex->read_data2) result = 1;
                //     else result = 0;
                // }
                // // bgeu
                // else if(id_ex->funct3 == 7){
                //     if((unsigned)id_ex->read_data1 >= (unsigned)id_ex->read_data2) result = 1;
                //     else result = 0;
                // }
            }
            else if(id_ex->AluOp == 2){
                if(id_ex->funct7 == 0b0000001){
                    // mul
                    if(id_ex->funct3 == 0){
                        result = (int)(((ll)id_ex->read_data1 * (ll)id_ex->read_data2) & 0x00000000FFFFFFFF);
                    }
                    //mulh
                    else if(id_ex->funct3 == 1){
                        ll temp = 0;
                        temp = (ll)id_ex->read_data1 * (ll)id_ex->read_data2;
                        result = temp >> 32;
                    }
                    // mulsu
                    else if(id_ex->funct3 == 2){
                        result = (int)(((ll)id_ex->read_data1 * (llu)id_ex->read_data2) & 0x00000000FFFFFFFF);
                    }
                    // mulu
                    else if(id_ex->funct3 == 3){
                        result = (int)(((llu)id_ex->read_data1 * (llu)id_ex->read_data2) & 0x00000000FFFFFFFF);
                    }
                    // div
                    else if(id_ex->funct3 == 4){
                        result = id_ex->read_data1 / id_ex->read_data2;
                    }
                    // divu
                    else if(id_ex->funct3 == 5){
                        result = (int)(((llu)id_ex->read_data1 / (llu)id_ex->read_data2) & 0x00000000FFFFFFFF);
                    }
                    // rem 
                    else if(id_ex->funct3 == 6){
                        result = id_ex->read_data1 % id_ex->read_data2;
                    }
                    // remu
                    else if(id_ex->funct3 == 7){
                        result = (int)(((llu)id_ex->read_data1 % (llu)id_ex->read_data2) & 0x00000000FFFFFFFF);
                    }
                }
                else{
                    // add
                    if((id_ex->funct3 == 0) && (id_ex->funct7 == 0b0000000)){
                        result = id_ex->read_data1 + id_ex->read_data2;
                    }
                    // sub
                    else if((id_ex->funct3 == 0) && (id_ex->funct7 == 0b0100000)){
                        result = id_ex->read_data1 - id_ex->read_data2;
                    }
                    // xor 
                    else if(id_ex->funct3 == 4){
                        result = id_ex->read_data1 ^ id_ex->read_data2;
                    }
                    // or
                    else if(id_ex->funct3 == 6){
                        result = id_ex->read_data1 | id_ex->read_data2;
                    }
                    // and
                    else if(id_ex->funct3 == 7){
                        result = id_ex->read_data1 & id_ex->read_data2;
                    }
                    // sll
                    else if(id_ex->funct3 == 1){
                        result = id_ex->read_data1 << id_ex->read_data2;
                    }
                    // srl
                    else if ((id_ex->funct3 == 5) && (id_ex->funct7 == 0b0000000)){
                        result = (uint32_t)id_ex->read_data1 >> id_ex->read_data2;
                    }
                    // sra
                    else if ((id_ex->funct3 == 5) && (id_ex->funct7 == 0b0100000)){
                        result = id_ex->read_data1 >> id_ex->read_data2; 
                    }
                    // slt
                    else if(id_ex->funct3 == 2){
                        if(id_ex->read_data1 < id_ex->read_data2) result = 1;
                        else result = 0;
                    }
                    // sltu
                    else if(id_ex->funct3 == 3){
                        if((unsigned)id_ex->read_data1 < (unsigned)id_ex->read_data2) result = 1;
                        else result = 0;
                    }                    
                }
            }
        }
        return result;
    }


    // int PC_updation(int& pc, int& offset, int& branch){
    //     if(branch){
    //         return pc + offset;
    //     }
    //     else{
    //         return pc + 4;
    //     }
    // }
    
    // returns the new PC and ALUresult
    void execute(ID_EX* id_ex/*, EX_MEM* ex_mem*/){
        // do this in main file 
        // if(ex_mem->RegWrite && (ex_mem->rd != 0)){
        //     if((ex_mem->rd == id_ex->rs1) || (ex_mem->rd == id_ex->rs2)){
        //         // yes we have a stall 
        //         // idhar kaise btau ki stall karna???
        //         // return the same PC?
        //         return {id_ex->PC,0};
        //     } 
        // }
        //id_ex->sign_extended_value <<= 1;
        int Aluresult = AluControl(id_ex);

        // int new_pc = PC_updation(id_ex->PC, id_ex->sign_extended_value, id_ex->Branch);
        
        this->ALUresult = Aluresult;
        // this->newPC = new_pc;
    }


    // write to EX_MEM register from ALU and ID_EX register
    void step(ID_EX* id_ex, EX_MEM* ex_mem){
        ex_mem->set_values(id_ex->PC, ALUresult, id_ex->read_data2, id_ex->MemRead, id_ex->MemtoReg, id_ex->MemWrite, id_ex->RegWrite, id_ex->rd, id_ex->funct3);
    }
};


class Data_Memory{
    public:
    unordered_map<int, int> memory;
    int read_data;

    Data_Memory(){
        memory.clear();
    }

    int Mem_Op(EX_MEM* ex_mem){
        if(ex_mem->MemRead){
            // load instructions
            // load byte
            if (ex_mem->funct3 == 0) {  
                int val = memory[ex_mem->ALU_result] & 0xFF;
                return (val & 0x80) ? (val | 0xFFFFFF00) : val; // sign extension
            }

            // load half
            else if (ex_mem->funct3 == 1) {  
                int val = 0;
                for (int i = 0; i < 2; i++) {
                    val |= ((int)(memory[ex_mem->ALU_result + i] & 0xFF) << (8 * i));  // Little Endian
                }
                return (val & 0x8000) ? (val | 0xFFFF0000) : val;  
            }

            // load word
            else if (ex_mem->funct3 == 2) {  
                int val = 0;
                for (int i = 0; i < 4; i++) {
                    val |= ((int)(memory[ex_mem->ALU_result + i] & 0xFF) << (8 * i));
                }
                return val;
            }

            // load doubleword
            // else if (ex_mem->funct3 == 3) {  
            //     int temp = 0;
            //     for (int i = 0; i < 8; i++) {  
            //         temp |= ((int)(memory[ex_mem->ALU_result + i] & 0xFF) << (8 * i)); 
            //     }
            //     return temp;
            // }

            // load byte unsigned
            else if (ex_mem->funct3 == 4) {  
                return memory[ex_mem->ALU_result] & 0xFF; 
            }

            // load half unsigned
            else if (ex_mem->funct3 == 5) {  
                int val = 0;
                for (int i = 0; i < 2; i++) {
                    val |= ((int)(memory[ex_mem->ALU_result + i] & 0xFF) << (8 * i));
                }
                return val & 0xFFFF; 
            }

            // load word unsigned 
            else if (ex_mem->funct3 == 6) {  
                int temp = 0;
                for (int i = 0; i < 4; i++) {  
                    temp |= ((int)(memory[ex_mem->ALU_result + i] & 0xFF) << (8 * i)); 
                }
                return temp & 0xFFFFFFFF;
            }
                    
        }
        else if(ex_mem->MemWrite){
            // store instructions
            // store byte
            if(ex_mem->funct3 == 0){
                memory[ex_mem->ALU_result] = ex_mem->read_data2 & 0xFF;
            }

            // store half
            else if(ex_mem->funct3 == 1){
                for (int i = 0; i < 2; i++) { 
                    memory[ex_mem->ALU_result + i] = (ex_mem->read_data2 >> (8 * i)) & 0xFF;
                }
            }

            // store word
            else if(ex_mem->funct3 == 2){
                for (int i = 0; i < 4; i++) {  
                    memory[ex_mem->ALU_result + i] = (ex_mem->read_data2 >> (8 * i)) & 0xFF;
                }
            }

            // store doubleword
            // else if(ex_mem->funct3 == 0){
            //     for (int i = 0; i < 8; i++) {  
            //         memory[ex_mem->ALU_result + i] = (ex_mem->read_data2 >> (8 * i)) & 0xFF; 
            //     }
            // }
        }
        return 0;
    }

    void operate(EX_MEM* ex_mem){
        this->read_data = Mem_Op(ex_mem);
    }
    
    void step(EX_MEM* ex_mem, MEM_WB* mem_wb){
        mem_wb->set_values(ex_mem->ALU_result, this->read_data, ex_mem->MemtoReg, ex_mem->RegWrite, ex_mem->rd, ex_mem->PC);
    }
};


class Write_Back{
	public:
	void Write(MEM_WB* mem_wb, ID* id_obj) {
		if((!mem_wb->RegWrite) || (mem_wb->rd==0)) return; //no writing
		if(mem_wb->MemtoReg) id_obj->registers.regfile[mem_wb->rd] = mem_wb->read_data;
		else id_obj->registers.regfile[mem_wb->rd] = mem_wb->ALU_result;
	}
};


class Hazard_detect_NO_forward{
    public:

    bool detect(ID_EX* id_ex, EX_MEM* ex_mem, ID* id){
        if((id_ex->RegWrite) && (id_ex->rd != 0) && (id->registers.rr1 == id_ex->rd)){
            return true;
        }
        else if ((id_ex->RegWrite) && (id_ex->rd != 0) && (id->registers.rr2 == id_ex->rd)){
            return true;
        }

        if ((ex_mem->RegWrite) && (ex_mem->rd != 0) && (id->registers.rr1 == ex_mem->rd)){
            return true;
        }
        else if ((ex_mem->RegWrite) && (ex_mem->rd != 0) && (id->registers.rr2 == ex_mem->rd)){
            return true;
        }
        
        return false;
    }
};


class ALU_Forwarding_unit{

    public:
    int ForwardA, ForwardB;
    ALU_Forwarding_unit(){
        this->ForwardA = 0;
        this->ForwardB = 0;
    }

    void Check_Forwarding(ID_EX* id_ex, EX_MEM* ex_mem, MEM_WB* mem_wb){
        // forwarding A
        if(ex_mem->RegWrite && (ex_mem->rd != 0) && (ex_mem->rd == id_ex->rs1)){
            this->ForwardA = 2;
        }
        else if(mem_wb->RegWrite && (mem_wb->rd != 0)  &&(mem_wb->rd == id_ex->rs1)){
            this->ForwardA = 1;
        }
        else{
            this->ForwardA = 0;
        }
        // forwarding B
        if(ex_mem->RegWrite && (ex_mem->rd != 0) && (ex_mem->rd == id_ex->rs2)){
            this->ForwardB = 2;
        }
        else if(mem_wb->RegWrite && (mem_wb->rd != 0) && (mem_wb->rd == id_ex->rs2)){
            this->ForwardB = 1;
        }
        else{
            this->ForwardB = 0;
        }
    }

    void reset(){
        this->ForwardA = 0;
        this->ForwardB = 0;
    }
};

class Branch_Forwarding_unit{
    public:
    int ForwardA, ForwardB;
    Branch_Forwarding_unit(){
        this->ForwardA = 0;
        this->ForwardB = 0;
    }

    // for ID stage
    void Check_Forwarding(ID*ID_stage, EX_MEM* ex_mem, MEM_WB* mem_wb){
        if(ex_mem->RegWrite && (ex_mem->rd != 0) && (ex_mem->rd == ID_stage->registers.rr1)){
            this->ForwardA = 2;
        }
        else if(mem_wb->RegWrite && (mem_wb->rd != 0) && (!(ex_mem->RegWrite && (ex_mem->rd != 0))) &&(mem_wb->rd == ID_stage->registers.rr1)){
            this->ForwardA = 1;
        }
        else{
            this->ForwardA = 0;
        }
        // forwarding B
        if(ex_mem->RegWrite && (ex_mem->rd != 0) && (ex_mem->rd == ID_stage->registers.rr2)){
            this->ForwardB = 2;
        }
        else if(mem_wb->RegWrite && (mem_wb->rd != 0) && (!(ex_mem->RegWrite && (ex_mem->rd != 0))) &&(mem_wb->rd == ID_stage->registers.rr2)){
            this->ForwardB = 1;
        }
        else{
            this->ForwardB = 0;
        }
    }

    void reset(){
        this->ForwardA = 0;
        this->ForwardB = 0;
    }
};


class Hazard_detect_forward{
    public:
    bool detect(ID_EX* id_ex, EX_MEM* ex_mem, ID* ID_stage){
        
        // load instruction ke baad agar branch to 2 stall else 1 stall

        // requirement in ALU stage
        // agar yeh instruction branch nhi hai tbhi toh stall hoga
        
        // if(ex_mem->MemRead && (ex_mem->rd != 0) && (ex_mem->rd == id_ex->rs1)){
        //     return true;
        // }
        // else if(ex_mem->MemRead && (ex_mem->rd != 0) && (ex_mem->rd == id_ex->rs2)){
        //     return true;
        // }

        // branch se pehle load/store ke alawa to 1 stall aaega 

        // requirement in ID stage
        // from MEM stage
        if(id_ex->MemRead && (id_ex->rd != 0) && (id_ex->rd == ID_stage->registers.rr1)){
            return true;
        }
        else if(id_ex->MemRead && (id_ex->rd != 0) && (id_ex->rd == ID_stage->registers.rr2)){
            return true;
        }

        // from EX stage
        int opcode = int_slice(ID_stage->instruction, 6, 0);
        if(opcode == 0b1100011 || opcode == 0b1100111){    // branch type
            if(id_ex->RegWrite && (id_ex->rd != 0) && (id_ex->rd == ID_stage->registers.rr1)){
                return true;
            }
            else if(id_ex->RegWrite && (id_ex->rd != 0) && (id_ex->rd == ID_stage->registers.rr2)){
                return true;
            }

            if(ex_mem->MemRead && (ex_mem->rd != 0) && (ex_mem->rd == ID_stage->registers.rr1)){
                return true;
            }
            else if(ex_mem->MemRead && (ex_mem->rd != 0) && (ex_mem->rd == ID_stage->registers.rr2)){
                return true;
            }
        }

        return false;
    }
};

#endif 
