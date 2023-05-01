
void elevationCheck() {
  
  if (alturaRelativa + 3.0 > alturaMaxima && banderaElevacionPositiva == false && banderaAterrizaje == false) {
    alturaMaxima = alturaRelativa;
    contadorAscenso++;
    if (contadorAscenso > 4){
    banderaElevacionPositiva = true;
    alturaMaxima = alturaRelativa;}
  }

  if (banderaElevacionPositiva == true && alturaRelativa < alturaMaxima - 3.0 && banderaElevacionNegativa == false && banderaAterrizaje == false) {
    contadorDescenso++;
    alturaMaxima = alturaRelativa;
    if (contadorDescenso > 4){
      banderaElevacionNegativa = true; 
    }
  }

  if (banderaElevacionPositiva == true && banderaElevacionNegativa == true && alturaRelativa < 4.0 && alturaRelativa > - 4.0 && banderaAterrizaje == false){
    banderaAterrizaje = true;
  }

  /*Adicion de lecturas por medio de giroscopio para determinar si el rover ya no esta en movimiento
    debido a la caida*/
  if (banderaAterrizaje == true && abs(Gx) <= 0.5 && abs(Gy) <= 0.5 && abs(Gz) <= 0.5) {
    banderaGiroscopio = true;
  }
  
  /*Al cumplirse la condicion anterior se define que el rover esta listo para moverse
    al equivaler la bandera de movimiento como verdadera*/
  if (banderaGiroscopio == true && banderaMovimiento == false){
    banderaMovimiento = true;
  }
}
