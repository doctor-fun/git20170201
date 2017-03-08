 ///
 /// @file    writer.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-03-08 10:46:31
 ///
 
#include <json/json.h>
#include <iostream>
#include <string>
#include <fstream>

using std::cout;
using std::endl;
using std::string;
using std::ofstream;


int main(void)
{
	Json::Value root;
	Json::Value arr;

	Json::Value elem;
	elem["title"] = "百度";
	elem["url"] = "www.baidu.com";
	elem["abstract"] = "王道";

	arr.append(elem);

	elem["title"] = "阿里巴巴";
	elem["url"] = "www.1688.com";
	elem["abstract"] = "批发商";

	arr.append(elem);

	elem["title"] = "腾讯";
	elem["url"] = "www.qq.com";
	elem["abstract"] = "社交";

	arr.append(elem);//往数组里添加信息

	root["BAT"] = arr;//将arr附给对象root

	Json::FastWriter writer;//
	//Json::StyledWriter writer;
	string msg = writer.write(root);//做成一个字符串流命名为msg
	cout << msg << endl;

	ofstream ofs("bat.json");//将数据流写进这个文件里
	ofs << msg;
	ofs.close();

	return 0;
}
