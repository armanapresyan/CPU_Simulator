#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>



enum class Opcode{
  MOV,
  ADD,
  SUB,
  MUL,
  DIV,
  AND,
  OR,
  NOT,
  CMP,
  JMP,
  JG,
  JL,
  JE,
  NAN = false
};

enum class Register{
  AYB,
  BEN,
  GIM,
  DA,
  ECH,
  ZA,
  NAN = false
};



class Instruction{
public:
   Opcode getOpcode() const {
        return m_opcode;
    }

    
    Register getDestinationReg() const {
        return m_destination_reg;
    }

    
    Register getSourceReg() const {
        return m_source_reg;
    }

   

    bool getIsImm() const {
        return m_is_imm;
    }

    
    int getTarget() const {
        return m_target;
    }

    int getImmVal() const{
        return m_value_imm;
    }

    int getRegVal() const{
        return m_value_reg;
    }

    
    void setOpcode(Opcode op) {
        m_opcode = op;
    }
 
    void setImmVal(int val){
       m_value_imm = val;
    }

    void setRegVal(int val){
        m_value_reg = val;
    }
   
    void setDestinationReg(Register reg) {
        m_destination_reg = reg;
    }

    void setSourceReg(Register reg) {
        m_source_reg = reg;
    }


    
    void setIsImm(bool imm) {
        m_is_imm = imm;
    }

   
    void setTarget(int tgt) {
        m_target = tgt;
    }



private:
    Opcode m_opcode;
    Register m_destination_reg;
    Register m_source_reg; 
    int m_value_imm;
    bool m_is_imm;
    int m_target;
    int m_value_reg;

};

std::map<int, Instruction> code;



class CPU{
public:

  Opcode get_opcode(std::string lexem){
       if(lexem == "MOV"){
        return Opcode::MOV;
       }else if(lexem == "ADD"){
        return Opcode::ADD;
       }else if(lexem == "SUB"){
        return Opcode::SUB;
       }else if(lexem == "SUB"){
        return Opcode::SUB;
       }else if(lexem == "MUL"){
        return Opcode::MUL;
       }else if(lexem == "DIV"){
        return Opcode::DIV;
       }
       return Opcode::NAN;
  }

  
  Register get_Register(std::string lexem){
    if(lexem == "AYB"){
        return Register::AYB;
    }else if(lexem == "BEN"){
        return Register::BEN;
    }else if(lexem == "GIM"){
        return Register::GIM;
    }else if(lexem == "DA"){
        return Register::DA;
    }else if(lexem == "ECH"){
        return Register::ECH;
    }else if(lexem == "ZA"){
        return Register::ZA;
    }
    return Register::NAN;
  }

public:

void MOV(Opcode opcode,Register des, Register srcReg, int src, int reg,int address, bool is_imm){
if(is_imm){
   if (des == Register::AYB || des == Register::BEN || des == Register::GIM ||
        des == Register::DA || des == Register::ECH || des == Register::ZA) {  
        reg = src;
        code[address].setRegVal(reg);
    }else{
        std::cout<<"Invalid Register"<<std::endl;
    }
 }
 
}

void ADD(Register des, int src, int reg, int address, bool is_imm) {
if(is_imm){
  if(des == Register::AYB || des == Register::BEN || des == Register::GIM ||
        des == Register::DA || des == Register::ECH || des == Register::ZA) {
            
         int getVal = code[static_cast<int>(des)].getRegVal();
         int sum = getVal + src;
         code[static_cast<int>(des)].setRegVal(sum);
        } else{
            std::cout<<"Invalid Register"<<std::endl;
        }
    }   
}


void  SUB(Register des, int src, int reg, int address, bool is_imm) {
     if(is_imm){
        if(des == Register::AYB || des == Register::BEN || des == Register::GIM ||
         des == Register::DA || des == Register::ECH || des == Register::ZA) {    
         int getVal = code[static_cast<int>(des)].getRegVal();
         int sum = getVal - src;
         code[static_cast<int>(des)].setRegVal(sum);
        }else{
            std::cout<<"Invalid Register"<<std::endl;
        } 
     }else{

     }

}
void  MUL(Register des, int src, int reg, int address, bool is_imm){
      if(is_imm){
        if(des == Register::AYB || des == Register::BEN || des == Register::GIM ||
         des == Register::DA || des == Register::ECH || des == Register::ZA) {    
         int getVal = code[static_cast<int>(des)].getRegVal();
         int sum = getVal * src;
         code[static_cast<int>(des)].setRegVal(sum);
        }else{
            std::cout<<"Invalid Register"<<std::endl;
        } 
     }else{

     }   
}
void  DIV(Register des, int src, int reg, int address, bool is_imm) {
      if(is_imm){
        if(des == Register::AYB || des == Register::BEN || des == Register::GIM ||
         des == Register::DA || des == Register::ECH || des == Register::ZA) {    
         int getVal = code[static_cast<int>(des)].getRegVal();
         int sum = getVal / src;
         code[static_cast<int>(des)].setRegVal(sum);
        }else{
            std::cout<<"Invalid Register"<<std::endl;
        } 
     }else{

     }  
}

public:
 void parse(std::string line, int address) {
    std::string token;
    std::vector<std::string> tokens;
    std::istringstream tokenizer(line);
    while (tokenizer >> token) {
        size_t commaPos = token.find(",");
        while (commaPos != std::string::npos) {
            tokens.push_back(token.substr(0, commaPos));
            token = token.substr(commaPos + 1);
            commaPos = token.find(",");
        }
        tokens.push_back(token);
       
        
      
    }
     Instruction tmp;
       tmp.setOpcode(get_opcode(tokens[0]));
        tmp.setTarget(address);
        tmp.setDestinationReg(get_Register(tokens[1]));
        tmp.setSourceReg(get_Register(tokens[3]));
        if(tmp.getDestinationReg() != Register::NAN){
             tmp.setRegVal(0);
        }

        if (tmp.getSourceReg() == Register::NAN) { 
            tmp.setIsImm(true);
            tmp.setImmVal(std::stoi(tokens[3]));
        } else {
            tmp.setIsImm(false);
        }
       
        code[address] = tmp;
        tokens.clear();
        
}

