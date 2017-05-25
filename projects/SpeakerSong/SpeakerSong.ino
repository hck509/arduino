void setup() {
  pinMode(7, OUTPUT);
}

void loop(){
  int one=200;
  
   tone(7,955,one); //c
   delay(one);
   tone(7,851,one); //b
   delay(one);
   
   tone(7,477,one*4); //cc
   delay(one*4);
   tone(7,715,one); //f
   delay(one);
   tone(7,758,one); //e
   delay(one);
   
   tone(7,715,one*4); //f
   delay(one*4);
   tone(7,477,one*2); //cc
   delay(one*2);
   
   tone(7,477,one*3); //cc
   delay(one*3);
   tone(7,425,one); //dd
   delay(one);
   tone(7,851,one); //b
   delay(one);
   tone(7,568,one); //a
   delay(one);
   
   tone(7,851,one*4); //b
   delay(one*4);
   tone(7,568,one); //a
   delay(one);
   tone(7,851,one); //b
   delay(one);
   
   tone(7,477,one*4); //cc
   delay(one*4);
   tone(7,715,one); //f
   delay(one);
   tone(7,758,one); //e
   delay(one);
} 

void c(){
  for(long i=0; i <100000 ; i+=500){ //1초동안 
    digitalWrite(7,1);
      delayMicroseconds(955);
      digitalWrite(7,0);
      delayMicroseconds(955);
  }
}  

void d(){
  for(long i=0; i <100000 ; i+=500){ //1초동안 
    digitalWrite(7,1);
      delayMicroseconds(851);
      digitalWrite(7,0);
      delayMicroseconds(851);
  }
}  

void e(){
  for(long i=0; i <100000 ; i+=500){ //1초동안 
    digitalWrite(7,1);
      delayMicroseconds(758);
      digitalWrite(7,0);
      delayMicroseconds(758);
  }
}  

void f(){
  for(long i=0; i <100000 ; i+=500){ //1초동안 
    digitalWrite(7,1);
      delayMicroseconds(715);
      digitalWrite(7,0);
      delayMicroseconds(715);
  }
}  

void g(){
  for(long i=0; i <100000 ; i+=500){ //1초동안 
    digitalWrite(7,1);
      delayMicroseconds(637);
      digitalWrite(7,0);
      delayMicroseconds(637);
  }
}  

void a(){
  for(long i=0; i <100000 ; i+=500){ //1초동안 
    digitalWrite(7,1);
      delayMicroseconds(568);
      digitalWrite(7,0);
      delayMicroseconds(568);
  }
}  

void b(){
  for(long i=0; i <100000 ; i+=500){ //1초동안 
    digitalWrite(7,1);
      delayMicroseconds(506);
      digitalWrite(7,0);
      delayMicroseconds(506);
  }
}  

void cc(){
  for(long i=0; i <100000 ; i+=500){ //1초동안 
    digitalWrite(7,1);
      delayMicroseconds(477);
      digitalWrite(7,0);
      delayMicroseconds(477);
  }
}  

void dd(){
  for(long i=0; i <100000 ; i+=500){ //1초동안 
    digitalWrite(7,1);
      delayMicroseconds(425);
      digitalWrite(7,0);
      delayMicroseconds(425);
  }
}  
