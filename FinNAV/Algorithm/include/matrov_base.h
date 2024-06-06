#pragma once
#include "Defines.h"


struct mr_Point2d
{
    fp32_t x;
    fp32_t y;
};
typedef struct mr_Point2d mr_Point2d_t;

struct mr_Point3d
{
    fp32_t x;
    fp32_t y;
    fp32_t z;
};
typedef struct mr_Point3d mr_Point3d_t;

//点计算
mr_Point2d_t mr_point2d_set(fp32_t x, fp32_t y); //直角坐标
mr_Point2d_t mr_point2d_set_polar(fp32_t r, fp32_t theta); //极坐标
mr_Point2d_t mr_point2d_from_array(fp32_t* array);
fp32_t* mr_point2d_to_array(mr_Point2d_t p);

mr_Point2d_t mr_point2d_add(mr_Point2d_t p1, mr_Point2d_t p2);
fp32_t mr_point2d_length(mr_Point2d_t p);
fp32_t mr_point2d_dist_euler(mr_Point2d_t p1, mr_Point2d_t p2);
fp32_t mr_point2d_dist_manhattan(mr_Point2d_t p1, mr_Point2d_t p2);
fp32_t mr_point2d_arg(mr_Point2d_t p); //求幅角

mr_Point3d_t mr_point3d_set(fp32_t x, fp32_t y, fp32_t z); //直角坐标
mr_Point3d_t mr_point3d_set_spher(fp32_t r, fp32_t theta, fp32_t phi); //球坐标
mr_Point3d_t mr_point3d_from_array(fp32_t* array);
fp32_t* mr_point3d_to_array(mr_Point3d_t p);

mr_point3d_add(mr_Point3d_t p1, mr_Point3d_t p2);
fp32_t mr_point3d_length(mr_Point3d_t p);
fp32_t mr_point3d_dist_euler(mr_Point3d_t p1, mr_Point3d_t p2);
fp32_t mr_point3d_theta(mr_Point3d_t p);
fp32_t mr_point3d_phi(mr_Point3d_t p);
