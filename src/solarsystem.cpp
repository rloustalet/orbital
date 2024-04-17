#include <vector>
#include <cmath>
#include <iostream>
#include <string>
#include <functional>
#include "solarsystem.h"
#include <fstream>
#include <curl/curl.h>
#include <regex>

using namespace std;

/**
 * Constructor for SolarSystem class.
 *
 * @param n The name of the solar system
 * @param objs Vector of objects in the solar system
 */
SolarSystem::SolarSystem(const string& n): name(n) {
    this->name=n;
}

/**
 * Print the progress bar based on the given percentage.
 *
 * @param percentage the percentage of progress completed
 *
 * @return void
 *
 * @throws None
 */
void SolarSystem::printProgress(double percentage, int iterations_so_far, int total_iterations) {
    // Calcul des valeurs pour la barre de progression
    int val = (int)(percentage * 100);
    int lpad = (int)(percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;

    // Affichage de la barre de progression
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);

    // Calcul du temps écoulé
    static clock_t start_time = 0;
    if (start_time == 0) {
        start_time = clock();
    }
    clock_t current_time = clock();
    double elapsed_seconds = (double)(current_time - start_time) / CLOCKS_PER_SEC;

    // Calcul du temps moyen par itération
    double average_time_per_iteration = elapsed_seconds / iterations_so_far;

    // Calcul du temps restant total
    double total_predicted_time = average_time_per_iteration * total_iterations;

    // Affichage du temps écoulé et du temps restant
    printf(" %.2fs/%.2fs, %.0fms/iter", elapsed_seconds, total_predicted_time, 1000*average_time_per_iteration);
    if (iterations_so_far == total_iterations) {
        printf("\n");
    }
}
/**
 * Writes data to a string and returns the size of the data written.
 *
 * @param contents pointer to the data to be written
 * @param size size of each element to be written
 * @param nmemb number of elements to be written
 * @param data pointer to the string to which the data is written
 *
 * @return total size of the data written
 */
static size_t writeCallback(void *contents, size_t size, size_t nmemb, string *data) {
    size_t totalSize = size * nmemb;
    data->append((char*)contents, totalSize);
    return totalSize;
}

/**
 * Gives the position of the Earth and the Sun at time t.
 *
 * @param algo the algorithm to be used
 * @param h the step size
 * @param t the time
 *
 * @return description of return value
 *
 * @throws ErrorType description of error
 */
void SolarSystem::solve(string algo, double h,double t){
    //donne la positon de la terre et du soleil à t
    string filename = "results/" + name + ".csv";
    if (remove(filename.c_str()) != 0) {
        cout << "Le fichier " << filename << " n'existe pas ou n'a pas pu être supprimé." << endl;
    }
    else {
        cout << "Le fichier " << filename << " a été supprimé avec succès." << endl;
    }
    for (Object obj : objects) {
        string filename ="results/" + obj.getName() + ".csv";
        if (remove(filename.c_str()) != 0) {
        cout << "Le fichier " << filename << " n'existe pas ou n'a pas pu être supprimé." << endl;
    } else {
        cout << "Le fichier " << filename << " a été supprimé avec succès." << endl;
    }
    }

    double steps=t/h;
    transform(algo.begin(), algo.end(), algo.begin(), ::tolower);

    for(double i=0;i<=steps+1;i++)
    {
        printProgress(i / steps, i, steps+1);
        for (int j=0;j<objects.size();j++) {
            vector<Object> subobjects = objects;
            subobjects.erase(subobjects.begin() + j);
            exportdata(objects[j]);
            if (algo == "rk4") {
                RK4(objects[j], subobjects, h);
            }
            else if (algo == "verlet") {
                verlet(objects[j], subobjects, h);
            }
            else if (algo == "euler") {
                euler(objects[j], subobjects, h);
            }
            else{
                cout << "l'algorithme n'existe pas" << endl;
            }
            objects[j].computeArea(h);
            objects[j].computePotentialEnergy(subobjects);
            objects[j].clearPotentialEnergy();

        }
        ofstream outfile;
        string filename = "results/" + name + ".csv";
        outfile.open(filename, ios_base::app);
        outfile << totalEnergy() << endl;
        outfile.close();


    }
}

/**
 * Exports data of the given object to a CSV file.
 *
 * @param obj the object to export
 *
 * @return void
 *
 * @throws ofstream::failure if the file opening fails
 */
