String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
int PinLed=13;
int comandos=0;
int TiempoEnmascarado=30000;

const int boton= 3;            // boton conectado al pin 4
const int tiempoAntirebote =10;

int cuenta =0;          //Guarda el numero de veces que el boton ha sido presionado
int estadoBoton;
int estadoBotonAnterior;

/*Función antirebote*/
boolean antirebote  (int pin ) {
  int  contador =0;
  boolean estado;            // guarda el estado del boton 
  boolean estadoAnterior;    // guarda el ultimo estado del boton 

  do {
    estado = digitalRead (pin);
    if (estado != estadoAnterior ){  // comparamos el estado actual 
      contador = 0;                   // reiniciamos el contador 
      estadoAnterior = estado;
    }
    else{
      contador = contador +1;       // aumentamos el contador en 1
    }
    delay (1);
  }
  while (contador < tiempoAntirebote);
  return estado;
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}

void setup (){                      
  Serial.begin(9600);   //Iniciamos la comunicacion serial
  pinMode(boton,INPUT); //declaramos el boton como entrada
  pinMode(PinLed,OUTPUT);
  
  
  inputString.reserve(100);
}

void loop () {
  estadoBoton =digitalRead (boton);              //leemos el estado del boton
  if ((estadoBoton  != estadoBotonAnterior)||(estadoBoton==1)) {     //si hay cambio con respeto al estado 
    if (antirebote (boton)){   
         Serial.write ("2\r\n");         //checamos  si esta preionado y si lo esta
        //  cuenta++;                
          delay(TiempoEnmascarado);
         //aumentamos la cuenta
         
    }
  }
  
  estadoBotonAnterior = estadoBoton;      // guardamos el estado del boton
  // Aca agrego la parte de datos seriales
   if (stringComplete) {
   // Serial.println(inputString); 
    
    if(inputString=="0\n"){
   //  Serial.println("llego un 0"); 
      digitalWrite(PinLed,LOW);
    Serial.write ("0\r\n");         //checamos  si esta preionado y si lo esta
        
    }else{if(inputString=="1\n"){
        digitalWrite(PinLed,HIGH);
    Serial.write ("1\r\n");         //checamos  si esta preionado y si lo esta
        
    }}
      
    
   // clear the string:
    inputString = "";
    stringComplete = false;
  }
  
  
  
}



