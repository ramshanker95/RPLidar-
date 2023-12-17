#include <RPLidar.h>
RPLidar lidar;

#define no_obj  27
#define obj_c   26
#define obj_l   25
#define obj_r   33
#define obj_C   34
#define obj_L   32
#define obj_R   35

const int rxPin = 3;  // GPIO 3 for RX
const int txPin = 1;  // GPIO 1 for TX

volatile int count = 0;
volatile int count_1 = 0;
volatile int count_2 = 0;
volatile int count_3 = 0;


void gpio_write(char ch)
{
  if (ch == 'f')
  {
    Serial.println("f");
    digitalWrite(no_obj, HIGH);
    digitalWrite(obj_c, LOW);
    digitalWrite(obj_l, LOW);
    digitalWrite(obj_r, LOW);
  }
  else if (ch == 'b')
  {
    Serial.println("b");
    digitalWrite(no_obj, HIGH);
    digitalWrite(obj_c, HIGH);
    digitalWrite(obj_l, HIGH);
    digitalWrite(obj_r, HIGH);
  }
  else if (ch == 'l')
  {
    Serial.println("l");
    digitalWrite(no_obj, LOW);
    digitalWrite(obj_c, LOW);
    digitalWrite(obj_l, HIGH);
    digitalWrite(obj_r, LOW);
  }
  else if (ch == 'r')
  {
    Serial.println("r");
    digitalWrite(no_obj, LOW);
    digitalWrite(obj_c, LOW);
    digitalWrite(obj_l, LOW);
    digitalWrite(obj_r, HIGH);
  }
}
void setup() 
{
  lidar.begin(Serial2);
  Serial.begin(115200, SERIAL_8N1, rxPin, txPin);
  pinMode(no_obj, OUTPUT);
  pinMode(obj_c, OUTPUT);
  pinMode(obj_l, OUTPUT);
  pinMode(obj_r, OUTPUT);
  pinMode(obj_C, INPUT);
  pinMode(obj_L, INPUT);
  pinMode(obj_R, INPUT);
  digitalWrite(no_obj, LOW);
  digitalWrite(obj_c, LOW);
  digitalWrite(obj_l, LOW);
  digitalWrite(obj_r, LOW);
  Serial.println("s");
//  red();
}

void loop()
{
//   digitalWrite(obj_r, HIGH);
  int var = 1;
  int var1 = 1;
  int var2 = 1;
  int var3 = 1;
  int a = 0;
  int b = 0;
  for (int i = 0; i <= 360; i++)
  {
    if (IS_OK(lidar.waitPoint()))
    {
      int distance = round(lidar.getCurrentPoint().distance); //distance value in mm unit
      int angle    = round(lidar.getCurrentPoint().angle); //anglue value in degree
      if (distance > 0)
      {
        if ((angle >= 0) && (angle <= 90))
        {
          if (distance <= 450)
          {
            var += 1;
          }
          else
          {
            var1 += 1;
          }
        }
        else if ((angle >= 270) && (angle <= 360))
        {
          if (distance <= 450)
          {
            var2 += 1;
          }
          else
          {
            var3 += 1;
          }
        }
      }
      }
    else {
      rplidar_response_device_info_t info;
      if (IS_OK(lidar.getDeviceInfo(info, 100))) {
        lidar.startScan();
        delay(500);
        Serial.println("hello");
      }
    }
  }
  
//  Serial.println("var:" + String(var) + " var1:" + String(var1) + " var2:" + String(var2) + "var3: " + String(var3));
  int obj_center = digitalRead(obj_C);
  int obj_right = digitalRead(obj_R);
  int obj_left = digitalRead(obj_L);
//  Serial.println("oc:"+String(obj_center)+" or:"+String(obj_right)+" ol:"+String(obj_left));
  if (((var <= 2) and (var1 >= 5) and (var2 <= 2) and (var3 >= 5))
  and((obj_center == 0) and (obj_right == 0) and (obj_left == 0)))
  {
    if(count>=1)
    {
      gpio_write('f');
      count = 0;
      count_1 = 0;
      count_2 = 0;
      count_3 = 0;
    }
    else
    {
      count+=1;
      gpio_write(' ');
    }
  }
  else if (((var > 1) and (var1 > 1) and (var2 <= 2) and (var3 >= 5))
    or((obj_center == 0) and (obj_right != 0) and (obj_left == 0))
    or((obj_center != 0) and (obj_right != 0) and (obj_left == 0)))
  {
    if(count_1>=1)
    {
      gpio_write('r');
      count = 0;
      count_1 = 0;
      count_2 = 0;
      count_3 = 0;
    }
    else
    {
      count_1+=1;
      gpio_write(' ');
    }
  }
  else if (((var <= 2) and (var1 >= 5) and (var2 > 1) and (var3 > 1))
    or((obj_center == 0) and (obj_right == 0) and (obj_left != 0))
    or((obj_center != 0) and (obj_right == 0) and (obj_left != 0)))
  {
    if(count_2>=1)
    {
      gpio_write('l');
      count = 0;
      count_1 = 0;
      count_2 = 0;
      count_3 = 0;
    }
    else
    {
      count_2 +=1;
      gpio_write(' ');
    }
  }
  else
  {
    if(count_3 >=1)
    {
      gpio_write('b');
      count = 0;
      count_1 = 0;
      count_2 = 0;
      count_3 = 0;
    }
    else
    {
      count_3 +=1;
      gpio_write(' ');
    }
  }
  Serial.flush();
}
