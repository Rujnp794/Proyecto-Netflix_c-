#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct Pelicula {
    string nombre;
    int duracion; //en minutos
    int cant_generos;
    string generos[100];
    int ano_estreno;
};

struct Capitulo{
    string nombre;
    int duracion; //en minutos
    int temporada;
};

struct Serie{
    string nombre;
    int num_temporadas;
    int cant_generos;
    string generos[100];
    int cant_capitulos;
    Capitulo capitulos[100];
};

//Declaracion Funciones

int leerPeliculas(string nombre_archivo, Pelicula peliculas[]);
int leerSeries(string nombre_archivo, Serie series[]);
void crearPelicula(Pelicula peliculas[]);
void crearSerie(Serie series[]);
bool sonIgualesSinMayusculas(string str1,string str2);
void AgregarCapitulo(Serie series[]);
bool existeSerie(string nombre_serie , Serie series[]);

int main() {
    int opcion = 0, cant_peliculas = 0, cant_series = 0;
    string nombre_archivo;
    Pelicula peliculas[100];
    Serie series[100];

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
            cin >> nombre_archivo;
            cant_peliculas = leerPeliculas(nombre_archivo, peliculas);
        }
        break;
    case 2:
        {
            cout << "Digite el nombre del archivo de series." << endl;
            cin >> nombre_archivo;
            cant_series = leerSeries(nombre_archivo, series);
        }
        break;
    default:
        cout << "Opcion no valida" << endl;
        break;
    case 3:
        {
            Pelicula peliculas[100];
            crearPelicula(peliculas, cant_peliculas);
            cant_peliculas++;
        }
    }

}

//Funcion para leer las peliculas del archivo
int leerPeliculas(string nombre_archivo, Pelicula peliculas[]) {
    ifstream archivo(nombre_archivo);
    string linea;
    int contador = 0;

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo " << nombre_archivo << endl;
        return;
    }

    // Leer la primera línea que contiene los encabezados
    getline(archivo, linea);

    // Leer cada línea del archivo
    while (getline(archivo, linea) ) {
        stringstream ss(linea);
        string nombre, duracion, ano_estreno, genero;
        int cant_generos = 0;

        // Leer los datos separados por comas
        getline(ss, nombre, ',');
        getline(ss, duracion, ',');
        getline(ss, ano_estreno, ',');

        // Leer el resto de la línea para obtener los generos
        while(getline(ss, genero, ',')){
            peliculas[contador].generos[cant_generos] = genero;
            cant_generos++;
        }

        // Crear una instancia de Pelicula y agregarla al arreglo
        peliculas[contador].nombre = nombre;
        peliculas[contador].duracion = stoi(duracion);
        peliculas[contador].ano_estreno = stoi(ano_estreno);  
        peliculas[contador].cant_generos = cant_generos;
    
        contador++;
    }

    archivo.close();

    return contador;
}

//Funcion para leer las series del archivo
int leerSeries(string nombre_archivo, Serie series[]) {
    ifstream archivo(nombre_archivo);
    string linea;
    int contador = 0;

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo " << nombre_archivo << endl;
        return;
    }

    // Leer la primera línea que contiene los encabezados
    getline(archivo, linea);

    // Leer cada línea del archivo
    while (getline(archivo, linea) ) {
        stringstream ss(linea);
        string nombre, num_temporadas, genero;
        int cant_generos = 0;

        // Leer los datos separados por comas
        getline(ss, nombre, ',');
        getline(ss, num_temporadas, ',');
        
        // Leer el resto de la línea para obtener los generos
        while(getline(ss, genero, ',')){
            series[contador].generos[cant_generos] = genero;
            cant_generos++;
        }

        // Crear una instancia de Serie y agregarla al arreglo
        series[contador].nombre = nombre;
        series[contador].num_temporadas = stoi(num_temporadas);
        series[contador].cant_generos = cant_generos;

        contador++;
    }

    archivo.close();

    return contador;
}

