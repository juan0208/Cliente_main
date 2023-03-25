#include <Arduino.h>
#include <WiFi.h>
//crear constante para un red inalambrica
const char * nombre = "DAGA4852";
const char * password = "Daga0777";
const char * host ="www.google.com";
const int puerto =80;
/**
 * @brief esta es la funcion de configuracion del dispositivo
 * */

void setup() {
  // code
  // put your setup code here, to run once:
  pinMode(2,OUTPUT); // coloco el pin 2 como salida
  Serial.begin(115200);//confuguracion de velocidad de wifi
  Serial.println("Inicializado el dispocitovo");
  WiFi.begin(nombre,password);

  Serial.printf("Estableciendo vinculo con el Ap.");
  while (WiFi.status() !=WL_CONNECTED){
  Serial.print(".");
  delay(1000);
    
  }
  Serial.println("\r\n Conecion establecida");
  Serial.println("numero IP asignado");
  Serial.println(WiFi.localIP());//imprime el numero ip
  Serial.println();
}

/**
 * @brief Esta funcion es un bucle inifinito que corresponde al main()
*/
void loop() {
  WiFiClient Cliente;
  //
  if(!(Cliente.connect(host,puerto))){
    Serial.println("Erro conexion la host fallida");
    delay(3000);
    return;
  }
  Serial.print("conexion al host exitosa");
  
  // peticion GET al servidor http
  Cliente.print("GET /index.html HTTP/1.1\r\nHost: "+String(host)+"\r\n"+"Connection: close\r\n\r\n");

  //Debemos darle un tiempo al servidor a que responda la peticion
  //delay(5000); // no funciona aqui bloequea el wifi bloqueante
  unsigned long milisegundos=millis(); //hora de inicio

while(Cliente.available()==0){// preguntamos si no hay datos recibidos disponibles
    if(millis()-milisegundos>7000){
      Serial.println("se expiro el tiempo de la conexion");
      Cliente.stop();
    }
}

while (Cliente.available()){
  String linea = Cliente.readStringUntil('\r');
  Serial.println(linea);
}

  Serial.println("Fin de la conexion");
  Cliente.stop();
  delay(2000);

}

