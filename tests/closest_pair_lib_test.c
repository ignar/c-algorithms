#include "minunit.h"
#include "../algorithms/closest_pair_lib.c"
/*
  15, 15
  17, 15
  30, 30
  20, 20
  10, 1
  35, 30
  30, 1
  39, 1
  17, 13
  13, 16
  9, 20
 */

/*
  15, 15
  17, 15
  30, 30
  20, 20
  10, 1
  35, 30

 */

/*
  15, 15
  17, 15
  30, 30
  20, 20
  10, 1
  35, 30
  30, 1
  */

char * test_closes_with_3_elem_x()
{
    struct Point points[3];
    struct Point f1 = {1, -10, 0};
    struct Point f2 = {2, 2, 0};
    struct Point f3 = {3, 4, 0};
    points[0] = f1;
    points[1] = f2;
    points[2] = f3;

    Line * sht = find_cls_pair(points, 0, 2);
    mu_assert("1: distance should eq 2", sht->dist == 2);
    mu_assert("1: first id is not 2", sht->fid == 2);
    mu_assert("1: second id is not 3", sht->sid == 3);
    return 0;
}

char * test_closes_with_3_elem_y()
{
    struct Point points[3];
    struct Point f1 = {1, 15, 15};
    struct Point f2 = {2, 17, 15};
    struct Point f3 = {3, 30, 30};
    points[0] = f1;
    points[1] = f2;
    points[2] = f3;

    Line * shl = find_cls_pair(points, 0, 2);
    mu_assert("2: distance is not 2", shl->dist == 2);
    mu_assert("2: first id is not 1", shl->fid == 1);
    mu_assert("2: second id is not 2", shl->sid == 2);
    return 0;
}

char * test_closes_with_more_when_3_elem_x()
{
    struct Point points[6];
    struct Point f1 = {1, 10, 1};
    struct Point f2 = {2, 17, 15};
    struct Point f3 = {3, 30, 30};
    struct Point f4 = {4, 20, 20};
    struct Point f5 = {5, 15, 15};
    struct Point f6 = {6, 35, 30};
    points[0] = f1;
    points[1] = f2;
    points[2] = f3;
    points[3] = f4;
    points[4] = f5;
    points[5] = f6;

    Line * sht = find_cls_pair(points, 0, 5);
    mu_assert("3: first id isn't 2", sht->fid == 2);
    mu_assert("3: second id isn't 5", sht->sid == 5);
    mu_assert("3: distance should eq 2", sht->dist == 2);
    return 0;
}

char * test_closes_with_more_when_3_elem()
{
    struct Point points[7];
    struct Point f1 = {1, 15, 15};
    struct Point f2 = {2, 17, 15};
    struct Point f3 = {3, 30, 30};
    struct Point f4 = {4, 20, 20};
    struct Point f5 = {5, 10, 1};
    struct Point f6 = {5, 35, 30};
    struct Point f7 = {5, 30, 1};
    points[0] = f1;
    points[1] = f2;
    points[2] = f3;
    points[3] = f4;
    points[4] = f5;
    points[5] = f6;
    points[6] = f7;

    Line * sht = find_cls_pair(points, 0, 5);
    mu_assert("4: first id isn't 1", sht->fid == 1);
    mu_assert("4: second id isn't 2", sht->sid == 2);
    mu_assert("4: distance should eq 2", sht->dist == 2);
    return 0;
}