// Crear una pelicula
void crearPelicula(Pelicula peliculas[], int cant_peliculas) {
    // Crear una instancia de Pelicula
    Pelicula pelicula;

    // Solicitar un nombre válido para la pelicula
    do {
        cout << "Ingrese el nombre de la pelicula: ";
        cin >> pelicula.nombre;
    } while (!nombreValidoPelicula(pelicula.nombre, peliculas, cant_peliculas));

    // Solicitar una duración válida para la pelicula
    do {
        cout << "Ingrese la duración de la pelicula: ";
        cin >> pelicula.duracion;
    } while (pelicula.duracion <= 0);

    // Solicitar una cantidad de géneros válida para la pelicula
    do {
        cout << "Ingrese la cantidad de géneros de la pelicula: ";
        cin >> pelicula.cant_generos;
    } while (pelicula.cant_generos <= 0);

    // Solicitar los géneros de la pelicula
    for(int i = 0; i < pelicula.cant_generos; i++){
        cout << "Ingrese el genero " << i+1 << " de la pelicula: ";
        cin >> pelicula.generos[i];
    }

    // Solicitar un año de estreno válido para la pelicula
    do {
        cout << "Ingrese el año de estreno de la pelicula: ";
        cin >> pelicula.ano_estreno;
    } while (pelicula.ano_estreno <= 0);
    
    // Todos los datos de la pelicula son validos, entonces podemos agregarla al arreglo
    peliculas[cant_peliculas] = pelicula;
}

// Función para validar el nombre de la pelicula
bool nombreValidoPelicula(string nombre, Pelicula peliculas[], int cant_peliculas) {
    if (nombre.empty()) {
        cout << "EL NOMBRE DE LA PELICULA NO PUEDE ESTAR VACIO, INTENTE DE NUEVO." << endl;
        return false;
    }
    // Comparar el nombre de la pelicula con los nombres de las peliculas existentes (en minúsculas)
    for (int i = 0; i < cant_peliculas; i++) {
        if (sonIgualesSinMayusculas(peliculas[i].nombre, nombre)) {
            cout << "ESTA PELICULA YA EXISTE, INTENTE DE NUEVO." << endl;
            return false;
        }
    }
    return true;
}

// Función para comparar dos strings sin importar mayúsculas y minúsculas
bool sonIgualesSinMayusculas(string str1, string str2) {
    if (str1.length() != str2.length()) {
        return false;
    }
    for (int i = 0; i < str1.length(); i++) {
        if (tolower(str1[i]) != tolower(str2[i])) {
            return false;
        }
    }
    return true;
}

// Crear una serie
void crearSerie(Serie series[], int cant_series) {
    // Crear una instancia de Serie
    Serie serie;

    // Solicitar un nombre válido para la serie
    do {
        cout << "Ingrese el nombre de la serie: ";
        cin >> serie.nombre;
    } while (!nombreValidoSerie(serie.nombre, series, cant_series));

    // Solicitar un número de temporadas válido para la serie
    do {
        cout << "Ingrese el número de temporadas de la serie: ";
        cin >> serie.num_temporadas;
    } while (serie.num_temporadas <= 0);

    // Solicitar los géneros de la serie y preguntar si desea agregar más
    int opcion = 0, i = 0;
    do {
        cout << "Ingrese el genero " << i+1 << " de la serie: ";
        cin >> serie.generos[i];
        i++;
        cout << "Desea agregar otro genero? (1. Si, 2. No)" << endl;
        cin >> opcion;
    } while (opcion == 1);
    serie.cant_generos = i;
    serie.cant_capitulos = 0;

    // Todos los datos de la serie son validos, entonces podemos agregarla al arreglo
    series[cant_series] = serie;
}

// Función para validar el nombre de la serie
bool nombreValidoSerie(string nombre, Serie series[], int cant_series) {
    if (nombre.empty()) {
        cout << "EL NOMBRE DE LA SERIE NO PUEDE ESTAR VACIO, INTENTE DE NUEVO." << endl;
        return false;
    }
    // Comparar el nombre de la serie con los nombres de las series existentes (en minúsculas)
    for (int i = 0; i < cant_series; i++) {
        if (sonIgualesSinMayusculas(series[i].nombre, nombre)) {
            cout << "ESTA SERIE YA EXISTE, INTENTE DE NUEVO." << endl;
            return false;
        }
    }
    return true;
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
            if(sonIgualesSinMayusculas(series[i].nombre, nombre_serie)){
                for(int j = 0; j < 100; j++){
                    if(series[i].capitulos[j].nombre == ""){
                        series[i].capitulos[j].nombre = nombre_capitulo;
                        series[i].capitulos[j].duracion = duracion;
                        series[i].capitulos[j].temporada = temporada;
                        break;
                    }
                }
                series[i].cant_capitulos++;
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
        if(sonIgualesSinMayusculas(series[i].nombre, nombre_serie)){
            return true;
        }
    }
    return false;
}

