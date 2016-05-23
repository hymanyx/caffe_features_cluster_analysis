/**
 * Copyright (C) 2016, xinxin - All rights reserved.
 * All rights reserved
 *
 * @file    mat_util.h
 * @brife   实现了cv::Mat类型变量读写文件的操作。
 *
 * 实现了cv::Mat类型变量读写文件的操作, 包括从不同原始文件读入数据构造cv::Mat类型变量,
 * 将cv::Mat类型变量写入xml/yaml文件, 从xml/yaml文件载入数据到cv::Mat类型变量。
 *
 * @version 1.0
 * @author  xinxin (292209415@qq.com)
 * @data    2016.5.13
 */

#ifndef MAT_UTIL_H
#define MAT_UTIL_H

#include <fstream>
#include <sstream>
#include <opencv2/opencv.hpp>

using std::string;
using namespace cv;

/**
 * @brife   将已赋值的cv::Mat类型变量写入xml/yaml文件
 *
 * @param   [in]  mat_file  xml/yaml文件路径
 * @param   [in]  mat       待写入xml/yaml文件的cv::Mat类型变量
 * @param   [in]  mat_name  mat名字,用于在xml/yaml文件中标记写入的mat
 * @return  none
 *
 * @note    文件名后缀决定了写入的格式是xml或者yaml
 */
void WriteMat(const string &mat_file, const cv::Mat &mat, const string &mat_name = "Matrix" ){
    cv::FileStorage output(mat_file, cv::FileStorage::WRITE);   // 构造一个FileStorage对象，只提供写操作
    output << mat_name << mat;
    output.release();                                           // 显式关闭，释放文件资源
};


/**
 * @brife   从xml/yaml文件中载入数据到cv::Mat类型变量(该方法较慢)
 *
 * @param   [in]  mat_file  xml/yaml文件路径
 * @param   [out] mat       从xml/yaml文件中载入的cv::Mat类型变量
 * @param   [in]  mat_name  mat名字,用于在xml/yaml文件中标记写入的mat
 * @return  none
 *
 * @note    载入的文件过大时会产生Segment Fault. 目前未找到解决办法，怀疑是opencv的bug
 */
void LoadMat(const string &mat_file, cv::Mat &mat, const string &mat_name = "Matrix"){
    FileStorage output;
    output.open(mat_file, FileStorage::READ);
    output[mat_name] >> mat;
};

#endif //MAT_UTIL_H
