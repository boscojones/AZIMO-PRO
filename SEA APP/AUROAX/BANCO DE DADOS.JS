const sqlite3 = require('sqlite3').verbose();

function createDatabase() {
    const db = new sqlite3.Database('users.db');

    db.serialize(() => {
        // Create users table
        db.run(`CREATE TABLE IF NOT EXISTS users (
            id TEXT PRIMARY KEY,
            isSubscriber INTEGER
        )`);

        // Insert example user
        const stmt = db.prepare("INSERT INTO users (id, isSubscriber) VALUES (?, ?)");
        stmt.run('user123', 1); // Example subscriber
        stmt.run('user456', 0); // Example non-subscriber
        stmt.finalize();
    });

    db.close();
}

createDatabase();
