#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

class Combatiente {
protected:
    string nombre;
    int vida;
    int resistencia;
    int danio;
    int vidaMaxima;

public:

    Combatiente(string n, int v, int r, int d){
        nombre = n;
        vida = v;
        resistencia = r;
        danio = d;
        vidaMaxima = v;  
    }
    void atacar(Combatiente &objetivo){
        if(resistencia >= 15){
    
            resistencia -= 15;
    
            int probabilidad = rand() % 100 + 1;
            int danoFinal = danio;
            bool esCritico = false;
    
            if(probabilidad <= 20){
                danoFinal = round(danio * 1.2);
                esCritico = true;
            }
    
            objetivo.recibirDanio(danoFinal);
    
            cout << nombre << " hizo " << danoFinal << " de daño";
            
            if(esCritico){
                cout << " (CRÍTICO)";
            }
    
            cout << endl;
        }
        else{
         cout << nombre << " no tiene suficiente resistencia.\n";
     }
    }   
    void defender(){
        resistencia += 10;
        if(resistencia > 100){
            resistencia = 100;
        }
    }

    void recibirDanio(int cantidad){
        vida -= cantidad;
        if(vida < 0){
            vida = 0;
        }
    }

    int getVida(){
        return vida;
    }

    int getResistencia(){
        return resistencia;
    }

    string getNombre(){
        return nombre;
    }
    void mostrarStats(){
    cout << "\n===== " << nombre << " =====\n";
    cout << "Vida: " << vida << endl;
    cout << "Resistencia: " << resistencia << endl;
    cout << "Daño: " << danio << endl;
}
    void mostrarVida(){
        cout << nombre 
             << " - Vida: " << vida 
             << " | Resistencia: " << resistencia 
             << endl;
}
    int getVidaMaxima(){
        return vidaMaxima;
    }
};
class personaje : public Combatiente {
public:
    personaje(string n, int v, int r, int d)
        : Combatiente(n, v, r, d)
    {
    }
};
class enemigo : public Combatiente {
public:
    enemigo(string n, int v, int r, int d)
        : Combatiente(n, v, r, d)
    {
    }
};

void separador(){
    cout<<"\n-------------------------\n";
}

void salto(){
    cout<<endl;
    cout<<endl;
}

void mostrarEstado(Combatiente &a, Combatiente &b){
    cout << "\nEstado actual:\n";
    a.mostrarVida();
    b.mostrarVida();
}

int main(){
    string nombre, respuesta,nombreClase;
    int edad, clase, numEnemigo,vida,resistencia,danio;
    
    cout<<"CREA TU PERSONAJE";
    
    salto();
    
    cout<<"¿Cual es tu nombre?"<<endl;
    cin>>nombre;
    cout<<"¿Cual es tu edad?"<<endl;
    cin>>edad;
    if(edad < 10){
    cout << "Eres demasiado joven para jugar.\n";
    return 0;
    }
    
    salto();
    
    cout<<"Antes de seguir debes elegir una clase:"<<endl;
    cout<<"1 -Mago"<<endl;
    cout<<"2 -Guerrero"<<endl;
    cout<<"3 -Tanque"<<endl;
    cout<<"4 -Sanador"<<endl;
    salto();
    cout<<"selector de clase: ";
    cin>>clase;

    while(clase < 1 || clase >4){
        cout<<"ERROR: vuelve a elegir. ";
        cin>>clase;
    }
    separador();
    switch(clase){
    case 1:
        cout<<"Elegiste MAGO\n";
        nombreClase = "MAGO";
        vida = 50;
        resistencia = 60;
        danio = 80;
        break;

    case 2:
        cout<<"Elegiste GUERRERO\n";
        nombreClase = "GUERRERO";
        vida = 80;
        resistencia = 60;
        danio = 70;
        break;

    case 3:
        cout<<"Elegiste TANQUE\n";
        nombreClase = "TANQUE";
        vida = 120;
        resistencia = 50;
        danio = 50;
        break;

    case 4:
        cout<<"Elegiste SANADOR\n";
        nombreClase = "SANADOR";
        vida = 70;
        resistencia = 70;
        danio = 40;
        break;

    default:
        cout<<"Clase invalida\n";
        return 0;
    }
    personaje jugador(nombreClase, vida, resistencia, danio);
    jugador.mostrarStats();
    separador();
    
    cout<<"Tienes que luchar contra: ";
   
    separador();
    
    srand(time(nullptr));
    numEnemigo=rand()%3 + 1;
    
    if(numEnemigo==1){
        nombreClase = "OGRO";
        vida = 100;
        resistencia = 35;
        danio = 40;
    }
    if(numEnemigo==2){
        nombreClase = "MAGO OSCURO";
        vida = 70;
        resistencia = 55;
        danio = 60;
    }
    if(numEnemigo==3){
        nombreClase = "GUERRERO CORRUPTO";
        vida = 90;
        resistencia = 60;
        danio = 50;
    }
    
    personaje enemigo(nombreClase, vida, resistencia, danio);
    enemigo.mostrarStats();
    separador();

    salto();
    cout<<"=====A LUCHAR=====";
    int comienzo;
    bool enemigoAtaca = false;
    comienzo=rand()%2;
    
    if(comienzo == 0){
    enemigoAtaca = true;
    }
    
    while(jugador.getVida() > 0 && enemigo.getVida() > 0){
    cout << "\n============================\n";
    cout << "Estado actual:\n";
    jugador.mostrarVida();
    enemigo.mostrarVida();
    cout << "============================\n";
    
        if(enemigoAtaca==false){ 
        cout << "\n--- TU TURNO ---\n";
        cout << "1) Atacar\n";
        cout << "2) Defender\n";

        int opcion;
        cin >> opcion;

        if(opcion == 1){
            jugador.atacar(enemigo);
        }
        else if(opcion == 2){
            jugador.defender();
            cout << jugador.getNombre() << " se defendió.\n";
        }
       enemigoAtaca = true; 
    }
    
        else{ 
        cout << "\n--- TURNO DEL ENEMIGO ---\n";

        if(enemigo.getResistencia() < 15){
            enemigo.defender();
            cout << enemigo.getNombre() << " se defendió.\n";
        }
        else{
            double porcentajeVida =
                (double)enemigo.getVida() /
                enemigo.getVidaMaxima() * 100;

            int decision = rand() % 100 + 1;
            if(porcentajeVida < 40){
                if(decision <= 50)
                    enemigo.atacar(jugador);
                else{
                    enemigo.defender();
                    cout << enemigo.getNombre() << " se defendió.\n";
                }
            }
            else{
                if(decision <= 70)
                    enemigo.atacar(jugador);
                else{
                    enemigo.defender();
                    cout << enemigo.getNombre() << " se defendió.\n";
                }
            }
        }
        enemigoAtaca= false;  
    }
    }
    if(jugador.getVida() <= 0){
        cout << "\n💀 Has sido derrotado...\n";
    }   
    else if(enemigo.getVida() <= 0){
        cout << "\n🏆 ¡Has ganado la batalla!\n";
    }
return 0;
}
