#ifndef MANAGER_UI_HPP
#define MANAGER_UI_HPP

#include "FamilyTree.hpp"
#include <cstdio>
#include <iostream>
#include <string>
#include <memory>
#include <cstdlib>
#include <map>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::vector;

typedef FamilyTree::FamilyMember FamilyMember;

class ManagerUI {
  public:
    ManagerUI(FamilyTree *tree) : m_familytree_ptr(tree) {}
    
    void PrintUI() {
        cout << "--------------------------------------------------------------------------------" << endl
            << "1. 插入妻子" << endl
            << "2. 插入孩子" << endl
            << "3. 批量插入孩子(未实现)" << endl
            << "4. 更新成员信息" << endl
            << "5. 删除成员" << endl
            << "6. 查询" << endl
            << "7. 打印家谱" << endl
            << "8. 数据统计" << endl
            << "0. 离开" << endl
            << "--------------------------------------------------------------------------------" << endl;
    }

    void InputLoop() {
        int command = 0;
        while (!m_familytree_ptr->root) {
            insertAncestor();
        }
        PrintUI();
        while (cin >> command, !cin.eof() && command != 0) {
            if (!m_familytree_ptr->root) {
                cout << "族谱祖先消失，程序终止" << endl;
                return;
            }
            switch(command) {
                case 1:
                insertWife(); break;
                case 2:
                insertChild(); break;
                case 3:
                insertSeveralChildren(); break;
                case 4:
                updateMember(); break;
                case 5:
                deleteMember(); break;
                case 6:
                queryMember(); break;
                case 7:
                printTree(); break;
                case 8:
                statisticAnalyze(); break;
                default:
                cout << "没有这样的操作，请确认跟提示是否相符" << endl; break;
            }

            cout << "按下Enter继续" << endl;
            getchar();
            getchar();
            #if defined(__linux) || defined(__linux__)
            system("clear");
            #elif defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
            system("cls");
            #endif
            PrintUI();
        }
    }

    void insertAncestor() {
        cout << "@ 插入祖先" << endl
             << "输入格式为：" << endl
             << "[名字] [年龄] [是否已故](0/1)" << endl;
        string t_name;
        int t_age = 0;
        int t_int_is_dead = 0;
        cin >> t_name >> t_age >> t_int_is_dead;
        m_familytree_ptr->insertWife(new FamilyMember(t_name, FamilyTree::Sex::boy, t_age, t_int_is_dead ? true:false) , nullptr);
    }

    void insertWife() {
        cout << "@ 插入妻子" << endl
             << "输入格式为：" << endl
             << "[名字] [年龄] [是否离婚](0/1) [是否已故](0/1)" << endl;
        string t_name;
        int t_age = 0;
        int t_int_is_divorced, t_int_is_dead = 0;
        cin >> t_name >> t_age >> t_int_is_divorced >> t_int_is_dead;
        auto newWife = new FamilyMember(t_name, FamilyTree::Sex::girl, t_age, t_int_is_dead ? true:false, t_int_is_divorced ? true:false);
        cout << "[丈夫姓名]" << endl;
        cin >> t_name;
        auto query_res = m_familytree_ptr->queryMember([&](const FamilyMember *person) -> bool {
            return person->name == t_name;
        });
        if (query_res.size() == 0) {
            cout << "丈夫查询失败" << endl;
            return;
        }
        FamilyMember *husband = nullptr;
        if (query_res.size() > 1)
            husband = handleMultiQueryResult(query_res);
        else
            husband = query_res[0];
        m_familytree_ptr->insertWife(newWife, husband);
    }

