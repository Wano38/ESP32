# 🌡️ ESP32 Temperature Monitor

Un système de surveillance de température intelligent utilisant l'ESP32 avec interface web moderne et alertes en temps réel.

## 🚀 Fonctionnalités

- 📊 Surveillance de température en temps réel
- 🌐 Interface web responsive et moderne
- 🔔 Système d'alertes visuelles et sonores
- 📈 Graphique de température en temps réel
- 📊 Statistiques détaillées (moyenne, min, max)
- 🎨 Design moderne avec animations
- 📱 Compatible mobile

## 🛠️ Composants nécessaires

- ESP32
- Capteur de température DS18B20
- LED rouge et bleue
- Buzzer
- Résistances (pull-up pour le capteur)
- Câbles de connexion

## 🔌 Configuration matérielle

| Composant | Pin ESP32 |
|-----------|-----------|
| DS18B20   | GPIO 4    |
| LED Rouge | GPIO 5    |
| LED Bleue | GPIO 18   |
| Buzzer    | GPIO 12   |

## ⚙️ Installation

1. Clonez le dépôt :
```bash
git clone https://github.com/votre-username/ESP32-Temperature-Monitor.git
```

2. Ouvrez le projet dans PlatformIO

3. Configurez vos paramètres WiFi dans `main.cpp` :
```cpp
const char* ssid = "votre_SSID";
const char* password = "votre_mot_de_passe";
```

4. Téléversez le code sur votre ESP32

## 🌐 Utilisation

1. Connectez-vous au réseau WiFi de l'ESP32
2. Ouvrez un navigateur et accédez à l'adresse IP de l'ESP32
3. L'interface web s'affiche avec :
   - Température actuelle
   - Graphique en temps réel
   - Statistiques
   - Alertes visuelles

## 🚨 Alertes

- 🔵 Température < 0°C : LED bleue clignotante + bip de déconnexion
- 🟢 Température normale : LED bleue allumée
- 🔴 Température > 28.5°C : LED rouge allumée + alarme sonore

## 📊 Statistiques

- Moyenne de température
- Température minimale
- Température maximale
- Historique sur 30 points

## 🎨 Interface Web

- Design moderne avec animations
- Graphique interactif
- Affichage responsive
- Thème sombre/clair
- Animations fluides

## 👥 Équipe

- Erwann
- Johann
- Othmane
- El-Tahar

## 📝 Licence

Ce projet est sous licence MIT. Voir le fichier `LICENSE` pour plus de détails.

## 🤝 Contribution

Les contributions sont les bienvenues ! N'hésitez pas à :
1. Fork le projet
2. Créer une branche (`git checkout -b feature/AmazingFeature`)
3. Commit vos changements (`git commit -m 'Add some AmazingFeature'`)
4. Push vers la branche (`git push origin feature/AmazingFeature`)
5. Ouvrir une Pull Request

## 📧 Contact

Pour toute question ou suggestion, n'hésitez pas à ouvrir une issue sur GitHub.
