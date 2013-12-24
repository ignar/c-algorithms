#include <errno.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "debug.h"
#include "common_lib.h"
#include "closest_pair_lib.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Give me path to csv file.\n");
        exit(EXIT_FAILURE);
    }

    FILE *csv_file = fopen(argv[1], "rb");
    if (csv_file == NULL) {
        fprintf(stderr, "Failed to open csv file.\n");
        exit(EXIT_FAILURE);
    }

    int cnt_of_lines = 0, ch;
    do {
        ch = fgetc(csv_file);
        if (ch == '\n')
            cnt_of_lines++;
    } while(ch != EOF);

    rewind(csv_file);

    if(cnt_of_lines == 0) {
        fprintf(stdout, "CSV file is empty.\n");
        exit(EXIT_SUCCESS);
    }

    char line[80];
    struct Point points[cnt_of_lines];
    int ind = 0;
    while (fgets(line, 80, csv_file) != NULL) {
        size_t len = 0;
        char **values = split_string(line, ",", &len);
        char *num;
        int x = (int)strtol(values[0], &num, 0);
        int y = (int)strtol(values[1], &num, 0);

        struct Point p = {ind+1, x, y};
        points[ind] = p;
        ind++;
     }
    if (DEBUG)
        print_points(points, cnt_of_lines);

    if (!DEBUG) {
        initscr();
        start_color();
        curs_set(0);
    }
    int idl = 0, idr = 0;

    scale_points(points, cnt_of_lines);
    plot_points(points, cnt_of_lines, idl, idr);

    sort_points_x(points, cnt_of_lines);
    Line * sht = find_cls_pair(points, 0, cnt_of_lines);
    getch();

    plot_points(points, cnt_of_lines, sht->fid, sht->sid);

    if (!DEBUG) {
        refresh();
        getch();
        endwin();
    }

    print_points(points, cnt_of_lines);
    printf("Shortets path id Line<dist:%f; fid:%d; sid:%d>\n", sht->dist, sht->fid, sht->sid);
    Point * fp = getpoint(points, cnt_of_lines-1, sht->fid);
    Point * sp = getpoint(points, cnt_of_lines-1, sht->sid);
    printf("Between Point<id:%d; x:%d; y:%d> and Point<id:%d; x:%d; y:%d>\n",
           fp->id, fp->x, fp->y,
           sp->id, sp->x, sp->y);
    free(sht);
    return EXIT_SUCCESS;
}
