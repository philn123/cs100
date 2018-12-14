#include "../header/And_Connector.h"
#include "../header/base.h"
#include "../header/Connector.h"
#include "../header/Or_Connector.h"
#include "../header/Semi_Connector.h"
#include "gtest/gtest.h"
#include "../header/command.h"
#include "../header/user.h"
#include "../header/Input_Redirect.h"
#include <iostream>
#include <string>
#include <list>
#include <vector>
using namespace std;

TEST(Cmd_Test, SingleCommand) {

    std::string s = "ls";
    std::string a = "-a"; //ls still works with different commands like -b
    char *c = (char*)s.c_str();
    char *d = (char*)a.c_str();
    std::vector<char*>v;
    v.push_back(c);
    v.push_back(d);
    Command *cmd = new Command(v);
    EXPECT_TRUE(cmd->execute()); 

    //single command with only 1 index in vector
    vector<char*> v1;
    v1.push_back(c);
    Command *cmd1 = new Command(v1);
    EXPECT_TRUE(cmd1-> execute());

    //expect false case
    vector<char*> v2;
    v2.push_back(d);
    Command *cmd2 = new Command(v2);
    EXPECT_FALSE(cmd2-> execute());

}
TEST(Connector_Test, AndConnector){
    std::string s = "ls";
    char *c = (char*)s.c_str();
    std::vector<char*>v;
    v.push_back(c);
    Command *x = new Command(v);

    std::vector<char*>v2;
    std::string ech = "echo";
    std::string hello = "hello world this is an rshell program1";
    char *e = (char*)ech.c_str();
    char *h = (char*)hello.c_str();
    v2.push_back(e);
    v2.push_back(h);
    Command *y = new Command(v2);
    


    And_Connector *tree = new And_Connector(x, y);
    EXPECT_TRUE(tree->execute());
    //false case with left failing
    vector<char*> v3;
    v3.push_back(h);
    Command *z = new Command(v3);
    And_Connector *false1 = new And_Connector(z, x);
    EXPECT_FALSE(false1-> execute());

    //false case with right failing
    And_Connector *false2 = new And_Connector(x, z);
    EXPECT_FALSE(false2-> execute());
}
TEST(Connector_Test, OrConnector){
    std::string s = "echo";
    std::string a = "testing the or connector";
    char *c = (char*)s.c_str();
    char *d = (char*)a.c_str();
    std::vector<char*>v;
    v.push_back(c);
    v.push_back(d);
    Command *x = new Command(v);

    std::vector<char*>v2;
    std::string ech = "echo";
    std::string hello = "hello world this is an rshell program2";
    char *e = (char*)ech.c_str();
    char *h = (char*)hello.c_str();
    v2.push_back(e);
    v2.push_back(h);
    Command *y = new Command(v2);
     


    Or_Connector *tree = new Or_Connector(x, y);
    EXPECT_TRUE(tree->execute());

    //false case where both fail
    string nonsense = "abcde";
    char *i = (char*)nonsense.c_str();
    vector<char*> v3;
    v3.push_back(i);
    Command *z = new Command(v3);
    Or_Connector *only_failcase = new Or_Connector(z,z);
    EXPECT_FALSE(only_failcase -> execute());

    //case where first fail but second pass
    Or_Connector *passcase = new Or_Connector(z, x);
    EXPECT_TRUE(passcase -> execute());
}
TEST(Connector_Test, SemiConnector){
    
    std::string s = "echo";
    std::string a = "testing the semi colon connector";
    char *c = (char*)s.c_str();
    char *d = (char*)a.c_str();
    std::vector<char*>v;
    v.push_back(c);
    v.push_back(d);
    Command *x = new Command(v);

    std::vector<char*>v2;
    std::string ech = "echo";
    std::string hello = "hello world this is an rshell program3";
    char *e = (char*)ech.c_str();
    char *h = (char*)hello.c_str();
    v2.push_back(e);
    v2.push_back(h);
    Command *y = new Command(v2);
  
    //false case where both fail
    Semi_Connector *tree = new Semi_Connector(x, y);
    EXPECT_TRUE(tree->execute());
    string random = "lsas";
    string random1 = "more failed code";
    char *i = (char*)random.c_str();
    char *j = (char*)random1.c_str();
    vector<char*> v3;
    v3.push_back(i);
    v3.push_back(j);
    Command *z = new Command(v3);
    Command *z1 = new Command(v3);
    Semi_Connector *expect_fail = new Semi_Connector(z,z1);
    EXPECT_FALSE(expect_fail->execute());

    //false case where first pass but second fail
    Semi_Connector *expect_fail2 = new Semi_Connector(x, z);
    EXPECT_FALSE(expect_fail2->execute());

    //true case where first fail but second pass
    Semi_Connector *expect_pass = new Semi_Connector(z, x);
    EXPECT_TRUE(expect_pass -> execute());
}

