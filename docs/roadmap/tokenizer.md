# Tokenizer/input parser/exctract input
- Check for quotes -> if quotes, check for the dollar sign ($) -> dollar sign should specify a parameter (f.e $? or $PWD)
- Split input according to whitespace (except for parameters and quotes)
- Check what input is and set token accordingly (build in command/relative command(path to cmd)/redirection operator/...)
