document.getElementById('connectButton').addEventListener('click', async () => {
    document.getElementById('status').innerText = 'Connecting...';
    // Simulate connection to Tesla 5001
    await new Promise(resolve => setTimeout(resolve, 2000)); // Simulated delay
    document.getElementById('status').innerText = 'Connected to Tesla 5001!';
});
