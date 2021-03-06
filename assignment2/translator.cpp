// convert Hack VM Code into Hack Assembler

#include "iobuffer.h"
#include "tokeniser.h"
#include "assembler-internal.h"

// to make out programs a bit neater
using namespace std ;

using namespace CS_IO_Buffers ;
using namespace Hack_Virtual_Machine ;

////////////////////////////////////////////////////////////////
/************     MODIFY CODE BETWEEN HERE     **************/
int count=0;
static int symbolcount=0;
static string name;
// translate vm operator command into assembly language
static void translate_vm_operator(TokenKind the_op)
{   string className = name.substr(0,name.find("."));
    start_of_vm_operator_command(the_op) ;

    // ... your code goes here ...
     // * vm_operator ::= 'add' | 'and' | 'eq' | 'gt' | 'lt' | 'neg' | 'not' | 'or' | 'sub' | 'return'
    switch (the_op){
        case tk_add:
            output_assembler("@SP");
            output_assembler("AM=M-1");
            output_assembler("D=M");
            output_assembler("A=A-1");
            output_assembler("M=D+M");
        break;
        case tk_and:
            output_assembler("@SP");
            output_assembler("AM=M-1");
            output_assembler("D=M");
            output_assembler("A=A-1");
            output_assembler("M=D&M");
            break;
        case tk_eq:
            output_assembler("@SP");
            output_assembler("AM=M-1");
            output_assembler("D=M");
            output_assembler("A=A-1");
            output_assembler("D=D-M");
            output_assembler("@"+name+"$EQ_"+to_string(symbolcount));
            output_assembler("D;JNE");
            output_assembler("@SP");
            output_assembler("A=M-1");
            output_assembler("M=-1");
            output_assembler("@"+name+"$END_"+to_string(symbolcount));
            output_assembler("0;JMP");
            output_assembler("("+name+"$EQ_"+to_string(symbolcount)+")");
            output_assembler("@SP");
            output_assembler("A=M-1");
            output_assembler("M=0");
            output_assembler("("+name+"$END_"+to_string(symbolcount)+")");
symbolcount++;
            break;
        case tk_gt:
             //test wjether 2 numbers have same symbol
            output_assembler("@SP");
            output_assembler("A=M");
            output_assembler("A=A-1");
            output_assembler("D=M");
            output_assembler("@"+name+"$DL0_"+to_string(symbolcount));
            output_assembler("D;JLE");
            output_assembler("@"+name+"$DG0_"+to_string(symbolcount));
            output_assembler("D;JGE");
            //test b < 0
            output_assembler("("+name+"$DL0_"+to_string(symbolcount)+")");
            output_assembler("@SP");
            output_assembler("A=M-1");
            output_assembler("A=A-1");
            
            output_assembler("D=M");
            output_assembler("@"+name+"$M_1_"+to_string(symbolcount));
            output_assembler("D;JGT");
            output_assembler("@"+name+"$M_a_"+to_string(symbolcount));
            output_assembler("0;JMP");
            //test b > 0
            output_assembler("("+name+"$DG0_"+to_string(symbolcount)+")");
            output_assembler("@SP");
            output_assembler("A=M-1");
            output_assembler("A=A-1");
            
            output_assembler("D=M");
            output_assembler("@"+name+"$M_0_"+to_string(symbolcount));
            output_assembler("D;JLT");
            output_assembler("@"+name+"$M_a_"+to_string(symbolcount));
            output_assembler("0;JMP");
        //M=1when a<0 and b>0
            output_assembler("("+name+"$M_1_"+to_string(symbolcount)+")");
            output_assembler("@SP");
            output_assembler("AM=M-1");
            //output_assembler("A=A-1");
            output_assembler("@SP");
            output_assembler("A=M-1");
            output_assembler("M=-1");
            output_assembler("@"+name+"$END_"+to_string(symbolcount));
            output_assembler("0;JMP");
        //M=1when a>0 and b<0
            output_assembler("("+name+"$M_0_"+to_string(symbolcount)+")");
            output_assembler("@SP");
            output_assembler("AM=M-1");
            //output_assembler("A=A-1");
            output_assembler("@SP");
            output_assembler("A=M-1");
            output_assembler("M=0");
            output_assembler("@"+name+"$END_"+to_string(symbolcount));
            output_assembler("0;JMP");
            //for same symbols
            output_assembler("("+name+"$M_a_"+to_string(symbolcount)+")");
            output_assembler("@SP");
            output_assembler("AM=M-1");
            output_assembler("D=M");
            output_assembler("A=A-1");
            output_assembler("D=D-M");
            output_assembler("@"+name+"$EQ_"+to_string(symbolcount));
            output_assembler("D;JGE");
            output_assembler("@SP");
            output_assembler("A=M-1");
            output_assembler("M=-1");
            output_assembler("@"+name+"$END_"+to_string(symbolcount));
            output_assembler("0;JMP");
            output_assembler("("+name+"$EQ_"+to_string(symbolcount)+")");
            output_assembler("@SP");
            output_assembler("A=M-1");
            output_assembler("M=0");
            output_assembler("("+name+"$END_"+to_string(symbolcount)+")");
            symbolcount++;
            break;
        case tk_lt:
            //test wjether 2 numbers have same symbol
            output_assembler("@SP");
            output_assembler("A=M");
            output_assembler("A=A-1");
            output_assembler("D=M");
            output_assembler("@"+name+"$DL0_"+to_string(symbolcount));
            output_assembler("D;JLE");
            output_assembler("@"+name+"$DG0_"+to_string(symbolcount));
            output_assembler("D;JGE");
            //test b < 0
            output_assembler("("+name+"$DL0_"+to_string(symbolcount)+")");
            output_assembler("@SP");
            output_assembler("A=M-1");
            output_assembler("A=A-1");
            
            output_assembler("D=M");
            output_assembler("@"+name+"$M_1_"+to_string(symbolcount));
            output_assembler("D;JGT");
            output_assembler("@"+name+"$M_a_"+to_string(symbolcount));
            output_assembler("0;JMP");
            //test b > 0
            output_assembler("("+name+"$DG0_"+to_string(symbolcount)+")");
            output_assembler("@SP");
            output_assembler("A=M-1");
            output_assembler("A=A-1");
            
            output_assembler("D=M");
            output_assembler("@"+name+"$M_0_"+to_string(symbolcount));
            output_assembler("D;JLT");
            output_assembler("@"+name+"$M_a_"+to_string(symbolcount));
            output_assembler("0;JMP");
        //M=1when a<0 and b>0
            output_assembler("("+name+"$M_1_"+to_string(symbolcount)+")");
            output_assembler("@SP");
            output_assembler("AM=M-1");
            //output_assembler("A=A-1");
            output_assembler("@SP");
            output_assembler("A=M-1");
            output_assembler("M=0");
            output_assembler("@"+name+"$END_"+to_string(symbolcount));
            output_assembler("0;JMP");
        //M=1when a>0 and b<0
            output_assembler("("+name+"$M_0_"+to_string(symbolcount)+")");
            output_assembler("@SP");
            output_assembler("AM=M-1");
            //output_assembler("A=A-1");
            output_assembler("@SP");
            output_assembler("A=M-1");
            output_assembler("M=-1");
            output_assembler("@"+name+"$END_"+to_string(symbolcount));
            output_assembler("0;JMP");
            //for same symbols
            output_assembler("("+name+"$M_a_"+to_string(symbolcount)+")");
            output_assembler("@SP");
            output_assembler("AM=M-1");
            output_assembler("D=M");
            output_assembler("A=A-1");
            output_assembler("D=D-M");
            output_assembler("@"+name+"$EQ_"+to_string(symbolcount));
            output_assembler("D;JLE");
            output_assembler("@SP");
            output_assembler("A=M-1");
            output_assembler("M=-1");
            output_assembler("@"+name+"$END_"+to_string(symbolcount));
            output_assembler("0;JMP");
            output_assembler("("+name+"$EQ_"+to_string(symbolcount)+")");
            output_assembler("@SP");
            output_assembler("A=M-1");
            output_assembler("M=0");
            output_assembler("("+name+"$END_"+to_string(symbolcount)+")");
            symbolcount++;
            break;
        case tk_neg:
            output_assembler("@SP");
            output_assembler("A=M");
            output_assembler("A=A-1");
            output_assembler("M=-M");
            break;
        case tk_not:
            output_assembler("@SP");
            output_assembler("A=M-1");
            output_assembler("M=!M");
            break;
        case tk_or:
            output_assembler("@SP");
            output_assembler("AM=M-1");
            output_assembler("D=M");
            output_assembler("A=A-1");
            output_assembler("M=D|M");
            
            break;
        case tk_sub:
            output_assembler("@SP");
            output_assembler("AM=M-1");
            output_assembler("D=M");
            output_assembler("A=A-1");
            output_assembler("M=M-D");
            break;
            // not finish return 
        case tk_return:
            // endFrame=LCL
        output_assembler("@LCL");
        output_assembler("D=M");
        output_assembler("@R13");
        output_assembler("M=D");
        //ret addr = *(endFrame-5)
        output_assembler("@R13");
        output_assembler("D=M");
        output_assembler("@5");
        output_assembler("D=D-A");
        output_assembler("A=D");
        output_assembler("D=M");
        output_assembler("@R14");
        output_assembler("M=D");
        //*ARG=pop()
        output_assembler("@SP");
        output_assembler("AM=M-1");
        output_assembler("D=M");
        output_assembler("@ARG");
        output_assembler("A=M");
        output_assembler("M=D");
        //SP=ARG+1
        output_assembler("@ARG");
        output_assembler("D=M+1");
        output_assembler("@SP");
        output_assembler("M=D");

        //THAT =*(endFrame-1)
        output_assembler("@R13");
        output_assembler("D=M");
        output_assembler("@1");
        output_assembler("D=D-A");
        output_assembler("A=D");
        output_assembler("D=M");
        output_assembler("@THAT");
        output_assembler("M=D");
        //This=***-2
        output_assembler("@R13");
        output_assembler("D=M");
        output_assembler("@2");
        output_assembler("D=D-A");
        output_assembler("A=D");
        output_assembler("D=M");
        output_assembler("@THIS");
        output_assembler("M=D");
        //ARG -3
        output_assembler("@R13");
        output_assembler("D=M");
        output_assembler("@3");
        output_assembler("D=D-A");
        output_assembler("A=D");
        output_assembler("D=M");
        output_assembler("@ARG");
        output_assembler("M=D");
        //LCL -4
        output_assembler("@R13");
        output_assembler("D=M");
        output_assembler("@4");
        output_assembler("D=D-A");
        output_assembler("A=D");
        output_assembler("D=M");
        output_assembler("@LCL");
        output_assembler("M=D");
        //goto retaDDr
        output_assembler("@R14");
        output_assembler("A=M");
        output_assembler("0;JMP");
            break;
         
            default: ;
    }

    


    end_of_vm_command() ;
}
//****
// translate vm jump command into assembly language
static void translate_vm_jump(TokenKind jump, string label)
{
    start_of_vm_jump_command(jump,label) ;
    
    // vm_jump ::= 'goto' | 'if-goto' | 'label

    // ... your code goes here ...
    if (jump == tk_goto) {
     output_assembler("@"+name+"$"+label);
     output_assembler("0;JMP");
    }
    if (jump == tk_if_goto) {
        output_assembler("@SP");
        output_assembler("AM=M-1");
        output_assembler("D=M");
        output_assembler("@"+name+"$"+label);
        output_assembler("D;JNE"); 
    }
    if (jump == tk_label) {
        output_assembler("("+name+"$"+label+")");
    }
    end_of_vm_command() ;
}