TEST(Connector_Test, Combine_Test){
    string valid = "ls";
    char *a = (char*)valid.c_str();
    vector<char*> v_valid;
    v_valid.push_back(a);
    string invalid = "abc";
    char *b = (char*)invalid.c_str();
    vector<char*> v_invalid;
    v_invalid.push_back(b);

    Command *passing = new Command(v_valid);
    Command *failing = new Command(v_invalid);

    Or_Connector *expect_pass = new Or_Connector(failing, passing);
    And_Connector *expect_fail = new And_Connector(expect_pass, failing);

    EXPECT_FALSE(expect_fail-> execute());
}

TEST(UserTest, CreateCommand) {
    vector<string> v;
    User *u = new User();
    string echo = "echo";
    string please = "please";
    v.push_back(echo);
    v.push_back(please);
    Base *cmd = u->createCommand(v);
    EXPECT_TRUE(cmd->execute());
    
    v.clear();

    string fail = "ls-a";
    v.push_back(fail);
    cmd = u->createCommand(v);
    EXPECT_FALSE(cmd->execute());

}
TEST(UserTest, ParseCommand) {
    vector<string> v;
    v.push_back("(");
    v.push_back("echo");
    v.push_back("a");
    v.push_back("&&");
    v.push_back("echo");
    v.push_back("b");
    v.push_back(")");
    
    string cmd = "(echo a && echo b)";
    User *u = new User();
    list<string> l = u->parse(cmd);
    for(auto it : v) {
        EXPECT_EQ(it, l.front());
        l.pop_front();
    }

}
TEST(UserTest, Parentheses){
   //usual parentheses test, adds spaces before and after parathesis to make them separate object for parser. Doesn't check for even
    User *test = new User();
    string usercommand = "((ls-a; echo hello)";
    list<string> result = test->parse(usercommand);
    EXPECT_EQ(7, result.size());
    //uneven paratheses test2, using CreateTree to see how it handles such cases
    testing::internal::CaptureStdout();
    bool flag = true;
    if(test-> createTree(result)== NULL){
	flag = false;
    }

    EXPECT_FALSE(flag);
    string str = testing::internal::GetCapturedStdout();
    EXPECT_EQ(str, "Error: Uneven Parentheses\n");

    //where parenthesis changes order, head would be & if no parenthesis, but is || instead
    usercommand = "(echo hello; ls) || (ls-a && ls-a)";
    result = test-> parse(usercommand);
    Base* example = test->createTree(result);
    EXPECT_TRUE(example-> execute());

    //parenthesis with just connector
    usercommand = "(&&)";
    result = test->parse(usercommand);
    testing::internal::CaptureStdout();
    example = test-> createTree(result);
    string str2 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(str2, "Error: Not enough arguments for connector\n");

    //empty parenthesis
    usercommand = "()";
    result = test-> parse(usercommand);
    testing::internal::CaptureStdout();
    example = test-> createTree(result);
    string str3 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(str3, "Error: No valid commands inside parentheses\n"); 
}

TEST(UserTest, TestCommand) {
    string test1 = "test";
    User *u = new User();
    list<string> l = u->parse(test1);
    Base *one = u->createTree(l);
    EXPECT_FALSE(one->execute());

    test1 = "test -e bin";
    l = u->parse(test1);
    one = u->createTree(l);
    EXPECT_TRUE(one->execute());

    test1 = "test -f Makefile";
    l = u->parse(test1);
    one = u->createTree(l);
    EXPECT_TRUE(one->execute());
    
    test1 = "test -d bin";    
    l = u->parse(test1);
    one = u->createTree(l);
    EXPECT_TRUE(one->execute());

    test1 = "test -d bin && ls-a";
    l = u->parse(test1);
    one = u->createTree(l);
    EXPECT_FALSE(one->execute());


}

TEST(UserTest, TestWithParentheses) {
    string test1;
    list<string> l;
    Base *one;
    User *u = new User();

    test1 = "test -d bin && ls-a";
    l = u->parse(test1);
    one = u->createTree(l);
    EXPECT_FALSE(one->execute());

    
    test1 = "test-d bin && ls-a";
    l = u->parse(test1);
    one = u->createTree(l);
    EXPECT_FALSE(one->execute());

    test1 = "test -d bin && echo a";
    l = u->parse(test1);
    one = u->createTree(l);
    EXPECT_TRUE(one->execute());


    test1 = "(test -e bin && echo a) && ls-a";
    l = u->parse(test1);
    one = u->createTree(l);
    EXPECT_FALSE(one->execute());

    test1 = "test -f bin && ls ";
    l = u->parse(test1);
    one = u->createTree(l);
    EXPECT_FALSE(one->execute());

    test1 = "test -d Makefile && ((echo a && echo b) && ls-a) ";
    l = u->parse(test1);
    one = u->createTree(l);
    EXPECT_FALSE(one->execute());

}

