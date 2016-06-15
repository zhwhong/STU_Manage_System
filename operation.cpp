#include "operation.h"
#include <cstring>
#include <algorithm>

Operation::Operation(){
    /***课程列表初始化***/
    ifstream fin;
    fin.open("Course.txt", ios::in);
    string cno, cname;
    float ccredit;
    while(!fin.eof()){
        fin >> cno >> cname >> ccredit;
        Course course(cno, cname, ccredit);
        cvec.push_back(course);
    }
    fin.close();
    /*初始化学生信息和选课成绩信息*/
    fin.open("Student.txt", ios::in);
    while(!fin.eof()){
        string sno, sname;
        string sex;
        Gender ssex;
        int sage, n;
        fin >> sno >> sname >> sex >> sage >> n;
        ssex = (sex == "男") ? MALE : FEMALE;
        Student stu(sno, sname, ssex, sage);
        string cno;
        float cscore;
        for(int i = 0; i < n; i++){
            fin >> cno >> cscore;
            stu.score += cscore;
            vector<Course>::iterator it;
            for(it = cvec.begin(); it != cvec.end(); it++){
                if(it->cno == cno){
                    stu.credit += it->ccredit;
                    Score score(*it, stu, cscore);
                    scvec.push_back(score);
                    break;
                }
            }
        }
        if(sno.length() == 0 || sname.length() == 0) continue;
        svec.push_back(stu);
    }
    fin.close();
}

void Operation::Search_stu(string sno){
    int find = 0;
    vector<Student>::iterator it;
    for(it = svec.begin(); it != svec.end(); it++){
        if(it->sno == sno){
            find = 1;
            printf("\t┌────────────┐\n");
            printf("\t│         查询结果       │\n");
            printf("\t│………………………………│\n");
            printf("\t│学号:%15s\t  │\n",it->sno.c_str());
            printf("\t│姓名:%15s\t  │\n",it->sname.c_str());
            if(it->ssex == MALE)
                printf("\t│性别:%15s\t  │\n","男");
            else
                printf("\t│性别:%15s\t  │\n","女");
            printf("\t│年龄:%15d\t  │\n",it->sage);
            printf("\t│总学分:%13.1f\t  │\n",it->credit);
            printf("\t│总成绩:%13.2f\t  │\n",it->score);
            printf("\t└────────────┘\n");
        }
    }
    if(find == 0)
        printf("未搜索到相关学生信息！\n");
}

void Operation::add()
{
    string sno, sname, sex;
    Gender ssex;
    int sage;
    cout << "请输入学生相关信息:" << endl;
    cout << "学号:"; cin >> sno;
    vector<Student>::iterator it1;
    for(it1 = svec.begin(); it1 != svec.end(); it1++){
        if(it1->sno == sno){
            cout << "该学生信息已存在,请重试！" << endl;
            return ;
        }
    }
    cout << "姓名:"; cin >> sname;
    cout << "性别[男/女]:"; cin >> sex;
    if(sex == "男")
        ssex = MALE;
    else if(sex == "女")
        ssex = FEMALE;
    else{
        cout << "Input Error!!!" << endl;
        return ;
    }
    cout << "年龄:"; cin >> sage;
    Student stu(sno, sname, ssex, sage);
    char ch1;
    while(1){
        cout << "是否继续输入成绩[y/n]？";
        cin >> ch1;
        getchar();
        if(ch1 == 'Y' || ch1 == 'y'){
            char ch2;
            vector< pair<string,float> > sc;
            string cno;
            float score;
            while(1){
                cout << "请输入课程号: "; cin >> cno;
                cout << "请输入成绩: "; cin >> score;

                int flag = 0;
                vector<Course>::iterator it;
                for(it = cvec.begin(); it != cvec.end(); it++){
                    if(it->cno == cno){
                        flag = 1;
                        break;
                    }
                }
                if(flag != 1){
                    cout << "不存在这门课程，请重新输入！" << endl;
                    cout << "是否结束输入成绩[y/n]？";
                    cin >> ch2;
                    if(ch2 == 'Y' || ch2 == 'y')
                        break;
                    else
                       continue;
                }

                sc.push_back(pair<string, float> (cno,score));
                while(1){
                    cout << "是否继续输入成绩[y/n]？";
                    cin >> ch2; getchar();
                    if(ch2 == 'Y' || ch2 == 'y'){
                        break;
                    }
                    else if(ch2 == 'N' || ch2 == 'n'){
                        break;
                    }
                    else{
                        cout << "输入不正确，请重新选择！" << endl;
                    }
                }
                if(ch2 == 'N' || ch2 == 'n') break;
            }
            //保存信息,break
            for(unsigned i = 0; i < sc.size(); i++){
                //fin >> cno >> cscore;
                stu.score += sc[i].second;
                vector<Course>::iterator it;
                for(it = cvec.begin(); it != cvec.end(); it++){
                    if(it->cno == sc[i].first){
                        stu.credit += it->ccredit;
                        Score score(*it, stu, sc[i].second);
                        scvec.push_back(score);
                        break;
                    }
                }
            }
            svec.push_back(stu);
            break;
        }
        else if(ch1 == 'N' || ch1 == 'n'){
            svec.push_back(stu);
            break;
        }
        else{
            cout << "输入不正确，请重新选择！" << endl;
        }
    }
    printf("插入成功!\n");
}

