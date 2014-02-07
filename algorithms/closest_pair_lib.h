#include <stdlib.h>

typedef struct Point Point;
struct Point {
    int id;
    int x;
    int y;
    int sx;
    int sy;
};

typedef struct Line Line;
struct Line {
    double dist;
    int fid;
    int sid;
};

extern struct Point closest_pair;

void plot_points(struct Point points[], size_t len, int h1_point, int h2_point);
void sort_points_x(struct Point points[], size_t len);
void sort_points_y(struct Point points[], size_t len);
int cmp_x(const void *a1, const void *a2);
int cmp_y(const void *a1, const void *a2);
double dist(struct Point p1, struct Point p2);
Point * getpoint(Point points[], size_t len, int id);
void print_points(Point points[], size_t len);
void scale_points(Point points[], size_t len);
Line * find_cls_pair(struct Point points[], int left, int right);
