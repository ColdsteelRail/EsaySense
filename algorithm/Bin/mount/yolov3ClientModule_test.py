# -*- coding: utf-8 -*-
import cv2
from PIL import Image

import yolov3ClientModule

cameraID = 1

timeStamps = 121
img = cv2.imread("./person.jpg")

# 测试AlgorithmGetProperty函数
isTrue, GPUUseup, alg_name = yolov3ClientModule.AlgorithmGetProperty()
print("isTrue:",isTrue)
print("GPUUseup:",GPUUseup)
print("alg_name:",alg_name)

# 测试AlgorithmInitModle函数
model_args = '{"test_k":"test_value"}'
address = '10.88.0.26'
port = '8001'
roi = '[]'
isTrue = yolov3ClientModule.AlgorithmInitModle(0, './yolov3ClientModuleLogs', model_args=model_args, address=address, port=port, roi=roi)
print("isTrue:",isTrue)

# 测试AlgorithmRun函数
ret, result, detection_result_json, save_input, save_output, image =yolov3ClientModule.AlgorithmRun(cameraID, timeStamps, img)
tmp_image = Image.fromarray(image)
tmp_image.save("./result.jpg")
print("ret:",ret)
print("result:",result)
print("detection_result_json:",detection_result_json)