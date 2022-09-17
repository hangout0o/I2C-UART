void start(int device);
void Stop();
void Write(int data);
int Read();
void Ser_beg();
void Ser_prnt();
char text[]={"WARNING TEMP IS OVER 50\n"};

int main(){
  Ser_beg();
  DDRD = 0b00000100;
  TWSR = 0; 
  TWBR = 72;
  int y;
  while(1){
  
    start(0b10011010);
    Write(0);
    start(0b10011011);
    
    int x = Read();
    Stop();
    
    if(x>50){ 
    PORTD= 0b00000100;
    if(y ==0){Ser_prnt();}
    y =1;
    }else{PORTD = 0;
    y =0;} 
    }}

void start(int device){
  TWCR =(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
  while(!(TWCR&(1<<TWINT)));
  TWDR = device;
  TWCR = (1<<TWINT) | (1<<TWEN);
  while(!(TWCR&(1<<TWINT)));
  }

void Stop(){
  TWCR =(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
  while((TWCR & (1<<TWINT)));
  }

void Write(int data){
  TWDR = data;
  TWCR =(1<<TWINT)|(1<<TWEN);
  while(!(TWCR & (1<<TWINT)));
  }
int Read(){
  TWCR =(1<<TWINT)|(1<<TWEN);
  while(!(TWCR & (1<<TWINT)));
  return TWDR ;}

void Ser_beg(){
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
  UCSR0C |= (0<<UMSEL00) |(0<<USBS0) |(3<<UCSZ00)|(0<<UPM00);
  UBRR0L = 103;  
  UBRR0H = (103>> 8);}

void Ser_prnt(){
  for(int f = 0; f<24; f++){  while(!(UCSR0A&(1<<UDRE0)));
  UDR0 = text[f];}}
  
