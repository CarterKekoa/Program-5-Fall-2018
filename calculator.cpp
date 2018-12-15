// Tarik Alauddin & Carter Mooring
// Filename: calculator.cpp
// Description: this code is a replication of an HP calculator. this calculator does operations
// in postfix notation, and will not exceed values of 10.
// Gonzaga University, CPSC 122, Dr. Yerion

#include "stack.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// description: checks to see if the user would still like to operate calculator,
      //gets user input, operates calculator, and ends program if user wishes.
// pre: the stack has been declared
// post: the stack contains user entered numbers and operation results
void runCalculator(Stack& theStack);

// description: prints user prompt to the screen
// pre: no paramaters required
// post: the user understands they need to enter something
void printPrompt();

// description: retrieves user entered values from stack, pops them, and prints them to temp stack
      //to then be displaid in reverese order (correctly) to the screen, simulating the calculator
// pre: the stack has been declared
// post: the stack contains user entered numbers and operation results
void printCalculatorScreen(Stack& theStack);

// description: writes user entered values to the stack to be later printed or
      //skips this step if any type of flow (ex. overflow etc.)
// pre: the stack has been declared, user has inputed, and skipPrintScreen boolean is known
// post: the tempStack contains necessary user input, ready to be printed
void writeToStack(Stack& theStack, ItemType userInputChar, bool& skipPrintScreen);

// description: stores the users entred char to be used later
// pre: no paramaters required
// post: the users entered char is able to be used
char getUserChar();

// description: converts characters to ascii integers
// pre: the user char is entered and usable
// post: the users char is now in integer form
int convertDigitToIntegerValue(char userChar);

// checks users input char to see if they would like to end program
// pre: users char has been entered
// post: the program couts a goodbye and returns a boolean to end program later
bool isInputFinished(ItemType achar);

// description: checks users character to see if they want to do addition
// pre: users char has been entered
// post: returns a boolean to do addition later
bool isAddition(ItemType achar);

// description: checks users character to see if they want to do doSubtraction
// pre: users char has been entered
// post: returns a boolean to do subtraction later
bool isSubtraction(ItemType achar);

// description: checks users character to see if they want to do multiplication
// pre: users char has been entered
// post: returns a boolean to do multiplication later
bool isMultiplication(ItemType achar);

// description: checks users character to see if they want to do division
// pre: users char has been entered
// post: returns a boolean to do division later
bool isDivision(ItemType achar);

// description: checks users entered char to determine if it is a number to be used
// pre: users char has been entered
// post: users char is able to be converted to integer for use later
bool isInteger(ItemType achar);

// description: determines what type of char the user has entered and determines
      //what action to take based on users char
// pre: the staack has been declared, user has inputed, skipPrintScreen has been created
// post: returns the value to be printed to the screen after operations
char determineChar(Stack& theStack, ItemType userInputChar, bool& skipPrintScreen);

// description: grabs and pops the top two values out of the stack to be operated
// pre: the stack has been declared, op1 has been determined, op2 has been determined
// post: op1 and op2 are able to be operated on elsewhere and are no longer in the stack
void retrieveForOperation(Stack& theStack, ItemType& op1, ItemType& op2);

// description: does additon on the top 2 values from the stack
// pre: op1 and op2 have been determined
// post: returns the sum of op1 and op2
int doAddition(int intOp1, int intOp2);

// description: subtractsd on the top 2 values from the stack from one another
// pre: op1 and op2 have been determined
// post: returns op1 and op2 subtracted from one another
int doSubtraction(int intOp1, int intOp2);

// description: multiplies the top 2 values from the stack
// pre: op1 and op2 have been determined
// post: returns the product of op1 and op2
int doMultiplication(int intOp1, int intOp2);

// description: does division on the top 2 values from the stack
// pre: op1 and op2 have been determined
// post: returns the quotient of op1 and op2
int doDivision(int intOp1, int intOp2);

// description: converts ascii integers back to a character
// pre: the integer is known
// post: the integer is now a character
char convertIntegertoCharacter(int integer);

// description: determines if a number to be printed in the stack is over 2 digits
// pre: value after the operations is known
// post: the boolean that determines whether there is overflow is known
bool isOverflow(int integerAfterOperation);

// description: determines if a number to be printed in the stack is a negative number
// pre: value after the operations is known
// post: the boolean that determines whether there is underflow is known
bool isUnderflow(int integerAfterOperation);

// description: prints overflow to the screen
// pre: no paramaters required
// post: overflow is printed to the screen
void printOverflow();

// description: prints underflow to the screen
// pre: no paramaters required
// post: underflow is printed to the screen
void printUnderflow();

// description: prints stackfull to the screen
// pre: no paramaters required
// post: stackfull is printed to the screen
void printStackFull();

// description: determines whether the stack is full of characters
// pre: isAdded is known
// post: the boolean that determines whether the stack is full is known
bool isStackFull(bool isAdded);

int main()
{
  Stack theStack;

  runCalculator(theStack);

  return 0;
}

