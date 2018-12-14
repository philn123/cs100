#include "gtest/gtest.h"
#include "composite.h"
#include "iterator.h"
#include <iostream>
#include <string>

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

TEST(IteratorTest, OperatorWithSquare) {
    Op* op3 = new Op(3);
    Sqr* s = new Sqr(op3);

    OperatorIterator* it = new OperatorIterator(s);
    it->first();
    EXPECT_EQ(3, it->current()->evaluate());
//    it->next();
//    EXPECT_EQ(NULL, it->current()->evaluate());
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

TEST(IteratorTest, UnaryNotSquare) {
    Op* op2 = new Op(2);
    Op* op6 = new Op(6);
    Add* a = new Add(op2, op6);
    
    UnaryIterator* u = new UnaryIterator(a);
    u->first();
    EXPECT_EQ(2, u->current()->evaluate());
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

    PreorderIterator *p = new PreorderIterator(r);
    p->first();

    EXPECT_EQ(3, p->current()->evaluate());
    //cout << p->current()->evaluate() << endl;
    p->next();
    
    EXPECT_EQ(1, p->current()->evaluate());
    //cout << p->current()->evaluate() << endl;
    p->next();

    EXPECT_EQ(2, p->current()->evaluate());
    //cout << p->current()->evaluate() << endl;
    
    p->next();
    EXPECT_TRUE(p->is_done());

    Sub *s = new Sub(a, op1);
    Mult *m = new Mult(a, s);
    Root *r2 = new Root(m);
    PreorderIterator *p2 = new PreorderIterator(r2);
    
    p2->first();
    
    EXPECT_EQ(6, p2->current()->evaluate());
    //cout << p2->current()->evaluate() << endl;
    p2->next();
    
    EXPECT_EQ(3, p2->current()->evaluate());
    //cout << p2->current()->evaluate() << endl;
    p2->next();

    EXPECT_EQ(1, p2->current()->evaluate());
    //cout << p2->current()->evaluate() << endl;
    p2->next();

    EXPECT_EQ(2, p2->current()->evaluate());
    //cout << p2->current()->evaluate() << endl;
    p2->next();
    
    EXPECT_EQ(2, p2->current()->evaluate());
    //cout << p2->current()->evaluate() << endl;
    p2->next();

    EXPECT_EQ(3, p2->current()->evaluate());
    //cout << p2->current()->evaluate() << endl;
    p2->next();

    EXPECT_EQ(1, p2->current()->evaluate());
    //cout << p2->current()->evaluate() << endl;
    p2->next();

    EXPECT_EQ(2, p2->current()->evaluate());
    //cout << p2->current()->evaluate() << endl;
    p2->next();

    EXPECT_EQ(1, p2->current()->evaluate());
    //cout << p2->current()->evaluate() << endl;
    p2->next();

    EXPECT_TRUE(p2->is_done());

    //o Only Child
    Root* r3 = new Root(op1);
    PreorderIterator* p3 = new PreorderIterator(r3);
    
    p3->first();

    EXPECT_EQ(1, p3->current()->evaluate());
    p3->next();
   
    EXPECT_TRUE(p3->is_done());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
