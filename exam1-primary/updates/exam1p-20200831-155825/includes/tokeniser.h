#ifndef EXAM_TOKENISER_H
#define EXAM_TOKENISER_H

#include <string>

// Interface for the workshop tokeniser
namespace Exam_Tokeniser
{
    // shorthand name for the string type
    typedef std::string string ;

    // the ID used to reference a Token - the implementation is hidden
    class _Token ;
    typedef _Token *Token ;

    // The kinds of token that are recognised?
    enum TokenKind
    {
        // *** BNF syntax for tokens
        // * literals inside ' '
        // * grouping ( )
        // * ASCII ranges -
        // * alternatives |
        // * 0 or 1 ?
        // * 0 or more *
        // * 1 or more +
        //

        // Exam Tokeniser Tokens
        // Grammar rule:    Definition
        // input:           token* eoi
        // token:           byte | stage1 | stage2 | stage3 | stage4 | stage5 | ...
        // byte:            any single character that cannot start another token
        // stage1:          ?? see below ??
        // stage2:          ?? see below ??
        // stage3:          ?? see below ??
        // stage4:          ?? see below ??
        // stage5:          ?? see below ??
        // ...
        // eoi:             the end of the input or any unexpected character
        //
        // * all input after returning an eoi token is ignored
        // * when parsing a token, if the token cannot be completed return the eoi token
        // * the web submission system will reveal the grammar rule(s) for each stage
        //   once all tests of the example for one the previous 2 stages has been passed
        //   ie the stage3 rules will be revealed by the first successful web submission of the start up files
        //      the stage4 rules will be revealed once the stage1 example tests are passed,
        //      the stage5 rules will be revealed once the stage3 example tests are passed, and so on

        tk_eoi,             // end of input reached or an unexpected character was found
        tk_byte,            // any single byte character that cannot start another token

                            // details of the following token kinds will be revealed by the web submission system
                            // this will include the grammar rules and, if required, details of any spelling changes to make
                            // not all of these token kinds may be used
        tk_number,          // some form of number
        tk_identifier,      // some form of identifier
        tk_operator,        // some form of operator
        tk_comment,         // some form of comment
        tk_string,          // some form of string
        tk_arbitrary,       // some form of arbitrary token
        tk_weird,           // some form of arbitrary token

        tk_error_message,   // ignore this - used to report errors during calls of next_token()
        tk_last             // ignore this
    } ;

    // ***** the following are implemented in library.cpp *****

    // return a string representation of the given token kind
    // returns "" if the kind is not recognised
    extern string to_string(TokenKind kind) ;

    // return the TokenKind for the given token
    // it is a fatal error if the token was not returned by a call to next_token()
    extern TokenKind token_kind(Token token) ;

    // return the spelling for the given token
    // it is a fatal error if the token was not returned by a call to next_token()
    extern string token_spelling(Token token) ;

    // return a string representation of the given token
    // it is a fatal error if the token was not returned by a call to next_token()
    extern string to_string(Token token) ;

    // is the token of the given kind or does it belong to the given group of tokens?
    // eg token_is(t,tk_colon) returns true if token_kind(t) is tk_colon
    // eg token_is(t,tk_op) returns true if token_kind(t) is tk_add, tk_sub, tk_times, tk_divide or tk_op
    extern bool token_is(Token token,TokenKind kind_or_grouping) ;

    // initialiase the tokeniser
    extern void initialise_tokeniser() ;

    // ***** the workshop involves implementing the following functions by completing tokeniser.cpp *****

    // read the next token from standard input
    extern Token next_token() ;
}

#endif //EXAM_TOKENISER_H
