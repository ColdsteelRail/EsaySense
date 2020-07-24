FROM ubuntu_client:16.04

WORKDIR /root
COPY . .
COPY dependency /usr/lib

ENV EVENT_ID ffasfa234sa
ENV MODEL_ARGS "{\"arg1\":1, \"arg2\":2}"
ENV ALGORITHM_INSTANCE_ADDRESS  10.88.0.26
ENV ALGORITHM_INSTANCE_PORT 	8001
ENV ANALYSIS_FREQUENCY	5
ENV CONTROL_FLAG	star
ENV ROI 		[[50,50],[450,500]]
#[Config]
ENV CONFIG_IP_ADDRESS	10.88.0.94
ENV CONFIG_PORT		12000	
ENV CONFIG_USER_NAME	admin
ENV CONFIG_PASS_WORD	admin
ENV HANDLE_INDEX_BEGIN	0
ENV HANDLE_INDEX_END	0

#[Upload]
ENV UPLOAD_IP_ADDRESS	10.88.0.94
ENV UPLOAD_PORT		12000

#[Alarm]
ENV ALARM_IP_ADDRESS	127.0.0.1
ENV ALARM_PORT		6379

#[Algorithm]
ENV Algorithm_type	3
ENV ALGORITHM_SO_NAME	yolov3ClientModule
ENV DEVICE_ID		1,

WORKDIR /root/foundation
RUN sh -c '/bin/echo -e "yes\n\nyes\n" | sh Miniconda3-4.5.4-Linux-x86_64.sh'
ENV PATH /root/foundation/cmake/cmake-3.8.0-Linux-x86_64/bin:/root/miniconda3/bin:$PATH
RUN pip install -r requirements.txt -i https://pypi.doubanio.com/simple/
RUN pip install tensorrtserver-1.3.0-py2.py3-none-linux_x86_64.whl
RUN apt-get update
RUN apt-get install -y --no-install-recommends 
RUN apt-get install -y gcc-4.8
RUN apt-get install -y g++-4.8 
RUN apt-get install -y uuid-dev
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 100
RUN update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.8 100

WORKDIR /root/algorithm/algorithm_new/build
RUN cmake .. 
RUN make

WORKDIR /root/algorithm/Bin
