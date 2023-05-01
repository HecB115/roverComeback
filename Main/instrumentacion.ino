
void brujula(){
  sensors_event_t event; 
  mag.getEvent(&event);
  
  magX = event.magnetic.x;
  magY = event.magnetic.y;
  magZ = event.magnetic.z;
  float headingRads = (atan2(magY, magX) + declinacionMagnetica);

  if(headingRads < 0)
    headingRads += 2*PI;
    
  if(headingRads > 2*PI)
    headingRads -= 2*PI;

  heading = headingRads * 180 / PI;
}

void imu(){ //Para obtener datos de IMU
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Ax = a.acceleration.x;
  Ay = a.acceleration.y;
  Az = a.acceleration.z;
  Gx = a.gyro.x;
  Gy = a.gyro.y;
  Gz = a.gyro.z;
  temperaturaMPU = temp.temperature;
}

void barometro(){
  temperaturaBMP = bmp.readTemperature(); //En Celsius
  presionBarometrica = bmp.readPressure(); //En Pascales
  alturaAbsoluta = bmp.readAltitude(101325); //Usando presion a nivel del mar como base
  
  if (banderaPresionSuelo == false){
    /*Personalmente cuando se trata de tomar una medida inicial o de muestreo
      prefiero hacer varias lecturas y utilizar un filtro para garantizar que
      la lectura tiene mayor fiabilidad y no solo depender de una lectura,
      en este caso creo que un filtro de promedios funciona bien.*/
    for(int i = 0; i <= 100; i++){
      muestraPresion += bmp.readPressure();
    }
    muestraPresion /= 100; 
    banderaPresionSuelo = true;
  }
  alturaRelativa = bmp.readAltitude(muestraPresion);
  
}

void ubicacion(){
  if (millis() - timer > 1000) {
    timer = millis();
    if(GPS.fix) {
      latitud = GPS.latitude;
      longitud = GPS.longitude;
      satelites = GPS.satellites;
    }
  }
}
