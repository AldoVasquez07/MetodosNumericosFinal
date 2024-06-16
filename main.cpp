#include <iostream>
#include <list>
#include <iomanip>
using namespace std;

void imprimirTablaEuler(list<string> listaN, list<string> listaX, list<string> listaY, list<string> listaCalculo) {

    if (listaN.size() != listaX.size() || listaN.size() != listaY.size() || listaN.size() != listaCalculo.size()) {
        cerr << "Error: Las listas no tienen el mismo tamaño." << endl;
        return;
    }

    cout << setw(10) << "N" << "\t"
              << setw(10) << "X" << "\t"
              << setw(10) << "Y" << "\t"
              << setw(15) << "Calculo" << endl;
    cout << string(10, '-') << "\t"
              << string(10, '-') << "\t"
              << string(10, '-') << "\t"
              << string(15, '-') << endl;

    auto itN = listaN.begin();
    auto itX = listaX.begin();
    auto itY = listaY.begin();
    auto itCalculo = listaCalculo.begin();

    while (itN != listaN.end() && itX != listaX.end() && itY != listaY.end() && itCalculo != listaCalculo.end()) {
        cout << setw(10) << *itN << "\t"
                  << setw(10) << *itX << "\t"
                  << setw(10) << *itY << "\t"
                  << setw(15) << *itCalculo << endl;

        ++itN;
        ++itX;
        ++itY;
        ++itCalculo;
    }
}

void separador() {
  cout << endl << endl;
  cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*";
  cout << endl << endl;
}

int menuOpciones(){
  int opcion = 0;
  cout << "Ingrese una opcion" << endl;
  cout << "1) Metodo de Euler" << endl;
  cout << "2) Metodo de Euler Iterado" << endl;
  cout << "3) Metodo de Euler Mejorado" << endl;
  cout << "4) Metodo de Euler Mejorado Iterado" << endl;
  cout << "5) Salir" << endl;
  cout << "\nSu eleccion: ";
  cin >> opcion;
  separador();
  return opcion;
}

void imprimirError(string error) {
  cout << endl << "Error Actual: " << error << "%" << endl;
  cout << endl << ". . . . . . . . . . . . . . . . . . . . . . . . . . .";
  cout << endl << endl << endl;
}

double calcularErrorIterativo(double actual, double anterior){
  double var = ((actual - anterior) / actual) * 100;
  if (var < 0){
    var *= -1;
  }
  return var;
}

double calcularDiferencia(double a, double b, int n) {
  return (b-a)/n;
}

double calcularEcuacionDiferencial(double x, double y){
  return (y - x);
}

double metodoDeEuler(double x, double y, double xDeseado, int n, bool tipoMetodo){
  double h = calcularDiferencia(x, xDeseado, n);
  list<string> listaN, listaX, listaY, listaCalculo;
  
  for (int i = 0; i < n + 1; i++) {
    double calculo = 0;
    
    if (tipoMetodo) {
      calculo = calcularEcuacionDiferencial(x, y);
    }
    else {
      calculo = y + calcularEcuacionDiferencial(x, y) * h;
    }
    
    listaN.push_back(to_string(i));
    listaX.push_back(to_string(x));
    listaY.push_back(to_string(y));
    
    if (i < n){
      listaCalculo.push_back(to_string(calculo));
      if (tipoMetodo){
        y += calculo * h;
      }
      else {
        y += h/2 * (calcularEcuacionDiferencial(x, y) + calcularEcuacionDiferencial(x + h, calculo));
      }
    }
    else{
      listaCalculo.push_back("");
    }
    x += h;
  }
  imprimirTablaEuler(listaN, listaX, listaY, listaCalculo);  
  return y;
}

double metodoDeEulerIterado(double x, double y, double xDeseado, double error, bool tipoMetodo){
  int nParticiones = 1;
  double errorAnterior = 0, errorActual = 1;
  double respuestaAnterior = 0, respuestaActual = 1;

  while(true) {
    cout << "Tamaño de paso: " << nParticiones << endl << endl;
    respuestaActual = metodoDeEuler(x, y, xDeseado, nParticiones, tipoMetodo);
    if(nParticiones > 1) {
      errorActual = calcularErrorIterativo(respuestaActual, respuestaAnterior);
      imprimirError(to_string(errorActual));
      
      if (errorActual < error) {
        break;
      }
    }
    else {
      imprimirError("-");
    }
    respuestaAnterior = respuestaActual;
    errorAnterior = errorActual;
    nParticiones++;
  }
  return respuestaActual;
}

void consultaMetodoEuler(bool tipoMetodo) {
  double x, y, xDeseado;
  int nParticiones;
  
  cout << "Ingrese el caso base" << endl;
  cout << "x: ";
  cin >> x;
  cout << "y: ";
  cin >> y;
  cout << endl;
  cout << "Ingrese el valor del x Deseado: ";
  cin >> xDeseado;
  cout << endl;
  cout << "Ingrese tamaño de paso " << endl;
  cout << "h: ";
  cin >> nParticiones;
  cout << endl;
  
  double respuesta = metodoDeEuler(x, y, xDeseado, nParticiones, tipoMetodo);
  cout << "\nEl valor de y(" << xDeseado << "), con h = ";
  cout<< nParticiones << ", es: " << respuesta << endl << endl;
  separador();
}

void consultaMetodoEulerIterado(bool tipoMetodo){
  double x, y, xDeseado, errorMaximo;

  cout << "Ingrese el caso base" << endl;
  cout << "x: ";
  cin >> x;
  cout << "y: ";
  cin >> y;
  cout << endl;
  cout << "Ingrese el valor del x Deseado: ";
  cin >> xDeseado;
  cout << endl;
  cout << "Ingrese el Error Deseado: ";
  cin >> errorMaximo;
  cout << endl;
  
  double respuesta = metodoDeEulerIterado(x, y, xDeseado, errorMaximo, tipoMetodo);
  cout << "\n→ El valor de y(" << xDeseado;
  cout << "), con un error menor a " << errorMaximo << "%, es: ";
  cout << respuesta << endl << endl;
  separador();
}

int main() {
  while(true){
    switch(menuOpciones()){
      case 1:{
        consultaMetodoEuler(true);
      }
        break;
      case 2:{
        consultaMetodoEulerIterado(true);
      }
        break;
      case 3:{
        consultaMetodoEuler(false);
      }
       break;
      case 4:{
        consultaMetodoEulerIterado(false);
      }
        break;
      case 5:
        return 0;
        break;
      default:
        break;
    }
  }
}
