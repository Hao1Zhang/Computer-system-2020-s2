// convert Text into Tokens 
#include "tokeniser.h"
#include <iostream>
#include <vector>

// to shorten the code
using namespace std ;

using namespace Exam_Tokeniser ;

// this main program tokenises standard input and
// prints the tokens as they are found
int main(int argc,char **argv)
{
    try
    {
        // initialise tokeniser
        initialise_tokeniser() ;

        // read and display the first 256 tokens, stop earlier if input ends
        Token token = next_token() ;
        for ( int count = 0 ; count < 256 && token_kind(token) != tk_eoi ; count++ )
        {
            cout << to_string(token) << endl ;
            token = next_token() ;
        }
    }
    catch ( string error )
    {
        cout << "Caught exception: " << error << endl ;
    }

    return 0 ;
}