void Operation::update()
{
    string sno;
    cout << "请输入待修改学生学号："; cin >> sno;
    //打印原始信息
    cout << endl << "该学生原始信息如下：" << endl;
    vector<Student>::iterator it1;
    for(it1 = svec.begin(); it1 != svec.end(); it1++){
        if(it1->sno == sno){
            printf("学号：%s  姓名：%s  ", it1->sno.c_str(), it1->sname.c_str());
            if(it1->ssex == MALE)
                printf("性别：男  年龄：%d\n", it1->sage);
            else
                printf("性别：女  年龄：%d\n", it1->sage);
            break;
        }
    }
    if(it1 == svec.end()){
        cout << "该学生不存在，请重试！" << endl;
        return ;
    }
    vector<Score>::iterator it2;
    for(it2 = scvec.begin(); it2 != scvec.end(); it2++){
        if(it2->student.sno == sno){
            cout << it2->course.cno << " " << it2->course.cname << " " << it2->score << endl;
        }
    }
    //重新录入新信息
    int cmd;
    cout << "---------------修改选项------------" << endl;
    cout << "        1.修改学生基本信息" <<endl;
    cout << "        2.修改学生成绩信息" <<endl;
    cout << "        3.返回" <<endl;
    cout << "-----------------------------------" << endl;
    cout << "Please input your option[1-3]: ";
    cin >> cmd;
    if(cmd == 1){
        cout << "请重新输入该学生基本信息:" << endl;
        string sname, sex;
        Gender ssex;
        int sage;
        cout << "姓名:"; cin >> sname;
        cout << "性别[男/女]:"; cin >> sex;
        if(sex == "男")
            ssex = MALE;
        else if(sex == "女")
            ssex = FEMALE;
        else{
            cout << "Input Error!!!" << endl;
            return ;
        }
        cout << "年龄:"; cin >> sage;
        //Student stu(sno, sname, ssex, sage);
        vector<Student>::iterator it3;
        for(it3 = svec.begin(); it3 != svec.end(); it3++){
            if(it3->sno == sno){
                it3->sname = sname;
                it3->ssex = ssex;
                it3->sage = sage;
                break;
            }
        }
        vector<Score>::iterator it4;
        for(it4 = scvec.begin(); it4 != scvec.end(); it4++){
            if(it4->student.sno == sno){
                it4->student.sname = sname;
                it4->student.ssex = ssex;
                it4->student.sage = sage;
            }
        }
        cout << "修改成功!" << endl;
    }
    else if(cmd == 2){
        cout << "请重新输入该学生成绩信息[如有变动]:" << endl;
        string cno;
        float score;
        vector< pair<string,float> > sc;
        while(1){
            cout << "请输入课程号: "; cin >> cno;
            cout << "请输入成绩: "; cin >> score;

            int flag = 0;
            char ch2;
            vector<Course>::iterator it;
            for(it = cvec.begin(); it != cvec.end(); it++){
                if(it->cno == cno){
                    flag = 1;
                    break;
                }
            }
            if(flag != 1){
                cout << "不存在这门课程，请重新输入！" << endl;
                cout << "是否结束输入成绩[y/n]？";
                cin >> ch2;
                if(ch2 == 'Y' || ch2 == 'y')
                    break;
                else
                   continue;
            }

            sc.push_back(pair<string, float> (cno,score));
            while(1){
                cout << "是否继续输入成绩[y/n]？";
                cin >> ch2; getchar();
                if(ch2 == 'Y' || ch2 == 'y'){
                    break;
                }
                else if(ch2 == 'N' || ch2 == 'n'){
                    break;
                }
                else{
                    cout << "输入不正确，请重新选择！" << endl;
                }
            }
            if(ch2 == 'N' || ch2 == 'n') break;
        }

        for(unsigned i = 0; i < sc.size(); i++){
            int find = 0;
            vector<Score>::iterator it;
            for(it = scvec.begin(); it != scvec.end(); it++){
                if(it->student.sno == sno && it->course.cno == sc[i].first){
                    find = 1;
                    float lep = sc[i].second - it->score;
                    it->score = sc[i].second;
                    //修改总成绩
                    vector<Student>::iterator it2;
                    for(it2 = svec.begin(); it2 != svec.end(); it2++){
                        if(it2->sno == sno){
                            it2->score += lep;
                        }
                    }
                    break;
                }
            }
            if(find != 1){
                vector<Student>::iterator it1;
                for(it1 = svec.begin(); it1 != svec.end(); it1++){
                    if(it1->sno == sno){
                        vector<Course>::iterator it2;
                        for(it2 = cvec.begin(); it2 != cvec.end(); it2++){
                            if(it2->cno == sc[i].first){
                                it1->credit += it2->ccredit;
                                it1->score += sc[i].second;
                                Score score(*it2, *it1, sc[i].second);
                                scvec.push_back(score);
                                break;
                            }
                        }
                    }
                }
            }
        }
        cout << "修改成功!" << endl;
    }
    else if(cmd == 3){}
    else{
        cout << "doesn't have the choice!!!" << endl;
    }
}

