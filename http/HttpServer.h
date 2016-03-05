
#ifndef HTTPSERVER_H_
#define HTTPSERVER_H_

#include <muduo/net/TcpServer.h>


namespace muduo
{
namespace net
{

class HttpRequest;
class HttpResponse;

class HttpServer
{
 public:
  typedef boost::function<void (const HttpRequest&,
                                HttpResponse*)> HttpCallback;

  HttpServer(EventLoop* loop,
             const InetAddress& listenAddr,
             const string& name,
             TcpServer::Option option = TcpServer::kReusePort);

  ~HttpServer();  

  EventLoop* getLoop() const { return server_.getLoop(); }

  //设置自定义http回调
  void setHttpCallback(const HttpCallback& cb)
  {
    httpCallback_ = cb;
  }

  void setThreadNum(int numThreads)
  {
    server_.setThreadNum(numThreads);
  }

  void start();

 private:
  void onConnection(const TcpConnectionPtr& conn);
  void onMessage(const TcpConnectionPtr& conn,
                 Buffer* buf,
                 Timestamp receiveTime);
  void onRequest(const TcpConnectionPtr&, const HttpRequest&);

  TcpServer server_;
  HttpCallback httpCallback_;
};

}
}

#endif  
