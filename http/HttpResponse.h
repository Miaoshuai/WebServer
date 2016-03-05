#ifndef HTTPRESPONSE_H_
#define HTTPRESPONSE_H_

#include <stdio.h>
#include <map>

namespace muduo
{
namespace net
{

class Buffer;
class HttpResponse
{
 public:
  enum HttpStatusCode
  {
    kUnknown,
    k200Ok = 200,
    k301MovedPermanently = 301,
    k400BadRequest = 400,
    k404NotFound = 404,
  };

  explicit HttpResponse(bool close)
    : statusCode_(kUnknown),
      closeConnection_(close)
  {
  }

  void setStatusCode(HttpStatusCode code)
  { statusCode_ = code; }

  void setStatusMessage(const string& message)
  { statusMessage_ = message; }

  void setCloseConnection(bool on)
  { closeConnection_ = on; }

  bool closeConnection() const
  { return closeConnection_; }

  void setContentType(const string& contentType)
  { 
      printf("hehe\n");
      addHeader("Content-Type", contentType); 
  }

  void addHeader(const string& key, const string& value)
  { headers_[key] = value; }


  void setFd(int fd)
  {
    fd_ = fd;
  }

  void appendToBuffer(Buffer* output) const;

  

 private:
  std::map<string, string> headers_;
  HttpStatusCode statusCode_;
  string statusMessage_;
  bool closeConnection_;
  int fd_;  //所请求资源文件的文件描述符
};

}
}

#endif
