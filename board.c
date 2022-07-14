#include "board.h"
#include <string.h>

char boards[NUM_AVAILABLE_BOARDS][MAX_BOARD_LENGTH] = {
    "a", // anime
    "c", // anime cute
    "w", // anime wallpapers
    "m", // mecha
    "cgl", // cosplay
    "cm", // cute male
    "f", // flash
    "n", // transportation
    "jp", // otaku culture
    "vt", // virtual youtubers
    "v", // video games
    "vg", // video game general
    "vm", // video games multiplayer
    "vmg", // video games mobile
    "vp", // pokémon
    "vr", // retro games
    "vrpg", // video games RPG
    "vst", // video games strategy
    "co", // comics & cartoon
    "g", // technology
    "tv", // television & film
    "k", // weapons
    "o", // auto
    "an", // animals & nature
    "tg", // traditional games
    "sp", // sports
    "xs", // extreme sports
    "pw", // professional wrestling
    "sci", // science & math
    "his", // history & humanities
    "int", // international
    "out", // outdoors
    "toy", // toys
    "i", // oekaki
    "po", // papercraft & origami
    "p", // photography
    "ck", // food & cooking
    "ic", // artwork/critique
    "wg", // wallpapers general
    "lit", // literature
    "mu", // music
    "fa", // fashion
    "3", // 3DCG
    "gd", // graphic design
    "diy", // do-it-yourself
    "wsg", // worksafe gif
    "qst", // quests
    "biz", // business & finance
    "trv", // travel
    "fit", // fitness
    "x", // paranormal
    "adv", // advice
    "lgtb", // lgtb
    "mlp", // pony
    "news", // current news
    "wsr", // worksafe requests
    "vip", // very important posts
    "b", // random
    "r9k", // robot9001
    "pol", // politically incorrect
    "bant", // international random
    "soc", // cams & meetups
    "s4s", // shit 4chan says
    "s", // sexy beautiful women
    "hc", // hardcore
    "hm", // handsome men
    "h", // hentai
    "e", // ecchi
    "u", // yuri
    "d", // hentai alternative
    "y", // yaoi
    "t", // torrents
    "hr", // high resolution
    "gif", // adult gif
    "aco", // adult cartoons
    "r", // adult requests
};

bool is_valid_board(char* str)
{
    if (strlen(str) > MAX_BOARD_LENGTH)
        return false;

    bool found = false;
    for (unsigned int i = 0; i < NUM_AVAILABLE_BOARDS && !found; i++)
        found = (strcmp(str, boards[i]) == 0);
    
    return found;
}
