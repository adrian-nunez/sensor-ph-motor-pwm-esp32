#include <Arduino.h>

float calibration_value = 21.34;
int phval = 0;
unsigned long int avgval;
int buffer_arr[10], temp;
float ph_act;

unsigned long int tiempoAnterior;
// int k; // Contador de vueltas

// Variables para el motor
int pwmValue;
int pinMotor = 2;

void setup()
{
  Serial.begin(115200);
  tiempoAnterior = millis();
}

void loop()
{
  // k = 0;

  for (int i = 0; i < 10; i++)
  {
    buffer_arr[i] = analogRead(34);

    delay(30); // ELIMINAR ESTE DELAY - REEMPLAZAR POR WHILE CON UN MILLIS
  }

  for (int i = 0; i < 9; i++)
  {
    for (int j = i + 1; j < 10; j++)
    {
      if (buffer_arr[i] > buffer_arr[j])
      {
        temp = buffer_arr[i];
        buffer_arr[i] = buffer_arr[j];
        buffer_arr[j] = temp;
      }
    }
  }
  avgval = 0;
  for (int i = 2; i < 8; i++)
    avgval += buffer_arr[i];
  float volt = (float)avgval * 3.3 / 4096 / 6; // convertir analógico a milivoltios
  Serial.println(volt);
  ph_act = -3.75 * volt + 16.375;

  Serial.print("pH Val: ");
  Serial.println(ph_act);

  // motor
  pwmValue = 165; // Este valor debe ser 0 cuando el pH es < 6.05
  analogWrite(pinMotor, pwmValue);
  delay(300);
  pwmValue = 0;
  analogWrite(pinMotor, pwmValue);
  delay(7000);

  delay(1000); // ELIMINAR ESTE DELAY
}
