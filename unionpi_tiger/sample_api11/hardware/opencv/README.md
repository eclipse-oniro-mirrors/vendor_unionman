#此样例为OPENCV的使用样例

需要移植OPENCV库到路径vendor / unionman / unionpi_tiger / sample / third_party /
    opencv才可以使用，样例中包含了图像尺寸转换的napi接口，来适配yolo5s的模型，yolo5s模型只能接收640x640x3的图片进行对象识别检测。下载链接为：https
    : // gitee.com/umspark/aml_npu_sdk

      将其中的third_party下载拷贝到vendor\unionman\unionpi_tiger\sample路径下。