// description: checks to see if the user would still like to operate calculator,
      //gets user input, operates calculator, and ends program if user wishes.
// pre: the stack has been declared
// post: the stack contains user entered numbers and operation results
void runCalculator(Stack& theStack)
{
  ItemType userInputChar;
  bool continueProgram = true;
  bool skipPrintScreen = false;

  while (continueProgram)
  {
    printPrompt();
    userInputChar = getUserChar();
    continueProgram = isInputFinished(userInputChar);
    if (continueProgram)
    {
      writeToStack(theStack, userInputChar, skipPrintScreen);
      if (!skipPrintScreen){
        printCalculatorScreen(theStack);
      }
    }  else
    {
      cout << endl << "Goodbye. Thanks for using our calculator!" << endl;
    }
  }
}

// description: prints user prompt to the screen
// pre: no paramaters required
// post: the user understands they need to enter something
void printPrompt()
{
  cout << "input> ";
}

// description: retrieves user entered values from stack, pops them, and prints them to temp stack
      //to then be displaid in reverese order (correctly) to the screen, simulating the calculator
// pre: the stack has been declared
// post: the stack contains user entered numbers and operation results
void printCalculatorScreen(Stack& theStack)
{
  Stack tempStack;
  ItemType item;
  bool isAdded;
  int counter = 0;

  while(not theStack.isEmpty())
  {
    theStack.retrieve(item);
    tempStack.push(item, isAdded);
    theStack.pop();
    counter++;
  }
  for (int k = 0; k < 3 - counter; k++)
  {
    tempStack.push(' ', isAdded);
  }
  int screenCount = 3;
  cout << setw(16) << "Screen" << endl;
  while(not tempStack.isEmpty())
  {
    tempStack.retrieve(item);
    if (counter < 4)
    {
      cout << setw(10) << screenCount << ": " << item << endl;
      screenCount--;
    }
    if (item != ' ')
    {
    theStack.push(item, isAdded);
    }
    tempStack.pop();
    counter--;
  }
}

// description: writes user entered values to the stack to be later printed or
      //skips this step if any type of flow (ex. overflow etc.)
// pre: the stack has been declared, user has inputed, and skipPrintScreen boolean is known
// post: the tempStack contains necessary user input, ready to be printed
void writeToStack(Stack& theStack, ItemType userInputChar, bool& skipPrintScreen)
{
  bool isAdded = true;
  bool stackFull;

  ItemType newUserInputChar;
  newUserInputChar = determineChar(theStack, userInputChar, skipPrintScreen);
  theStack.push(newUserInputChar, isAdded);

  stackFull = isStackFull(isAdded);
  if(stackFull)
  {
    printStackFull();
    skipPrintScreen = true;
  }
}

// description: stores the users entred char to be used later
// pre: no paramaters required
// post: the users entered char is able to be used
char getUserChar()
{
  char userChar;
  cin.get(userChar);
  cin.ignore();
  return userChar;
}

// description: converts characters to ascii integers
// pre: the user char is entered and usable
// post: the users char is now in integer form
int convertDigitToIntegerValue(char userChar)
{
  int charToInt;
  charToInt = userChar;
  return (charToInt - '0');
}

// description: converts ascii integers back to a character
// pre: the integer is known
// post: the integer is now a character
char convertIntegertoCharacter(int integer)
{
  char intToChar;
  intToChar = integer;
  return (intToChar + '0');
}

// description: determines what type of char the user has entered and determines
      //what action to take based on users char
// pre: the staack has been declared, user has inputed, skipPrintScreen has been created
// post: returns the value to be printed to the screen after operations
char determineChar(Stack& theStack, ItemType userInputChar, bool& skipPrintScreen)
{
  ItemType op1;
  ItemType op2;
  int intOp1;
  int intOp2;
  int integerAfterOperation;
  char afterOperations;
  bool isUnder;
  bool isOver;

  bool doAdd = isAddition(userInputChar);
  bool doSub = isSubtraction(userInputChar);
  bool doMult = isMultiplication(userInputChar);
  bool doDiv = isDivision(userInputChar);
  bool doInt = isInteger(userInputChar);

  if (not doInt)
  {
    retrieveForOperation(theStack, op1, op2);
    intOp1 = convertDigitToIntegerValue(op1);
    intOp2 = convertDigitToIntegerValue(op2);
  }

  if(doInt)
  {
    afterOperations = userInputChar;
    return afterOperations;
  }
  else if(doAdd)
  {
    integerAfterOperation = doAddition(intOp1, intOp2);
  }
  else if(doSub)
  {
    integerAfterOperation = doSubtraction(intOp1, intOp2);
  }
  else if(doMult)
  {
    integerAfterOperation = doMultiplication(intOp1, intOp2);
  }
  else if(doDiv)
  {
    integerAfterOperation = doDivision(intOp1, intOp2);
  }

  isOver = isOverflow(integerAfterOperation);
  isUnder = isUnderflow(integerAfterOperation);

  if(isOver)
  {
    printOverflow();
    skipPrintScreen = true;
  }
  else if(isUnder)
  {
    printUnderflow();
    skipPrintScreen = true;
  }
  else
  {
    afterOperations = convertIntegertoCharacter(integerAfterOperation);
  }

  return afterOperations;
}

