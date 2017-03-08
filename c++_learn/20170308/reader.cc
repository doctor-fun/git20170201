 ///
 /// @file    json.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-03-08 10:34:20
 ///
 
#include <json/json.h>
#include <iostream>
#include <fstream>
#include <string>
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

int main(void)
{
	ifstream ifs("test.json");//读取jason文件	
	if(!ifs.good())
	{	cout << "ifstream open error!" << endl; return -1;}
	
	Json::Reader reader;//解系js
	Json::Value root;//对象

	if(!reader.parse(ifs, root, false))//root容器,失败返回零
	{
		cout << "json parse error!" << endl;
		ifs.close();
		return -1;
	}

	string title;
	string url;
	string abstract;
	Json::Value arr = root["BAT"];//获得键值
	for(size_t idx = 0; idx != arr.size(); ++ idx)
	{
		title = arr[idx]["title"].asString();//二维数据，asString使用字符串的方式打印出来
		url = arr[idx]["url"].asString();
		abstract = arr[idx]["abstract"].asString();
		cout << "title:" << title << endl;
		cout << "url:" << url << endl;
		cout << "abstract:" << abstract << endl;
		cout << endl;
	}

	return 0;
}
