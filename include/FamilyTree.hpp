#include <string>
#include <functional>
#include <vector>

using std::string;
using std::function;
using std::vector;

class FamilyTree {
 public:
  enum Sex {
    boy,
    girl,
    unknown
  };

  struct FamilyMember {
    int id;
    string name;
    Sex sex;
    int age;
    bool dead;
    bool divorced;
    FamilyMember *left;
    FamilyMember *right;
    FamilyMember(int t_id, string t_name, Sex t_sex, int t_age, bool t_die, FamilyMember *t_left, FamilyMember *t_right);
  };

  FamilyTree();

  ~FamilyTree();

  void insertChild(FamilyMember *person, FamilyMember *mother);

  void insertWife(FamilyMember *person, FamilyMember *husband);

  bool deleteMember(function<bool(const FamilyMember *person)> filter);

  vector<FamilyMember*> queryMember(function<bool(const FamilyMember *person)> filter);

  bool updateMember(function<bool(const FamilyMember *person)> filter, function<void(FamilyMember *person)> switcher);

  size_t countMembers(function<bool(const FamilyMember *person)> filter);

  static void PrintMembers(const FamilyMember* root, int printLevelzz, bool isLeft = false, int blankIndex = 0);

};
