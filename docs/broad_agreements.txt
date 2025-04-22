working on 2 branches: exec and parse
always push during and after session
rebase/merge to main only on completed commits

never git add .
add files with intention

includes libraries in   libaries.header
structs in              structs.header
defines in              defines.header
functions in            functions.header

naming of files, variables and functions always snake_case
words seperated by underscore and no capital letters.

no digits in function names, if neccisary can be used for variables
but not recommended

be mindfull to remove old functions, or add WIP to non functioning functions.

be clear not clever

feel free to use comments in WIP functions, to signify what needs to happen next,
leave only comments above when function is done, to signify usage or new concept

intellisense comments in header?

node for linked list structure suggestions:

  -----------------
/					\
|enum = token types	|
|value?				|
|char	*command	|
|bool	in_singles	|
|bool	in_doubles	|
|node	next		|
\					/
  -----------------