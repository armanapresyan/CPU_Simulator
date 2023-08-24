#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>

// Registers
int AYB, BEN, GIM, DA, EC, ZA, GH;

// Memory
std::vector<int> memory(32);

// Instructions
enum Instructions {
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
    JE
};

// Parse the instruction and arguments from a line of code
void parseInstruction(const std::string& line, int& instruction, int& arg1, int& arg2) {
    std::istringstream iss(line);
    std::string opcode;
    iss >> opcode >> arg1 >> arg2;

    if (opcode == "MOV") instruction = MOV;
    else if (opcode == "ADD") instruction = ADD;
    else if (opcode == "SUB") instruction = SUB;
    else if (opcode == "MUL") instruction = MUL;
    else if (opcode == "DIV") instruction = DIV;
    else if (opcode == "AND") instruction = AND;
    else if (opcode == "OR") instruction = OR;
    else if (opcode == "NOT") instruction = NOT;
    else if (opcode == "CMP") instruction = CMP;
    else if (opcode == "JMP") instruction = JMP;
    else if (opcode == "JG") instruction = JG;
    else if (opcode == "JL") instruction = JL;
    else if (opcode == "JE") instruction = JE;
}

// Execute the given instruction with arguments
void executeInstruction(int instruction, int arg1, int arg2) {
    switch (instruction) {
        case MOV:
            arg2 == AYB ? AYB = arg1 : memory[arg2] = arg1;
            break;
        case ADD:
            AYB = AYB + arg1;
            break;
        case SUB:
            AYB = AYB - arg1;
            break;
        case MUL:
            AYB = AYB * arg1;
            break;
        case DIV:
            AYB = AYB / arg1;
            break;
        case AND:
            AYB = AYB & arg1;
            break;
        case OR:
            AYB = AYB | arg1;
            break;
        case NOT:
            AYB = ~AYB;
            break;
        case CMP:
            DA = AYB - arg1;
            if (DA > 0) ZA = 1;  // Set greater flag
            else if (DA < 0) ZA = -1;  // Set less flag
            else ZA = 0;  // Set equal flag
            break;
        case JMP:
            GH = arg1;
            break;
        case JG:
            if (ZA == 1) GH = arg1;
            break;
        case JL:
            if (ZA == -1) GH = arg1;
            break;
        case JE:
            if (ZA == 0) GH = arg1;
            break;
    }
}

// Dump memory contents
void dump_memory() {
    for (int i = 0; i < memory.size(); ++i) {
        std::cout << "[" << i << "]: " << memory[i] << std::endl;
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cout << "Failed to open input file." << std::endl;
        return 1;
    }

    std::vector<std::string> instructions;
    std::string line;
    while (std::getline(inputFile, line)) {
        instructions.push_back(line);
    }

    // Load instructions into memory
    for (int i = 0; i < instructions.size(); ++i) {
        int instruction, arg1, arg2;
        parseInstruction(instructions[i], instruction, arg1, arg2);
        memory[i] = (instruction << 16) | (arg1 << 8) | arg2;
    }

    // Start execution from address 0
    GH = 0;

    // Execute instructions
    while (GH < instructions.size()) {
        int instruction = memory[GH] >> 16;
        int arg1 = (memory[GH] >> 8) & 0xFF;
        int arg2 = memory[GH] & 0xFF;

        executeInstruction(instruction, arg1, arg2);

        ++GH;
    }

    // Dump memory contents after execution
    dump_memory();

    return 0;
}
