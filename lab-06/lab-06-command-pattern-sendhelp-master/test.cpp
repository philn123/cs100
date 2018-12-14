#include "command.h"
#include "composite.h"
#include "menu.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>
using namespace std;

TEST(OpTest, TestingOpCommand){
    OpCommand *o = new OpCommand(5);
    EXPECT_EQ(o->execute(), 5.0);

}

TEST(AddTest, TestingAddCommand) {
    OpCommand *o = new OpCommand(5);
    AddCommand *a = new AddCommand(o, 10);
    EXPECT_EQ(a->execute(), 15.0);
}

TEST(SubTest, TestingSubCommand) {
    OpCommand *o = new OpCommand(5);
    SubCommand *s = new SubCommand(o, 10);
    EXPECT_EQ(s->execute(), -5);
}

TEST(MultTest, TestingMultCommand) {
    OpCommand *o = new OpCommand(5);
    MultCommand *m = new MultCommand(o, 3);
    EXPECT_EQ(m->execute(), 15);
}

TEST(SqrTest, TestingSqrCommand) {
    OpCommand *o = new OpCommand(7);
    SqrCommand *s = new SqrCommand(o);
    EXPECT_EQ(s->execute(), 49);
}

TEST(MenuTest, MenuAddCommand){
    Menu *me = new Menu();
    me->add_command(new OpCommand(5));
    testing::internal::CaptureStdout();
    me->execute();
    string output = testing::internal::GetCapturedStdout(); 

    EXPECT_EQ("5\n", output);
}

TEST(MenuTest, MenuInitializedandExecute) {
    Menu *menu = new Menu();
    testing::internal::CaptureStdout();
    menu->execute();
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ("0\n", output);

    EXPECT_FALSE(menu->initialized());

    menu->add_command(new OpCommand(5));

    EXPECT_TRUE(menu->initialized());
}

TEST(MenuTest, MenuGetCommand) {
    Menu *m = new Menu();
    EXPECT_TRUE(!m->get_command());
    
    OpCommand *o = new OpCommand(5);
    m->add_command(o);

    EXPECT_EQ(5, m->get_command()->execute());

}

TEST(MenuTest, MenuUndoandRedo){
    Menu *m = new Menu();
    m->add_command(new OpCommand(1));
    m->add_command(new OpCommand(2));
    m->undo();
    EXPECT_EQ(1, m->get_command()->execute());
    
    m->redo();
    EXPECT_EQ(2, m->get_command()->execute());
}

TEST(MenuTest, MenuOperationsUndoRedo) {
    Menu *m = new Menu();
    OpCommand* o1 = new OpCommand(2);
    AddCommand* a = new AddCommand(o1, 3);
    SubCommand* s = new SubCommand(o1, 3);
    MultCommand* mu = new MultCommand(o1, 3);
    m->add_command(a);
    m->add_command(s);
    m->add_command(mu);

    m->undo();
    EXPECT_EQ(-1, m->get_command()->execute());
    m->undo();
    EXPECT_EQ(5, m->get_command()->execute());
    m->redo();
    m->redo();
    EXPECT_EQ(6, m->get_command()->execute());
}
    

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
