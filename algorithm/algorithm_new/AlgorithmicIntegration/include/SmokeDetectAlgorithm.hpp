//
// Created by rawk on 2019-09-11.
//

#ifndef JIALGORITHM_SDK_SMOKEDETECTALGORITHM_HPP
#define JIALGORITHM_SDK_SMOKEDETECTALGORITHM_HPP

#include <JIAlgorithm.hpp>
#ifdef __cplusplus
#include <string.h>
#include <stdlib.h>
#endif // __cplusplus


class SmokeDetectAlgorithm: public JIAlgorithm {
public:
    SmokeDetectAlgorithm() {
        std::string name = "SmokeDetectAlgorithm";
        mAlgorithmName = (char *)malloc(name.size() + 1);
        strcpy(mAlgorithmName, name.c_str());
    }
    int AlgorithmGetProperty(double *GPUUseup, char **AlgName) override;

    int AlgorithmInitModle(int GPUID, char *logPath) override;

    int AlgorithmRun(char *cameraID, long long timeStamps, CV_FRAME *image, PROCESS_RESULT *processResult) override;

    void AlgorithmUnInitModle() override;

};


#endif //JIALGORITHM_SDK_SMOKEDETECTALGORITHM_HPP
