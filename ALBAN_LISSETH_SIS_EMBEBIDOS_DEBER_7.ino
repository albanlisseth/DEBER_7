/*UNIVERDIDAD TECNICA DEL NORTE
*FICA-CITEL
*SISTEMAS EMBEBIDOS
*DEBER#7
*EEPROM
*LISSETH ALBAN
*/
#include <Keypad.h>
#include <LiquidCrystal.h>   
#include <EEPROM.h>
const byte rows = 4; 
const byte col = 4;
const int POT = A3; 
int value,PW,CurrentPW=4563;
float volt;
char Key;
byte pRows[]  = {3,2,1,0};
byte pCol[] = {7,6,5,4};
char teclas[4][4] = {{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}};
Keypad teclado = Keypad( makeKeymap(teclas), pRows, pCol, rows, col); 
LiquidCrystal lcd(13, 12, 11, 10, 9, 8); //(RS, E, D4,D5, D6, D7)
void setup() {
lcd.begin(16, 2);   //  LCD 16x02 
teclado.setHoldTime(1000); //TIempo de espera para el teclado
EEPROM.get( 0, PW );
if(PW!=CurrentPW && PW>0){
CurrentPW=PW;
}

}
int password(void){
int pass,i=0;
String KeyWord;
//Pergunta por los 4 digitos de la contraseña
lcd.setCursor(0, 1);
while(i<4){
Key=teclado.waitForKey(); 
if(Key>='0' && Key<='9'){
lcd.print('*');
KeyWord += Key;   //indica los caracteres
i++;
}
if(Key=='D'){ 
i=4;
}
}
if(KeyWord.length()>0){
pass=KeyWord.toInt(); 
}else{
pass=0;
}
return(pass);
}
void loop() {
char KeyOp;
int i,j;
float vEE[4];

value=analogRead(POT); 

volt=(value*5/1023.0);
lcd.home();         // Coloca el cursor en las coordenadas (0,0)
lcd.print("LECTURA INVALIDA");    
lcd.setCursor(0,1);         // Coloca el cursor en las coordenadas (0,0)
Key=teclado.getKey();
if(Key>='A' && Key<='C'){
KeyOp=Key;
lcd.clear();
lcd.home();         // Coloca el cursor en las coordenadas (0,0)   
lcd.print("Digite LA Contraseña:"); // Escribe en LCD   

PW=password();//Valida a contraseña

if(PW == CurrentPW){
if(KeyOp=='A'){ 
lcd.clear();
lcd.home();         // Coloca el cursor en las coordenadas (0,0)   
lcd.print("Cargando"); // Escribe en LCD 

EEPROM.put( i, volt );  //Graba en la EEPROM
delay(1000);
}
}
if(KeyOp=='B'){
lcd.clear();
lcd.home();         // Coloca el cursor en las coordenadas (0,0)   
lcd.print("Nueva Contraseña:"); // Escribe en LCD 
PW=password();
EEPROM.put( 0, PW );  //Graba en EEPROM
lcd.clear();
lcd.home();         // Coloca el cursor en las coordenadas (0,0)   
lcd.print("Contraseña Guardada"); // Escribe en LCD
CurrentPW=PW;
delay(2000);
}
if(KeyOp=='C'){ 
lcd.clear();
lcd.home();         // Coloca el cursor en las coordenadas (0,0)   
j=0;

for(i=2;i<2+ 4*sizeof(float);i+= sizeof(float)){
EEPROM.get( i, vEE[j] );  
j++;
}
lcd.setCursor(0,0);
for(j=0;j<2;j++){         
lcd.print(j+1);
lcd.print(')');
lcd.print(vEE[j]);
lcd.print("; ");
}
lcd.setCursor(0,1);
for(j=2;j<4;j++){         
lcd.print(j+1);
lcd.print(')');
lcd.print(vEE[j]);
lcd.print("; ");
}
delay(10000);
lcd.clear();
}
}else{
lcd.clear();
lcd.home();         // Coloca el cursor en las coordenadas (0,0)   
lcd.print("Contraseña Equivocada"); // Escribe en LCD  
delay(2000); 
}
}
 
