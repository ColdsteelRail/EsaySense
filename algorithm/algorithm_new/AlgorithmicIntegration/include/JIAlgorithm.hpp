//
// Created by hrh on 2019-09-07.
//


#ifndef JIALGORITHM_SDK_H
#define JIALGORITHM_SDK_H

#include <string>

#define GET_PROPERTY_SUCCESS 100
#define INIT_MODULE_SUCCESS 200
#define PROCESS_SUCCESS 300
#define FAILED -1

typedef struct {
    int ret;   // 状态码
    char *detectResult; // 检测结果（json格式的字符串）
    int *result;    // 结果码
    int resultLen;  // 结果码长度
} PROCESS_RESULT;

// RGB24 格式的图像
typedef struct {
    int cols;  // image cols
    int rows;   // image rows
    unsigned char *data; // image buffer, RGB24, e.g. RGBRGBRGB
} CV_FRAME;

/**
 * 算法接口基类
 *
 */
class JIAlgorithm {

public:

    /**
     * 获取模型运行所需的资源情况
     *
     * @param[out] GPUUseup 算法对GPU的显存消耗值，单位GB
     * @param[out] AlgName 算法名称，由内部申请内存并填充，内存由内部释放
     * @return 成功返回GET_PROPERTY_SUCCESS，失败返回FAILED
     */
    virtual int AlgorithmGetProperty(double *GPUUseup, char **AlgName) = 0;

    /**
     * 设置算法的运行参数
     *
     * @param[in] GPUID 设置算法运行在哪块GPU上，-1表示用CPU，0-N表示GPU的编号
     * @param[in] logPath 设置日志全路径名称，包括文件名字，由内部申请内存并填充，内存由内部释放
     * @return 成功返回GET_PROPERTY_SUCCESS，失败返回FAILED
     */
    virtual int AlgorithmInitModle(int GPUID, char *logPath) = 0;

    /**
     * 调用算法处理图片，并返回结果
     *
     * @param[in] cameraID 相机编号
     * @param[in] timeStamps 当前时间戳
     * @param[in] image RGB24图像
     * @param[out] processResult 返回的结果信息，参考PROCESS_RESULT的定义，由外部提供一个PROCESS_RESULT结构体的指针，由外部负责释放
     *                           所使用的内存
     * @return 成功返回INIT_MODULE_SUCCESS，失败返回FAILED
     */
    virtual int AlgorithmRun(char *cameraID, long long timeStamps, CV_FRAME *image, PROCESS_RESULT *processResult) = 0;

    /**
     * 反初始化函数，用于释放资源
     */
    virtual void AlgorithmUnInitModle() = 0;

protected:
    char *mAlgorithmName;   // 算法名称
};

#endif //JIALGORITHM_SDK_H
