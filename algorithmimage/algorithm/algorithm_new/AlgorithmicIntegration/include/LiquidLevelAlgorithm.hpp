//
// Created by rawk on 2019-09-11.
//

#ifndef JIALGORITHM_SDK_LIQUIDLEVELALGORITHM_HPP
#define JIALGORITHM_SDK_LIQUIDLEVELALGORITHM_HPP

#include <JIAlgorithm.hpp>
#include <string>

#ifdef __cplusplus
extern "C" {
#include "image.h"
};
#endif
#include "network.h"

class LiquidLevelAlgorithm: public JIAlgorithm {
private:
    image **alphabet;
    float demo_thresh = 0.5;
    float hier_thresh=0.5;
    int demo_classes=1;
    network *predictor = NULL;
    char **names = NULL;
    float nms = .45;    // 0.4F
public:
    LiquidLevelAlgorithm() {
        std::string name = "LiquidLevelAlgorithm";
        mAlgorithmName = (char *)malloc(name.size() + 1);
        strcpy(mAlgorithmName, name.c_str());
    }

    int AlgorithmGetProperty(double *GPUUseup, char **AlgName) override;

    int AlgorithmInitModle(int GPUID, char *logPath) override;

    int AlgorithmRun(char *cameraID, long long timeStamps, CV_FRAME *image, PROCESS_RESULT *processResult) override;

    void AlgorithmUnInitModle() override;

};


#endif //JIALGORITHM_SDK_LIQUIDLEVELALGORITHM_HPP
