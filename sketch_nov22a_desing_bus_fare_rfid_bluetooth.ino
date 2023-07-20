#include <SoftwareSerial.h>
#include <EEPROM.h>
SoftwareSerial rfid(2, 3);

char tag[] = "0800AAB72A3F";
char input[12];
int count = 0;
boolean flag = 0;
const int granted = 12, denied = 13;
String route1 = "PONDY-VALAVANUR", route2 = "PONDY-VILLUPURAM", route3 = "VALAVANUR-PONDY";
String route4 = "VALAVANUR-VILLUPURAM", route5 = "VILLUPURAM-VALAVANUR", route6 = "VILLUPURAM-PONDY";
String current_route,temp;
int route,route1_ticket = 15, route2_ticket = 30, route3_ticket = 15, route4_ticket = 20, route5_ticket = 20, route6_ticket = 30;
int total_amount = 1000, used_amount,remaining_amount;

  void setup() {
    Serial.begin(9600);
    rfid.begin(9600);
    pinMode(granted, OUTPUT);
    pinMode(denied, OUTPUT);
    pinMode(19,INPUT_PULLUP);
    if(digitalRead(19) ==  LOW){
      EEPROM.put(0, total_amount);
      Serial.println("Amount Recharged");
      Serial.print("Remaining Amount : ");Serial.println(total_amount);
      while(1);
    }else{
      EEPROM.get(0, remaining_amount);  
    }
  }
void loop() {
  while (Serial.available()) {
    delay(10);
    char c = Serial.read();
    //Serial.print(c);
    if (c == '#') {
      current_route = temp;
       current_route.toUpperCase();
      temp = "";
      Serial.print("Journey Details : ");
      if (current_route.indexOf(route1) != -1) {
        Serial.println(route1);
        route = 1;
      }
      else if (current_route.indexOf(route2) != -1) {
        Serial.println(route2);
        route =2;
      }
      else if (current_route.indexOf(route3) != -1) {
        Serial.println(route3);
        route = 3;
      }
      else if (current_route.indexOf(route4) != -1) {
        Serial.println(route4);
        route =4;
      }
      else if (current_route.indexOf(route5) != -1) {
        Serial.println(route5);
        route = 5;
      }
      else if (current_route.indexOf(route6) != -1) {
        Serial.println(route6);
        route = 6;
      }else{
        Serial.print(current_route);
        Serial.println(" is not Valid");
        current_route = "";
        route = 0;
      }
      break;
    }
    temp += c;
  }
  if (rfid.available()) {
    count = 0;
    while (rfid.available() && count < 12) {
      char id = rfid.read();
      input[count] = id;
      count++;
      //      Serial.print(id);
      delay(5);
    }
    if (count == 12) {
      //      Serial.println();
      count = 0;
      flag = 1;
      while (count < 12 && flag != 0) {
        if (input[count] == tag[count])
          flag = 1;
        else
          flag = 0;
        count++;
      }
    }
    if (flag == 1) {
      //      Serial.println("Access Allowed!");
      if(route == 0){
                Serial.println("Journey Route not selected");
      }
      else if(route == 1){
        remaining_amount = remaining_amount - route1_ticket;
        Serial.print("Ticket Rate : ");Serial.println(route1_ticket);
        current_route = "";route = 0;
      }
      else if(route == 2){
        remaining_amount = remaining_amount - route2_ticket;
        Serial.print("Ticket Rate : ");Serial.println(route2_ticket);
        current_route = "";route = 0;
      }
      else if(route == 3){
        remaining_amount = remaining_amount - route3_ticket;
        Serial.print("Ticket Rate : ");Serial.println(route3_ticket);
        current_route = "";route = 0;
      }
      else if(route == 4){
        remaining_amount = remaining_amount - route4_ticket;
        Serial.print("Ticket Rate : ");Serial.println(route4_ticket);
        current_route = "";route = 0;
      }
      else if(route == 5){
        remaining_amount = remaining_amount - route5_ticket;
        Serial.print("Ticket Rate : ");Serial.println(route5_ticket);
        current_route = "";route = 0;
      }
      else if(route == 6){
        remaining_amount = remaining_amount - route6_ticket;
        Serial.print("Ticket Rate : ");Serial.println(route6_ticket);
        current_route = "";route = 0;
      }
      EEPROM.put(0, remaining_amount);
      Serial.print("Remaining Amount : ");Serial.println(remaining_amount);
      
    } else {
       Serial.println("Access Denied");
    }
    for (count = 0; count < 12; count++) {
      input[count] = 'F';
    }
    count = 0;
  }
}
