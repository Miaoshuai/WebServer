#include "HttpResponse.h"
#include "buffer.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

using namespace muduo;
using namespace muduo::net;

void HttpResponse::appendToBuffer(Buffer* output) const
{
  char buf[32];
  int size = 0;
  snprintf(buf, sizeof buf, "HTTP/1.1 %d ", statusCode_);
  output->append(buf);
  output->append(statusMessage_);
  output->append("\r\n");

  if (closeConnection_)
  {
    output->append("Connection: close\r\n");
  }
  else
  {
    //printf("\n**%d**\n",body_.length());
    //snprintf(buf, sizeof buf, "Content-Length: %zd\r\n", body_.size());
    //output->append(buf);
  }

  for (std::map<string, string>::const_iterator it = headers_.begin();
       it != headers_.end();
       ++it)
  {
    output->append(it->first);
    output->append(": ");
    output->append(it->second);
    output->append("\r\n");
  }

    struct stat stat_buf;
    fstat(fd_,&stat_buf);
    snprintf(buf, sizeof buf, "Content-Length: %ld\r\n",stat_buf.st_size);
   // printf("\nsize = %d\n",size);
    output->append("Connection: Keep-Alive\r\n");
    output->append(buf);
    output->append("\r\n");
    char data[1024];
    int ret;
    
    while((ret = read(fd_,data,sizeof(data))) > 0)
    {
        output->append(data,ret);
        size += ret;
    }

    printf("\nsize = %d\n",size);
    close(fd_);
    
    snprintf(buf, sizeof buf, "Content-Length: %d\r\n",size);
    printf("\nsize = %d\n",size);
    output->append("Connection: Keep-Alive\r\n");
}
