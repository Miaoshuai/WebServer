/*======================================================
    > File Name: HttpContext.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月04日 星期五 13时23分10秒
 =======================================================*/

#ifndef HTTPCONTEXT_H_
#define HTTPCONTEXT_H_

#include "HttpRequest.h"


    class Buffer;
    class HttpContext : public muduo::copyable
    {
        public:
            enum HttpRequestParseState
            {
                kExpectRequestLine,
                kExpectHeaders,
                kExpectBody,
                kGotAll,
            };

            HttpContext()
                :state_(kExpectRequestLine)
            {
            
            }
            
            bool parseRequest(Buffer *buf,Timestamp receiveTime);

            bool gotAll()const  //请求结束获得所有内容
            {
                return state_ == kGotAll;
            }

            void reset()
            {
                state_ = kExpectRequestLine;
                HttpRequest dummy;
                request_.swap(dummy);
            }

            const HttpRequest &request()const   //获得完整的http请求
            {
                return request_;
            }

            HttpRequest &request()
            {
                return request_;
            }
        private:
            //处理请求行
            bool processRequestLine(const char *begin,const char *end);

            HttpRequestParseState state_;   //处理请求的状态
            HttpRequest request_;           //请求类
            
    };
}
}

#endif
