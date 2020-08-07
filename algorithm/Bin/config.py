import cv2
import numpy as np


# 设置画面ROI区域
ROI = [0,960,80,540]
WIDTH = ROI[1]-ROI[0]
HEIGHT = ROI[3]-ROI[2]
# 模板图片
standard_figure = cv2.imread('standard_figure.jpg',-1).astype(np.uint8)

# 后处理相关参数
max_zero_conut = 50
area_list_length = 5 # 建议设置为奇数，便于计算中位数
area_list = [None]*area_list_length # 存储历史面积数据的数组
median_index = (area_list_length+1)//2

# 图像处理参数
min_area = 1000       # 需要去除的小轮廓面积阈值
max_area = 20000      # 激光线二值图最大允许面积
min_area_max = 10000  # 最小有效面积

PIXEL_WIDTH = 855