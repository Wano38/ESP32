#include <Arduino.h>

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
<head>
  <meta charset="UTF-8">
  <title>ESP32 Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link href="https://fonts.googleapis.com/css2?family=Poppins:wght@300;400;600;700&display=swap" rel="stylesheet">
  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0/css/all.min.css">
  <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
  <style>
    :root {
      --primary-color: #2196F3;
      --primary-dark: #1976D2;
      --warning-color: #ff4444;
      --warning-dark: #ff0000;
      --success-color: #4CAF50;
      --background-color: #f0f2f5;
      --card-shadow: 0 8px 32px rgba(0, 0, 0, 0.1);
      --text-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
    }

    * {
      margin: 0;
      padding: 0;
      box-sizing: border-box;
    }

    body { 
      font-family: 'Poppins', sans-serif;
      background: linear-gradient(135deg, #f5f7fa 0%, #c3cfe2 100%);
      min-height: 100vh;
      display: flex;
      align-items: center;
      justify-content: center;
      padding: 20px;
    }

    .container {
      width: 100%;
      max-width: 1200px;
      background: rgba(255, 255, 255, 0.95);
      backdrop-filter: blur(10px);
      border-radius: 30px;
      box-shadow: var(--card-shadow);
      overflow: hidden;
      animation: fadeIn 0.8s ease-out;
      border: 1px solid rgba(255, 255, 255, 0.2);
    }

    .header {
      background: linear-gradient(135deg, var(--primary-color), var(--primary-dark));
      color: white;
      padding: 30px;
      text-align: center;
      position: relative;
      overflow: hidden;
    }

    .header::before {
      content: '';
      position: absolute;
      top: 0;
      left: 0;
      right: 0;
      bottom: 0;
      background: linear-gradient(45deg, transparent, rgba(255,255,255,0.1), transparent);
      animation: shine 3s infinite;
    }

    .logo-container {
      display: flex;
      justify-content: center;
      align-items: center;
      gap: 20px;
      margin-bottom: 20px;
    }

    .logo {
      width: 60px;
      height: 60px;
      background: rgba(255, 255, 255, 0.2);
      border-radius: 50%;
      display: flex;
      align-items: center;
      justify-content: center;
      animation: float 3s ease-in-out infinite;
    }

    .logo i {
      font-size: 2em;
      color: white;
    }

    .header h1 {
      font-size: 2.5em;
      margin-bottom: 15px;
      font-weight: 700;
      text-shadow: var(--text-shadow);
      position: relative;
    }

    .header p {
      font-size: 1.1em;
      opacity: 0.9;
      margin-bottom: 10px;
    }

    .dashboard {
      display: grid;
      grid-template-columns: 1fr 1fr;
      gap: 20px;
      padding: 30px;
    }

    .sensor-data {
      background: rgba(255, 255, 255, 0.9);
      border-radius: 20px;
      padding: 30px;
      box-shadow: var(--card-shadow);
      transition: all 0.3s ease;
      position: relative;
      overflow: hidden;
      border: 1px solid rgba(255, 255, 255, 0.3);
    }

    .temperature-card {
      text-align: center;
      margin-bottom: 20px;
    }

    .temperature-card::before {
      content: '';
      position: absolute;
      top: 0;
      left: 0;
      width: 100%;
      height: 100%;
      background: linear-gradient(45deg, transparent, rgba(255,255,255,0.1), transparent);
      transform: translateX(-100%);
      transition: 0.6s;
    }

    .temperature-card:hover::before {
      transform: translateX(100%);
    }

    .temperature-value {
      font-size: 3.5em;
      font-weight: 700;
      color: var(--primary-color);
      margin: 15px 0;
      text-shadow: var(--text-shadow);
      background: linear-gradient(135deg, var(--primary-color), var(--primary-dark));
      -webkit-background-clip: text;
      -webkit-text-fill-color: transparent;
    }

    .chart-container {
      position: relative;
      height: 300px;
      width: 100%;
    }

    .warning {
      display: none;
      background: linear-gradient(135deg, var(--warning-color), var(--warning-dark));
      color: white;
      padding: 20px;
      margin: 20px;
      border-radius: 15px;
      animation: pulse 1.5s infinite;
      text-align: center;
      box-shadow: 0 10px 30px rgba(255, 68, 68, 0.3);
      position: relative;
      overflow: hidden;
    }

    .warning::before {
      content: '';
      position: absolute;
      top: 0;
      left: 0;
      width: 100%;
      height: 100%;
      background: linear-gradient(45deg, transparent, rgba(255,255,255,0.2), transparent);
      animation: shine 2s infinite;
    }

    .warning i {
      font-size: 2.5em;
      margin-bottom: 10px;
      animation: shake 0.5s infinite;
    }

    .warning h2 {
      font-size: 1.5em;
      margin-bottom: 10px;
      text-shadow: 0 2px 4px rgba(0, 0, 0, 0.2);
    }

    .footer {
      text-align: center;
      padding: 30px;
      color: #666;
      font-size: 0.9em;
      background: rgba(255, 255, 255, 0.5);
      backdrop-filter: blur(5px);
      position: relative;
    }

    .footer::before {
      content: '';
      position: absolute;
      top: 0;
      left: 0;
      right: 0;
      height: 1px;
      background: linear-gradient(90deg, transparent, rgba(0,0,0,0.1), transparent);
    }

    .copyright {
      margin-top: 15px;
      font-size: 0.9em;
      color: #666;
    }

    .team-names {
      display: flex;
      justify-content: center;
      gap: 15px;
      margin-top: 10px;
      flex-wrap: wrap;
    }

    .team-member {
      background: rgba(255, 255, 255, 0.8);
      padding: 5px 15px;
      border-radius: 20px;
      font-weight: 600;
      color: var(--primary-color);
      box-shadow: 0 2px 5px rgba(0,0,0,0.1);
      transition: transform 0.3s ease;
    }

    .team-member:hover {
      transform: translateY(-2px);
    }

    .temperature-label {
      font-size: 1.2em;
      color: #666;
      margin-bottom: 10px;
      font-weight: 600;
    }

    .last-update {
      font-size: 0.8em;
      color: #999;
      margin-top: 10px;
      font-style: italic;
    }

    .stats-table {
      width: 100%;
      margin-top: 20px;
      border-collapse: collapse;
      background: rgba(255, 255, 255, 0.9);
      border-radius: 15px;
      overflow: hidden;
      box-shadow: var(--card-shadow);
    }

    .stats-table th, .stats-table td {
      padding: 15px;
      text-align: center;
      border-bottom: 1px solid rgba(0, 0, 0, 0.1);
    }

    .stats-table th {
      background: linear-gradient(135deg, var(--primary-color), var(--primary-dark));
      color: white;
      font-weight: 600;
    }

    .stats-table tr:last-child td {
      border-bottom: none;
    }

    .stats-value {
      font-size: 1.2em;
      font-weight: 600;
      color: var(--primary-color);
    }

    .stats-label {
      color: #666;
      font-size: 0.9em;
    }

    .stats-icon {
      margin-right: 8px;
      color: var(--primary-color);
    }

    @media (max-width: 768px) {
      .container {
        margin: 10px;
        border-radius: 20px;
      }

      .dashboard {
        grid-template-columns: 1fr;
        padding: 15px;
        gap: 15px;
      }

      .header {
        padding: 20px;
      }

      .header h1 {
        font-size: 1.8em;
      }

      .header p {
        font-size: 1em;
      }

      .logo-container {
        gap: 10px;
      }

      .logo {
        width: 50px;
        height: 50px;
      }

      .team-names {
        gap: 10px;
      }

      .team-member {
        padding: 4px 12px;
        font-size: 0.8em;
      }

      .temperature-value {
        font-size: 2.5em;
      }

      .chart-container {
        height: 250px;
      }

      .sensor-data {
        padding: 20px;
      }

      .warning {
        margin: 15px;
        padding: 15px;
      }

      .warning h2 {
        font-size: 1.2em;
      }

      .stats-table th, .stats-table td {
        padding: 10px;
        font-size: 0.9em;
      }

      .stats-value {
        font-size: 1.1em;
      }
    }

    @keyframes fadeIn {
      from { 
        opacity: 0; 
        transform: translateY(30px) scale(0.95);
      }
      to { 
        opacity: 1; 
        transform: translateY(0) scale(1);
      }
    }

    @keyframes float {
      0% { transform: translateY(0px) rotate(0deg); }
      50% { transform: translateY(-10px) rotate(5deg); }
      100% { transform: translateY(0px) rotate(0deg); }
    }

    @keyframes pulse {
      0% { transform: scale(1); box-shadow: 0 0 0 0 rgba(255, 68, 68, 0.7); }
      70% { transform: scale(1.05); box-shadow: 0 0 0 15px rgba(255, 68, 68, 0); }
      100% { transform: scale(1); box-shadow: 0 0 0 0 rgba(255, 68, 68, 0); }
    }

    @keyframes shine {
      0% { transform: translateX(-100%); }
      100% { transform: translateX(100%); }
    }

    @keyframes shake {
      0%, 100% { transform: rotate(0deg); }
      25% { transform: rotate(-5deg); }
      75% { transform: rotate(5deg); }
    }
  </style>
  <script>
    let isAlarmActive = false;
    let lastUpdate = new Date();
    let temperatureHistory = [];
    const maxHistoryPoints = 30;
    let minTemp = Infinity;
    let maxTemp = -Infinity;
    let totalTemp = 0;
    let count = 0;
    
    // Configuration du graphique
    const ctx = document.createElement('canvas');
    ctx.id = 'temperatureChart';
    const chart = new Chart(ctx, {
      type: 'line',
      data: {
        labels: [],
        datasets: [{
          label: 'Température (°C)',
          data: [],
          borderColor: '#2196F3',
          backgroundColor: 'rgba(33, 150, 243, 0.1)',
          borderWidth: 2,
          tension: 0.4,
          fill: true
        }]
      },
      options: {
        responsive: true,
        maintainAspectRatio: false,
        scales: {
          y: {
            beginAtZero: false,
            grid: {
              color: 'rgba(0, 0, 0, 0.1)'
            }
          },
          x: {
            grid: {
              display: false
            }
          }
        },
        plugins: {
          legend: {
            display: false
          }
        }
      }
    });
    
    function calculateStats(temp) {
      // Mise à jour des statistiques
      minTemp = Math.min(minTemp, temp);
      maxTemp = Math.max(maxTemp, temp);
      totalTemp += temp;
      count++;
      
      // Mise à jour de l'affichage
      document.getElementById('avgTemp').textContent = (totalTemp / count).toFixed(1) + '°C';
      document.getElementById('minTemp').textContent = minTemp.toFixed(1) + '°C';
      document.getElementById('maxTemp').textContent = maxTemp.toFixed(1) + '°C';
    }
    
    function updateData() {
      fetch('/temperature')
        .then(response => response.text())
        .then(data => {
          const temp = parseFloat(data);
          const now = new Date();
          
          // Mise à jour de la température
          document.getElementById('temperature').innerHTML = data + '°C';
          document.getElementById('lastUpdate').textContent = 
            'Dernière mise à jour: ' + now.toLocaleTimeString();
          
          // Mise à jour du graphique
          temperatureHistory.push(temp);
          if (temperatureHistory.length > maxHistoryPoints) {
            temperatureHistory.shift();
          }
          
          chart.data.datasets[0].data = temperatureHistory;
          chart.data.labels = Array.from({length: temperatureHistory.length}, (_, i) => '');
          chart.update();
          
          // Calcul des statistiques
          calculateStats(temp);
          
          // Gestion des alertes
          if (temp > 28.5) {
            if (!isAlarmActive) {
              document.getElementById('warning').style.display = 'block';
              isAlarmActive = true;
            }
          } else {
            if (isAlarmActive) {
              document.getElementById('warning').style.display = 'none';
              isAlarmActive = false;
            }
          }
        });

      setTimeout(updateData, 1000);
    }
    
    window.onload = function() {
      document.querySelector('.chart-container').appendChild(ctx);
      updateData();
    };
  </script>
</head>
<body>
  <div class="container">
    <div class="header">
      <div class="logo-container">
        <div class="logo">
          <i class="fas fa-microchip"></i>
        </div>
        <div class="logo">
          <i class="fas fa-temperature-high"></i>
        </div>
        <div class="logo">
          <i class="fas fa-wifi"></i>
        </div>
      </div>
      <h1>ESP32 Temperature Monitor</h1>
      <p>Surveillance de température en temps réel</p>
    </div>
    
    <div class="dashboard">
      <div class="sensor-data">
        <div class="temperature-card">
          <div class="temperature-label">
            <i class="fas fa-temperature-high"></i> Température actuelle
          </div>
          <div class="temperature-value" id="temperature">--</div>
          <div class="last-update" id="lastUpdate">Mise à jour en cours...</div>
        </div>

        <table class="stats-table">
          <tr>
            <th colspan="2">Statistiques de température</th>
          </tr>
          <tr>
            <td>
              <i class="fas fa-calculator stats-icon"></i>
              <span class="stats-label">Moyenne</span>
            </td>
            <td class="stats-value" id="avgTemp">--</td>
          </tr>
          <tr>
            <td>
              <i class="fas fa-arrow-down stats-icon"></i>
              <span class="stats-label">Minimum</span>
            </td>
            <td class="stats-value" id="minTemp">--</td>
          </tr>
          <tr>
            <td>
              <i class="fas fa-arrow-up stats-icon"></i>
              <span class="stats-label">Maximum</span>
            </td>
            <td class="stats-value" id="maxTemp">--</td>
          </tr>
        </table>
      </div>

      <div class="sensor-data">
        <div class="chart-container"></div>
      </div>
    </div>

    <div id="warning" class="warning">
      <i class="fas fa-exclamation-triangle"></i>
      <h2>ALERTE TEMPÉRATURE ÉLEVÉE</h2>
      <p>La température a dépassé le seuil critique</p>
    </div>

    <div class="footer">
      <p>ESP32 Web Server © 2024</p>
      <div class="team-names">
        <span class="team-member">Erwan</span>
        <span class="team-member">Johan</span>
        <span class="team-member">Othmane</span>
        <span class="team-member">El-Tahar</span>
      </div>
      <div class="copyright">
        Projet développé par l'équipe de surveillance de température
      </div>
    </div>
  </div>
</body>
</html>
)rawliteral";