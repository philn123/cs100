#include "gtest/gtest.h"
#include "composite.h"
#include "iterator.h"
#include <iostream>
#include <string>
#include "visitor.h"
using namespace std;

TEST(IteratorTest, OperatorIterator) {
    Op *op8 = new Op(8);
    Op *op3 = new Op(3);
    Add *a = new Add(op3, op8);

    OperatorIterator *it = new OperatorIterator(a);
    it->first();
    EXPECT_EQ(3, it->current()->evaluate());
    it->next();
    EXPECT_EQ(8, it->current()->evaluate());
    it->next();
    it->next();
    EXPECT_TRUE(it->is_done());

}

TEST(IteratorTest, UnaryIterator) {
    Op *op5 = new Op(5);
    Sqr *s = new Sqr(op5);

    UnaryIterator *u = new UnaryIterator(s);
    u->first();
    EXPECT_EQ(5, u->current()->evaluate());
    u->next();
    EXPECT_TRUE(u->is_done());
    u->first();
    EXPECT_FALSE(u->is_done());
}

TEST(IteratorTest, NullIterator) {
    Op *op1 = new Op(1);
    NullIterator *n = new NullIterator(op1);

    n->first();
    n->next();
    EXPECT_TRUE(n->is_done());
    EXPECT_FALSE(n->current());


}

TEST(PreOrderTest, PreOrderIteratorFunctions) {
    Op *op1 = new Op(1);
    Op *op2 = new Op(2);
    Add *a = new Add(op1, op2);
    Root *r = new Root(a);
    
    PrintVisitor *v_print = new PrintVisitor();
    PreorderIterator *p = new PreorderIterator(r);
    p->first();

    EXPECT_EQ(3, p->current()->evaluate());
    //cout << p->current()->evaluate() << endl;
    p->current()->accept(v_print);
    p->next();
    
    EXPECT_EQ(1, p->current()->evaluate());
    //cout << p->current()->evaluate() << endl;
    p->current()->accept(v_print);
    p->next();

    EXPECT_EQ(2, p->current()->evaluate());
    //cout << p->current()->evaluate() << endl;
    p->current()->accept(v_print);
    p->next();
    EXPECT_TRUE(p->is_done());
    
    ::testing::internal::CaptureStdout();
    v_print->execute();
    string output = ::testing::internal::GetCapturedStdout();
    EXPECT_EQ("+ 1 2 \n", output);

    Sub *s = new Sub(a, op1);
    Mult *m = new Mult(a, s);
    Root *r2 = new Root(m);
    PreorderIterator *p2 = new PreorderIterator(r2);
    PrintVisitor *v1 = new PrintVisitor();
    
    p2->first();
    
    EXPECT_EQ(6, p2->current()->evaluate());
    p2->current()->accept(v1);
    p2->next();
    
    EXPECT_EQ(3, p2->current()->evaluate());
    //cout << p2->current()->evaluate() << endl;
    p2->current()->accept(v1);
    p2->next();

    EXPECT_EQ(1, p2->current()->evaluate());
    //cout << p2->current()->evaluate() << endl;
    p2->current()->accept(v1);
    p2->next();

    EXPECT_EQ(2, p2->current()->evaluate());
    //cout << p2->current()->evaluate() << endl;
    p2->current()->accept(v1);
    p2->next();
    
    EXPECT_EQ(2, p2->current()->evaluate());
    //cout << p2->current()->evaluate() << endl;
    p2->current()->accept(v1);
    p2->next();

    EXPECT_EQ(3, p2->current()->evaluate());
    //cout << p2->current()->evaluate() << endl;
    p2->current()->accept(v1);
    p2->next();

    EXPECT_EQ(1, p2->current()->evaluate());
    //cout << p2->current()->evaluate() << endl;
    p2->current()->accept(v1);
    p2->next();

    EXPECT_EQ(2, p2->current()->evaluate());
    //cout << p2->current()->evaluate() << endl;
    p2->current()->accept(v1);
    p2->next();

    EXPECT_EQ(1, p2->current()->evaluate());
    //cout << p2->current()->evaluate() << endl;
    p2->current()->accept(v1);
    p2->next();

    EXPECT_TRUE(p2->is_done());
    
    ::testing::internal::CaptureStdout();
    v1->execute();
    output = ::testing::internal::GetCapturedStdout();
    EXPECT_EQ("* + 1 2 - + 1 2 1 \n", output);
}

TEST(VisitorTest, Preorder) {
    Op* op2 = new Op(2);
    Op* op4 = new Op(4);
    Sub* s = new Sub(op4, op2);
    Root* r = new Root(s);

    PreorderIterator* it = new PreorderIterator(r);
    PrintVisitor* v = new PrintVisitor();

    it->first();
    EXPECT_EQ(2, it->current()->evaluate());
    it->current()->accept(v);

    it->next();
    EXPECT_EQ(4, it->current()->evaluate());
    it->current()->accept(v);

    it->next();
    EXPECT_EQ(2, it->current()->evaluate());
    it->current()->accept(v);

    it->next();
    EXPECT_TRUE(it->is_done());
    ::testing::internal::CaptureStdout();
    v->execute();
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ("- 4 2 \n", output);
}

TEST(VisitorTest, Operator) {
    Op* op2 = new Op(2);
    Op* op4 = new Op(4);
    Add* a = new Add(op2, op4);

    PrintVisitor* v = new PrintVisitor();

    OperatorIterator* it = new OperatorIterator(a);
    it->first();
    EXPECT_EQ(2, it->current()->evaluate());
    it->current()->accept(v);
    
    it->next();
    EXPECT_EQ(4, it->current()->evaluate());
    it->current()->accept(v);

    it->next();
    EXPECT_TRUE(it->is_done());

    ::testing::internal::CaptureStdout();
    v->execute();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("2 4 \n", output);
}

TEST(VisitorTest, Unary) {
    Op* op3 = new Op(3);
    Sqr* s = new Sqr(op3);

    PrintVisitor* v = new PrintVisitor();

    UnaryIterator* it = new UnaryIterator(s);
    it->first();
    EXPECT_EQ(3, it->current()->evaluate());
    it->current()->accept(v);
    it->next();
    EXPECT_TRUE(it->is_done());

    ::testing::internal::CaptureStdout();
    v->execute();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("3 \n", output);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
