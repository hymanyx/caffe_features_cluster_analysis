## 程序功能
caffe中extract_features.bin程序提取不同层的特征写入leveldb/imdb中，该程序用来读取leveldb中的特征，并对特征进行聚类分析。

## 代码结构
不同主机上依赖库的安装路径及版本都不同，故在代码中提供了部分依赖库的头文件和链接库。

`include/caffe`   caffe头文件

`include/google/gflags`  gflags头文件

`include/google/glog`   glog头文件

`include/google/protobuf` protobuf头文件

`lib/caffe`     caffe编译后生成的动态/静态链接库

`lib/google/gflags-2.1.2`   gflags编译后生成的动态/静态链接库

`lib/google/glog-0.3.4`     glog编译后生成的动态/静态链接库

`lib/google/protobuf`       protobuf编译后生成的动态/静态链接库