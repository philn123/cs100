# Decorator Pattern
**You *must* work in a group of two for this lab**

In this lab you will be extending your Composite and Strategy Pattern lab. The easiest way to transfer your code from the previous lab is to clone this repository, copy your files into the repository from the last lab, and commit them into the new repository as a repo "initialization". You will be using the decorator pattern to extend the functionality of the expression tree. For example, we may want to create the following equation
```
ceil(3 + 7 * 4 - 2)
```
would be represented with the following tree, with the top most node being a decorator

![Equation tree for Decorator Pattern](https://github.com/cs100/lab05-decoratorPattern/blob/master/Images/decorator.png)

You can see how the ceiling function simply modifies the return of the statement, and that the return value at the top would be the ceiling of the equation below. You will be in charge of building three separate decorator classes, and testing each one at different levels of your system (including when decorators have children which are other decorators). Note that it is easiest to fully test a system when it holds double values rather than integer values. You must create the following classes as decorators:

* Ceiling (`ceil()`)
* Floor (`floor()`)
* Absolute value (`abs()`)

To implement the functionality of each of these classes, you may employ the cmath library (`math.h`). This makes the implementation of the functionality trivial, so it is important that you are fully testing all variations of decorator composition (specifically, when an absolute value points to a ceiling/floor and vice-versa), since this is one of the more important concepts when discussing decorator patterns. 

## Submission
To receive credit for this lab you must show an example program to your TA that demonstrates the full functionality of this pattern along with the composite and strategy patterns, and must explain to your TA the structure of both your classes and how they interact. You must also show your TA the tests that you have created for validating your decorator class and its interactions with the other classes.

