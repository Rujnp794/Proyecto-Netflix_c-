#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

struct Pelicula {
    string Nombre;
    int Duracion; //en minutos
    string Genero;
    int ano_estreno;
};

struct Capitulo{
    string Nombre;
    int Duracion; //en minutos
    int Temporada;
};

struct Serie{
    string Nombre;
    int Cant_capitulos;
    int Num_temporadas;
    string Genero;
    Capitulo capitulos[100];
};

//Declaracion Funciones

void leerPeliculas(string nombreArchivo, Pelicula peliculas[], int numPeliculas);
void leerSeries(string nombreArchivo, Serie series[], int numSeries);
void crearPelicula(Pelicula peliculas[]);
void crearSeries(Serie series[]);
bool sonIgualesSinMayusculas(string str1,string str2);
void AgregarCapitulo(Serie series[]);
bool existeSerie(string nombre_serie , Serie series[]);

int main() {
    int opcion = 0;
    string nombreArchivo;

    cout << "Bienvenido a Netflix" << endl;
    cout << "¿Que desea hacer?" << endl;   
    cout << "1. Cargar peliculas" << endl;
    cout << "2. Cargar series" << endl;
    cout << "3. Crear pelicula" << endl;
    cout << "4. Crear serie" << endl;
    cout << "5. Agregar capitulo a serie" << endl;
    cout << "6. Salir" << endl;

    cin >> opcion;
    switch(opcion){
    case 1:
        {
            cout << "Digite el nombre del archivo de peliculas." << endl;
            cin >> nombreArchivo;
            Pelicula peliculas[100];
            leerPeliculas(nombreArchivo, peliculas);
        }
        break;
    case 2:
        {
            cout << "Digite el nombre del archivo de series." << endl;
            cin >> nombreArchivo;
            Serie series[100];
            leerSeries(nombreArchivo, series);
        }
        break;
    default:
        cout << "Opcion no valida" << endl;
        break;
    case 3:
        {
            Pelicula peliculas[100];
            crearPelicula(peliculas);
        }
    }

}

//Funcion para leer las peliculas del archivo

void leerPeliculas(string nombreArchivo, Pelicula peliculas[]) {
    ifstream archivo(nombreArchivo);
    string linea;
    int contador = 0;

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    // Leer la primera línea que contiene los encabezados
    getline(archivo, linea);

    // Leer cada línea del archivo
    while (getline(archivo, linea) ) {
        stringstream ss(linea);
        string nombre, duracion, ano_estreno, genero;

        // Leer los datos separados por comas
        getline(ss, nombre, ',');
        getline(ss, duracion, ',');
        getline(ss, ano_estreno, ',');
        getline(ss, genero, ',');

        // Crear una instancia de Pelicula y agregarla al arreglo
        peliculas[contador].Nombre = nombre;
        peliculas[contador].Duracion = stoi(duracion);
        peliculas[contador].ano_estreno = stoi(ano_estreno);  
        peliculas[contador].Genero = stoi(genero);
    
        contador++;
    }

    archivo.close();
}

//Funcion para leer las series del archivo

void leerSeries(string nombreArchivo, Serie series[]) {
    ifstream archivo(nombreArchivo);
    string linea;
    int contador = 0;

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    // Leer la primera línea que contiene los encabezados
    getline(archivo, linea);

    // Leer cada línea del archivo
    while (getline(archivo, linea) ) {
        stringstream ss(linea);
        string nombre, cant_capitulos, num_temporadas, genero;

        // Leer los datos separados por comas
        getline(ss, nombre, ',');
        getline(ss, cant_capitulos, ',');
        getline(ss, num_temporadas, ',');
        getline(ss, genero, ',');

        // Crear una instancia de Serie y agregarla al arreglo
        series[contador].Nombre = nombre;
        series[contador].Cant_capitulos = stoi(cant_capitulos);
        series[contador].Num_temporadas = stoi(num_temporadas);
        series[contador].Genero = stoi(genero);


        contador++;
    }

    archivo.close();
}

// Crear una pelicula

void crearPelicula(Pelicula peliculas[]) {
    string nombre;
    int duracion = 0;
    string genero;
    int ano_estreno = 0;
    int opcion = 0;
    bool valida = true;
    // Solicitar los datos de la pelicula al usuario
    cout<<"Ingrese el nombre de la pelicula: ";
    cin>>nombre;
    cout<<"Ingrese la duracion de la pelicula: ";
    cin>>duracion;
    cout<<"Ingrese el genero de la pelicula: ";
    cin>>genero;
    cout<<"Ingrese el año de estreno de la pelicula: ";
    cin>>ano_estreno;
    // Crear una instancia de Pelicula
    Pelicula pelicula;
    // Inicializar los atributos de la pelicula
    pelicula.Nombre = nombre;
    pelicula.Duracion = duracion;
    pelicula.Genero = genero;
    pelicula.ano_estreno = ano_estreno;

    //Revisar si la pelicula ya existe en la lista de peliculas
    for(int i = 0; i < 100; i++){
        if(sonIgualesSinMayusculas(peliculas[i].Nombre, nombre)){
            cout<<"La pelicula ya existe en la lista de peliculas"<<endl;
            valida = false;
        }
    }
    
    //Validar que no tenga datos raros o negativos

    if(duracion < 0 || ano_estreno < 0 || nombre.empty()){
        cout<<"LOS DATOS INGRESADOS SON INCORRECTOS, INTENTE DE NUEVO."<<endl;
        valida = false;
    }
    // si la pelicula es valida en cualquier aspecto ahi si se agrega al arreglo
    if(valida){
        // Agregar la pelicula al arreglo de peliculas en la primera posicion disponible si la pelicula fue valida
        for(int i = 0; i < 100; i++){
            if(peliculas[i].Nombre == ""){
                peliculas[i] = pelicula;
                break;
            }
        }
        cout<<"La pelicula fue agregada exitosamente"<<endl;
    }
}