void SolarSystem::exportdata(Object obj){
    ofstream outfile;
    string filename = "results/" + obj.getName() + ".csv";
    outfile.open(filename, ios_base::app);
    outfile << obj.getPosition()[0] << " " 
    << obj.getPosition()[1] << " " << obj.getPosition()[2] << " " 
    << obj.getSpeed()[0] << " " 
    << obj.getSpeed()[1] << " " << obj.getSpeed()[2] << " " << obj.totalEnergy() << 
    " " << obj.getArea() << " " << obj.normeCinematicMoment() << endl;
    outfile.close();
}

/**
 * Updates the position and speed of an object using the Euler method.
 *
 * @param obj1 The object to update
 * @param objects Other objects influencing the object
 * @param h The time step for the update
 *
 * @return void
 *
 * @throws None
 */
void SolarSystem::euler(Object &obj1, vector<Object> objects, double h)
{
vector<double>position = obj1.getPosition();
vector<double>vitesse = obj1.getSpeed();

obj1.computeAcceleration(objects);

for(int k=0;k<=2;k++)
        {
        vitesse[k] += obj1.getAcceleration()[k]*h;
        position[k] += vitesse[k]*h;
        }
obj1.setPosition(position);
obj1.setSpeed(vitesse);

}

/**
 * Perform the Verlet integration to update the position and velocity of the given object.
 *
 * @param obj1 The object for which the position and velocity are to be updated.
 * @param objects The vector of other objects affecting the given object.
 * @param h The time step for the integration.
 *
 * @return None
 *
 * @throws None
 */
void SolarSystem::verlet(Object &obj1, vector<Object> objects, double h)
{
//x(t+h)=x(t)+v(t)*h+1/2*a(t)*h**2
//v(t+h/2)=v(t)+a(t)*h/2
//a(t+h)=
//v(t+h)=v(t+h/2)+a(t+h)*h/2
vector<double>position = obj1.getPosition();
vector<double>vitesse = obj1.getSpeed();
vector<double> acceleration = obj1.getAcceleration();

for(int k=0;k<=2;k++)
        {
        position[k] += vitesse[k]*h+(0.5L)*obj1.getAcceleration()[k]*(h*h);
        }
obj1.setPosition(position);
obj1.computeAcceleration(objects);
for(int k=0;k<=2;k++)
        {
        vitesse[k] += (acceleration[k] + obj1.getAcceleration()[k])*h/2L;
        }
obj1.setSpeed(vitesse);

}

/**
 * Runge-Kutta 4th Order method implementation for solving differential equations.
 *
 * @param obj1 The main object for which the RK4 method is applied
 * @param objects Other objects influencing the main object
 * @param h The time step for the RK4 method
 *
 * @return void
 *
 * @throws None
 */
void SolarSystem::RK4(Object &obj1, vector<Object> objects, double h)
{
vector<double>position(3);
vector<double>positioninit = obj1.getPosition();
vector<double>vitesse = obj1.getSpeed();
vector<double>vitesseinit = obj1.getSpeed();
vector<double>force(3);

vector<double> k0(3);
vector<double> l0(3);

vector<double> k1(3);
vector<double> l1(3);

vector<double> k2(3);
vector<double> l2(3);

vector<double> k3(3);
vector<double> l3(3);

obj1.computeAcceleration(objects);

for (int k=0;k<=2;k++)
        {
        k0[k] = vitesse[k];
        l0[k] = obj1.getAcceleration()[k];
        }

obj1.setSpeed(k0);

for(int k=0;k<=2;k++)
        {
        position[k] = positioninit[k] + obj1.getSpeed()[k]*h/2L;
        vitesse[k] = vitesseinit[k] + l0[k]*h/2L;
        }

obj1.setPosition(position);

obj1.computeAcceleration(objects);

for(int k=0;k<=2;k++)
        {
        k1[k] = vitesse[k];
        l1[k] = obj1.getAcceleration()[k];
        }

obj1.setSpeed(k1);

for(int k=0;k<=2;k++)
        {
        position[k] = positioninit[k] + obj1.getSpeed()[k]*h/2L;
        vitesse[k] = vitesseinit[k] + l1[k]*h/2L;
        }

obj1.setPosition(position);

obj1.computeAcceleration(objects);

for(int k=0;k<=2;k++)
        {
        k2[k] = vitesse[k];
        l2[k] = obj1.getAcceleration()[k];
        }

obj1.setSpeed(k2);

for(int k=0;k<=2;k++)
        {
        position[k] = positioninit[k] + vitesse[k]*h;
        vitesse[k] = vitesseinit[k] + l2[k]*h;
        }

obj1.setPosition(position);

obj1.computeAcceleration(objects);

for(int k=0;k<=2;k++)
        {
        k3[k] =  vitesse[k];
        l3[k] = obj1.getAcceleration()[k];
        }

obj1.setSpeed(k3);

for(int k=0;k<=2;k++)
        {
        position[k] = positioninit[k] + (k0[k] + 2L*k1[k] + 2L*k2[k] + k3[k])*h/6L;
        vitesse[k] = vitesseinit[k] + (l0[k] + 2L*l1[k] + 2L*l2[k] + l3[k])*h/6L;
        }

obj1.setPosition(position);
obj1.setSpeed(vitesse);



}

