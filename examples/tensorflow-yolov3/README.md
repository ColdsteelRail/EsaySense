## 将模型导出为SavedModel格式
1. 克隆当前项目
```bashrc
$ git clone https://gitlab.segma.tech/segma-easy-sense/easy-sense-algorithm.git
```
2.  安装第三方包依赖
```bashrc
$ cd examples/tensorflow-yolov3
$ pip install -r ./docs/requirements.txt
```
3. 下载checkpoint(`yolov3_coco.ckpt`)【[BaiduCloud](https://pan.baidu.com/s/11mwiUy8KotjUVQXqkGGPFQ&shfl=sharepset)】
```bashrc
$ cd checkpoint
$ wget https://github.com/YunYang1994/tensorflow-yolov3/releases/download/v1.0/yolov3_coco.tar.gz
$ tar -xvf yolov3_coco.tar.gz
$ cd ..
$ python convert_weight.py
$ python freeze_graph.py
```
4. 运行demo脚本
```bashrc
$ python image_demo.py
$ python video_demo.py # if use camera, set video_path = 0
```
5. 导出成可部署的saved model格式
```bashrc
$ python save_model.py
```
6. 改变导出文件的目录结构，以满足Triton Inference server要求
```bashrc
$ mkdir -p savemodel/yolov3/1/model.savedmodel
$ mv savemodel/yolov3/1/saved_model.pb savemodel/yolov3/1/model.savedmodel/
$ mv savemodel/yolov3/1/variables savemodel/yolov3/1/model.savedmodel/
```
## 参考
[tensorflow-yolov3](https://github.com/YunYang1994/tensorflow-yolov3)