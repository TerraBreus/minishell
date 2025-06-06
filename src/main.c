/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:41:36 by masmit            #+#    #+#             */
/*   Updated: 2025/06/06 18:46:26 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// absolute paths arent absolute yet
// ''""'' persmission denied
// echo 'hi'" "'hello' error: syntax error near unexpected token `UNCLOSED QUOTE
// hello shd be Command 'hello' not found and exit code 127
// argument after exit should be translated to exit code eg
// exit 188; echo $?; 188 --this number can overflow 9223372036854775807
//my_shell: cat | cat | ls, cat: -: Bad file descriptor, cat: closing standard input: Bad file descriptor
// cat shd stay open. -> wait for every child finish, not only last pipe
// sleep 3 | ls, ours works left to right, bash works concurrent

// dfdf | fdf Syscall param close(fd) contains uninitialised byte(s)
// echo hi > permission (this permission has no right to do anything), program write hi into permission and quit program, exit code again
// echo HI >> 1 >> 2 >> 3 not append HI in file 3
// cat << eof
// > hi
// > ctrl-c definitely lost 1 from run_heredoc, ft_strdup
// if heredoc with several empty lines, direct leaks
// delimitor with quote, shdnt expand
// ctrl c noq quicks shell
// >> is overwrite instead append
// cat << eof > file | cat file, should not cat the file
// echo hi | echo "&" do nothing
//cat < hello  didnt check the file is exist or not
//nest minishell, signal handling
// echo + - !
int	main(void)
{
	t_shell	shell;

	if (shell_init(&shell) == FAILURE)
		return (quick_clean(&shell), EXIT_FAILURE);
	while (true)
		loop(&shell);
}