//funcion para validar si dos strings son iguales sin importar mayusculas
bool sonIgualesSinMayusculas(string str1,string str2) {
    if (str1.size() != str2.size()) {
        return false;
    }
    for (size_t i = 0; i < str1.size(); ++i) {
        if (tolower(str1[i]) != tolower(str2[i])) {
            return false;
        }
    }
    return true;
}

// Crear una serie

void crearSeries(Serie series[]) {
    string nombre;
    int cant_capitulos = 0;
    int num_temporadas = 0;
    string genero;
    int opcion = 0;
    bool valida = true;
    // Solicitar los datos de la serie al usuario
    cout<<"Ingrese el nombre de la serie: ";
    cin>>nombre;
    cout<<"Ingrese la cantidad de capitulos de la serie: ";
    cin>>cant_capitulos;
    cout<<"Ingrese el numero de temporadas de la serie: ";
    cin>>num_temporadas;
    cout<<"Ingrese el genero de la serie: ";
    cin>>genero;
    // Crear una instancia de Serie
    Serie serie;
    // Inicializar los atributos de la serie
    serie.Nombre = nombre;
    serie.Cant_capitulos = cant_capitulos;
    serie.Num_temporadas = num_temporadas;
    serie.Genero = genero;

    //Revisar si la serie ya existe en la lista de series
    for(int i = 0; i < 100; i++){
        if(sonIgualesSinMayusculas(series[i].Nombre, nombre)){
            cout<<"La serie ya existe en la lista de series"<<endl;
            valida = false;
        }
    }
    
    //Validar que no tenga datos raros o negativos
    if(cant_capitulos < 0 || num_temporadas < 0 || nombre.empty()){
        cout<<"LOS DATOS INGRESADOS SON INCORRECTOS, INTENTE DE NUEVO."<<endl;
        valida = false;
    }

    // si la pelicula es valida en cualquier aspecto ahi si se agrega al arreglo
    if(valida){
        // Agregar la serie al arreglo de series en la primera posicion disponible si la serie fue valida
        for(int i = 0; i < 100; i++){
            if(series[i].Nombre == ""){
                series[i] = serie;
                break;
            }
        }
        cout<<"La serie fue agregada exitosamente"<<endl;
    }
}

//Añadir un nuevo capitulo a una serie que ya existe

void AgregarCapitulo(Serie series[]){
    string nombre_serie;
    string nombre_capitulo;
    int duracion = 0;
    int temporada = 0;
    bool parar = false;
    int opcion = 0;
    cout<<"Ingrese el nombre de la serie a la que desea agregar un capitulo: ";
    cin>>nombre_serie;
    if(nombre_serie.empty()){
        cout<<"El nombre de la serie no puede estar vacio"<<endl;
        return;
    }
    else if(!existeSerie(nombre_serie , series)){
        cout<<"La serie no existe en la lista de series"<<endl;
        return;
    }
    //Digitar datos del capitulo
    while(!parar){
    cout<<"Digite el nombre del capitulo: ";
    cin>>nombre_capitulo;
    cout<<"Digite la duracion del capitulo: ";
    cin>>duracion;
    cout<<"Digite la temporada del capitulo: ";
    cin>>temporada;

    //Validar que no tenga datos raros o negativos
    if(duracion < 0 || temporada < 0 || nombre_capitulo.empty()){
        cout<<"LOS DATOS INGRESADOS SON INCORRECTOS, INTENTE DE NUEVO."<<endl;
    }
    else{
        cout<<"El capitulo fue agregado exitosamente"<<endl;
        parar = true;
        //Agregar el capitulo a la serie
        for(int i = 0; i < 100; i++){
            if(sonIgualesSinMayusculas(series[i].Nombre, nombre_serie)){
                for(int j = 0; j < 100; j++){
                    if(series[i].capitulos[j].Nombre == ""){
                        series[i].capitulos[j].Nombre = nombre_capitulo;
                        series[i].capitulos[j].Duracion = duracion;
                        series[i].capitulos[j].Temporada = temporada;
                        break;
                    }
                }
                series[i].Cant_capitulos++;
            }
            
        }
    }
    cout << "Desea agregar otro capitulo? (1. Si, 2. No)" << endl;
    cin >> opcion;
    if(opcion == 2){
        parar = true;
    }
    }
}

//Funcion para verificar si una serie existe en la lista de series

bool existeSerie(string nombre_serie , Serie series[]){
    for(int i = 0; i < 100; i++){
        if(sonIgualesSinMayusculas(series[i].Nombre, nombre_serie)){
            return true;
        }
    }
    return false;
}

