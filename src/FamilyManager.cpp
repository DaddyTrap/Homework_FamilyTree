#include "FamilyTree.hpp"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

void printInputHint() {
    cout << "Insert person" << endl <<
            "type: insert a child or a wife. 0 for child, 1 for wife" << endl <<
            "sex: 0 for girl, 1 for boy, other for unknown" << endl <<
            "hus_mot_name: the name of the husband or mother" << endl <<
            "[type] [name] [sex] [age] [hus_mot_name]" << endl;
}

int main() {
    FamilyTree familytree;
    typedef FamilyTree::FamilyMember FamilyMember;
    int t_insert = 0;   // 0 for insert Child, 1 for insert Wife
    string t_name, t_hus_mot_name;
    int t_int_sex = 0, t_age = 0;
    FamilyTree::Sex t_sex = FamilyTree::Sex::unknown;

    cout << "Insert ancestor first." << endl <<
            "sex: 0 for girl, 1 for boy, other for unknown" << endl <<
            "[name] [sex] [age]" << endl;

    cin >> t_name >> t_int_sex >> t_age;
    if (t_int_sex == 0) t_sex = FamilyTree::Sex::girl;
    else if (t_int_sex == 1) t_sex = FamilyTree::Sex::boy;
    else t_sex = FamilyTree::Sex::unknown;
    familytree.insertWife(new FamilyMember(t_name, t_sex, t_age), nullptr);

    printInputHint();
    while (cin >> t_insert >> t_name >> t_int_sex >> t_age >> t_hus_mot_name) {
        if (t_int_sex == 0) t_sex = FamilyTree::Sex::girl;
        else if (t_int_sex == 1) t_sex = FamilyTree::Sex::boy;
        else t_sex = FamilyTree::Sex::unknown;

        auto hus_mot = familytree.queryMember([&](const FamilyMember *person) -> bool {
            return t_hus_mot_name == person->name;
        })[0];
        if (t_insert == 1) {
            familytree.insertWife(new FamilyMember(t_name, t_sex, t_age), hus_mot);
        } else {
            familytree.insertChild(new FamilyMember(t_name, t_sex, t_age), hus_mot);
        }

        printInputHint();
    }
    cout << familytree.countMembers([](const FamilyMember *person) -> bool {
        return true;
    }) << endl;
    FamilyTree::PrintMembers(familytree.root);
    return 0;
}
