#include<bits/stdc++.h>
using namespace std;
#include"components.hpp"

int main(int argc, char*argv[]){
    if(argc != 3){
        cout << "Usage: ./a.out <input_file> <cycle_count>\n";
        return 1;
    }
    string input_file = argv[1];
    int max_cycle_cnt = stoi(argv[2]);

    // STAGES
    Instruction_Memory* IF_stage = new Instruction_Memory(input_file);
    ID* ID_stage = new ID();
    ALU* ALU_stage = new ALU();
    // Forwarding_unit* FU_stage = new Forwarding_unit();
    Hazard_detect_NO_forward* HD_stage = new Hazard_detect_NO_forward();
    Data_Memory* DM_stage = new Data_Memory();
    Write_Back* WB_stage = new Write_Back();

    // PIPELINE REGISTERS
    IF_ID* IF_ID_reg = new IF_ID();
    ID_EX* ID_EX_reg = new ID_EX();
    EX_MEM* EX_MEM_reg = new EX_MEM();
    MEM_WB* MEM_WB_reg = new MEM_WB();
    
    // for printing the pipeline diagram
    vector<vector<int>> diagram(max_cycle_cnt, vector<int>(5, INT_MIN));

    int cycle = 0;
    int pc = 0;
    int total_instruction = IF_stage->get_instruction_count();

    while(cycle<max_cycle_cnt){
        // cout<<"Cycle: "<<cycle<<endl;
        // cout<<"PC: "<<pc<<endl;

        // IF STAGE
        int instruction = -1;
        if(pc/4 < total_instruction){
            instruction = IF_stage->read_instruction(pc); // write in IF_ID register in the end of this clock cycle
            diagram[cycle][0] = pc;
        }

        diagram[cycle][1] = IF_ID_reg->PC;
        diagram[cycle][2] = ID_EX_reg->PC;
        diagram[cycle][3] = EX_MEM_reg->PC;
        diagram[cycle][4] = MEM_WB_reg->PC;

        // WRITE BACK STAGE
        WB_stage->Write(MEM_WB_reg, ID_stage);

        // ID STAGE and hazard detection stage
        ID_stage->detect_op(IF_ID_reg);
        
        if(HD_stage->detect(ID_EX_reg, EX_MEM_reg, ID_stage)){
            ALU_stage->execute(ID_EX_reg);
            DM_stage->operate(EX_MEM_reg);
            DM_stage->step(EX_MEM_reg, MEM_WB_reg);
            ALU_stage->step(ID_EX_reg, EX_MEM_reg);
            ID_EX_reg->Flush();
            cycle++;
            continue;
        }      
        
        // checking branch taken or not
        if(ID_stage->branch_taken || ID_stage->c_u.isJal || ID_stage->c_u.isJalr){
            ID_stage->branch_taken= 0;
			ALU_stage->execute(ID_EX_reg);
            DM_stage->operate(EX_MEM_reg);
            DM_stage->step(EX_MEM_reg, MEM_WB_reg);
            ALU_stage->step(ID_EX_reg, EX_MEM_reg);
            ID_stage->step(ID_EX_reg);
            IF_ID_reg->Flush();
            pc = ID_stage->id_new_pc;
            cycle++;    
            continue;
        }

        // EX STAGE
        ALU_stage->execute(ID_EX_reg);

        // MEM STAGE
        DM_stage->operate(EX_MEM_reg);

        // MEM_WB REG WRITE
        DM_stage->step(EX_MEM_reg, MEM_WB_reg);

        // EX_MEM REG WRITE
        ALU_stage->step(ID_EX_reg, EX_MEM_reg);

        // ID_EX REG WRITE
        ID_stage->step(ID_EX_reg);

        // IF_ID REG WRITE
        if(instruction != -1){
            IF_stage->step(pc,instruction, IF_ID_reg);
        }
        else {
            IF_ID_reg->Flush();
        }



        // cout<<"IF_ID: "<<IF_ID_reg->instruction<<endl;
        // cout<<endl;
        pc+=4;
        cycle++;
    }  
    
    // print the pipeline diagram
    // sahi aaya
    // for(int i = 0;i<max_cycle_cnt;i++){
    //     cout<<"Cycle: "<<i<<endl;
    //     cout<<"IF: "<<diagram[i][0]<<endl;
    //     cout<<"ID: "<<diagram[i][1]<<endl;
    //     cout<<"EX: "<<diagram[i][2]<<endl;
    //     cout<<"MEM: "<<diagram[i][3]<<endl;
    //     cout<<"WB: "<<diagram[i][4]<<endl;
    //     cout<<endl;
    // }
	
	vector<vector<string>> output(total_instruction, vector<string> (max_cycle_cnt, ""));
    for(int i=0; i<max_cycle_cnt; i++){
        for(int j=0; j<5; j++){
            if(diagram[i][j] == INT_MIN) continue;
            else if (diagram[i][j] == -1) continue;
            else {
                int k = diagram[i][j]/4;
                switch(j){
                    case 0: output[k][i] = "IF";
                            break;
                    case 1: output[k][i] = "ID";
                            break;
                    case 2: output[k][i] = "EX";
                            break;
                    case 3: output[k][i] = "ME";
                            break;
                    case 4: output[k][i] = "WB";
                            break;
                }                
            }
        }
    }
    // string output_file_name = "";
    // int start = 0;
    // if(input_file[start] == '.') start = 2;
    // for(int i=start;i<input_file.size();i++){
    //     if(input_file[i] == '.') break;
    //     output_file_name += input_file[i];
    // }
    // output_file_name += "_noforward_out.txt";
    int maxi  = 0;
    for(int i=0;i<total_instruction;i++){
        int size = IF_stage->get_instruction_name(i*4).size();
        maxi = max(maxi, size);
    }

    for(int i=0; i<total_instruction; i++){
        string inst = IF_stage->get_instruction_name(i*4);
        cout<<inst;
        for(int i = inst.size();i<=maxi+1;i++) cout<<' ';
        cout<<"; ";
        for(int j=0; j<max_cycle_cnt; j++){
            string temp = output[i][j];
            int k = temp.size();
            if(k) cout<<' '<<temp<<' ';
            else cout<<"    ";
            cout<<";";
        }
        cout<<endl;
    }

    // ofstream file(output_file_name);
    // if (file.is_open()) {
    //     for(int i=0; i<total_instruction; i++){
    //         string inst = IF_stage->get_instruction_name(i*4);
    //         file<<inst;
    //         for(int i = inst.size();i<=maxi+1;i++) file<<' ';
    //         file<<"; ";
    //         for(int j=0; j<max_cycle_cnt; j++){
    //             string temp = output[i][j];
    //             int k = temp.size();
    //             if(k) file<<' '<<temp<<' ';
    //             else file<<"    ";
    //             file<<";";
    //         }
    //         file<<endl;
    //     }
    //     file.close();
    // } 
    // else {
    //     std::cerr << "Error opening file to write!" << std::endl;
    // }

    delete(IF_stage);
    delete(ID_stage);
    delete(ALU_stage);
    delete(HD_stage);
    delete(DM_stage);
    delete(WB_stage);
    delete(IF_ID_reg);
    delete(ID_EX_reg);
    delete(EX_MEM_reg);
    delete(MEM_WB_reg);
    return 0;
}

