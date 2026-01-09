#include <iostream> 
#include <string>
#include "ViraTempo.hpp"

int main() {
  ViraTempo vt(5);
  vt.mostrarTempo();
  vt.avancarTempo();
  vt.mostrarTempo();
  vt.virarTempo();
  vt.avancarTempo();
  vt.mostrarTempo();
  vt.virarTempo();
  for (int i = 0; i < 6; i++){
	vt.avancarTempo();
	vt.mostrarTempo();
  }
  vt.virarTempo();
  for (int i = 0; i < 7; i++){
	vt.avancarTempo();
	vt.mostrarTempo();
  }
 
  return 0;
}