    void insertChild() {
        cout << "@ 插入孩子" << endl
             << "0: 女\t1: 男\t2: 不明" << endl
             << "输入格式为：" << endl
             << "[名字] [性别] [年龄] [是否已故](0/1)" << endl;
        string t_name;
        int t_age = 0, t_int_sex = 0;
        int t_int_is_dead = 0;
        cin >> t_name >> t_int_sex >> t_age >> t_int_is_dead;
        auto newChild = new FamilyMember(t_name, IntToSex[t_int_sex], t_age, t_int_is_dead ? true:false);
        cout << "[母亲姓名]" << endl;
        cin >> t_name;
        auto query_res = m_familytree_ptr->queryMember([&](const FamilyMember *person) -> bool {
            return person->name == t_name;
        });
        FamilyMember *mother = nullptr;
        if (query_res.size() == 0) {
            cout << "母亲查询失败" << endl;
            return;
        }
        if (query_res.size() > 1)
            mother = handleMultiQueryResult(query_res);
        else
            mother = query_res[0];
        m_familytree_ptr->insertChild(newChild, mother);
    }

    void insertSeveralChildren() {
        cout << "未实现功能" << endl;
    }

    void updateMember() {
        cout << "@ 更新成员信息" << endl
             << "输入要更新的成员姓名" << endl;
        string t_name;
        cin >> t_name;
        auto query_res = m_familytree_ptr->queryMember([&](const FamilyMember *person) -> bool {
            return person->name == t_name;
        });
        FamilyMember *member = nullptr;
        if (query_res.size() == 0) {
            cout << "成员查询失败" << endl;
            return;
        }
        if (query_res.size() > 1)
            member = handleMultiQueryResult(query_res);
        else
            member = query_res[0];
        cout << "当前成员信息:" << endl;
        printOneMember(member);
        cout << "输入更新后成员信息:" << endl;
        cout << "[姓名] [性别] [年龄] [已故](0/1) [离婚](女性)" << endl;
        int t_age = 0, t_int_sex = 0, t_int_dead = 0, t_int_divorced = 0;
        cin >> t_name >> t_int_sex >> t_age >> t_int_dead;
        if (member->sex == FamilyTree::Sex::girl) {
            cin >> t_int_divorced;
            member->divorced = t_int_divorced;
        } 
        member->name = t_name;
        member->sex = IntToSex[t_int_sex];
        member->age = t_age;
        member->dead = t_int_dead;
    }

    void deleteMember() {
        cout << "@ 删除成员信息" << endl
             << "输入要删除的成员姓名" << endl;
        string t_name;
        cin >> t_name;
        auto query_res = m_familytree_ptr->queryMember([&](const FamilyMember *person) -> bool {
            return person->name == t_name;
        });
        FamilyMember *member = nullptr;
        if (query_res.size() == 0) {
            cout << "成员查询失败" << endl;
            return;
        }
        if (query_res.size() > 1)
            member = handleMultiQueryResult(query_res);
        else
            member = query_res[0];
        cout << "当前成员信息:" << endl;
        printOneMember(member);
        m_familytree_ptr->deleteMember([&](const FamilyMember* person) {
            return member == person;
        });
        cout << "已删除" << endl;
    }

    void queryMember() {
        cout << "@ 查询" << endl
             << "输入查询条件" << endl
             << "条件: 0 姓名 1 性别 2 年龄 3 已故 4 离婚" << endl
             << "[条件] [值]" << endl;

        int condition = 0;
        cin >> condition;

        vector<FamilyMember*> query_res;
        string t_name;
        int t_int_sex = 0;
        int t_age = 0;
        int t_int_dead;
        int t_int_divorced;

        switch (condition) {
            case 0:
            cin >> t_name;
            query_res = m_familytree_ptr->queryMember([&](const FamilyMember* person) -> bool {
                return person->name == t_name;
            });
            break;

            case 1:
            cin >> t_int_sex;
            query_res = m_familytree_ptr->queryMember([&](const FamilyMember* person) -> bool {
                return person->sex == IntToSex[t_int_sex];
            });
            break;

            case 2:
            cin >> t_age;
            query_res = m_familytree_ptr->queryMember([&](const FamilyMember* person) -> bool {
                return person->age == t_age;
            });
            break;

            case 3:
            cin >> t_int_dead;
            query_res = m_familytree_ptr->queryMember([&](const FamilyMember* person) -> bool {
                return person->dead == t_int_dead ? true:false;
            });
            break;

            case 4:
            cin >> t_int_divorced;
            query_res = m_familytree_ptr->queryMember([&](const FamilyMember* person) -> bool {
                return person->divorced == t_int_divorced ? true:false;
            });
        }

        printMembers(query_res);
    }

