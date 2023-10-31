# cpp微服务操作功能

## 1. 对 C++ 代码编译，将C++转为C

### 1.1 创建构建目录

```bash
mkdir build
```

### 1.2 进入构建目录

```bash 
cd build
```

### 1.3 使用 CMake 配置项目

```bash
cmake ..
```

### 1.4 构建 Release 版本

```bash
cmake --build . --config Release
```

### 1.5 构建 Debug 版本

```bash
cmake --build . --config Debug 
```

## 2. 使用 ctypes 将 C 函数封装为 Python

利用 ctypes 包将 C 函数封装为 Python 可以调用的接口。

### 2.1 导入 ctypes 接口和 lib
```python
import ctypes
 
lib = ctypes.cdll.LoadLibrary('../build/include/Debug/c_model.dll')

```

### 2.2 调用 ctypes 接口
```python
    PointBuffer = lib.c_PointBuffer
    PointBuffer.argtypes = [c_char_p, c_double, c_int]
    PointBuffer.restype = c_char_p
```

### 2.3 返回结果

```python
def PointBuffer(wkt, distance, segments):

    PointBuffer = lib.c_PointBuffer
    PointBuffer.argtypes = [c_char_p, c_double, c_int]
    PointBuffer.restype = c_char_p

    geom = wkt.encode()
    result = PointBuffer(geom, distance, segments)
    print(result.decode())
    return result.decode()
```

## 3. 使用 Flask 发布 Web 服务

```python
import ctypes
import json
import numpy as np
from flask import Flask, request, jsonify
```

### 3.1 定义 Flask 路由

```python
@app.route('/PointBuffer', methods=['GET'])
def _PointBuffer():
    wkt = request.args.get('wkt')
    distance = request.args.get('distance', type=float)
    segments = request.args.get('segments', type=int)
    result = PointBuffer(wkt, distance, segments)
    return jsonify({"result": result})
```
### 3.2 运行 Flask 服务
启动 run.py

### 3.3 通过浏览器或 curl 调用接口

http://127.0.0.1:5000/xxx

xxx：路由及参数信息

demo：

```bash
http://127.0.0.1:5000/pointbuffer?wkt=POINT(1 2)&distance=0.5&segments=16
```
![效果图](./image/调用效果.png)
