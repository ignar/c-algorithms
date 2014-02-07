#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <float.h>

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#include "debug.h"
#include "common_lib.h"
#include "closest_pair_lib.h"

void plot_points(Point points[], size_t len, int h1_point, int h2_point)
{
    if(DEBUG) return;

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    for (size_t i = 0; i < len; i++) {
        if (h1_point == points[i].id || h2_point == points[i].id) {
            attroff(COLOR_PAIR(1));
            attron(COLOR_PAIR(2));
            mvaddch(points[i].sy, points[i].sx, ACS_DIAMOND);
            attroff(COLOR_PAIR(2));
            attron(COLOR_PAIR(1));
        } else {
            mvaddch(points[i].sy, points[i].sx, ACS_BULLET);
        }
    }
    attroff(COLOR_PAIR(1));
    return;
}

Point * getpoint(Point points[], size_t len, int id)
{
    for(size_t i = 0; i < len; i++) {
        if(points[i].id == id) {
            return &points[i];
        }
    }
    return NULL;
}

void print_points(Point points[], size_t len)
{
    for(size_t i = 0; i < len; i++) {
        printf("i:%ld Point<id:%d; x:%d; y:%d>\n", i, points[i].id, points[i].x, points[i].y);
    }
    printf("\n");
    return;
}

int cmp_x(const void *a1, const void *a2)
{
    Point *p1 = (Point*)a1;
    Point *p2 = (Point*)a2;
    return p1->x - p2->x;
}

int cmp_y(const void *a1, const void *a2)
{
    Point *p1 = (Point*)a1;
    Point *p2 = (Point*)a2;
    return p1->y - p2->y;
}

void sort_points_x(Point points[], size_t len)
{
    qsort(points, len, sizeof(Point), cmp_x);
}

void sort_points_y(Point points[], size_t len)
{
    qsort(points, len, sizeof(Point), cmp_y);
}

double dist(Point p1, Point p2)
{
    double dist = sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y) + .0);
    return dist;
}

void scale_points(Point points[], size_t len)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    int max_y = 0,
        max_x = 0,
        mx_p,
        mx_t;
    for(size_t i = 0; i < len; i++) {
        max_y = MAX(max_y, points[i].y);
        max_x = MAX(max_x, points[i].x);
    }

    mx_p = MAX(max_y, max_x);
    mx_t = MIN(w.ws_col, w.ws_row);
    debug_print("Terminal max res is set to %d, max point coord is %d\n", mx_t, mx_p);

    if(mx_p > mx_t) {
        float k = (float)mx_t / (float)mx_p;
        debug_print("Points coordinates needs to be scaled with k:%f\n", k);
        for(size_t i = 0; i < len; i++) {
            points[i].sx = round((float)points[i].x * k);
            points[i].sy = round((float)points[i].y * k);
            debug_print("Scaling (%d:%d) => (%d:%d)\n",
                        points[i].x, points[i].y, points[i].sx, points[i].sy);
        }
    }

    for(size_t i = 0; i < len; i++)
        points[i].sy = w.ws_row - points[i].sy;

    return;
}

Line * find_cls_pair(struct Point points[], int left, int right)
{
    debug_print("Receive left:%d and right:%d\n", left, right);
    Line * sht = malloc(sizeof(Line));

    if(left+1 == right) {
        sht->dist = dist(points[left], points[left+1]);
        sht->fid = points[left].id;
        sht->sid = points[left+1].id;
        debug_print("Only two points and line is Line<dist:%f; fid:%d; sid:%d>\n\n", sht->dist, sht->fid, sht->sid);
        return sht;
    }

    if((right - left) < 3) {
        double d1 = dist(points[left], points[left+1]);
        double d2 = dist(points[left+1], points[right]);
        debug_print("Comparing Point<id:%d; x:%d; y:%d> and Point<id:%d; x:%d; y:%d> and Point<id:%d; x:%d; y:%d>\n",
                    points[left].id, points[left].x, points[left].y,
                    points[left+1].id, points[left+1].x, points[left+1].y,
                    points[right].id, points[right].x, points[right].y);
        debug_print("Distances are %f and %f\n", d1, d2);
        if(d1 < d2) {
            sht->dist = d1;
            sht->fid = points[left].id;
            sht->sid = points[left+1].id;
        } else {
            sht->dist = d2;
            sht->fid = points[left+1].id;
            sht->sid = points[right].id;
        }
        debug_print("Found new shortest distance Line<dist:%f; fid:%d; sid:%d>\n", sht->dist, sht->fid, sht->sid);
        return sht;
    }

    int m = (left + right) >> 1;
    double mid = points[right].x - points[left].x;
    debug_print("Splitting by (%d; %d) and (%d, %d)\n\n", left, m, m+1, right);
    Line * shtf = find_cls_pair(points, left, m);
    Line * shts = find_cls_pair(points, m+1, right);
    debug_print("Plane first Line<dist:%f; fid:%d; sid:%d>\n", shtf->dist, shtf->fid, shtf->sid);
    debug_print("Plane second Line<dist:%f; fid:%d; sid:%d>\n", shts->dist, shts->fid, shts->sid);

    if (shtf->dist < shts->dist) {
        free(shts);
        sht = shtf;
    } else {
        free(shtf);
        sht = shts;
    }
    debug_print("Shortest Plane is Line<dist:%f; fid:%d; sid:%d>\n\n", sht->dist, sht->fid, sht->sid);

    // TODO use merge sort
    sort_points_y(points+left, right-left);

    debug_print("Checking Plane1 < mid < Plane2 left:%d right:%d min_dist:%f\n", left, right, sht->dist);
    for(int i = left, j = left + 1; i < right-1; i++, j++) {
        if(abs(points[i].x - mid) <= sht->dist) {
            if((points[i].y - sht->dist) <= points[j].y) {
                double d = dist(points[i], points[j]);
                debug_print("Comparing Point<id:%d; x:%d; y:%d> and Point<id:%d; x:%d; y:%d> distance is %f\n",
                            points[i].id, points[i].x, points[i].y,
                            points[j].id, points[j].x, points[j].y,
                            d);
                if(d < sht->dist) {
                    sht->dist = d;
                    sht->fid = points[i].id;
                    sht->sid = points[j].id;
                    debug_print("Found new shortest distance Line<dist:%f; fid:%d; sid:%d>\n", sht->dist, sht->fid, sht->sid);
                }
            }
        }
    }
    debug_print("\n");

    return sht;
}
