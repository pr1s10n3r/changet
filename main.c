#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "board.h"
#include "thread.h"

#define VERSION "1.0.0"

static int vflag, vrsflag;

void print_help(const char* progname);

int main(int argc, char* argv[])
{
    const char* progname = argv[0];

    const struct option options[] = {
        {"--verbose", no_argument, &vflag, 1},
        {"--version", no_argument, &vrsflag, 'v'},
        {"--help", no_argument, 0, 'h'},
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
                printf("%s v%s\n", progname, VERSION);
                break;
            case 'b':
                if (is_valid_board(optarg)) {
                    memcpy(board, optarg, MAX_BOARD_LENGTH);
                } else {
                    fprintf(stderr, "%s: invalid argument for --board\n", progname);
                    exit(EXIT_FAILURE);
                }
                break;
            case 't':
                thread_id = (u64)atoi(optarg);
                break;
            case 'h':
                print_help(progname);
                break;
            case '?':
                print_help(progname);
                break;
            default:
                abort();
        }
    }

    if (vrsflag)
        return EXIT_SUCCESS;

    if (thread_id == 0) {
        fprintf(stderr, "%s: no thread id\n", progname);
        print_help(progname);
        return EXIT_FAILURE;
    } else if (strlen(board) == 0) {
        fprintf(stderr, "%s: no board name\n", progname);
        print_help(progname);
        return EXIT_FAILURE;
    }

    linked_list_t* posts = get_thread_posts(board, thread_id);
    if (posts == NULL)
    {
        fprintf(stderr, "%s: could not get thread posts\n", progname);
        return EXIT_FAILURE;
    }

    for (usize i = 0; i < posts->length; i++)
    {
        node_t* node = list_get_idx(posts, i);
        post_t* post = (post_t*)node->value;
        printf("Filename: %s%s\n", post->filename, post->ext);
    }

    printf("Freeing\n");
    list_destroy(posts);

    return EXIT_SUCCESS;
}

void print_help(const char* progname)
{
    printf(
            "Usage:\n"
            "  %s --board BOARD --thread ID [options]\n\n"
            "OPTIONS\n"
            "  -?, --help    show     list of command-line options\n"
            "  -v, --version show     version of %s\n"
            "      --verbose show     more detailed information about what is happening\n"
            "  -o, --output  PATH     save all downloaded files into PATH\n"
            "  -i, --ignore FORMAT(s) if a file format is detected while downloading, ignore it.\n"
            "                         Available formats: jpg,png,gif,pdf,swf,webm\n",
            progname, progname
    );
}
