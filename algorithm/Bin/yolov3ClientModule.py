# -*- coding: utf-8 -*-
import json
import traceback

import cv2
import numpy as np
from PIL import Image
from loguru import logger
from tensorrtserver.api import *
import tensorrtserver.api.model_config_pb2 as model_config

import utils

class Yolov3RemoteInference(object):
    def __init__(self, protocol="grpc", url="localhost:8001", 
        model_name="yolov3", model_version=1, batch_size=1, verbose=False, roi=None, model_args=None):
        self.roi = roi
        self.model_args = model_args
        self.num_classes = 80
        self.model_name = model_name
        self.protocol = ProtocolType.from_str(protocol)
        self.input_name, self.output_name, self.c, self.h, self.w, \
        self.format, self.dtype, self.max_batch_size = self.parse_model(
            url, self.protocol, self.model_name, batch_size, verbose)

        logger.info("algorithm instance url is: {}".format(url))
        logger.info("model args is: {}".format(str(self.model_args)))
        logger.info("roi is: {}".format(str(self.roi)))
        logger.info("model input names:{}".format(self.input_name))
        logger.info("model output names:{}".format(self.output_name))
        logger.info("model input image height:{}, width:{}, channel:{}, format:{}, dtype:{}".format(
            self.h, self.w, self.c, model_config.ModelInput.Format.Name(self.format), self.dtype))

        self.ctx = InferContext(url, self.protocol, self.model_name,
                       model_version, verbose, 0, False)

    def parse_model(self, url, protocol, model_name, batch_size, verbose=False):
        

        print("url:",url)
        print("protocol:",protocol)
        print("model_name:",model_name)
        print("verbose:",verbose)
        ctx = ServerStatusContext(url, protocol, model_name, verbose)
        server_status = ctx.get_server_status()
        if model_name not in server_status.model_status:
            raise Exception("unable to get status for '" + model_name + "'")

        status = server_status.model_status[model_name]
        config = status.config

        print("input:", config.input)
        print("output:", config.output)
        input_name = [x.name for x in config.input]
        output_name = [x.name for x in config.output]

        max_batch_size = config.max_batch_size

        if max_batch_size == 0:
            if batch_size != 1:
                raise Exception("batching not supported for model '" + model_name + "'")
        else:
            if batch_size > max_batch_size:
                raise Exception("expecting batch size <= {} for model {}".format(max_batch_size, model_name))
        
        input = config.input[0]
        if ((input.format != model_config.ModelInput.FORMAT_NCHW) and
            (input.format != model_config.ModelInput.FORMAT_NHWC)):
            raise Exception("unexpected input format " + model_config.ModelInput.Format.Name(input.format) +
                            ", expecting " +
                            model_config.ModelInput.Format.Name(model_config.ModelInput.FORMAT_NCHW) +
                            " or " +
                            model_config.ModelInput.Format.Name(model_config.ModelInput.FORMAT_NHWC))
        if input.format == model_config.ModelInput.FORMAT_NHWC:
            h = input.dims[0]
            w = input.dims[1]
            c = input.dims[2]
        else:
            c = input.dims[0]
            h = input.dims[1]
            w = input.dims[2]
        
        return (input_name, output_name, c, h, w, input.format, self.model_dtype_to_np(input.data_type), max_batch_size)
    
    def model_dtype_to_np(self, model_dtype):
        if model_dtype == model_config.TYPE_BOOL:
            return np.bool
        elif model_dtype == model_config.TYPE_INT8:
            return np.int8
        elif model_dtype == model_config.TYPE_INT16:
            return np.int16
        elif model_dtype == model_config.TYPE_INT32:
            return np.int32
        elif model_dtype == model_config.TYPE_INT64:
            return np.int64
        elif model_dtype == model_config.TYPE_UINT8:
            return np.uint8
        elif model_dtype == model_config.TYPE_UINT16:
            return np.uint16
        elif model_dtype == model_config.TYPE_FP16:
            return np.float16
        elif model_dtype == model_config.TYPE_FP32:
            return np.float32
        elif model_dtype == model_config.TYPE_FP64:
            return np.float64
        elif model_dtype == model_config.TYPE_STRING:
            return np.dtype(object)
        return None

    def run(self, input_batch, batch_size):

        if batch_size > self.max_batch_size:
            raise Exception("expecting batch size <= {} for model {}".format(self.max_batch_size, self.model_name))

        results = self.ctx.run(
            { self.input_name[0] : input_batch},
            { self.output_name[0] : (InferContext.ResultFormat.RAW),
              self.output_name[1] : (InferContext.ResultFormat.RAW),
              self.output_name[2] : (InferContext.ResultFormat.RAW)},
            batch_size
        )
        return results

