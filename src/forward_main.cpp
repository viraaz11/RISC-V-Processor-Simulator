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
    ALU_Forwarding_unit* ALU_Forward_unit = new ALU_Forwarding_unit();
    Branch_Forwarding_unit* Branch_Forward_unit = new Branch_Forwarding_unit();
    Hazard_detect_forward* HD_stage = new Hazard_detect_forward();
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

        // do forwarding if required then check hazard 
        
        if(HD_stage->detect(ID_EX_reg, EX_MEM_reg, ID_stage)){
            ALU_Forward_unit->Check_Forwarding(ID_EX_reg, EX_MEM_reg, MEM_WB_reg);
            switch(ALU_Forward_unit->ForwardA){
                case 0: break;
                case 1: ID_EX_reg->read_data1 = MEM_WB_reg->read_data;
                        break;
                case 2: ID_EX_reg->read_data1 = EX_MEM_reg->ALU_result;
                        break;
            }

            switch(ALU_Forward_unit->ForwardB) {
                case 0: break;
                case 1: ID_EX_reg->read_data2 = MEM_WB_reg->read_data;
                        break;
                case 2: ID_EX_reg->read_data2 = EX_MEM_reg->ALU_result;
                        break;
            }

            ALU_stage->execute(ID_EX_reg);
            DM_stage->operate(EX_MEM_reg);
            DM_stage->step(EX_MEM_reg, MEM_WB_reg);
            ALU_stage->step(ID_EX_reg, EX_MEM_reg);
            ID_EX_reg->Flush();
            cycle++;
            ALU_Forward_unit->reset();
            continue;
        }      
        
        Branch_Forward_unit->Check_Forwarding(ID_stage, EX_MEM_reg, MEM_WB_reg);
        
        //checking forwarding 
        ID_stage->branch_taken = 0;
        if(ID_stage->c_u.Branch) {
            switch(Branch_Forward_unit->ForwardA){
                case 0: break;
                case 1: ID_stage->registers.read_data1 = MEM_WB_reg->read_data;
                        break;
                case 2: ID_stage->registers.read_data1 = EX_MEM_reg->ALU_result;
                        break;
            }
            switch(Branch_Forward_unit->ForwardB) {
                case 0: break;
                case 1: ID_stage->registers.read_data2 = MEM_WB_reg->read_data;
                        break;
                case 2: ID_stage->registers.read_data2 = EX_MEM_reg->ALU_result;
                        break;
            }

            ID_stage->branch_taken = check_branch(ID_stage->registers.read_data1, ID_stage->registers.read_data2, ID_stage->funct3) ? 1 : 0; //Branch will be zero if no branch
        }
        else if(ID_stage->c_u.isJalr) {
            switch(Branch_Forward_unit->ForwardA) {
                case 0: break;
                case 1: ID_stage->id_new_pc = MEM_WB_reg->read_data + ID_stage->im_generator.imm;
                        break;
                case 2: ID_stage->id_new_pc = EX_MEM_reg->ALU_result + ID_stage->im_generator.imm;
                        break;
            }
        }
        // checking branch taken or not
        if(ID_stage->branch_taken && ID_stage->c_u.Branch || ID_stage->c_u.isJalr || ID_stage->c_u.isJal){
            ID_stage->branch_taken = 0;
            
            ALU_Forward_unit->Check_Forwarding(ID_EX_reg, EX_MEM_reg, MEM_WB_reg);
            switch(ALU_Forward_unit->ForwardA){
                case 0: break;
                case 1: {
                        if(MEM_WB_reg->MemtoReg) ID_EX_reg->read_data1 = MEM_WB_reg->read_data;
                        else ID_EX_reg->read_data1 = MEM_WB_reg->ALU_result;
                        break;
                }
                case 2: ID_EX_reg->read_data1 = EX_MEM_reg->ALU_result;
                        break;
            }

            switch(ALU_Forward_unit->ForwardB) {
                case 0: break;
                case 1: {
                        if(MEM_WB_reg->MemtoReg) ID_EX_reg->read_data2 = MEM_WB_reg->read_data;
                        else ID_EX_reg->read_data2 = MEM_WB_reg->ALU_result;
                        break;
                }
                case 2: ID_EX_reg->read_data2 = EX_MEM_reg->ALU_result;
                        break;
            }

			ALU_stage->execute(ID_EX_reg);
            DM_stage->operate(EX_MEM_reg);
            DM_stage->step(EX_MEM_reg, MEM_WB_reg);
            ALU_stage->step(ID_EX_reg, EX_MEM_reg);
            ID_stage->step(ID_EX_reg);
            IF_ID_reg->Flush();
            pc = ID_stage->id_new_pc;
            cycle++;    
            ALU_Forward_unit->reset();
            Branch_Forward_unit->reset();
            continue;
        }
        else {
            ID_stage->branch_taken = 0;
        }

        // EX STAGE here do forwarding if required before calling the execute function
        ALU_Forward_unit->Check_Forwarding(ID_EX_reg, EX_MEM_reg, MEM_WB_reg);
        switch(ALU_Forward_unit->ForwardA){
            case 0: break;
            case 1: {
                    if(MEM_WB_reg->MemtoReg) ID_EX_reg->read_data1 = MEM_WB_reg->read_data;
                    else ID_EX_reg->read_data1 = MEM_WB_reg->ALU_result;
                    break;
            }
            case 2: ID_EX_reg->read_data1 = EX_MEM_reg->ALU_result;
                    break;
        }

        switch(ALU_Forward_unit->ForwardB) {
            case 0: break;
            case 1:  {
                    if(MEM_WB_reg->MemtoReg) ID_EX_reg->read_data2 = MEM_WB_reg->read_data;
                    else ID_EX_reg->read_data2 = MEM_WB_reg->ALU_result;
                    break;
            }
            case 2: ID_EX_reg->read_data2 = EX_MEM_reg->ALU_result;
                    break;
        }

        ALU_stage->execute(ID_EX_reg);

        // MEM STAGE
        DM_stage->operate(EX_MEM_reg);

        // MEM_WB REG WRITE
        DM_stage->step(EX_MEM_reg, MEM_WB_reg);

        // EX_MEM REG WRITE
        ALU_stage->step(ID_EX_reg, EX_MEM_reg);

        // ID_EX REG WRITE
        ID_stage->step(ID_EX_reg);
        ALU_Forward_unit->reset();
        Branch_Forward_unit->reset();
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
    // for(int i = 0; i<32; i++) cout<<ID_stage->registers.regfile[i]<<' ';
    // cout<<endl;

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
    // output_file_name += "_forward_out.txt";
    int maxi  = 0;
    for(int i=0;i<total_instruction;i++){
        int size = IF_stage->get_instruction_name(i*4).size();
        maxi = max(maxi, size);
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

    // for(int i=0; i<total_instruction; i++){
    //     string inst = IF_stage->get_instruction_name(i*4);
    //     cout<<inst;
    //     for(int i = inst.size();i<=12;i++) cout<<' ';
    //     cout<<": ";
    //     for(int j=0; j<max_cycle_cnt; j++){
    //         string temp = output[i][j];
    //         int k = temp.size();
    //         if(k) cout<<' '<<temp<<' ';
    //         else cout<<"    ";
    //         cout<<";";
    //     }
    //     cout<<endl;
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