    void printTree() {
        FamilyTree::PrintMembers(m_familytree_ptr->root);
    }

    void statisticAnalyze() {
        cout << "请输入统计的项目" << endl
             << "0. 总人数" << endl
             << "1. 平均死亡年龄" << endl
             << "2. 男女比例" << endl;
        int statisticType = 0;
        cin >> statisticType;
        vector<FamilyMember*> query_res;
        int tmp1 = 0, tmp2 = 0;
        switch(statisticType) {
            case 0:
            query_res = m_familytree_ptr->queryMember([&](const FamilyMember *person) -> bool {
                return true;
            });
            cout << "总人数: " << query_res.size() << endl;
            break;

            case 1:
            query_res = m_familytree_ptr->queryMember([&](const FamilyMember *person) -> bool {
                return person->dead;
            });
            tmp1 = 0;
            for (auto &i : query_res) {
                tmp1 += i->age;
            }
            if (query_res.size()) {
                cout << query_res.size() << "人已故，平均死亡年龄为" << double(tmp1) / query_res.size() << endl;
            } else {
                cout << "0人已故，平均死亡年龄无法计算" << endl;
            }
            break;

            case 2:
            query_res = m_familytree_ptr->queryMember([&](const FamilyMember *person) -> bool {
                return person->sex == FamilyTree::Sex::boy;
            });
            tmp1 = query_res.size();
            query_res = m_familytree_ptr->queryMember([&](const FamilyMember *person) -> bool {
                return person->sex == FamilyTree::Sex::girl;
            });
            tmp2 = query_res.size();
            cout << "共有" << tmp1 << "个男性，" << tmp2 << "个女性" << endl
                 << "男女比例为" << double(tmp1) / tmp2 << endl;
            break;

            default:
            cout << "没有这个选项，请重新确认选项" << endl;
            break;
        }
    }

    FamilyMember* handleMultiQueryResult(vector<FamilyMember*> &res) {
        cout << "有" << res.size() << "个查询结果" << endl;
        for (int i = 0; i < res.size(); ++i) {
            cout << "选择 " << i << endl;
            printOneMember(res[i]);
        }
        cout << "请选择一个成员" << endl;
        int select = 0;
        while (cin >> select, select < 0 || select >= res.size()) {
            cout << "请输入正确的序号" << endl;
        }
        return res[select];
    }

  private:
    std::shared_ptr<FamilyTree> m_familytree_ptr;
    std::map<FamilyTree::Sex, string> SexToString {
        {FamilyTree::Sex::boy, "Male"},
        {FamilyTree::Sex::girl, "Female"},
        {FamilyTree::Sex::unknown, "Unknown"}
    };
    std::map<int, FamilyTree::Sex> IntToSex {
        {0, FamilyTree::Sex::girl},
        {1, FamilyTree::Sex::boy},
        {2, FamilyTree::Sex::unknown}
    };
    void printOneMember(FamilyMember *member) {
        cout << "ID: " << member->id << endl
             << "姓名: " << member->name << endl
             << "性别: " << SexToString[member->sex] << endl
             << "年龄: " << member->age << endl
             << "已故: " << (member->dead ? "是" : "否") << endl;
        if (member->sex == FamilyTree::Sex::girl)
        cout << "离婚: " << (member->divorced ? "是" : "否") << endl;
    }
    
    void printMembers(const vector<FamilyMember*> vec) {
        for (int i = 0; i < vec.size(); ++i) {
            cout << "查询结果 " << i << ":" << endl;
            printOneMember(vec[i]);
        }
    }
};

#endif
