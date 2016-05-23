#include "mat_util.h"
#include <opencv2/flann/flann.hpp>
#include "caffe/common.hpp"
#include "caffe/util/db.hpp"                // Wrapper for operating lmdb and leveldb

using std::string;
using std::cerr;
using std::endl;

int main(int argc, char **argv) {
    // 解析参数
    if (argc != 4){
        cerr << "Useage:\n./caffe_features_cluster_analysis  leveldb_path[input]  center_num[input]  center_file[output]" << endl;
        return -1;
    }
    string leveldb_path = argv[1];
    int center_num = std::stoi(argv[2]);
    string center_file = argv[3];

    // 打开leveldb
    caffe::DataParameter_DB db_type = caffe::DataParameter_DB_LEVELDB;              // string db_type = "leveldb";
    std::shared_ptr<caffe::db::DB> feature_db(caffe::db::GetDB(db_type));
    feature_db->Open(leveldb_path, caffe::db::READ);
    std::shared_ptr<caffe::db::Cursor> cursor(feature_db->NewCursor());             // get cursor for iterator reading,
    //std::shared_ptr<caffe_features_cluster_analysis::db::Transaction> txn(feature_db->NewTransaction());    // get transaction for writing

    // 从字符串中解析出Datum，转换成cv::Mat类型
    cv::Mat features;
    caffe::Datum datum;
    for (cursor->SeekToFirst(); cursor->valid(); cursor->Next()){
        // 从字符串中解析出Datum，一个Datum存储一副图片的所有特征
        datum.ParseFromString(cursor->value());

        // 将Datum转换成cv::Mat类型
        int rows = datum.channels();
        int cols = datum.height() * datum.width();
        cv::Mat feature(rows, cols, CV_32F);
        int datum_index = 0;
        for (int h = 0; h < rows; h++){
            float* ptr = feature.ptr<float>(h);
            for (int w = 0; w < cols; w++){
                *(ptr+w) = datum.float_data(datum_index++);
            }
        }

        // 保存一副图片的所有特征
        features.push_back(feature);
    }
    std::cout << "features - row: " << features.rows << std::endl;
    std::cout << "features - col: " << features.cols << std::endl;

    // 聚类分析
    cerr << "begin to cluster analysis" << endl;
    cv::Mat centers(center_num, features.cols, features.type());  // 聚类中心Mat
    cvflann::KMeansIndexParams params;                            // 聚类参数, 使用默认值
    int n = flann::hierarchicalClustering<cv::flann::L2<float>>(features, centers, params);
    if (center_num > n){
        centers.pop_back(center_num-n);                           // center_num是期望的聚类中心个数，n是实际的聚类中心个数
    }
    cerr << "centers - row: " << centers.rows << endl;
    cerr << "centers - col: " << centers.cols << endl;

    // 写聚类中心到xml文件
    WriteMat(center_file, centers);
    return 0;
}