void Operation::del()
{
    string sno;
    cout << "请输入待删除学生学号："; cin >> sno;
    //打印原始信息
    cout << endl << "该学生原始信息如下：" << endl;
    vector<Student>::iterator it1;
    for(it1 = svec.begin(); it1 != svec.end(); it1++){
        if(it1->sno == sno){
            printf("学号：%s  姓名：%s  ", it1->sno.c_str(), it1->sname.c_str());
            if(it1->ssex == MALE)
                printf("性别：男  年龄：%d\n", it1->sage);
            else
                printf("性别：女  年龄：%d\n", it1->sage);
            break;
        }
    }
    if(it1 == svec.end()){
        cout << "该学生不存在，请重试！" << endl;
        return ;
    }
    vector<Score>::iterator it2;
    for(it2 = scvec.begin(); it2 != scvec.end(); it2++){
        if(it2->student.sno == sno){
            cout << it2->course.cno << " " << it2->course.cname << " " << it2->score << endl;
        }
    }

    int cmd;
    cout << "---------------删除选项------------" << endl;
    cout << "        1. 删除学生所有信息" <<endl;
    cout << "        2. 删除学生成绩信息" <<endl;
    cout << "        3. 返回" <<endl;
    cout << "-----------------------------------" << endl;
    cout << "Please input your option[1-3]: ";
    cin >> cmd;
    switch(cmd){
        case 1:{
            char ch;
            while(1){
                cout << "确认删除该生所有信息[y/n]？："; cin >> ch; getchar();
                if(ch == 'Y' || ch == 'y'){
                    vector<Student>::iterator it1;
                    for(it1 = svec.begin(); it1 != svec.end(); ){
                        if(it1->sno == sno){
                            it1 = svec.erase(it1);
                        }
                        else
                            ++it1;
                    }
                    vector<Score>::iterator it2;
                    for(it2 = scvec.begin(); it2 != scvec.end(); ){
                        if(it2->student.sno == sno){
                            it2 = scvec.erase(it2);
                        }
                        else
                            ++it2;
                    }
                    cout << "删除成功！" << endl;
                    break;
                }
                else if(ch == 'N' || ch == 'n'){
                    cout << "成功放弃删除！" << endl;
                    break;
                }
                else{
                    cout << "输入有误，请重新选择！" << endl;
                }
            }
            break;}
        case 2:{
            string cno;
            while(1){
                cout << "请输入要删除的课程号：" ; cin >> cno;
                vector<Score>::iterator it1;
                int find = 0;
                for(it1 = scvec.begin(); it1 != scvec.end(); ){
                    if(it1->student.sno == sno && it1->course.cno == cno){
                        find = 1;
                        vector<Student>::iterator it2;
                        for(it2 = svec.begin(); it2 != svec.end(); it2++){
                            if(it2->sno == sno){
                                //找到减少的学分
                                float credit;
                                vector<Course>::iterator it3;
                                for(it3 = cvec.begin(); it3 != cvec.end(); it3++){
                                    if(it3->cno == cno){
                                        credit = it3->ccredit;
                                        break;
                                    }
                                }
                                it2->score -= it1->score; //减少的分数
                                it2->credit -= credit;    //减少的学分
                                break;
                            }
                        }
                        it1 = scvec.erase(it1);
                        break;
                    }
                    else
                        ++it1;
                }
                char ch;
                if(find != 1){
                    cout << "该生没有选修过这门课，删除失败！" << endl;
                    while(1){
                        cout << "是否继续删除工作[y/n]？："; cin >> ch;
                        if(ch == 'Y' || ch == 'y')
                            break;
                        else if(ch == 'N' || ch == 'n')
                            break;
                        else
                            cout << "输入有误，请重新输入'y'或'n'！" << endl;
                    }
                    if(ch == 'N' || ch == 'n') break;
                    if(ch == 'Y' || ch == 'y') continue;
                }
                cout << "删除成功！" << endl;
                while(1){
                    cout << "是否继续删除其他课程成绩[y/n]？："; cin >> ch;
                    if(ch == 'Y' || ch == 'y'){
                        break;
                    }
                    else if(ch == 'N' || ch == 'n'){
                        break;
                    }
                    else{
                        cout << "输入有误，请重新输入'y'或'n'！" << endl;
                    }
                }
                if(ch == 'N' || ch == 'n') break;
            }
            //cout << "删除成功！" << endl;
            break;}
        case 3:
            break;
        default:
            cout << "doesn't have the choice!!!" << endl;
    }
}

