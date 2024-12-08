//CÓDIGO ARDUINO-NANO MOVER GRUA MEDIANTE BLUETOOTH
int led1 = 13;
int option;
//*****************************************************************************

//Pines de conexión del driver
// Motor A
int ENA_Velocidad = 9;
int IN1_Adelante = 2;
int IN2_Retrocede = 3;

// Motor B
int ENB_Velocidad = 10;
int IN3_Adelante = 4;
int IN4_Retrocede = 5;
//int tiempo=0;
char estado;

//*****************************************************************************

void setup() {
  // inicializar la comunicación serial a 9600 bits por segundo:
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  
  // configuramos los pines como salida
  //Velocidad
  pinMode (ENA_Velocidad, OUTPUT);
  pinMode (ENB_Velocidad, OUTPUT);  
  //Motor A (Izquierda)
  pinMode(IN1_Adelante, OUTPUT);
  pinMode(IN2_Retrocede, OUTPUT);
  //Motor B (Derecha)
  pinMode(IN3_Adelante, OUTPUT);
  pinMode(IN4_Retrocede, OUTPUT);
}

//*****************************************************************************

void loop() {
  if (Serial.available()) {estado = Serial.read();}

//*****************************************************************************

  if (estado =='e')  {Embarque();}  // Embarque
//Sif (estado =='d')  {Desembarque();}  // Desembarque
}

//*****************************************************************************

void Embarque() {

  // Activa automatización y espera cuadre camión
 delay(4000); 

  // Baja brazo...........................................................
 digitalWrite(led1, HIGH);  
  //Direccion motor A
 digitalWrite (IN1_Adelante, LOW);
 digitalWrite (IN2_Retrocede, LOW);
 //analogWrite (ENA, 255); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3_Adelante, HIGH);
 digitalWrite (IN4_Retrocede, LOW);
 //analogWrite (ENB, 255); //Velocidad motor B
 delay(2000);           

  // Atrapa contenedor...........................................................         
 digitalWrite(led1, LOW);  //Apaga ambos motores
   //Direccion motor A
 digitalWrite (IN1_Adelante, LOW);
 digitalWrite (IN2_Retrocede, LOW);
 //analogWrite (ENA, 255); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3_Adelante, LOW);
 digitalWrite (IN4_Retrocede, LOW);
 //analogWrite (ENB, 255); //Velocidad motor B
 delay(4000);  

  // Sube brazo...........................................................           
 digitalWrite(led1, LOW);  
   //Direccion motor A
 digitalWrite (IN1_Adelante, LOW);
 digitalWrite (IN2_Retrocede, LOW);
 //analogWrite (ENA, 255); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3_Adelante, LOW);
 digitalWrite (IN4_Retrocede, HIGH);
 //analogWrite (ENB, 255); //Velocidad motor B
 delay(2000);   

  // Sale del mar y va al centro...........................................................           
 digitalWrite(led1, LOW);  
   //Direccion motor A
 digitalWrite (IN1_Adelante, LOW);
 digitalWrite (IN2_Retrocede, HIGH);
 //analogWrite (ENA, 255); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3_Adelante, LOW);
 digitalWrite (IN4_Retrocede, LOW);
 //analogWrite (ENB, 255); //Velocidad motor B
 delay(2000);  

  // Baja el brazo...........................................................................
 digitalWrite(led1, HIGH);  
   //Direccion motor A
 digitalWrite (IN1_Adelante, LOW);
 digitalWrite (IN2_Retrocede, LOW);
 //analogWrite (ENA, 255); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3_Adelante, HIGH);
 digitalWrite (IN4_Retrocede, LOW);
 //analogWrite (ENB, 255); //Velocidad motor B
 delay(2000); 

  // Suelta contenedor........................................................................           
 digitalWrite(led1, LOW);    //Apaga ambos motores
   //Direccion motor A
 digitalWrite (IN1_Adelante, LOW);
 digitalWrite (IN2_Retrocede, LOW);
 //analogWrite (ENA, 255); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3_Adelante, LOW);
 digitalWrite (IN4_Retrocede, LOW);
 //analogWrite (ENB, 255); //Velocidad motor B
 delay(4000); 

  // Sube brazo...............................................................................           
 digitalWrite(led1, LOW);  
   //Direccion motor A
 digitalWrite (IN1_Adelante, LOW);
 digitalWrite (IN2_Retrocede, LOW);
 //analogWrite (ENA, 255); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3_Adelante, LOW);
 digitalWrite (IN4_Retrocede, HIGH);
 //analogWrite (ENB, 255); //Velocidad motor B
 delay(2000);  
 
  // Sale del centro y va al mar (regresa posición inicial)...................................
 digitalWrite(led1, LOW);  
   //Direccion motor A
 digitalWrite (IN1_Adelante, HIGH);
 digitalWrite (IN2_Retrocede, LOW);
 //analogWrite (ENA, 255); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3_Adelante, HIGH);
 digitalWrite (IN4_Retrocede, LOW);
 //analogWrite (ENB, 255); //Velocidad motor B
 delay(2000);}