/**
 * Adds an object to the Solar System based on the name provided.
 *
 * @param name the name of the object to be added
 *
 * @return void
 *
 * @throws ErrorType an error message if there is any issue with the request or processing the response
 */
void SolarSystem::addObjectFromHorizons(string name) {
        transform(name.begin(), name.end(), name.begin(), ::tolower);
        cout << "performing query for " << name << endl;
        string object_id = "0";
        if (name == "sun") {
            object_id = "10";
        } else if (name == "mercury") {
            object_id = "199";
        } else if (name == "venus") {
            object_id = "299";
        } else if (name == "earth") {
            object_id = "399";
        } else if (name == "mars") {
            object_id = "499";
        } else if (name == "jupiter") {
            object_id = "599";
        } else if (name == "saturn") {
            object_id = "699";
        } else if (name == "uranus") {
            object_id = "799";
        } else if (name == "neptune") {
            object_id = "899";
        }
        else if (name == "pluto") {
            object_id = "999";
        }
        else if (name == "moon") {
            object_id = "301";
        }
        else if (name == "ceres") {
        object_id = "1";
        } 
        else if (name == "pallas") {
            object_id = "2";
        } 
        else if (name == "vesta") {
            object_id = "4";
        } 
        else if (name == "juno") {
            object_id = "3";
        } 
        else if (name == "io") {
            object_id = "501";
        } 
        else if (name == "europa") {
            object_id = "502";
        } 
        else if (name == "ganymede") {
            object_id = "503";
        } 
        else if (name == "callisto") {
            object_id = "504";
        } 
        else if (name == "titan") {
            object_id = "606";
        } 
        else if (name == "enceladus") {
            object_id = "602";
        } 
        else if (name == "mimas") {
            object_id = "601";
        } 
        else if (name == "tethys") {
            object_id = "603";
        } 
        else if (name == "dione") {
            object_id = "604";
        } 
        else if (name == "rhea") {
            object_id = "605";
        } 
        else if (name == "hyperion") {
            object_id = "607";
        } 
        else if (name == "iapetus") {
            object_id = "608";
        } 
        else if (name == "miranda") {
            object_id = "701";
        } 
        else if (name == "ariel") {
            object_id = "702";
        } 
        else if (name == "umbriel") {
            object_id = "703";
        } 
        else if (name == "titania") {
            object_id = "704";
        } 
        else if (name == "oberon") {
            object_id = "705";
        } 
        else if (name == "triton") {
            object_id = "801";
        } 
        else if (name == "charon") {
            object_id = "901";
        } 
        else if (name == "halley") {
            object_id = "1P";
        } 
        else if (name == "borrelly") {
            object_id = "19P";
        } 
        else if (name == "tempel1") {
            object_id = "9P";
        } 
        else if (name == "chiron") {
            object_id = "2060";
        } 
        else if (name == "eros") {
            object_id = "433";
        }

        CURL *curl;
        CURLcode res;
        string response;

        // Initialisation de libcurl
        curl = curl_easy_init();
        if (curl) {
            // Définition de l'URL à laquelle faire la requête
            string url = "https://ssd.jpl.nasa.gov/api/horizons.api?format=text&COMMAND='"+ object_id +"'&OBJ_DATA='YES'&EPHEM_TYPE='VECTOR'&CENTER='500@0'&START_TIME='2000-01-01'&STOP_TIME='2000-01-02'&STEP_SIZE='25h'";
            const char* cstr = url.c_str();
            // Configuration de la requête
            curl_easy_setopt(curl, CURLOPT_URL, cstr);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

            // Exécution de la requête
            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                cerr << "Erreur lors de la requête : " << curl_easy_strerror(res) << endl;
            } else {
                // Traitement de la réponse
                double mass = processMass(response);
                vector<double> position = processPosition(response);
                vector<double> speed = processSpeed(response);
                vector<double> acceleration(3);
                Object newobj(name, position, speed, acceleration, mass);
                objects.push_back(newobj);
            }

            // Nettoyage
            curl_easy_cleanup(curl);
        } else {
            cerr << "Impossible d'initialiser libcurl" << endl;
        }
        
    }

