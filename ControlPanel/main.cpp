#include "ControlPanel.h"
#include <QtWidgets/QApplication>
#include <regex>
#include <string>
using namespace std;

int execmd(char* cmd, char* result) {
	char buffer[128];                         //���建����                        
	FILE* pipe = _popen(cmd, "r");            //�򿪹ܵ�����ִ������ 
	if (!pipe)
		return 0;                      //����0��ʾ����ʧ�� 

	while (!feof(pipe)) {
		if (fgets(buffer, 128, pipe)) {             //���ܵ������result�� 
			strcat(result, buffer);
		}
	}
	_pclose(pipe);                            //�رչܵ� 
	return 1;                                 //����1��ʾ���гɹ� 
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
		QMessageBox::critical(nullptr, "���ش���", "��֧�ֵ�ϵͳ�汾");
		return 0;
	}

    ControlPanel w;
    w.show();
    return a.exec();
}
