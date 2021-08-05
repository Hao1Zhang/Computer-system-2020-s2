                                //
                                //
        tk_call,                // 'call'
        tk_case,                // 'case'
        tk_default,             // 'default'
        tk_do,                  // 'do'
        tk_else,                // 'else'
        tk_if,                  // 'if'
        tk_let,                 // 'let'
        tk_switch,              // 'switch'
        tk_throw,               // 'throw'
        tk_var,                 // 'var'
        tk_while,               // 'while'

                                // The following tokens are not produced by the tokeniser
                                // These are provided to describe groups of tokens
        tg_starts_statement,    // any token that can start the statement rule
        tg_starts_labelled,     // any token that can start the labelled rule
        tg_starts_label,        // any token that can start the label rule
        tg_starts_expressions,  // any token that can start the expressions rule
        tg_operator,            // any token that can be used as an operator in the expression rule
        tg_starts_term,         // any token that can start a term

        tk_last                 // the last token value