TEST(Test, TestBrackets) {
    
    string test1;
    list<string> l;
    Base *one;
    User *u = new User();

    test1 = "[-e bin ]";
    l= u->parse(test1);
    one = u->createTree(l);
    EXPECT_FALSE(one->execute());

    test1 = "[ -e bin ]";
    l= u->parse(test1);
    one = u->createTree(l);
    EXPECT_TRUE(one->execute());

    test1 = "[-e bin]";
    l= u->parse(test1);
    one = u->createTree(l);
    EXPECT_FALSE(one->execute());

    test1 = "[ -f bin ]";
    l= u->parse(test1);
    one = u->createTree(l);
    EXPECT_FALSE(one->execute());

    test1 = "[ -d bin ]";
    l= u->parse(test1);
    one = u->createTree(l);
    EXPECT_TRUE(one->execute());

    test1 = "[ test bin ]";
    l= u->parse(test1);
    one = u->createTree(l);
    EXPECT_FALSE(one->execute());
    
    test1 = "[ -e bin ] && echo path";
    l= u->parse(test1);
    one = u->createTree(l);
    EXPECT_TRUE(one->execute());

    test1 = "[ Makefile ] && ls-a";
    l= u->parse(test1);
    one = u->createTree(l);
    EXPECT_FALSE(one->execute());

    test1 = "echo testing && [ -e bin ] ";
    l = u->parse(test1);
    one = u->createTree(l);
    EXPECT_TRUE(one->execute());
    
    test1 = "[ -e bin; hello ] ";
    l = u->parse(test1);
    one = u->createTree(l);
    EXPECT_FALSE(one->execute());
    delete u;
    delete one;
}
TEST(Redirection, InputRedirection) {
    User *u = new User();
    string command = "cat < bin";
    list<string> l = u->parse(command);
    Base *b = u->createTree(l);
    EXPECT_FALSE(b->execute());
    
    command = "cat < CMakeLists.txt";
    l = u->parse(command);
    b = u->createTree(l);
    EXPECT_TRUE(b->execute());

    delete u;
    delete b;
}
TEST(Redirection, SingleOutputRedirection) {
    User *u = new User();
    string command = "ls > newfile";
    list<string> l = u->parse(command);
    Base *b = u->createTree(l);
    EXPECT_TRUE(b->execute());
    
    command = "cat < CMakeLists.txt > newfile";
    l = u->parse(command);
    b = u->createTree(l);
    EXPECT_TRUE(b->execute());
    
    command = "rm -r newfile";
    l = u->parse(command);
    b = u->createTree(l);
    EXPECT_TRUE(b->execute());
    delete u;
}

TEST(Redirection, DoubleOutputRedirection) {
    User *u = new User();
    string command = "cat < CMakeLists.txt > newfile && ls >> newfile";
    list<string> l = u->parse(command);
    Base *b = u->createTree(l);
    EXPECT_TRUE(b->execute());
    
    command = "(cat < Makefile >> newfile) && (cat < bin && echo yeet)";
    l = u->parse(command);
    b = u->createTree(l);
    EXPECT_FALSE(b->execute());

    command = "rm -r newfile";
    l = u->parse(command);
    b = u->createTree(l);
    EXPECT_TRUE(b->execute());
    delete u;
    delete b;
    
}
TEST(Redirection, PIPING) {
    User *u = new User();
    string command = "cat < CMakeLists.txt | head -5";
    list<string> l = u->parse(command);
    Base *b = u->createTree(l);
    EXPECT_TRUE(b->execute());


    command = "ls | wc -l";
    l = u->parse(command);
    b = u->createTree(l);
    EXPECT_TRUE(b->execute());


    command = "ps aux | grep 'Z'";
    l = u->parse(command);
    b = u->createTree(l);
    EXPECT_TRUE(b->execute());

    command = "ps aux | grep 'Z' >> newoutputfile";
    l = u->parse(command);
    b = u->createTree(l);
    EXPECT_TRUE(b->execute());

    delete u;
    delete b;


}
TEST(SeperatePipe, Pipe2) {

    User *u2 = new User();
    string cmd2 = "cat < CMakeLists.txt | tr A-Z a-z | tee newOutputFile1 | tr a-z A-Z > newOutputFile2";
    list<string> l2 = u2->parse(cmd2);
    Base *b2 = u2->createTree(l2); 
    EXPECT_TRUE(b2->execute()); 
    
    cmd2 = "rm -r newOutputFile1 newOutputFile2";
    l2 = u2->parse(cmd2);
    b2 = u2->createTree(l2);
    EXPECT_TRUE(b2->execute());

    cmd2 = "cat < CMakeLists.txt | tr A-Z a-z | tee newOutputFile1 | tr a-z A-Z > newOutputFile2 && ls | head -3 >> newOutputFile1";
    l2 = u2->parse(cmd2);
    b2 = u2->createTree(l2);
    EXPECT_TRUE(b2->execute());

    cmd2 = "lsof | wc -l >> numberprocess";
    l2 = u2->parse(cmd2);
    b2 = u2->createTree(l2);
    EXPECT_TRUE(b2->execute());

    cmd2 = "rm -r newOutputFile1 newOutputFile2 numberprocess newoutputfile";
    l2 = u2->parse(cmd2);
    b2 = u2->createTree(l2);
    EXPECT_TRUE(b2->execute());

    delete u2;
    delete b2;

}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
