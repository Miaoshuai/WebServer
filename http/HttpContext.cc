/*======================================================
    > File Name: HttpContext.cc
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月04日 星期五 13时24分00秒
 =======================================================*/

#include <muduo/net/Buffer.h>
#include "HttpContext.h"
#include <stdio.h>
using namespace muduo;
using namespace muduo::net;

//解析请求行
bool HttpContext::processRequestLine(const char *begin,const char *end)
{
    bool succeed = false;
    const char *start = begin;
    const char *space = std::find(start,end,' ');//找到空格的位置

    if(space != end && request_.setMethod(start,space))//将start到空格的值赋给请求方式
    {
        start = space + 1;
        space = std::find(start,end,' ');//继续寻找下个空格
        if(space != end)
        {
            const char *question = std::find(start,space,'?');//看url里是否传了值
            if(question != space)   //如果GET里有值的话
            {
                request_.setPath(start,question);//设置路径
                request_.setQuery(question,space);//设置传值的内容

            }
            else    //只是url没传值    
            {
                request_.setPath(start,space);//请求的地址
            }
            start = space + 1;
            
            succeed = end-start == 8 && std::equal(start,end - 1,"HTTP/1.");//是否为http协议
            if(succeed)
            {
                if(*(end - 1) == '1')
                {
                    request_.setVersion(HttpRequest::kHttp11);//给版本类型赋值
                }
                else if(*(end -1) == '0')
                {
                    request_.setVersion(HttpRequest::kHttp10);
                }

                else
                {
                    succeed = false;
                }
            }
        }
    }
    return succeed;
}

bool HttpContext::parseRequest(Buffer *buf,Timestamp receiveTime)
{
    bool ok = true;
    bool hasMore = true;
    while(hasMore)
    {
        if(state_ == kExpectRequestLine)
        {
            const char *crlf = buf->findCRLF();
            if(crlf)
            {
                ok = processRequestLine(buf->peek(),crlf);//解析请求行
                if(ok)
                {
                    request_.setReceiveTime(receiveTime);
                    buf->retrieveUntil(crlf +2);
                    state_ = kExpectHeaders;

                }
                else
                {
                    hasMore = false;
                }
            }
            else
            {
                hasMore = false;
            }
        }
        else if(state_ == kExpectHeaders)//解析头部
        {
            const char *crlf = buf->findCRLF();
            if(crlf)
            {
                const char *colon = std::find(buf->peek(),crlf,':');
                if(colon != crlf)
                {
                    request_.addHeader(buf->peek(),colon,crlf);
                }
                else
                {
                    //printf("\n\n呵呵\n\n");
                    state_ = kExpectBody;   //头部解析结束
                    //hasMore = false;
                }
                buf->retrieveUntil(crlf + 2);   //Buffer位置的移动
            }
            else
            {
                //属于出错情况
                hasMore = false;
            }
        }
        else if(state_ == kExpectBody)//解析body
        {
            //如果buffer中无可读字节，说明body为空
            if(buf->readableBytes() <= 0)
            {
                state_ = kGotAll;   //获得全部内容的状态标志
                break;
            }

            //std::string body(buf->peek(),buf->readableBytes());
            //将剩余内容设置为主体内容
            request_.setQuery(buf->peek(),buf->peek() + buf->readableBytes());
        }
    }
    return ok;
}
