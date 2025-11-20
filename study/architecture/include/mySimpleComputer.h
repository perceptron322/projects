#pragma once

#include "myTerm.h"
#include <stdio.h>

#define MEMORY_SIZE 128

#define FLAG_P 0b10000
#define FLAG_0 0b1000
#define FLAG_M 0b100
#define FLAG_T 0b10
#define FLAG_E 0b1

#define C_NOP 0
#define C_CPUINFO 1

#define C_READ 10
#define C_WRITE 11

#define C_LOAD 20
#define C_STORE 21

#define C_ADD 30
#define C_SUB 31
#define C_DIVIDE 32
#define C_MUL 33

#define C_JUMP 40
#define C_JNEG 41
#define C_JZ 42
#define C_HALT 43

#define C_NOT 51
#define C_AND 52
#define C_OR 53
#define C_XOR 54
#define C_JNS 55
#define C_JC 56
#define C_JNC 57
#define C_JP 58
#define C_JNP 59

#define C_CHL 60
#define C_SHR 61
#define C_RCL 62
#define C_RCR 63
#define C_NEG 64
#define C_ADDC 65
#define C_SUBC 66
#define C_LOGLC 67

#define C_LOGRC 68
#define C_RCCL 69
#define C_RCCR 70
#define C_MOVA 71
#define C_MOVR 72
#define C_MOVСA 73
#define C_MOVСR 74
#define C_ADDC2 75
#define C_SUBC2 76
#define C_ASSIGN1 99

// -- Memory --
int sc_memoryInit (void);
int sc_memorySet (int address, int value);
int sc_memoryGet (int address, int *value);
int sc_memorySave (char *filename);
int sc_memoryLoad (char *filename);

// -- Registers --
int sc_regInit (void);
int sc_regSet (int reg, int value);
int sc_regGet (int reg, int *value);

// -- Accumulator --
int sc_accumulatorInit (void);
int sc_accumulatorSet (int value);
int sc_accumulatorGet (int *value);

// -- Icounter --
int sc_icounterInit (void);
int sc_icounterSet (int value);
int sc_icounterGet (int *value);
void sc_icounterIncrement ();

// -- Command --
int sc_commandEncode (int sign, int command, int operand, int *value);
int sc_commandDecode (int value, int *sign, int *command, int *operand);
int sc_commandValidate (int command);

// -- Print --
void printAccumulator (void);
void printCell (int address, enum colors fg, enum colors bg);
void printDecodedCommand (int value);
void printFlags (void);
void printCounters (void);
void printCommand (void);
void printCasheLine (int line);

void addTerm (int address, int input);
void termInit ();
void printTerm (int x, int y);

void sc_casheInit ();
void addToCashe (int line);
void cashePrior (int line);

int cu_memoryGet (int address, int *value);
int cu_memorySet (int address, int value);

int mk_get (int address, int *value);
int mk_Set (int address, int value);