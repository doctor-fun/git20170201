#include<iostream>
#include<set>
#include<map>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>//字符串流
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::set;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::ostream;
using std::cin;
class TextQuery
{
	public:
	    void readFile(const string filename);
		ostream &query_and_print(const string & word,ostream & os);
		string  trans(const string &s);
		void  runQueries();
	private:
		vector<string> _vecLines;//每行内容
	    map<string, set<int> > _mapWord2Line;//单词所在行
		map<string, int> _mapWordFreq;//单词出现的频率
};
string  TextQuery::trans(const string &s)//对单词进行处理，如大写转换为小写,逗号和句号删除
{
	string s_back;
	for(auto it=s.begin();it!=s.end();++it)
	{
	if(!ispunct(*it))//字母、数字、空格则返回零
		s_back +=tolower(*it);//
	}
	return s_back;
}
void TextQuery::readFile(const string filename)
{	
		//文件打开
		ifstream infile;
		infile.open(filename.c_str());
		if(!infile.good()){
			cout<<"File opened error!"<<endl;
			infile.close();
			return;
		}
		//开始读行
		string line;
		int lineno=0;
		string word;//定义一个单词
		while(getline(infile,line))//从infile输入流里面逐行(getline)读入内容
		{
		int line_tmp=lineno++;//行数加1
			_vecLines.push_back(line);//将此行放进_vecLines这一容器内

			istringstream iss(line);//将此行的内容绑定到iss，以空格作为分隔符将这一行的内容分开
			while(iss>>word)//将iss一行数据的内容以单词的形式逐个放到word中备处理
			{
				//以下是进行计数的过程	
				trans(word);//对单词进行处理，去大写去符号
				auto ret=_mapWordFreq.insert({word,1});//将单词进行计数,如果插入成功，则ret.second返回值为true
				//否则ret.second返回值为false
				if(!ret.second)
				{
					(ret.first->second)++;//已有的单词（ret.first）则次数加1(++)；
				}
				_mapWord2Line[trans(word)].insert(line_tmp);
			}
		}
		infile.close();		
}


 ostream &TextQuery:: query_and_print(const string &word,ostream &os)
{
	auto loc=_mapWord2Line.find(word);//返回指向word的set<int>的迭代器
	auto times=_mapWordFreq.find(word);
	if (loc==_mapWord2Line.end())
	{		
		os<<loc->first<<"出现了0次"<<endl;
	}else{
		os<<word<<"出现了"<<times->second<<"次"<<endl;
		for(auto num:loc->second)
			os<<"\t(第"<<num+1<<"行)"<<*(_vecLines.begin()+num)<<endl;
	}
	return os;
}

void TextQuery:: runQueries()
{
	while(true){
		cout<<"enter word to look for,or q to quit:";
		string s;
		if(!(cin>>s)||s=="q")break;//遇到文件尾，或者用户输入q则退出循环；
		query_and_print(s,cout);
	}

}
int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		printf("args error\n");
	}
	 string s1 = "hello";
    TextQuery tq;
	tq.readFile(argv[1]);
	tq.runQueries();
	return 0;
}
			
