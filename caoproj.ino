int LED_BUILTIN = 2;

void setup()
{
    pinMode (LED_BUILTIN, OUTPUT);
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH); //turns led on
    delay(1000);                   // 1s delay
    
    digitalWrite(LED_BUILTIN, LOW);//turns led off
    delay(1000);
}
