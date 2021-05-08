#include "ControlPanel.h"
#include <QtWidgets/QApplication>
#include <regex>
#include <string>
using namespace std;

int execmd(char* cmd, char* result) {
	char buffer[128];                         //定义缓冲区                        
	FILE* pipe = _popen(cmd, "r");            //打开管道，并执行命令 
	if (!pipe)
		return 0;                      //返回0表示运行失败 

	while (!feof(pipe)) {
		if (fgets(buffer, 128, pipe)) {             //将管道输出到result中 
			strcat(result, buffer);
		}
	}
	_pclose(pipe);                            //关闭管道 
	return 1;                                 //返回1表示运行成功 
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	char buffer[128];
	execmd("VER", buffer);
	string tempStr = string(buffer);
	smatch subFormulaMatch;
	regex pattern(R"(\d+\.\d+\.(\d+))");
	regex_search(tempStr, subFormulaMatch, pattern);
	if (subFormulaMatch.size()==2&&stoi(subFormulaMatch[1].str()) > 7601)
	{
		QMessageBox::critical(nullptr, "严重错误", "不支持的系统版本");
		return 0;
	}

    ControlPanel w;
    w.show();
    return a.exec();
}