// checks users input char to see if they would like to end program
// pre: users char has been entered
// post: the program couts a goodbye and returns a boolean to end program later
bool isInputFinished(ItemType achar)
{
  if (achar == 'x' or achar == 'X')
  {
    return false;
  } else
  {
    return true;
  }
}

// description: checks users character to see if they want to do addition
// pre: users char has been entered
// post: returns a boolean to do addition later
bool isAddition(ItemType achar)
{
  if (achar == '+')
  {
    return true;
  } else
  {
    return false;
  }
}

// description: does additon on the top 2 values from the stack
// pre: op1 and op2 have been determined
// post: returns the sum of op1 and op2
int doAddition(int intOp1, int intOp2)
{
  return (intOp1 + intOp2);
}

// description: checks users character to see if they want to do doSubtraction
// pre: users char has been entered
// post: returns a boolean to do subtraction later
bool isSubtraction(ItemType achar)
{
  if (achar == '-')
  {
    return true;
  } else
  {
    return false;
  }
}

// description: subtractsd on the top 2 values from the stack from one another
// pre: op1 and op2 have been determined
// post: returns op1 and op2 subtracted from one another
int doSubtraction(int intOp1, int intOp2)
{
  return (intOp2 - intOp1);
}

// description: checks users character to see if they want to do multiplication
// pre: users char has been entered
// post: returns a boolean to do multiplication later
bool isMultiplication(ItemType achar)
{
  if (achar == '*')
  {
    return true;
  } else
  {
    return false;
  }
}

// description: multiplies the top 2 values from the stack
// pre: op1 and op2 have been determined
// post: returns the product of op1 and op2
int doMultiplication(int intOp1, int intOp2)
{
  return (intOp2 * intOp1);
}

// description: checks users character to see if they want to do division
// pre: users char has been entered
// post: returns a boolean to do division later
bool isDivision(ItemType achar)
{
  if (achar == '/')
  {
    return true;
  } else
  {
    return false;
  }
}

// description: does division on the top 2 values from the stack
// pre: op1 and op2 have been determined
// post: returns the quotient of op1 and op2
int doDivision(int intOp1, int intOp2)
{
  return (intOp2 / intOp1);
}

// description: checks users entered char to determine if it is a number to be used
// pre: users char has been entered
// post: users char is able to be converted to integer for use later
bool isInteger(ItemType achar)
{
  if (achar <= '9' and achar >= '0')
  {
    return true;
  } else
  {
    return false;
  }
}

// description: grabs and pops the top two values out of the stack to be operated
// pre: the stack has been declared, op1 has been determined, op2 has been determined
// post: op1 and op2 are able to be operated on elsewhere and are no longer in the stack
void retrieveForOperation(Stack& theStack, ItemType& op1, ItemType& op2)
{
  theStack.retrieve(op1);
  theStack.pop();
  theStack.retrieve(op2);
  theStack.pop();
}

// description: determines if a number to be printed in the stack is over 2 digits
// pre: value after the operations is known
// post: the boolean that determines whether there is overflow is known
bool isOverflow(int integerAfterOperation)
{
  bool isOverflow = false;
  if (integerAfterOperation > 9)
  {
    isOverflow = true;
  }
  return isOverflow;
}

// description: determines if a number to be printed in the stack is a negative number
// pre: value after the operations is known
// post: the boolean that determines whether there is underflow is known
bool isUnderflow(int integerAfterOperation)
{
  bool isUnderflow = false;
  if (integerAfterOperation < 0)
  {
    isUnderflow = true;
  }
  return isUnderflow;
}

// description: prints overflow to the screen
// pre: no paramaters required
// post: overflow is printed to the screen
void printOverflow()
{
  cout << setw(12) << "          Screen" << endl;
  cout << setw(12) << "  3: " << endl << setw(12) << "  2: " << endl << "         1: OVERFLOW"  << endl;
}

// description: prints underflow to the screen
// pre: no paramaters required
// post: underflow is printed to the screen
void printUnderflow()
{
  cout << setw(12) << "          Screen" << endl;
  cout << setw(12) << "  3: " << endl << setw(12) << "  2: " << endl << "         1: UNDERFLOW" << endl;
}

// description: prints stackfull to the screen
// pre: no paramaters required
// post: stackfull is printed to the screen
void printStackFull()
{
  cout << setw(12) << "          Screen" << endl;
  cout << setw(12) << "  3: " << endl << setw(12) << "  2: " << endl << "         1: STACKFULL" << endl;
}

// description: determines whether the stack is full of characters
// pre: isAdded is known
// post: the boolean that determines whether the stack is full is known
bool isStackFull(bool isAdded)
{
  bool isStackFull = false;
  if(!isAdded)
  {
    isStackFull = true;
  }
  return isStackFull;
}
