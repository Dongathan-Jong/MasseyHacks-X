#include <StopWatch.h>

#include <LiquidCrystal_I2C.h>

#define left 2
#define middle 3
#define right 4

#define red 6
#define green 7

StopWatch sw;

int firstInt;
int secondInt;

int score = 0;

long counterStart;
long counterFinish;

double timeTaken;

int answers = 0;

int currentDigit = 0;
int digitPlace = 0;

boolean questionSelection = true;
boolean answer = false;

int option;

LiquidCrystal_I2C lcd(0x3F,  16, 2);

void setup()
{
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  pinMode(left, INPUT_PULLUP);
  pinMode(middle, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0));

  digitalWrite(green, HIGH);
  digitalWrite(red, HIGH);

}

void loop(){
  if(questionSelection)
  {
    lcd.setCursor(0,0);
    lcd.print("Select a mode:");
    lcd.setCursor(0,1);
    lcd.print("+      -       *");
  	if(digitalRead(left) == 0)
  	{
      delay(200);
  	  option = 1;
      questionSelection = false;
      firstInt = random(499);
      secondInt =  random(499);
      lcd.clear();
  	}
  	else if(digitalRead(middle) == 0)
  	{
      delay(200);
  	  option = 2;
      questionSelection = false;
      firstInt = random(500,1000);
      secondInt = random(250,499);
      lcd.clear();
  	}
  	else if(digitalRead(right) == 0)
  	{
      delay(200);
  	  option = 3;
      questionSelection = false;
      firstInt = random(10,30);
      secondInt = random(10,30);
      lcd.clear();
  	}
    
  }
  
  
  if(questionSelection == false && answer == false)
  {
  	lcd.setCursor(0,0);
  	
  	lcd.print(firstInt);
  	if(option == 1)
  	{
  	  lcd.print(" + ");
  	}
  	else if(option == 2)
  	{
  	  lcd.print(" - ");
  	}
  	else
  	{
  	  lcd.print(" x ");
  	}
  	lcd.print(secondInt);
    lcd.print("= ?");
    answer = true;

    sw.start();

  }
  
  if(answer)
  {
    
    if(digitalRead(middle) == 0)
    {
      currentDigit++;
      delay(250);
    }
    if(currentDigit == 10)
    {
      currentDigit = 0;
    }
    lcd.setCursor(digitPlace,1);
    lcd.print(currentDigit);
    
    if(digitalRead(right) == 0 && digitPlace < 2)
    {
      delay(300);
      if(digitPlace == 0)
      {
        answers = (currentDigit * 100);
      }
      if(digitPlace == 1)
      {
        answers = answers + (currentDigit * 10);
      }
      if(digitPlace == 2)
      {
        answers = answers + currentDigit;
      }
      
      currentDigit = 0;
      if(digitPlace < 2)
      {
      	digitPlace++;
      }
      
    }
    Serial.println(answers);
    
    if(digitalRead(left) == 0)
    {
      answers = answers + currentDigit;

      sw.stop();
      timeTaken = (double)sw.elapsed() / 1000;

      Serial.println(timeTaken);

      Serial.println(sw.elapsed());
      
      
      if(option == 1)
      {
        if(firstInt+secondInt == answers)
        {
          
          lcd.clear();
          lcd.print("Correct!!!");
          score = score + (firstInt + secondInt) / 100;
          digitalWrite(green, LOW);
          lcd.setCursor(0,1);
          lcd.print("Solve time:");
          lcd.print(timeTaken);
          lcd.setCursor(15,1);
          lcd.print("s");
          delay(2000);
          digitalWrite(green, HIGH);
          answer = false;
          questionSelection = true;
          lcd.clear();
          lcd.print("Score: ");
          lcd.print(score);
          delay(1000);
          lcd.clear();
        }
        else
        {
          
          lcd.clear();
          lcd.print("Incorrect!!!");
          digitalWrite(red, LOW);
          lcd.setCursor(0,1);
          lcd.print("Solve time:");
          lcd.print(timeTaken);
          lcd.setCursor(15,1);
          lcd.print("s");
          delay(2000);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Right Answer:");
          lcd.setCursor(0,1);
          lcd.print(firstInt + secondInt);
          delay(2000);
          digitalWrite(red, HIGH);
          answer = false;
          questionSelection = true;
          lcd.clear();
          lcd.print("Score: ");
          lcd.print(score);
          delay(1000);
          lcd.clear();
        }
      }
      if(option == 2)
      {
        if(firstInt-secondInt == answers)
        {
          
          lcd.clear();
          lcd.print("Correct!!!");
          score = score + (firstInt - secondInt) / 100;
          digitalWrite(green, LOW);
          lcd.setCursor(0,1);
          lcd.print("Solve time:");
          lcd.print(timeTaken);
          lcd.setCursor(15,1);
          lcd.print("s");
          delay(2000);
          digitalWrite(green, HIGH);
          answer = false;
          questionSelection = true;
          lcd.clear();
          lcd.print("Score: ");
          lcd.print(score);
          delay(1000);
          lcd.clear();
        }
        else
        {
         
          lcd.clear();
          lcd.print("Incorrect!!!");
          digitalWrite(red, LOW);
          lcd.setCursor(0,1);
          lcd.print("Solve time:");
          lcd.print(timeTaken);
          lcd.setCursor(15,1);
          lcd.print("s");
          delay(2000);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Right Answer:");
          lcd.setCursor(0,1);
          lcd.print(firstInt - secondInt);
          delay(2000);
          digitalWrite(red, HIGH);
          answer = false;
          questionSelection = true;
          lcd.clear();
          lcd.print("Score: ");
          lcd.print(score);
          delay(1000);
          lcd.clear();
        }
      }
      if(option == 3)
      {
        if(firstInt*secondInt == answers)
        {
        
          lcd.clear();
          lcd.print("Correct!!!");
          score = score + (firstInt * secondInt) / 100 * 2;
          digitalWrite(green, LOW);
          lcd.setCursor(0,1);
          lcd.print("Solve time:");
          lcd.print(timeTaken);
          lcd.setCursor(15,1);
          lcd.print("s");
          delay(2000);
          digitalWrite(green, HIGH);
          answer = false;
          questionSelection = true;
          lcd.clear();
          lcd.print("Score: ");
          lcd.print(score);
          delay(1000);
          lcd.clear();
        }
        else
        {
         
          lcd.clear();
          lcd.print("Incorrect!!!");
          digitalWrite(red, LOW);
          lcd.setCursor(0,1);
          lcd.print("Solve time:");
          lcd.print(timeTaken);
          lcd.setCursor(15,1);
          lcd.print("s");
          delay(2000);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Right Answer:");
          lcd.setCursor(0,1);
          lcd.print(firstInt * secondInt);
          delay(1000);
          digitalWrite(red, HIGH);
          answer = false;
          questionSelection = true;
          lcd.clear();
          lcd.print("Score: ");
          lcd.print(score);
          delay(1000);
          lcd.clear();
        }
      }
      delay(100);
      
      currentDigit = 0;
      digitPlace = 0;

      sw.reset();
      
    }
  }
  

}
