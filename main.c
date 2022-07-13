#include <getopt.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "types.h"
#include "board.h"
#include "thread.h"

#define VERSION "1.0.0"

static int vflag, vrsflag, hflag;

void print_help(const char* program);

int main(int argc, char* argv[])
{
    const char* program = argv[0];

    const struct option options[] = {
        {"verbose", no_argument, &vflag, 1},
        {"version", no_argument, &vrsflag, 'v'},
        {"help", no_argument, &hflag, 'h'},
        {"thread", required_argument, 0, 't'},
        {"board", required_argument, 0, 'b'},
        {0, 0, 0, 0}
    };

    u64 thread_id = 0;
    char board[MAX_BOARD_LENGTH] = {0};

    while (true)
    {
        int optindex = 0;

        int c = getopt_long(argc, argv, "hvb:t:", options, &optindex);
        if (c == -1)
            break;
      
        switch (c)
        {
            case 'v':
                printf("%s v%s\n", program, VERSION);
                break;
            case 'b':
                if (is_valid_board(optarg)) {
                    memcpy(board, optarg, MAX_BOARD_LENGTH);
                } else {
                    fprintf(stderr, "%s: invalid argument for --board\n", program);
                    exit(EXIT_FAILURE);
                }
                break;
            case 't':
                thread_id = (u64)atoi(optarg);
                break;
            case 'h':
            case '?':
                print_help(program);
                break;
            default:
                abort();
        }
    }

    if (vrsflag || hflag)
        return EXIT_SUCCESS;

    post_t* posts = get_thread_posts(board, thread_id);
    free(posts);

    return EXIT_SUCCESS;
}

void print_help(const char* program)
{
    printf(
            "Usage:\n"
            "  %s --thread <id> [options]\n\n"
            "META OPTIONS\n"
            "  -?, --help show list of command-line options\n"
            "  -v, --version show version of %s\n",
            program, program
    );
}
