const express = require('express');
const os = require('os');
const http = require('http');

const app = express();
const port = 5000;

// Endpoint to get the CPU usage information and send it to the host server
app.get('/cpu-status', (req, res) => {
  const cpuUsage = os.loadavg(); // Returns an array with the 1, 5, and 15 minute load averages
  const message = JSON.stringify({
    cpuUsage: cpuUsage
  });

  const options = {
    hostname: '192.168.14.40',
    port: 5000,
    path: '/cpu-status',
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
      'Content-Length': message.length
    }
  };

  const request = http.request(options, (response) => {
    console.log(`Response: ${response.statusCode} ${response.statusMessage}`);
  });

  request.on('error', (error) => {
    console.error(`Error: ${error}`);
  });

  request.write(message);
  request.end();
});

// Send CPU usage information every 5 seconds
setInterval(() => {
  http.get('http://localhost:5000/cpu-status');
}, 5000);

app.listen(port, () => {
  console.log(`Node.js server running on port ${port}`);
});