# @logger.catch
def AlgorithmInitModle(GPUID, log_path, model_args=None, address="localhost", port="8001", roi=None):

    logger.add(log_path, rotation="1 MB", backtrace=False, level="DEBUG")
    logger.info("python: GPUID received: %d" % GPUID)
    logger.info("log_path received: %s\n" % log_path)

    #生成INFO.log
    logger.add(log_path,
                level="INFO",
                format="{time:YYYY-MM-DD at HH:mm:ss} | {level} | {message}",
                rotation="00:00",
                retention="1 month")
    # # 生成ERROR.log
    logger.add(log_path,
               level="ERROR",
               format="{time:YYYY-MM-DD at HH:mm:ss} | {level} | {message}",
               rotation="00:00",
               retention="1 month")

    # 初始化模型远程推理类
    global Yolov3Inference
    try:
        url = address + ":" + port
        model_args = json.loads(model_args)
        Yolov3Inference = Yolov3RemoteInference(url=url, roi=roi, model_args=model_args)  
        return int(1)
    except Exception as e:
        # 捕获错误信息
        error_info = traceback.format_exc()
        logger.error(error_info)
        return int(0)

# @logger.catch
def AlgorithmGetProperty():

    GPUUseup = 0 # GPU ID
    alg_name = 'yolov3' # 算法名称
    logger.info("GPUUseup %f" %GPUUseup)
    logger.info("Algorithm name: %s" %alg_name)
    return True, GPUUseup, alg_name

# @logger.catch
def AlgorithmRun(cameraID, timeStamps, img):

    global Yolov3Inference
    # Yolov3Inference = Yolov3RemoteInference()  
    # init return values
    ret = False
    result = []
    boxes = []
    save_input = False
    save_output = False

    try:
        original_image_list = []
        original_image_size_list = []
        original_image = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        original_image_list.append(original_image)
        original_image_size_list.append(original_image.shape[:2])
        # preprocess
        image_data = utils.preprocess(np.copy(original_image), [Yolov3Inference.h, Yolov3Inference.w])
        image_data = image_data.astype(np.float32)
        # batch images inference avaiable
        input_batch = []
        input_batch.append(image_data)
        batch_size = len(input_batch)
        if batch_size != 1:
            raise("Do not support batch size {}, expect 1".format(batch_size))

        results = Yolov3Inference.run(input_batch, batch_size)

        for indx in range(batch_size):
            pred_sbbox = results["pred_sbbox"][indx]
            # print("pred_sbbox shape:", pred_sbbox.shape)
            pred_mbbox = results["pred_mbbox"][indx]
            # print("pred_mbbox shape:", pred_mbbox.shape)
            pred_lbbox = results["pred_lbbox"][indx]
            # print("pred_lbbox shape:", pred_lbbox.shape)

            pred_bbox = np.concatenate([np.reshape(pred_sbbox, (-1, 5 + Yolov3Inference.num_classes)),
                                        np.reshape(pred_mbbox, (-1, 5 + Yolov3Inference.num_classes)),
                                        np.reshape(pred_lbbox, (-1, 5 + Yolov3Inference.num_classes))], axis=0)
            
            bboxes = utils.postprocess_boxes(pred_bbox, original_image_size_list[indx], 608, 0.3)
            bboxes = utils.nms(bboxes, 0.45, method='nms')


            if len(bboxes)>0:
                image, bboxes_json = utils.draw_bbox(original_image_list[indx], bboxes)

                pic_size = list(image.shape)
                result = [1]
                boxes = bboxes_json
            else:
                image = img
                pic_size = list(image.shape)
                
            detection_result = {"cameraID":cameraID,
                                "timeStamps": timeStamps,
                                "picSize":pic_size,
                                "boxes":boxes,
                                "result":result,
                                "res1":"",
                                "res2":""
                                }
            ret = True

    except Exception as e:
        # 捕获错误信息
        error_info = traceback.format_exc()
        logger.error(error_info)
        image = img
        pic_size = list(image.shape)
        # 生成返回的json信息
        detection_result = {"cameraID":cameraID,
                            "timeStamps": timeStamps,
                            "picSize":pic_size,
                            "boxes":boxes,
                            "result":result,
                            "res1":"",
                            "res2":""
                            }

    detectResult = json.dumps(detection_result)


    return ret, result, detectResult, save_input, save_output, image