// translate vm call or function command into assembly language
static void translate_vm_function(TokenKind func, string label, int n)
{   
    start_of_vm_func_command(func,label,n) ;

    // ... your code goes here ...
    //* vm_func ::= 'call' | 'function'
    if (func == tk_call) {
    //  push return address (ret1+count)
        output_assembler("@"+name+"$"+"retAddr01"+to_string(count)+"$"+label);
        output_assembler("D=A");
        output_assembler("@SP");
        output_assembler("AM=M+1");
        output_assembler("A=A-1");
        output_assembler("M=D");
        //push LCL  -> to space
        output_assembler("@LCL");
        output_assembler("D=M");
        output_assembler("@SP");
        output_assembler("A=M");
        output_assembler("M=D");
        
        //push ARG  ->to next space
        output_assembler("@SP");
        output_assembler("M=M+1");
        output_assembler("@ARG");
        output_assembler("D=M");
        output_assembler("@SP");
        output_assembler("A=M");
        output_assembler("M=D");
        
        //push THIS
        output_assembler("@SP");
        output_assembler("M=M+1");
        output_assembler("@THIS");
        output_assembler("D=M");
        output_assembler("@SP");
        output_assembler("A=M");
        output_assembler("M=D");
        
        //THAT
        output_assembler("@SP");
        output_assembler("M=M+1");
        output_assembler("@THAT");
        output_assembler("D=M");
        output_assembler("@SP");
        output_assembler("A=M");
        output_assembler("M=D");
        //ARG=SP-5-n(Args)  -> push SP -(5 + n)
        output_assembler("@SP");
        output_assembler("M=M+1");
        output_assembler("@SP");
        output_assembler("D=M");
        output_assembler("@" + to_string(n));
        output_assembler("D=D-A");
        output_assembler("@5");
        output_assembler("D=D-A");
        output_assembler("@ARG");
        output_assembler("M=D");

        //LCL=SP
        
        output_assembler("@SP");
        output_assembler("D=M");
        output_assembler("@LCL");
        output_assembler("M=D");
        //goto functionname
        output_assembler("@" + label);
        output_assembler("0;JMP");
        //(returnAddress)
        output_assembler("(" + name + "$retAddr01" + to_string(count) + "$" + label + ")");
    
    //for next return address
        count++;
    }
   if (func == tk_function) {
    name =  label;
    //(function name)
    output_assembler("("+label+")");
    //for nARG times, push 0;
    for (int i =0; i<n ; i++){
        output_assembler("@0");
        output_assembler("D=A");
        output_assembler("@SP");
        output_assembler("AM=M+1");
        output_assembler("A=A-1");
        output_assembler("M=D");
    }
}

    end_of_vm_command() ;
}