 void execute(std::map<int, Instruction>& code){
      
   for (const auto& entry : code) {
            int address = entry.first;
            const Instruction& instr = entry.second;
            int i_value = instr.getImmVal();
            int r_value = instr.getRegVal();
            bool is_imm = instr.getIsImm();
            Opcode opcode = instr.getOpcode();

            if(instr.getOpcode() == Opcode::MOV){     
                MOV(opcode, instr.getDestinationReg(), instr.getSourceReg(), i_value, r_value, address, is_imm);
            }
            if(instr.getOpcode() == Opcode::ADD){
                ADD(instr.getDestinationReg(), i_value, r_value, address, is_imm);
            }
            if(instr.getOpcode() == Opcode::SUB){
                SUB(instr.getDestinationReg(), i_value, r_value, address, is_imm);
            }
            if(instr.getOpcode() == Opcode::MUL){
                MUL(instr.getDestinationReg(), i_value, r_value, address, is_imm);
            }
            if(instr.getOpcode() == Opcode::DIV){
                DIV(instr.getDestinationReg(), i_value, r_value, address, is_imm);
            }
            
   }

}
 
};




int main(){

int line = 0;
std::string file = "code.txt";

std::ifstream input(file);
  
CPU cpu;
if (input.is_open()) {
        std::string lineText;
        while (std::getline(input, lineText)) {
            cpu.parse(lineText, line);
            line++;
            
        }

        input.close();
    } 

cpu.execute(code);

  for (std::map<int, Instruction>::const_iterator it = code.begin(); it != code.end(); ++it) {
    std::cout << "Address: " << it->first << std::endl;
    const Instruction& instr = it->second;
    std::cout << "Opcode: " << static_cast<int>(instr.getOpcode()) << std::endl;
    std::cout << "Destination Register: " << static_cast<int>(instr.getDestinationReg()) << std::endl;
    std::cout << "Source Register: " << static_cast<int>(instr.getSourceReg()) << std::endl;
    std::cout << "Immediate: " << instr.getImmVal() << std::endl;
    std::cout << "reg: " << instr.getRegVal() << std::endl;
    std::cout << "Is Immediate: " << instr.getIsImm() << std::endl;
    std::cout << "Target: " << instr.getTarget() << std::endl;
    std::cout << "--------" << std::endl;
}

return 0;
}