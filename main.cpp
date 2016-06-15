#include "operation.h"
#include <cstdio>

void mainmenu(void);

int main(){
	Operation operation;
	int op;
	do{
		mainmenu();
		cout << "Please input your option[1-5]: ";
		cin >> op;
		cout << endl;
		int cmd;
		switch(op){
			case 1:
				cout << "---------------管理----------------" << endl;
				cout << "        1.查询学生信息" <<endl;
				cout << "        2.增加学生信息" <<endl;
				cout << "        3.修改学生信息" <<endl;
				cout << "        4.删除学生信息" <<endl;
				cout << "        5.返回上一级" <<endl;
				cout << "-----------------------------------" << endl;
				cout << "Please input your option[1-5]: ";
				cin >> cmd;
				switch(cmd){
					case 1:{
                        string sno;
                        cout << "请输入待查询学生的学号： ";
                        cin >> sno;
                        operation.Search_stu(sno);
						break;
					}
					case 2:
					    operation.add();
						break;
					case 3:
					    operation.update();
						break;
					case 4:
					    operation.del();
						break;
                    case 5:
                        break;
					default:
					    cout << "doesn't have the choice, please choose again!" << endl;
						break;
				}
				cout << "Press any key to continue...";
				getchar();getchar();
				break;
			case 2:
				cout << "--------------------查询---------------------" << endl;
				cout << "    1. 按学号查询学生成绩和学分信息" <<endl;
				cout << "    2. 按课程查询某门课程的所有学生成绩" <<endl;
				cout << "    3. 返回上一级" <<endl;
				cout << "---------------------------------------------" << endl;
				cout << "Please input your option[1-3]: ";
				cin >> cmd;

				if(cmd == 1){
					string sno;
					cout << "请输入学号： ";
					cin >> sno;
					operation.Search_sno(sno);
				}
				else if(cmd == 2){
                    string cno;
					cout << "请输入课程号： ";
					cin >> cno;
					operation.Search_cno(cno);
				}
				else if(cmd == 3){}
				else{
                    cout << "doesn't have the choice, please choose again!" << endl;
				}
				cout << "Press any key to continue...";
				getchar();getchar();
				break;
			case 3:
				cout << "--------------------统计---------------------" << endl;
				cout << "    1. 按课程统计不及格学生" <<endl;
				cout << "    2. 按课程将某门课的成绩排序" <<endl;
				cout << "    3. 按所有课程的总学分排序" <<endl;
				cout << "    4. 返回上一级" <<endl;
				cout << "---------------------------------------------" << endl;
				cout << "Please input your option[1-4]: ";
				cin >> cmd;
				if(cmd == 1)
					operation.Stat1();
				else if(cmd == 2)
					operation.Stat2();
				else if(cmd == 3)
                    operation.Stat3();
                else if(cmd == 4)
                    ;
                else
                    cout << "doesn't have the choice, please choose again!" << endl;
				cout << "Press any key to continue...";
				getchar();getchar();
				break;
            case 4:
                operation.save();
                op = 5;
                break;
            case 5:
                break;
			default:
			    cout << "doesn't have the choice, please choose again!" << endl;
				break;
		}
	}while(op != 5);
	cout << endl << "--------------------Welcome again!--------------------" << endl;
	return 0;
}

void mainmenu(void){
	cout << endl;
	cout << "***************主菜单**************" << endl;
	cout << "          1. 学生信息" <<endl;
	cout << "          2. 成绩查询" <<endl;
	cout << "          3. 成绩统计" <<endl;
	cout << "          4. 保存并退出"    <<endl;
	cout << "          5. 不保存退出"    <<endl;
	cout << "***************主菜单**************" << endl;
}
