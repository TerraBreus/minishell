/*
 * Structure must needs arguments, of which command must always be the first.
 * Second it needs direction of data-flow and setup IO accordingly.
 * We will most likely need some kind of priority addition to ececute the whole
 * flow accordingly to the execution of the re/pipe direction flow.
 * Thus we need a minimum of three things to keep track of:
 *  - Our arguments
 *  - Pipe flow (I/O or -1)
 *    Here we would also need the fd's of the pipes.
 *  - Redirection flow (I/O or -1)
 *    And here we would need the filenames for redirection.
 *
 * I would suggest a following structure:
 */

#include <cstddef>
#include <sys/types.h>
typedef struct s_cp_pipex {
  char **args;       // NULL terminated argument list. cmd must be at [0].
  void *pipe;        // Would point to pipe structure or NULL if irrelevant.
  void *redirection; // for redirection, NULL if irrelevant.
} t_pipex;

typedef struct s_pipe {
  int in_out; // 0 for IN, 1 for OUT, 2 for IN/OUT; (we can probably use
              // bitshifting to be cool)
  int pipe_fd[2];
} t_pipe;

typedef struct s_redir {
  bool in_out; // TRUE for IN, FALSE for OUT.
  char *file;  // Path/filename of file to read/write.
} t_reddit;

/*
 * We would still have to write a function that calculates the order of
 * execution for the entire command line input, but even in the case of multiple
 * pipes, we would still have to do them 1 by 1 eventually. So we can first
 * create a program that, based on the pipex structure, sets up the I/O for the
 * command to execute.
 */

#include <cstddef>

void setup_io(t_pipex *data) {
  if (data->pipe != NULL) {
    // setup I/O
  }
  if (data->redirection != NULL) {
    // setup I/O
  }
  if (data->pipe == NULL && data->redirection == NULL)
    unnecessary_piping();
}

void exterminate(char **arguments) {
  char **path;

  path = find_path(*arguments);
  execve(path, arguments, NULL);
  free(path);
  return_status();
}

void reset_io(t_pipex *data) { close_idle_pipe(data->pipe); }

void copy_pasta_pipex(t_pipex *data) {
  pid_t pid;

  setup_io(data);
  pid = fork();
  if (pid == 0) {
    reset_io(data);
    exterminate(
        data->args); // I find this a funny meme cause it is a word play between
                     // execute and terminate, which it sorta does both.
  }
  close_io(data);
}

/*
 * In the case of multiple flow operations, we will need an order of execution.
 * I consider this a multitude of pipes, therfore the name plumbing.
 * We will need still a program that, from the entire command line, creates the
 * information for the plumber to follow I mean by this an algorithm that, from
 * the entire cmdline, snips it into pieces in an order of execution (with
 * priority). The plumber then only needs to follow the instructions.
 */

// FYI this is just a linked list.

typedef struct s_plumber {
  t_pipex *current_piece;
  struct s_plumber *next; // NULL if there is none. (we are at the last cmd)
} t_plumber;

void plumbing(t_plumber *plumbing_data) {
  copy_pasta_pipex(plumbing_data->current_piece);
  if (plumbing_data->next != NULL) {
    plumbing_data->current_piece = plumbing_data->next->current_piece;
    plumbing_data->next = plumbing_data->next->next;
    plumbing(plumbing_data); // lol why not...
  }
}