// translate vm push or pop command into assembly language
static void translate_vm_stack(TokenKind stack,TokenKind segment,int offset)
{  
    start_of_vm_stack_command(stack,segment,offset) ;

    // ... your code goes here ...
    string className = name.substr(0,name.find("."));
    if (stack == tk_push){
        switch (segment) {
            case tk_constant:
            output_assembler("@" + to_string(offset));
            output_assembler("D=A");
            output_assembler("@SP");
            output_assembler("AM=M+1");
            output_assembler("A=A-1");
            output_assembler("M=D");
            break;
            
            case tk_static:
            output_assembler("@"+className+"."+to_string(offset));
            output_assembler("D=M");
            output_assembler("@SP");
            output_assembler("A=M");
            output_assembler("M=D");
            output_assembler("@SP");
            output_assembler("M=M+1");
            break;
           
            case tk_temp: 
            output_assembler("@"+to_string(offset+5));
            output_assembler("D=M");
            output_assembler("@SP");
            output_assembler("A=M");
            output_assembler("M=D");
            output_assembler("@SP");
            output_assembler("M=M+1");
            break;
            
            case tk_pointer: 
            output_assembler("@"+to_string(offset));
            output_assembler("@THIS");
            output_assembler("D=M");
            output_assembler("@SP");
            output_assembler("AM=M+1");
            output_assembler("A=A-1");
            output_assembler("M=D");

            break;

            case tk_local: 
            output_assembler("@LCL");
            output_assembler("D=M");
            output_assembler("@"+to_string(offset));
            output_assembler("A=D+A");
            output_assembler("D=M");
            output_assembler("@SP");
            output_assembler("A=M");
            output_assembler("M=D");
            output_assembler("@SP");
            output_assembler("M=M+1");
            break;
            
            case tk_this: 
            output_assembler("@THIS");
            output_assembler("D=M");
            output_assembler("@"+to_string(offset));
            output_assembler("A=D+A");
            output_assembler("D=M");
            output_assembler("@SP");
            output_assembler("A=M");
            output_assembler("M=D");
            output_assembler("@SP");
            output_assembler("M=M+1");
            break;
            
            case tk_that: 
            output_assembler("@THAT");
            output_assembler("D=M");
            output_assembler("@"+to_string(offset));
            output_assembler("A=D+A");
            output_assembler("D=M");
            output_assembler("@SP");
            output_assembler("A=M");
            output_assembler("M=D");
            output_assembler("@SP");
            output_assembler("M=M+1");
            break;

            case tk_argument: 
            output_assembler("@ARG");
            output_assembler("D=M");
            output_assembler("@"+to_string(offset));
            output_assembler("A=D+A");
            output_assembler("D=M");
            output_assembler("@SP");
            output_assembler("A=M");
            output_assembler("M=D");
            output_assembler("@SP");
            output_assembler("M=M+1");
            break;
            default:;
            
        }
    }
        if (stack == tk_pop){
        switch (segment) {
            
            
            case tk_static: 
            output_assembler("@SP");
            output_assembler("AM=M-1");
            output_assembler("D=M");
            output_assembler("@"+to_string(offset+16));
            output_assembler("M=D");
            break;
            case tk_temp: 
            output_assembler("@SP");
            output_assembler("AM=M-1");
            output_assembler("D=M");
            output_assembler("@R"+to_string(offset+5));
            output_assembler("M=D");
            
            break;
            case tk_pointer: 
            if(offset == 1)
            {
            output_assembler("@SP");
            output_assembler("AM=M-1");
            output_assembler("D=M");
            output_assembler("@THAT");
            output_assembler("M=D");
            }
            else
            {
            output_assembler("@SP");
            output_assembler("AM=M-1");
            output_assembler("D=M");
            output_assembler("@THIS");
            output_assembler("M=D");
            }
            break;

            case tk_local: 
            output_assembler("@LCL");
            output_assembler("D=M");
            output_assembler("@"+to_string(offset));
            output_assembler("D=D+A");
            output_assembler("@R13");
            output_assembler("M=D");
            output_assembler("@SP");
            output_assembler("AM=M-1");
            output_assembler("D=M");
            output_assembler("@R13");
            output_assembler("A=M");
            output_assembler("M=D");
            break;
            
            case tk_this: 
            output_assembler("@THIS");
            output_assembler("D=M");
            output_assembler("@"+to_string(offset));
            output_assembler("D=D+A");
            output_assembler("@R13");
            output_assembler("M=D");
            output_assembler("@SP");
            output_assembler("AM=M-1");
            output_assembler("D=M");
            output_assembler("@R13");
            output_assembler("A=M");
            output_assembler("M=D");
            break;
            
            case tk_that: 
            output_assembler("@THAT");
            output_assembler("D=M");
            output_assembler("@"+to_string(offset));
            output_assembler("D=D+A");
            output_assembler("@R13");
            output_assembler("M=D");
            output_assembler("@SP");
            output_assembler("AM=M-1");
            output_assembler("D=M");
            output_assembler("@R13");
            output_assembler("A=M");
            output_assembler("M=D");
            break;

            case tk_argument: 
            output_assembler("@ARG");
            output_assembler("D=M");
            output_assembler("@"+to_string(offset));
            output_assembler("D=D+A");
            output_assembler("@R13");
            output_assembler("M=D");
            output_assembler("@SP");
            output_assembler("AM=M-1");
            output_assembler("D=M");
            output_assembler("@R13");
            output_assembler("A=M");
            output_assembler("M=D");
            break;
            default: ;
        }
}



    end_of_vm_command() ;
}


