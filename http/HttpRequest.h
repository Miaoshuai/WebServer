/*======================================================
    > File Name: HttpRequest.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月04日 星期五 10时43分15秒
 =======================================================*/

#ifndef HTTPREQUEST_H_
#define HTTPREQUEST_H_

#include <map>
#include <assert.h>
#include <stdio.h>

namespace muduo
{
namespace net
{
    class HttpRequest
    {
        public:
            enum Method     //http请求的方法
            {
                kInvalid,kGet,kPost,kHead,kOptions,kPut,kDelete
            };

            enum Version    //http版本
            {
                kUnknown,kHttp10,kHttp11
            };
            
            void setVersion(Version v)
            {
                version_ = v;
            }

            Version getVersion()const
            {
                return version_;
            }
            
            //设置方法
            bool setMethod(const char *start,const char *end)
            {
                assert(method_ == kInvalid);
                string m(start,end);
                if(m == "GET")
                {
                    method_ = kGet;
                }
                else if(m == "POST")
                {
                    method_ = kPost;
                }
                else if(m == "HEAD")
                {
                    method_ = kHead;
                }
                else if(m == "PUT")
                {
                    method_ = kPut;
                }
                else if(m == "DELETE")
                {
                    method_ = kDelete;
                }
                else
                {
                    method__ != kInvalid;
                }

                return method_ != kInvalid;
            }

            Method method()const
            {
                return method_;
            };

            const char *methodString()const
            {
                const char *result = "UNKNOWN";
                switch(method_)
                {
                    case kGet:
                        result = "GET";     //常用于获取某个资源文件
                        break;
                    case kPost:
                        result = "POST";    //通常用来获得表单提交
                        break;
                    case kHead:
                        result = "HEAD";    //和GET方法类似，只获取头部没有body
                        break;
                    case kOptions:
                        result = "OPTIONS"
                    case kPut:
                        result = "PUT";     //不支持
                        break;
                    case kDelete:
                        result = "DELETE";  //不支持
                        break;
                    default:
                        break;
                
                    return result;
                }
            }

            void setPath(const char *start,const char *end)
            {
                path_.assign(start,end);        //将start-end赋给path_
            }

            const string &path()const
            {
                return path_;
            }

            void setQuery(const char *start,const char *end)
            {
                query_.assign(start,end);
            }

            const string &query()const
            {
                return query_;
            }
            
            //增加请求头的内容
            void addHeader(const char *start,const char *colon,const char *end)
            {
                string field(start,colon);//头类型
                ++colon;
                while(colon < end && isspace(*colon))
                {
                    ++colon;
                }

                string value(colon,end);//头内容
                while(!value.empty() && isspace(value[value.size() - 1]))
                {
                    value.resize(value.size() - 1);
                }
                headers_[field] = value;
            }

            //获得某项头部信息
            string getHeader(const string &field)const
            {
                string result;
                std::map<string,string>::const_iterator it = headers_.find(field);
                if(it != headers_.end())
                {
                  return result = it->second;
                }
                return NULL;
            }
            
            //获得所有头部信息
            const std::map<string,string> &headers()const
            {
                return headers_;
            }

            //交换http请求
            void swap(HttpRequest &that)
            {
                std::swap(method__,that.method_);
                path_.swap(that.path_);
                query_.swap(that.query_);
                receiveTime_.swap(that.receiveTime_);
                headers_.swap(that,headers_);
            }


        private:
            Method method_;     //http请求的方法
            Version version_;   //http版本号
            string path_;       //请求的路径
            string query_;      //请求body的内容
            std::map<string,string> headers_;//请求头的各个选项

    };
}
}

#endif
