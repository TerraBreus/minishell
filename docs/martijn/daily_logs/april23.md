## 23-04

added first tokenizing file, using libft bonus for making the list.
isnt completed yet so ill make more time to check if the nodes are created in order as hoped.

//goal day 2
	place all seperate words from input in token_list		[x]
	print list to check if tokens and flags applyas intended[x]

nice to have
	operator recognizition (>, <, |)						[x]
	money ($) recognizition									[ ]
	removing quotes from tokens and activating flags		[ ]

#TODO on bigger scale

env variables ($ and $VAR)
merging adjecent quotes (a"b"c -> abc)
recognizing filenames after redirection
heredoc stuff (havent read up about it)

havent started on env knowlegde

operators and tokens are now properly split:
test>test = [test][>][test]
test > test = [test][>][test]