/************            AND HERE              **************/
///////////////////////////////////////////////////////////////

// grammar to be parsed:
// vm_class ::= command* eoi
// command ::= vm_operator | vm_jump | vm_func | vm_stack
// vm_operator ::= 'add' | 'and' | 'eq' | 'gt' | 'lt' | 'neg' | 'not' | 'or' | 'sub' | 'return'
// vm_jump ::= jump label
// vm_func ::= func label number
// vm_stack ::= stack segment number

// forward declare parsing functions - one per rule
static void parse_class() ;
static void parse_command() ;
static void parse_op() ;
static void parse_jump() ;
static void parse_func() ;
static void parse_stack() ;

// Note: always read one token after the one recognised

// vm_class ::= command* eoi
static void parse_class()
{
    // tell the output system we are starting to translate VM commands for a Jack class
    start_of_vm_class() ;

    while ( have(tk_vm_command) ) parse_command() ;
    mustbe(tk_eoi) ;

    // tell the output system we have just finished translating VM commands for a Jack class
    end_of_vm_class() ;
}

// command ::= vm_operator | vm_jump | vm_func | vm_stack
static void parse_command()
{
    if ( have(tk_vm_operator) ) parse_op() ; else
    if ( have(tk_vm_jump) )     parse_jump() ; else
    if ( have(tk_vm_func) )     parse_func() ; else
    if ( have(tk_vm_stack) )    parse_stack() ; else
    mustbe(tk_vm_command) ;
}

