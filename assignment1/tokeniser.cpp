// a skeleton implementation of a tokeniser

#include "tokeniser-extras.h"

// to shorten the code
using namespace std ;

/////////////////////////////////////////////////////////////////////////

// a skeleton implementation of a tokeniser

#include "tokeniser-extras.h"

// to shorten the code
using namespace std ;

/////////////////////////////////////////////////////////////////////////

namespace Assignment_Tokeniser
{

    static TokenKind new_token_kind ;

    // return the next Token object by reading more of the input
    // you must read input using the nextch() function
    // the last character read is in the static variable ch
    // always read one character past the end of the token being returned
//from basic 
    static void parse_extra(TokenKind kind)
    {
        //parse one extra ch so that ch can be the start of the next token
        new_token_kind = kind ;
        nextch();
    }

    static void parse_wspace(TokenKind kind)
    {
        //parse the white space
        parse_extra(kind);
    }

    static void parse_identifier()
    {
        new_token_kind = tk_identifier;
        do nextch() ; while (c_have(cg_extends_identifier) );
    }

    /*static void parse_integer(TokenKind kind)
    {
        new_token_kind = kind;
        do nextch(); while (c_have(tk_integer)) ;

    }*/


    static void parse_integer(){
        new_token_kind = tk_integer;
        do nextch(); while (c_have(cg_digit19));
    }

    static void parse_integer_zero(){
        new_token_kind = tk_integer;
        nextch();
    }

    
    static void parse_eq(TokenKind kind)
    {
        new_token_kind = kind;
        do nextch(); while(c_have_next(tk_eq));
    }
    
    
    static void parse_symbol(TokenKind kind)
    {
        new_token_kind = kind ;
        do nextch(); while (c_have(tk_at|tk_stop|tk_lcb|tk_rcb|tk_lrb|tk_rrb|tk_lsb|tk_rsb));
    }


        

    

    
    
    Token next_token()
    {
                        // ch is always the next char to read
   
                        // this should follow the style used in the workshops ...
                        // but remember that the token grammar is different in this assignment
                        //
                        // add additional case labels here for characters that can start tokens
                        // call a parse_*() function to parse the token
                        //

                     
                        // End of Inptut

    
    switch(ch)
    {

    // * wspace ::= '\n' | ' '
    case ' ':               
        parse_wspace(tk_space) ;
        break ;
        
    case '\n':
        parse_wspace(tk_newline) ;
        break ;

    // * identifier ::= (letter|'$') (letter|digit|'-'|'$'|'.')*
    //   - letter ::= 'a'-'z'|'A'-'Z'
        //letter
    case 'a'...'z':
        case 'A'...'Z':
        case '$':
        parse_identifier();
        break;      
   
/*
    case '.':
        parse_identifier();
        break;           
*/
    // * integer ::= zero | digits
    //   - digit  ::= '0'-'9'
         //integer

    case '0': //zero includes in digits in this assignment
        parse_integer_zero();
        break;

        case '1'...'9': //zero includes in digits in this assignment
        parse_integer();
        break;
    // * symbol ::= '@'|'-='|'+='|'*='|'/='|'!='|'=='|'<<<'|'<<'|'>>>'|'>>'|'{'|'}'|'('|')'|'['|']'|'.'
    //   - symbols each have their own TokenKind
        case '@':   
            parse_symbol(tk_at);
            break;


        case '.':
            parse_symbol(tk_stop);
            break;
        
        case '{':   
            parse_symbol(tk_lcb);
            break;
        
        case '}':   
            parse_symbol(tk_rcb);
            break;

        case '(':   
            parse_symbol(tk_lrb);
            break;

        case ')':   
            parse_symbol(tk_rrb);
            break;

        case '[':
            parse_symbol(tk_lsb);
            break;
        
        case ']':
            parse_symbol(tk_rsb);
            break;


//because parse_eq is not in .h file 
        case '=':
            new_token_kind = tk_eq ;
            nextch(); c_mustbe('=');
            break;
        case '!':
            new_token_kind = tk_not_eq ;
            nextch() ; c_mustbe('=') ;
            break;

        case '-':
            new_token_kind = tk_sub_assign ;
            nextch() ; c_mustbe('=');
            break;

        case EOF:
            new_token_kind = tk_eoi ;
            break ;
        
        default:
            c_did_not_find(cg_start_of_token) ;
            break ;
        }

        Token token = new_token(new_token_kind) ;

                        // before returning a token check if the kind or spelling needs updating
                        // ...

        return token ;
   }
}