#ifndef ROI_H
#define ROI_H
#include "opencv2/imgproc/imgproc_c.h"
//请注意，roi感兴趣区域 分为3种，点，线，面，其中面为多边形（例如，三角形，或矩形，或者其他） 下列有对应的写法
//char * roiPoint = "POINT(0.9 0.5)|POINT(0.9 0.5)";这是多点写法（多线段和多个多边形类似）里面的参数 为比例分割 例如： 0.1 = 1/10
// 极市小工具网址  http://dev.polygonlinepointtool.extremevision.com.cn/   
CvPoint * roi(char *roiPolygon ,CvSize curSize ,CvPoint *put);
#endif