void Operation::Search_sno(string sno){
    int find = 0;
    printf("\n%22s【查询结果】\n"," ");
    vector<Student>::iterator it1;
    for(it1 = svec.begin(); it1 != svec.end(); it1++){
        if(it1->sno == sno){
            printf("  学号：%s\t姓名：%s\t总学分：%.1f\n", it1->sno.c_str(), it1->sname.c_str(), it1->credit);
            break;
        }
    }
    printf("┌───────────────────────────┐\n");
    printf("│  课程号  │         课程名         │  成绩  │ 学分 │\n");
    printf("│───────────────────────────│\n");
    vector<Score>::iterator it2;
    for(it2 = scvec.begin(); it2 != scvec.end(); it2++){
        if(it2->student.sno == sno){
            find = 1;
            printf("│  %-8s│ %-22s │ %-7.2f│ %-5.1f│\n",it2->course.cno.c_str(),it2->course.cname.c_str(),it2->score,it2->course.ccredit);
        }
    }
    if(find==0)
        printf("│%18s未搜索到相关信息！%18s│\n"," "," ");
    printf("└───────────────────────────┘\n");
}

void Operation::Search_cno(string cno){
    int find = 0;
    printf("\n%24s【查询结果】\n"," ");
    vector<Course>::iterator it1;
    for(it1 = cvec.begin(); it1 != cvec.end(); it1++){
        if(it1->cno == cno){
            printf("  课程号：%s  课程名：%s  学分：%.1f\n", it1->cno.c_str(), it1->cname.c_str(), it1->ccredit);
            break;
        }
    }
    printf("┌───────────────────────────┐\n");
    printf("│       学号       │       姓名       │     成绩     │\n");
    printf("│───────────────────────────│\n");
    vector<Score>::iterator it2;
    for(it2 = scvec.begin(); it2 != scvec.end(); it2++){
        if(it2->course.cno == cno){
            find = 1;
            printf("│    %-14s│      %-11s │    %-10.2f│\n",it2->student.sno.c_str(),it2->student.sname.c_str(),it2->score);
        }
    }
    if(find==0)
        printf("│%18s未搜索到相关信息！%18s│\n"," "," ");
    printf("└───────────────────────────┘\n");
}