// vm_operator ::= 'add' | 'and' | 'eq' | 'gt' | 'lt' | 'neg' | 'not' | 'or' | 'sub' | 'return'
static void parse_op()
{
    TokenKind the_op = token_kind(mustbe(tk_vm_operator)) ;

    translate_vm_operator(the_op) ;
}

// vm_jump ::= jump label
// jump command - label, goto label or if-goto label
static void parse_jump()
{
    TokenKind command = token_kind(mustbe(tk_vm_jump)) ;
    string label = token_spelling(mustbe(tk_a_label)) ;

    translate_vm_jump(command,label) ;
}

// vm_func ::= func label number
// call function-name #args or function function-name #locals
static void parse_func()
{
    TokenKind command = token_kind(mustbe(tk_vm_func)) ;
    string label = token_spelling(mustbe(tk_a_label)) ;
    int number = token_ivalue(mustbe(tk_a_number)) ;

    translate_vm_function(command,label,number) ;
}

// vm_stack ::= stack segment number
// push segment offset or pop segment offset
static void parse_stack()
{
    TokenKind stack = token_kind(mustbe(tk_vm_stack)) ;
    TokenKind segment = token_kind(mustbe(tk_vm_segment)) ;
    int number = token_ivalue(mustbe(tk_a_number)) ;

    translate_vm_stack(stack,segment,number) ;
}

// main program
int main(int argc,char **argv)
{
    // initialise the tokeniser by reading the first token
    next_token() ;

    // parse a class and output VM code
    parse_class() ;

    // flush the output and any errors
    print_output() ;
    print_errors() ;
}

