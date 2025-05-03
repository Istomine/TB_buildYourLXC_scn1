# Scénario 1 – Adversaire dans le cadre de l'évaluation d’un conteneur self-made et de LXC

Dans ce scénario, l’adversaire est représenté par un programme malveillant qui se fait passer pour un antivirus classique. En réalité, ce programme cherche à extraire des informations sensibles depuis le système hôte, telles que :

- Le contenu du fichier /etc/shadow
- Le contenu du fichier /etc/passwd
- Toutes les clés SSH présentes dans le répertoire .ssh de chaque utilisateur
- La liste des noms de fichiers dans le répertoire ~/Documents

Pour rappel, ce scénario repose sur une isolation du système de fichiers mise en œuvre à l’aide des éléments suivants :

- Un système de fichiers de base Ubuntu
- Une isolation via les namespaces utilisateur, mount, PID
- L’utilisation de pivot_root pour changer la racine du système de fichiers
- Une comparaison avec l’approche chroot
- Le UID mapping (mappage des identifiants utilisateurs)

Si la configuration du conteneur self-made est correctement réalisée, le programme malveillant ne devrait pas être en mesure d’accéder à ces données sensibles.

# Cas de test

Le programme est exécuté dans cinq configurations différentes, chacune illustrant un niveau d’isolation croissant :

- Exécution sur l’hôte en tant qu’utilisateur standard, sans isolation
- Exécution sur l’hôte en tant que superutilisateur (sudo), sans isolation
- Exécution dans une chroot jail sur l’hôte, en tant que superutilisateur
- Exécution dans le conteneur self-made, après mise en place de l’isolation, mais avant le changement vers un utilisateur moins privilégié (juste avant les deux dernières commandes du script final de laboratoire)
- Exécution dans le conteneur self-made en tant qu’utilisateur non privilégié, après isolation complète

Ces cas permettent de démontrer l’efficacité progressive des mécanismes d’isolation face au programme malveillant.

# Intégration dans Labtainer et autocorrection

Ce programme constitue l’élément central du mécanisme d’autocorrection dans l’environnement Labtainer. En plus de collecter des données sensibles (à titre de test), il met en œuvre plusieurs mécanismes de vérification :

- Vérification de la présence du fichier /etc/shadow pour distinguer les exécutions avec privilèges élevés
- Identification du contexte d’exécution (hôte ou conteneur) par la détection des utilisateurs host_SuperAdmin et container_superAdmin dans /etc/shadow ou /etc/passwd
- Détection du type d’utilisateur actif par la présence de clés SSH de type rsa pour l’utilisateur base, et ed25519 pour l’utilisateur self

Le programme réalise également des contrôles techniques supplémentaires :

- Un test d’évasion de chroot permet de s’assurer que pivot_root et les montages sont correctement effectués ; en cas d’échec, un accès à l’hôte resterait possible
- Vérification que l’ancien répertoire racine (old_root) est vide, ce qui confirme que le démontage final a bien été réalisé
- Contrôle du PID du processus principal, qui doit être égal à 1 dans un espace de noms PID correctement configuré
- Lecture de /proc/self/uid_map pour valider l’utilisation d’un user namespace et la mise en place correcte du mappage des UID
- Lecture de /proc/self/gid_map pour valider l’utilisation d’un user namespace et la mise en place correcte du mappage des GID

# Sortie du programme

Chaque exécution génère un fichier de sortie nommé resultat_NUMERO.txt, où le numéro correspond au cas de configuration. Ces fichiers permettent une comparaison claire entre les différents niveaux d’isolation testés.
