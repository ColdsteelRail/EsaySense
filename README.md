# esay-sense
***

算法模块基础镜像文件
环境：
    * 1. ubuntu16.04
    * 2. gcc4.8 g++4.8 cmake3.8
    * 3. miniconda python3.6 opencv4.1
功能：
    >1. 获取视频流，解码RGB24
    2. 调用算法动态库
    3. 上传算法检测结果
    4. 上传报警结果
    5. 报警逻辑处理
    6. 生成报警uuid
    7. 抓取报警图片
    
环境变量传参：
    * Dockerfile中设置环境变量，变量命名与详细设计文档中相同
    * 根据文档添加部分Config.h中数据和成员
    * iniFile.cpp中添加readStrEnv和readIntEnv函数，读取环境变量
    * 更改Config.cpp/SettingConfig函数中readStrEnv与readIntEnv中参数位环境变量名
