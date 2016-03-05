/*======================================================
    > File Name: HttpCallback.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月08日 星期二 16时50分43秒
 =======================================================*/
#include "HttpRequest.h"
#include "HttpResponse.h"

#include <string>
#include <map>


//从字符串中截取配置名字和配置内容
std::pair<std::string,std::string> intercept(const char *str);

//从字符串中提取map的key和value
std::pair<std::string,std::string> extract(const char *str);


//获得MIME的map(将包含文件后缀名和对应MIME类型装载成一个map)
std::map<std::string,std::string> getAllMIME(void);


//根据key在配置文件中获得对应的属性
std::string getMessageFromFile(const std::string &key);

//获得客户端要获取的文件的后缀名
std::string getContentType(const std::string path);

//http服务器回调
void httpCallback(const muduo::net::HttpRequest &req,muduo::net::HttpResponse *resp);
