import ctypes
import json
import numpy as np
from flask import Flask, request, jsonify
from plugin.buffer import LineBuffer, PointBuffer, AreaBuffer, BufferMerger
app = Flask(__name__)


#调用： xxx/pointbuffer?wkt=POINT(1 2)&distance=0.5&segments=16
@app.route('/PointBuffer', methods=['GET'])
def _PointBuffer():
    wkt = request.args.get('wkt')
    distance = request.args.get('distance', type=float)
    segments = request.args.get('segments', type=int)
    result = PointBuffer(wkt, distance, segments)
    return jsonify({"result": result})

#调用： xxx/LineBuffer?wkt=LINESTRING(0 0, 1 1)&distance=1.0&segments=16
@app.route('/LineBuffer', methods=['GET'])
def _LineBuffer():
    wkt = request.args.get('wkt')
    distance = request.args.get('distance', type=float)
    segments = request.args.get('segments', type=int)
    result = LineBuffer(wkt, distance, segments)
    return jsonify({"result": result})

@app.route('/AreaBuffer', methods=['GET'])
def _AreaBuffer():
    wkt = request.args.get('wkt')
    distance = request.args.get('distance', type=float)
    segments = request.args.get('segments', type=int)
    result = AreaBuffer(wkt, distance, segments)
    return jsonify({"result": result})

#调用： /BufferMerger?wkts=LINESTRING(0 0, 1 1)&wkts=LINESTRING(1 3, 3 1)
@app.route('/BufferMerger', methods=['GET'])
def _BufferMerger():
    wkts = request.args.getlist('wkts')
    num = len(wkts)
    result = BufferMerger(wkts, num)
    return jsonify({"result": result})
