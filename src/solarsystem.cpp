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

SolarSystem::SolarSystem(const std::string& n,const vector<Object>& objs): name(n), objects(objs) {
    this->name=n;
    this->objects=objs;
}

void SolarSystem::printProgress(double percentage) {
    int val = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}
static size_t writeCallback(void *contents, size_t size, size_t nmemb, string *data) {
    size_t totalSize = size * nmemb;
    data->append((char*)contents, totalSize);
    return totalSize;
}

void SolarSystem::solve(string algo, double h,double t){
    //donne la positon de la terre et du soleil à t
    for (Object obj : objects) {
        string name = obj.getName() + ".csv";
        if (std::remove(name.c_str()) != 0) {
        std::cout << "Le fichier " << name << " n'existe pas ou n'a pas pu être supprimé." << std::endl;
    } else {
        std::cout << "Le fichier " << name << " a été supprimé avec succès." << std::endl;
    }
    }

    double steps=t/h;

    transform(algo.begin(), algo.end(), algo.begin(), ::tolower);

    for(int i=0;i<=steps+1;i++)
    {
        printProgress(i / steps);
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
            else{
                std::cout << "l'algorithme n'existe pas" << std::endl;
            }
            objects[j].computePotentialEnergy(subobjects);
            objects[j].clearPotentialEnergy();

        }

    }
}

void SolarSystem::exportdata(Object obj){
    std::ofstream outfile;
    string name = obj.getName() + ".csv";
    outfile.open(name, std::ios_base::app);
    outfile << obj.getName() << " " << obj.getPosition()[0] << " " 
    << obj.getPosition()[1] << " " << obj.getPosition()[2] << " " 
    << obj.getSpeed()[0] << " " 
    << obj.getSpeed()[1] << " " << obj.getSpeed()[2] << " " << obj.totalEnergy() << std::endl;
    outfile.close();
}

void SolarSystem::verlet(Object &obj1, std::vector<Object> objects, double h)
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
        position[k] += vitesse[k]*h+(1/2)*obj1.getAcceleration()[k]*(h*h);
        }
obj1.setPosition(position);
obj1.computeAcceleration(objects);
for(int k=0;k<=2;k++)
        {
        vitesse[k] += (acceleration[k] + obj1.getAcceleration()[k])*h/2;
        }
obj1.setSpeed(vitesse);

}

void SolarSystem::RK4(Object &obj1, std::vector<Object> objects, double h)
{
std::vector<double>position(3);
std::vector<double>positioninit = obj1.getPosition();
std::vector<double>vitesse = obj1.getSpeed();
std::vector<double>vitesseinit = obj1.getSpeed();
std::vector<double>force(3);

std::vector<double> k0(3);
std::vector<double> l0(3);

std::vector<double> k1(3);
std::vector<double> l1(3);

std::vector<double> k2(3);
std::vector<double> l2(3);

std::vector<double> k3(3);
std::vector<double> l3(3);

obj1.computeAcceleration(objects);

for (int k=0;k<=2;k++)
        {
        k0[k] = vitesse[k];
        l0[k] = obj1.getAcceleration()[k];
        }

obj1.setSpeed(k0);

for(int k=0;k<=2;k++)
        {
        position[k] = positioninit[k] + obj1.getSpeed()[k]*h/2;
        vitesse[k] = vitesseinit[k] + l0[k]*h/2;
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
        position[k] = positioninit[k] + obj1.getSpeed()[k]*h/2;
        vitesse[k] = vitesseinit[k] + l1[k]*h/2;
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
        position[k] = positioninit[k] + (k0[k] + 2*k1[k] + 2*k2[k] + k3[k])*h/6;
        vitesse[k] = vitesseinit[k] + (l0[k] + 2*l1[k] + 2*l2[k] + l3[k])*h/6;
        }

obj1.setPosition(position);
obj1.setSpeed(vitesse);



}

bool SolarSystem::isStar(Object* obj) {
    return dynamic_cast<Object*>(obj) != nullptr;

}

void SolarSystem::addObjectFromHorizons(string name) {
        transform(name.begin(), name.end(), name.begin(), ::tolower);
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

double SolarSystem::processMass(const string& response) {
        regex GMPattern("GM[,\\s*][(\\s*]km\\^3.s\\^2[\\s+)]\\s+=\\s+(\\d+.\\d+)");
        smatch GMMatches;
        if (regex_search(response, GMMatches, GMPattern)) {
            double GM = stod(GMMatches[1].str())*pow(10,9);
            return GM/6.67e-11;
        } else {
            cerr << "GM non trouvée." << endl;
            return 0.0;
        }
    }

    vector<double> SolarSystem::processSpeed(const string& response) {
        // Expression régulière pour extraire les coordonnées des vecteurs de vitesse
        regex speedPattern("VX\\s*=\\s*(-?\\d+\\.\\d+(?:E[+-]\\d+)?)\\s+VY\\s*=\\s*(-?\\d+\\.\\d+(?:E[+-]\\d+)?)\\s+VZ\\s*=\\s*(-?\\d+\\.\\d+(?:E[+-]\\d+)?)");
        smatch speedMatches;
        if (regex_search(response, speedMatches, speedPattern)) {
            vector<double> speed;
            for (int i = 1; i <= 3; ++i) {
                speed.push_back(stod(speedMatches[i].str())*1000);
            }
            return speed;
        } else {
            cerr << "Aucune correspondance trouvée pour les coordonnées de vitesse." << endl;
            return vector<double>(3);
        }
    }

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

    std::vector<Object> SolarSystem::getObjects() {
        return objects;
    }