void Operation::Stat1(){
    int find = 0;
    printf("\n%24s【统计结果】\n"," ");
    printf("┌───────────────────────────┐\n");
    printf("│           课程           │     学生     │   成绩   │\n");
    printf("│───────────────────────────│\n");
    vector<Score>::iterator it2;
    for(it2 = scvec.begin(); it2 != scvec.end(); it2++){
        if(it2->score < 60){
            find = 1;
            printf("│  %-24s│    %-9s │  %-8.2f│\n",it2->course.cname.c_str(),it2->student.sname.c_str(),it2->score);
        }
    }
    if(find==0)
        printf("│%18s未搜索到相关信息！%18s│\n"," "," ");
    printf("└───────────────────────────┘\n");
}

bool compare2(Score i,Score j)
{
    if(!(i.course.cno == j.course.cno))
        return (i.course.cno < j.course.cno);
    return (i.score < j.score);
}

void Operation::Stat2(){
    int find = 0;
    printf("\n%24s【统计结果】\n"," ");
    printf("┌───────────────────────────┐\n");
    printf("│           课程           │     学生     │   成绩   │\n");
    printf("│───────────────────────────│\n");
    stable_sort(scvec.begin(), scvec.end(), compare2);

    vector<Score>::iterator it2;
    for(it2 = scvec.begin(); it2 != scvec.end(); it2++){
        find = 1;
        printf("│  %-24s│    %-9s │  %-8.2f│\n",it2->course.cname.c_str(),it2->student.sname.c_str(),it2->score);
    }
    if(find==0)
        printf("│%18s未搜索到相关信息！%18s│\n"," "," ");
    printf("└───────────────────────────┘\n");
}

bool compare3(Student i,Student j)
{
    return (i.credit < j.credit);
}

void Operation::Stat3(){
    int find = 0;
    printf("\n%24s【统计结果】\n"," ");
    printf("┌───────────────────────────┐\n");
    printf("│     学号     │    姓名   │   总学分   │  总成绩   │\n");
    printf("│───────────────────────────│\n");

    stable_sort(svec.begin(), svec.end(), compare3);
    vector<Student>::iterator it2;
    for(it2 = svec.begin(); it2 != svec.end(); it2++){
        find = 1;
        printf("│  %-12s│  %-8s │    %-8.1f│  %-9.2f│\n",it2->sno.c_str(),it2->sname.c_str(),it2->credit,it2->score);
    }
    if(find==0)
        printf("│%18s未搜索到相关信息！%18s│\n"," "," ");
    printf("└───────────────────────────┘\n");
}

void Operation::save()
{
    ofstream fout;
    fout.open("Student.txt", ios::out);
    if(!fout){
        cout << "保存文件失败" << endl;
        return ;
    }
    //fout << "hhh" << endl;

    vector<Student>::iterator it1;
    for(it1 = svec.begin(); it1 != svec.end(); it1++){
            //cout << "1111" << endl;
            fout << it1->sno << " " << it1->sname << " ";
            //cout << it1->sno << " " << it1->sname << " ";
            if(it1->ssex == MALE){
                fout << "男 " << it1->sage << " ";
                //cout << "男 " << it1->sage << " ";
            }
            else{
                fout << "女 " << it1->sage << " ";
                //cout << "女 " << it1->sage << " ";
            }
            vector<Score>::iterator it2;
            int n = 0;
            for(it2 = scvec.begin(); it2 != scvec.end(); it2++){
                if(it2->student.sno == it1->sno) ++n;
            }
            fout << n << endl;
            //cout << n << endl;
            vector<Score>::iterator it3;
            for(it3 = scvec.begin(); it3 != scvec.end(); it3++){
                if(it3->student.sno == it1->sno){
                    fout << it3->course.cno << " " << it3->score << endl;
                    //cout << it3->course.cno << " " << it3->score << endl;
                }
            }
    }
}


