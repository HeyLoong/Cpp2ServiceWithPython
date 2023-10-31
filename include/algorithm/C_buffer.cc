#include <geos/geom/Geometry.h>
#include <geos/geom/GeometryFactory.h>
#include <geos/geom/LineString.h>
#include <geos/geom/LinearRing.h>
#include <geos/geom/Point.h>
#include <geos/geom/Polygon.h>
#include <geos/io/WKTReader.h>
#include <geos/io/WKTWriter.h>

#include <iostream>

#include "algorithm/analysis/buffer.h"
using namespace algorithm::analysis; 
using namespace geos::geom; 
using namespace geos::io;

/*
buffer重写

对于复杂类型 我们将重写函数的输入设置为wkt参数  输出wkt，以便于前端的数据获取解析
*/

#ifdef __cplusplus
extern "C" {
#endif

__declspec(dllexport) char* c_PointBuffer(char* req, double distance, int n) {
  // 创建几何工厂
  GeometryFactory::Ptr factory = GeometryFactory::create();
  WKTReader reader(*factory);
  std::unique_ptr<Geometry> geometry(reader.read(req));

  // 调用
  auto result = PointBuffer(dynamic_cast<geos::geom::Point*>(geometry.get()),
                            distance, n);

  // 输出
  geos::geom::LinearRing* res = static_cast<geos::geom::LinearRing*>(&result);
  WKTWriter writer;
  writer.setTrim(true);
  std::string inter_wkt = writer.write(res);
  char* response = strdup(inter_wkt.c_str());
  return response;
}

__declspec(dllexport) char* c_LineBuffer(char* req, double distance, int n) {
  // 创建几何工厂
  GeometryFactory::Ptr factory = GeometryFactory::create();
  WKTReader reader(*factory);
  std::unique_ptr<Geometry> geometry(reader.read(req));

  // 调用
  auto result = LineBuffer(
      dynamic_cast<geos::geom::LineString*>(geometry.get()), distance, n);

  // 输出
  geos::geom::LinearRing* res = static_cast<geos::geom::LinearRing*>(&result);
  WKTWriter writer;
  writer.setTrim(true);
  std::string inter_wkt = writer.write(res);
  char* response = strdup(inter_wkt.c_str());
  return response;
}

__declspec(dllexport) char* c_AreaBuffer(char* req, double distance, int n) {
  // 创建几何工厂
  GeometryFactory::Ptr factory = GeometryFactory::create();
  WKTReader reader(*factory);
  std::unique_ptr<Geometry> geometry(reader.read(req));

  // 调用
  auto result = AreaBuffer(dynamic_cast<geos::geom::Polygon*>(geometry.get()),
                           distance, n);

  // 输出
  geos::geom::LinearRing* res = static_cast<geos::geom::LinearRing*>(&result);
  WKTWriter writer;
  writer.setTrim(true);
  std::string inter_wkt = writer.write(res);
  char* response = strdup(inter_wkt.c_str());
  return response;
}

__declspec(dllexport) char* c_BufferMerger(char** buffers, int buffers_num) {
  // 创建几何工厂
  GeometryFactory::Ptr factory = GeometryFactory::create();
  WKTReader reader(*factory);

  std::vector<LinearRing> geo_buffers;
  for (int i = 0; i < buffers_num; i++) {
    std::unique_ptr<Geometry> geometry(reader.read(buffers[i])); 
    LinearRing* ring = dynamic_cast<LinearRing*>(geometry.get());
    geo_buffers.push_back(*ring);
  }
  // 调用
  auto result = BufferMerger(geo_buffers);

  // 输出
  geos::geom::LinearRing* res = static_cast<geos::geom::LinearRing*>(&result);
  WKTWriter writer;
  writer.setTrim(true);
  std::string inter_wkt = writer.write(res);
  char* response = strdup(inter_wkt.c_str());
  return response;
}

#ifdef __cplusplus
}
#endif