/**
 * Process the mass of the Solar System based on the given response.
 *
 * @param response the input string containing the GM value
 *
 * @return the mass of the Solar System
 *
 * @throws None
 */
double SolarSystem::processMass(const string& response) {
        regex GMPattern("GM[(,\\s*]*km\\^3.s\\^2[\\s+)]\\s+=\\s+(\\d+.\\d+)");
        smatch GMMatches;
        if (regex_search(response, GMMatches, GMPattern)) {
            double GM = stod(GMMatches[1].str())*pow(10,9);
            return GM/6.67e-11L;
        } else {
            cerr << "GM non trouvée." << endl;
            return 0.0;
        }
    }

/**
 * Process the speed coordinates from the given response string.
 *
 * @param response the string containing the speed information
 *
 * @return a vector of doubles representing the speed coordinates
 *
 * @throws N/A
 */
vector<double> SolarSystem::processSpeed(const string& response) {
        // Expression régulière pour extraire les coordonnées des vecteurs de vitesse
        regex speedPattern("VX\\s*=\\s*(-?\\d+\\.\\d+(?:E[+-]\\d+)?)\\s+VY\\s*=\\s*(-?\\d+\\.\\d+(?:E[+-]\\d+)?)\\s+VZ\\s*=\\s*(-?\\d+\\.\\d+(?:E[+-]\\d+)?)");
        smatch speedMatches;
        if (regex_search(response, speedMatches, speedPattern)) {
            vector<double> speed;
            for (int i = 1; i <= 3; ++i) {
                speed.push_back(stod(speedMatches[i].str())*1000L);
            }
            return speed;
        } else {
            cerr << "Aucune correspondance trouvée pour les coordonnées de vitesse." << endl;
            return vector<double>(3);
        }
    }

/**
 * Regular expression to extract the coordinates of the position vectors
 *
 * @param response const reference to the response string
 *
 * @return vector<double> the processed position vector
 *
 * @throws None
 */
vector<double> SolarSystem::processPosition(const string& response) {
        // Expression régulière pour extraire les coordonnées des vecteurs de position
        regex positionPattern("X\\s*=\\s*(-?\\d+\\.\\d+(?:E[+-]\\d+)?)\\s+Y\\s*=\\s*(-?\\d+\\.\\d+(?:E[+-]\\d+)?)\\s+Z\\s*=\\s*(-?\\d+\\.\\d+(?:E[+-]\\d+)?)");
        smatch positionMatches;
        if (regex_search(response, positionMatches, positionPattern)) {
            vector<double> position;
            for (int i = 1; i <= 3; ++i) {
                position.push_back(stod(positionMatches[i].str())*1000);
            }
            return position;
        } else {
            cerr << "Aucune correspondance trouvée pour les coordonnées de position." << endl;
            return vector<double>();
        }
    }

    /**
     * Get the list of objects in the SolarSystem.
     *
     * @return the list of objects
     */
    vector<Object> SolarSystem::getObjects() {
        return objects;
    }

    /**
     * Calculate the total energy of the SolarSystem.
     *
     * @return the total energy of the SolarSystem
     *
     * @throws None
     */
    double SolarSystem::totalEnergy() {
        double energy = 0.0;
        for (Object obj : objects) {
            energy += obj.totalEnergy();
        }
        return energy;
    }

    /**
     * Adds a new object to the SolarSystem with the given name, position, speed, acceleration, and mass.
     *
     * @param name The name of the object.
     * @param position The position of the object as a vector of three double values.
     * @param speed The speed of the object as a vector of three double values.
     * @param acceleration The acceleration of the object as a vector of three double values.
     * @param mass The mass of the object.
     *
     * @throws None.
     */
    void SolarSystem::addObject(string name, vector<double> position, vector<double> speed, vector<double> acceleration, double mass){
        Object newobj(name, position, speed, acceleration, mass);
        objects.push_back(newobj);
    }

